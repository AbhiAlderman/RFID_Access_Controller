
const int relay = 2;
String receive;
unsigned long valid[] = {
502597,
617489,
578937,
595831,
577672,
525722,
627941,
624730,
531335,
545889,
525154,
594696,
576455,
525734,
507609,
606923,
577944,
572481,
581557,
572490,
618280,
531110,
561379,
577514,
59044,
533275,
586691,
588045,
567758,
618468,
545136,
531303,
576390};
int max = sizeof(valid) / sizeof(unsigned long);


// Watch dog timer initialization
#include <avr/wdt.h>

unsigned long myTime; // Millis() function time value
unsigned long elapsedTime;
unsigned long timeExpected = 5000UL; // Is in milliseconds. So rn its every 5 seconds
const int RESET_PIN = 2; // Reset pin's connection

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

  // Watchdog setup
  myTime = millis();
  Serial.println("INIT");
  wdt_enable(WDTO_2S); //Enable wdt every two seconds
}



bool validateInput(String hex) {
  char * pEnd;
  unsigned long num = strtol (hex.substring(6, 12).c_str(), &pEnd, 16);
  Serial.println(num);
  unsigned long mask = 0b000111111111111111111110;
  num = (num & mask) >> 1;
  Serial.println(num);
  for (int i = 0; i < max; i++) {
    if (valid[i] == num) {
      Serial.println("Valid code!");
      return true;
    }
  }
  Serial.println("Not valid code");
  return false;

  
}
void loop() {
  //************RESET HANDLER********************//
  elapsedTime = millis() - myTime;
  if (elapsedTime > timeExpected) {
    Serial.print("RESET");
    while (1); //Intentionally halt the program, so the watchdog performs the reset    
  }
  
  if(Serial.available() > 0) {
    receive = Serial.readString();
    Serial.println(receive);
    if (validateInput(receive)) {
      digitalWrite(relay, HIGH);
      delay(100);
      digitalWrite(relay, LOW);
    }
    delay(100);
  }
  delay(100);

  
  //**********************************************
  //****************REST OF THE PROGRAM***********
  wdt_reset(); //Ensure one call to this function at least one time in two seconds or less
  Serial.println(elapsedTime); // prints time since program started
}