/**
   Basic 2114 Static RAM tester

   The 2114 is a 4096 bit static ram chip organised as 1024 4 bit values

   This type of RAM is used on the ZX81.
*/

/*
   Some standard timings for 2144 Static RAM chips
   ------------------------------------------------
   Minimum write pulse time = 150ns
   Data setup time = 150ns
   Write cycle time = 300ns

   PIN definitions

   Port Arduino   2114
   -------------------
   PC0  A0        IO1
   PC1  A1        IO2
   PC2  A2        IO3
   PC3  A3        IO4

   LEDs
   -------------------
   PC4  A4        Green LED
   PC5  A5        Red LED

   Special
   -------------------
   PD0  0         Serial (Debug) - leave empty for USB
   PD1  1         Serial (Debug) - leave empty for USB
   PD2  2         /CS (Chip Select)
   PD3  3         /WE (Write Enabled)

   Address lines
   -------------------
   PD4  4         A0
   PD5  5         A1
   PD6  6         A2
   PD7  7         A3
   PB0  8         A4
   PB1  9         A5
   PB2  10        A6
   PB3  11        A7
   PB4  12        A8
   PB5  13        A9
*/
// Constants
#define MAX_ADDRESS 1024
#define MAX_VALUE 16
#define NUM_BITS 4


// LED pins
#define GREEN_LED  (1<<4)
#define RED_LED    (1<<5)

// The serial pins are PD0 and PD1
#define SERIAL_PINS 0b00000011

// RAM pins
#define RAM_CS     0b00000100  // Active Low
#define RAM_WE     0b00001000  // Active Low

// Helper Macros for the LEDS
#define green_led_on()  PORTC |= GREEN_LED
#define green_led_off() PORTC &= ~GREEN_LED
#define red_led_on()    PORTC |= RED_LED
#define red_led_off()   PORTC &= ~RED_LED

// NB: CS and WE are active low so ON==0 and OFF==1
// We don't want to mess with the serial pins on PD0 and PD1 so mask them off
#define enable_cs()     PORTD &= (~RAM_CS)
#define disable_cs()    PORTD |= (RAM_CS | SERIAL_PINS)

#define enable_we()     PORTD &= (~RAM_WE)
#define disable_we()    PORTD |= (RAM_WE | SERIAL_PINS)

#define disable_ram()  PORTD |= (RAM_WE | RAM_CS | SERIAL_PINS)


#define data_in()       DDRC = 0b00110000;        // 0011 0000 - 4 bits input and 2 bits output
#define data_out()      DDRC = 0b00111111;        // 0011 1111 - 4 bits output and 2 bits output


/**
   Global variables
*/
boolean test_state = false;

/**
   Setup the direction of the pins
   Disable CS and WE ready to start running tests
*/
void setup() {
  // Setup the serial debug
  Serial.begin(115200);

  // IO pins*4 (IN) and LED pins*2 (OUT)
  DDRC = 0b00110000;       // 0011 0000 - 4 bits input and 2 bits output
  // All output but leave serial lines alone (PD0 and PD1)
  DDRD |=  0b11111100;     // 1111 1100
  // A4-9 outputs
  DDRB = 0b00111111;       // 0011 1111

  // Set the initial state of the Chip select and write enabled to OFF
  disable_cs();
  disable_we();

  Serial.println("Starting tests");
  test_state = true;
  
  green_led_on();
  red_led_off();
}

/**
   Run the main test loop
*/
void loop() {
  // Run the tests until one fails
  if ( test_state ) {

    Serial.println("Performing test loop");
    if (!test_sequence() ) {
      Serial.println("Sequence test failed");
      test_state = false;
    }
    else if (!test_sequence2() ) {
      Serial.println("Sequence2 test failed");
      test_state = false;
    }
    else if (!test_sliding_bit() ) {
      Serial.println("Sliding bit test failed");
      test_state = false;
    }
    else if (!test_checker_board() ) {
      Serial.println("Checker board test failed");
      test_state = false;
    }
  } else {
    green_led_off();
    red_led_on();
  }
}

/*********************************************************
   Tests to execute
 *********************************************************/

/*
   Write an incrementing value to each consecutive memory location
   and read it back immediately
*/
boolean test_sequence() {
  byte test_data = 0;
  for (word address = 0; address < MAX_ADDRESS ; address++) {
    test_data = address % MAX_VALUE;
    if (!test_write_read( address, test_data)) {
      return false;
    }
  }
  return true;
}

/**
   Write a to each memory location then read them all back
*/
boolean test_sequence2() {
  byte test_data = 0;
  for (word address = 0; address < MAX_ADDRESS ; address++) {
    test_data = address % MAX_VALUE;
    write_data_to_address(address, test_data);
  }

  set_data(0);

  for (word address = 0; address < MAX_ADDRESS ; address++) {
    test_data = address % MAX_VALUE;
    byte result = read_data_at_address(address);
    if ( result != test_data) {
      output_test_result(address, test_data, result);
      return false;
    }
  }

  return true;
}

/*
   Slide a bit through each position for each location
*/
boolean test_sliding_bit() {
  for (word address = 0; address < MAX_ADDRESS; address++ ) {
    for (int x = 0; x <= NUM_BITS; x++) {
      byte data = (1 << x) & 0b00001111;
      if ( !test_write_read( address , data)) {
        return false;
      }
    }
  }

  return true;
}

boolean test_checker_board() {
  byte pattern = 0b00000101;
  for (word address = 0; address < MAX_ADDRESS; address++ ) {
    if (!test_write_read(address, pattern)) {
      return false;
    }
    pattern = ~pattern & 0b00001111;
  }

  pattern = 0b00000101;
  for (word address = 0; address < MAX_ADDRESS; address++ ) {
    byte result = read_data_at_address( address );
    if ( pattern != result ) {
      output_test_result( address, pattern , result );
      return false;
    }
    pattern = ~pattern & 0b00001111;
  }
  return true;
}

/*****************************************************
   Utility test routines
 *****************************************************/
boolean test_write_read( word address, byte value ) {
  write_data_to_address( address , value );
  byte result = (byte)read_data_at_address(address);
  if ( result != value) {
    output_test_result(address , value, result);
    return false;
  }
  return true;
}

void output_test_result( word address, byte expected, byte returned) {
  Serial.print("Address (");
  Serial.print(address);
  Serial.print(") : expected (");
  Serial.print(expected, BIN);
  Serial.print(") -> Returned (");
  Serial.print(returned, BIN);
  Serial.println(")");
}


/************************************************
   Bit bashing routines to read and write data
 ************************************************/
void set_address(word address) {
  // Mask first 4 bits to avoid serial and CS/WE then
  PORTD &= 0b00001111;
  PORTD |= (byte)(0b00001111 & address) << 4;

  PORTB &= 0b11000000;
  PORTB |= (byte)(0b00111111 & (address >> 4));
}

void set_data(byte data) {
  PORTC &= 0b11110000;
  PORTC |= (data & 0b00001111);
}

byte get_data() {
  byte data = (PINC & 0b00001111);
  return data;
}

/*
   Write the data to the specified address
*/
void write_data_to_address(word address, byte data) {
  disable_ram();
  data_out();

  set_address(address);
  set_data(data);

  enable_cs();
  enable_we();

  // Wait for write = 300ns - a NOP is 62.5ns
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");

  disable_ram();
}

/*
   Read the data at the specified address
   The data will be in the low bits of the byte
*/
byte read_data_at_address(word address) {

  disable_ram();
  data_in();

  set_address(address);
  enable_cs();

  // Wait for read = 150ns - a NOP is 62.5ns assuming 16Mhz clock
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");

  byte data = get_data();
  disable_ram();

  return data;
}

/*
   Debug output routines
*/
void output_debug() {
#ifdef DEBUG

  byte port = PORTD;
  boolean chip_select = !(port & 0b00000100);
  boolean write_enabled = !(port & 0b00001000);

  Serial.print("/CS : ");
  Serial.println( chip_select ? "ON" : "OFF");
  Serial.print("/WE : ");
  Serial.println( write_enabled ? "ON" : "OFF");
#endif
}
