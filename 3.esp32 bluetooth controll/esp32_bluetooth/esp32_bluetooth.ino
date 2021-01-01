// MENGADAPTASI DARI https://www.youtube.com/watch?v=wNW-1MQTkvQ
// dikembangkan oleh dafa wijaya
// u can contact me at  https://github.com//dafawijaya


#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


#define S1 32
#define R1 15

#define S2 35
#define R2 2

#define S3 34
#define R3 4

#define S4 39
#define R4 22


#define LED1 26
#define LED2 25
#define LED3 27
#define Buzzer 21

String res = "";

BluetoothSerial SerialBT;
void without_bluetooth()
{

  digitalWrite(R1, digitalRead(S1));
  digitalWrite(R2, digitalRead(S2));
  digitalWrite(R3, digitalRead(S3));
  digitalWrite(R4, digitalRead(S4));

}

void setup() {
  Serial.begin(115200);
  pinMode(S1, INPUT);
  pinMode(R1, OUTPUT);

  pinMode(S2, INPUT);
  pinMode(R2, OUTPUT);

  pinMode(S3, INPUT);
  pinMode(R3, OUTPUT);

  pinMode(S4, INPUT);
  pinMode(R4, OUTPUT);


  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW);
  delay(500);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW);
  delay(500);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW);
  delay(500);


  SerialBT.begin("ESP32test");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop()
{
  while (!SerialBT.available()); // Wait Until anything is coming from bluetooth client

  while (SerialBT.available()) // Read until the bluetooth client is sending.
  {
    char add = SerialBT.read();
    res = res + add;
    delay(1);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
  }



  // Assigning Actions on particular conditions
  if (res == "T")
  {
    Serial.println("Connection Established!!!");
    without_bluetooth();
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);

  }
  if (res == "1")
  {
    Serial.println("Turning ON 1st led");
    digitalWrite(R1, LOW);
  }
  if (res == "A")
  {
    Serial.println("Turning OFF 1st led");
    digitalWrite(R1, HIGH);
  }
  if (res == "2")
  {
    Serial.println("Turning ON 2nd led");
    digitalWrite(R2, LOW);
  }
  if (res == "B")
  {
    Serial.println("Turning OFF 2nd led");
    digitalWrite(R2, HIGH);
  }
  if (res == "3")
  {
    Serial.println("Turning ON 3rd led");
    digitalWrite(R3, LOW);
  }
  if (res == "C")
  {
    Serial.println("Turning OFF 3rd led");
    digitalWrite(R3, HIGH);
  }
  if (res == "4")
  {
    Serial.println("Turning ON 4th led");
    digitalWrite(R4, LOW);
  }
  if (res == "D")
  {
    Serial.println("Turning OFF 4th led");
    digitalWrite(R4, HIGH);
  }
  if (res == "9")
  {
    Serial.println("Turning ON all led");
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
    digitalWrite(R3, LOW);
    digitalWrite(R4, LOW);

  }
  if (res == "I")
  {
    Serial.println("Turning OFF all led");
    digitalWrite(R1, HIGH);
    digitalWrite(R2, HIGH);
    digitalWrite(R3, HIGH);
    digitalWrite(R4, HIGH);

  }


  res = ""; // clearing the string.


}
