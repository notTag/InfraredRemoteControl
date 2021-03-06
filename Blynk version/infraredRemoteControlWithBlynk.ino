#include <IRLib.h>

//SMOKO Lamp Tools
#define BRIGHT_UP 0xFFA05F
#define BRIGHT_DOWN 0xFF20DF
#define BUTTON_ON 0xFFE01F
#define BUTTON_OFF 0xFF609F
//SMOKO Lamp Built in Light functions
#define BUTTON_FLASH 0xFFF00F
#define BUTTON_STROBE 0xFFE817
#define BUTTON_FADE 0xFFD827
#define BUTTON_SMOOTH 0xFFC837
//SMOKO Main Lamp Colors
#define COLOR_RED 0xFF906F
#define COLOR_GREEN 0xFF10EF
#define COLOR_BLUE 0xFF50AF
#define COLOR_WHITE 0xFFD02F
#define COLOR_PURPLE 0xFF708F
//SMOKO Extra Lamp Colors
//#define COLOR_LIGHT_RED 0xFFB04F
//#define COLOR_LIGHT_GREEN 0xFF30CF
#define COLOR_ORANGE 0xFFA857
//#define COLOR_TURQ 0xFF28D7
//#define COLOR_DARK_BLUE 0xFF6897
//#define COLOR_LIGHT_ORANGE 0xFF9867
//#define COLOR_LIGHT_TURQ 0xFF18E7
//#define COLOR_DARKER_BLUE 0xFF58A7
//#define COLOR_YELLOW 0xFF8877
//#define COLOR_LIGHT_BLUE 0xFF08F7
//#define COLOR_PINK 0xFF48B7

#include <BlynkApiArduino.h>
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(8,9); //Rx, Tx

#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleStream.h>

char auth[] = "bca7f3c4eee44a06a581b871db6f29cc";

IRrecv receiver(11);
IRsend sender;
IRdecode decoder;

void setup() {
  DebugSerial.begin(9600);
  Serial.begin(9600);
  Blynk.begin(auth, Serial);
  receiver.enableIRIn(); // Start receiver
  Serial.println(F("SMOKO Unicorn Controller. Type 'H' for help.\n"));
}

void loop() {
    Blynk.run();
}  

BLYNK_WRITE(V0) {
  char input = Serial.read();
  switch (input) {
    case '1':
      sender.send(NEC, BUTTON_ON, 20);
      Serial.println(F("Command Executed: Power ON"));
      break;
    case '0':
      sender.send(NEC, BUTTON_OFF, 20);
      Serial.println(F("Command Executed: Power OFF"));
      getIRValues();
      break;
    case '+':
      sender.send(NEC, BRIGHT_UP, 20);
      Serial.println(F("Command Executed: Brightness Up"));
      break;
    case '-':
      sender.send(NEC, BRIGHT_DOWN, 20);
      Serial.println(F("Command Executed: Brightness Down"));
      break;
    case 'R':
    case 'r':
      sender.send(NEC, COLOR_RED, 20);
      Serial.println(F("Command Executed: Lamp Color: RED"));
      break;
    case 'G':
    case 'g':
      sender.send(NEC, COLOR_GREEN, 20);
      Serial.println(F("Command Executed: Lamp Color: GREEN"));
      break;
    case 'B':
    case 'b':
      sender.send(NEC, COLOR_BLUE, 20);
      Serial.println(F("Command Executed: Lamp Color: BLUE"));
      break;
    case 'W':
    case 'w':
      sender.send(NEC, COLOR_WHITE, 20);
      Serial.println(F("Command Executed: Lamp Color: WHITE"));
      break;
    case 'P':
    case 'p':
      sender.send(NEC, COLOR_PURPLE, 20);
      Serial.println(F("Command Executed: Lamp Color: PURPLE"));
      break;
    case 'O':
    case 'o':
      sender.send(NEC, COLOR_ORANGE, 20);
      Serial.println(F("Command Executed: Lamp Color: ORANGE"));
      break;
    case 'F':
    case 'f':
      sender.send(NEC, BUTTON_FLASH, 20);
      Serial.println(F("Command Executed: FLASH"));
      break;
    case 'T':
    case 't':
      sender.send(NEC, BUTTON_STROBE, 20);
      Serial.println(F("Command Executed: STROBE"));
      break;
    case 'A':
    case 'a':
      sender.send(NEC, BUTTON_FADE, 20);
      Serial.println(F("Command Executed: FADE"));
      break;
    case 'S':
    case 's':
      sender.send(NEC, BUTTON_SMOOTH, 20);
      Serial.println(F("Command Executed: SMOOTH"));
      break;
    case 'H':
    case 'h':
      Serial.println(F("Command Executed: Help Menu"));
      Serial.println(F("------------------------------"));
      Serial.println(F("Command\t  Description"));
      Serial.println(F("   1 \t  Turn lamp On"));
      Serial.println(F("   0 \t  Turn lamp Off"));
      Serial.println(F("   + \t  Brightness Up"));
      Serial.println(F("   - \t  Brightness Down"));
      Serial.println(F("   R \t  Color: Red"));
      Serial.println(F("   G \t  Color: GREEN"));
      Serial.println(F("   B \t  Color: BLUE"));
      Serial.println(F("   W \t  Color: WHITE"));
      Serial.println(F("   P \t  Color: PURPLE"));
      Serial.println(F("   O \t  Color: Orange"));
      Serial.println(F("   F \t  Transition: Flash"));
      Serial.println(F("   T \t  Transition: Strobe"));
      Serial.println(F("   A \t  Transition: Fade"));
      Serial.println(F("   S \t  Transition: Smooth"));
      Serial.println(F("NOTE: To record a value send the off command (0) and then begin testing with an IR Remote."));
      Serial.println(F("-----------------------------"));
      break;
    default:
      receiver.No_Output(); //ensures that output pin is set to low (recommended by documentation for safety to the circuit)
      break;
  }
}

void getIRValues(){
  Serial.println(F("\nEntering receive mode."));
  Serial.println(F("Awaiting input from IR Remote."));
  
  receiver.No_Output();
  boolean decoderValue = true; //on button has been pressed
  int input = 0;
  receiver.enableIRIn(); // Re-enable receiver
  while(decoderValue && input != 48){
    input = Serial.read();
    if (receiver.GetResults(&decoder)) {
      decoder.decode();      //Decode the data
      decoder.DumpResults(); //output to serial monitor
      Serial.print(F("Value read: "));
      if(decoder.value == BUTTON_OFF){
          decoderValue = false;
      }
      receiver.resume();     //Restart the receiver
      Serial.println(F("Exit: Press off button on remote or enter 0\n"));
    }
  }
  Serial.println(F("\nExiting receive mode.\n\n"));
}

