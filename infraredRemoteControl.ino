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
//SMOKO Extra Lamp Colors
#define COLOR_LIGHT_RED 0xFFB04F
#define COLOR_LIGHT_GREEN 0xFF30CF
#define COLOR_PURPLE 0xFF708F
#define COLOR_ORANGE 0xFFA857
#define COLOR_TURQ 0xFF28D7
#define COLOR_DARK_BLUE 0xFF6897
#define COLOR_LIGHT_ORANGE 0xFF9867
#define COLOR_LIGHT_TURQ 0xFF18E7
#define COLOR_DARKER_BLUE 0xFF58A7
#define COLOR_YELLOW 0xFF8877
#define COLOR_LIGHT_BLUE 0xFF08F7
#define COLOR_PINK 0xFF48B7
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
  //Uncomment below to receive data from infrared remote.
  //  if (receiver.GetResults(&decoder)) {
  //    Serial.print("here");
  //    decoder.decode();    //Decode the data
  //    decoder.DumpResults(); //output to serial monitor
  //    receiver.resume();     //Restart the receiver
  //  }
  char input = Serial.read();
  switch (input) {
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
    case 'F':
    case 'f':
      sender.send(NEC, BUTTON_FLASH, 20);
      Serial.println("Command Executed: FLASH");
      break;
    case 'T':
    case 't':
      sender.send(NEC, BUTTON_STROBE, 20);
      Serial.println("Command Executed: STROBE");
      break;
    case 'A':
    case 'a':
      sender.send(NEC, BUTTON_FADE, 20);
      Serial.println("Command Executed: FADE");
      break;
    case 'S':
    case 's':
      sender.send(NEC, BUTTON_SMOOTH, 20);
      Serial.println("Command Executed: SMOOTH");
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
      Serial.println("\t   F \t  Transition: Flash");
      Serial.println("\t   T \t  Transition: Strobe");
      Serial.println("\t   A \t  Transition: Fade");
      Serial.println("\t   S \t  Transition: Smooth");
      Serial.println("\t   R \t  Color: Red");
      Serial.println("\t   G \t  Color: GREEN");
      Serial.println("\t   B \t  Color: BLUE");
      Serial.println("\t   W \t  Color: WHITE");
      Serial.println("\t-----------------------");
      break;
  }
}

