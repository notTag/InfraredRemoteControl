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
//unsigned long output;

IRrecv receiver(11);
IRsend sender;
IRdecode decoder;
 
void setup() {
  Serial.begin(9600);
  receiver.enableIRIn(); // Start receiver
  Serial.println("SMOKO Unicorn Controller. Type 'H' for help.\n");
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
      sender.send(NEC, BUTTON_ON, 20);
      Serial.println("Command Executed: Power ON");
      break;
    case '0':
      sender.send(NEC, BUTTON_OFF, 20);
      Serial.println("Command Executed: Power OFF");
      break;
    case '+':
      sender.send(NEC, BRIGHT_UP, 20);
      Serial.println("Command Executed: Brightness Up");
      break;
    case '-':
      sender.send(NEC, BRIGHT_DOWN, 20);
      Serial.println("Command Executed: Brightness Down");
      break;
    case 'R':
    case 'r':
      sender.send(NEC, COLOR_RED, 20);
      Serial.println("Command Executed: Lamp Color: RED");
      break;
    case 'G':
    case 'g':
      sender.send(NEC, COLOR_GREEN, 20);
      Serial.println("Command Executed: Lamp Color: GREEN");
      break;
    case 'B':
    case 'b':
      sender.send(NEC, COLOR_BLUE, 20);
      Serial.println("Command Executed: Lamp Color: BLUE");
      break;
    case 'W':
    case 'w':
      sender.send(NEC, COLOR_WHITE, 20);
      Serial.println("Command Executed: Lamp Color: WHITE");
      break;
     case 'H':
     case 'h':
     Serial.println("Command Executed: Help Menu");
      Serial.println("\tCommand\t  Description");
      Serial.println("\t-----------------------");
      Serial.println("\t   1 \t  Turn lamp On");
      Serial.println("\t   0 \t  Turn lamp Off");
      Serial.println("\t   + \t  Brightness Up");
      Serial.println("\t   - \t  Brightness Down");
      Serial.println("\t   R \t  Color: Red");
      Serial.println("\t   G \t  Color: GREEN");
      Serial.println("\t   B \t  Color: BLUE");
      Serial.println("\t   W \t  Color: WHITE");
      Serial.println("\t-----------------------");
      break;
  }
}

