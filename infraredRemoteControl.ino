#include <IRLib.h>

//SMOKO Lamp Tools
#define BRIGHT_UP 0xFFA05F
#define BRIGHT_DOWN 0xFF20DF
#define BUTTON_ON 0xFFE01F
#define BUTTON_OFF 0xFF609F
//SMOKO Lamp Built in Light functions
#define BUTTON_FLASH 0xFFF00Få
#define BUTTON_STROBE 0xFFE817
#define BUTTON_FADE 0xFFD827
#define BUTTON_SMOOTH 0xFFC837
//SMOKO Lamp Colors
#define COLOR_RED 0xFF906F
#define COLOR_GREEN 0xFF10EF
#define COLOR_BLUE 0xFF50AF
#define COLOR_WHITE 0xFFD02F
unsigned long output;

IRrecv receiver(11);
IRsend sender;
IRdecode decoder;
 
void setup() {
  Serial.begin(9600);
  receiver.enableIRIn(); // Start receiver
}
 
void loop() {
//    receiver.enableIRIn(); // restart receiver
//  if (receiver.GetResults(&decoder)) {
//    decoder.decode();    //Decode the data
//    decoder.DumpResults(); //output to serial monitor
//    receiver.resume();     //Restart the receiver
//  }
  char input = Serial.read();
  switch(input){
    case '1':
      output = BUTTON_ON;
      Serial.println("Power ON");
      break;
    case '0':
      output = BUTTON_OFF;
      Serial.println("Power OFF");
      break;
    case '>':
      output = BRIGHT_UP;
      Serial.println("Brightness Up");
      break;
    case '<':
      output = BRIGHT_DOWN;
      Serial.println("Brightness Down");
      break;
    case 'r':
      output = COLOR_RED;
      Serial.println("Lamp Color: RED");
      break;
    case 'b':
      output = COLOR_BLUE;
      Serial.println("Lamp Color: BLUE");
      break;
    case 'g':
      output = COLOR_GREEN;
      Serial.println("Lamp Color: GREEN");
      break;
    case 'w':
      output = COLOR_WHITE;
      Serial.println("Lamp Color: WHITE");
      break;
  }
  sender.send(NEC, output, 20);
}

