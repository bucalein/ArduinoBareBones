/*
 * Small sketch for writing "Hello world!" onto the LCD,
 * without using any LCD library
 */

#define FUNCTION_SET_1    0b00111000  // 8bit; 2 line ; 5x8 char
#define DISPLAY_SET_1     0b00001110  // display and cursor ON
#define ENTRY_MODE_SET_1  0b00000110  // increment to the right; shift to the right; display not shifted


//lcd_data_bus[0] = D0, [1] = D1, ...
int lcd_data_bus[ ] = { 9, 8, 7, 6, 5, 4, 3, 2, 1};
int rs = 13;
int rw = 12;
int e = 11;


const char *str = "Hello world!";

// at i == 0 we get the less significant bit
void write_to_lcd_data_bus(uint8_t val){
  
  for(int i = 0; i < 8; ++i) {
    int val_bit = (val & (1 << i)) >> i;
    digitalWrite(lcd_data_bus[i], val_bit == 1 ? HIGH : LOW);
  }
}


void enable_lcd( ){
  
  digitalWrite(e, HIGH);
  delay(100);
  digitalWrite(e, LOW);
  delay(200);
  
}


void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 8; i++)
    pinMode(lcd_data_bus[i], OUTPUT);

  pinMode(rs, OUTPUT);
  pinMode(rw, OUTPUT);
  pinMode(e, OUTPUT);

  //SET FUNCTION; 8-bit operation; 2 line display; 5x8 char
  digitalWrite(rs, LOW);
  digitalWrite(rw, LOW);

  write_to_lcd_data_bus(FUNCTION_SET_1);
  enable_lcd( );


  //DISPLAY SET; display and cursor ON; 
  write_to_lcd_data_bus(DISPLAY_SET_1);
  enable_lcd( );
  
  // ENTRY MODE SET; increment by one; shift to the right; display not shifted
  write_to_lcd_data_bus(ENTRY_MODE_SET_1);
  enable_lcd( );

  // WRITE CHARACTER;
  digitalWrite(rs, HIGH);


  // start to write the characters
  for(int i = 0; i < strlen(str); ++i){ 
    write_to_lcd_data_bus(str[i]);
    enable_lcd( );
  }
}

void loop() {

}
