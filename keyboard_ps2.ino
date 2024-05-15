#define PS2_BITS_PER_FRAME 11

/*
 * Display the keyboard bits (automatically SET 2 for my device) on the LEDs:
 * 1 - START BIT: always OFF
 * 2 - less significant bit first
 * 3 - PARITY BIT: it's on when there is an even number of bits
 * 4 - STOP BIT: always ON
 */

int data_pin  = 0;
int clock_pin = 2;  // used for triggering the interrupt

int output_leds[ ] = { 
  3, // led start bit
  4, // led first less significant bit
  
  5, 6, 7, 8, 9, 10, 11,
  
  12, // led parity bit
  13  // led stop bit
};


// interrupt routine to get the data from the keyboard
// on the clock falling edge
void ps2_interrupt( ){
  static int bit_count = 0;
  
  unsigned int val = digitalRead(data_pin);
  
  digitalWrite(output_leds[bit_count], val > 0 ? HIGH: LOW);
  bit_count++;

  if(bit_count == PS2_BITS_PER_FRAME){
    bit_count = 0;
  }
  
}


void setup() {
  pinMode(data_pin, INPUT_PULLUP);
  pinMode(clock_pin, INPUT_PULLUP);

  for(int i = 0; i < PS2_BITS_PER_FRAME; ++i){
    pinMode(output_leds[i], OUTPUT);
  }
  
  attachInterrupt(digitalPinToInterrupt(2), ps2_interrupt, FALLING);
  
}

void loop() {
  
}
