#include <SoftwareSerial.h>
#include <helium.h>

HeliumModem* modem;

void setup() {
  modem = new HeliumModem();
  modem->sleepModem(1);

  Serial.begin(9600);
  Serial.println("LISTENING");
}

void loop() {
  modem->loop();

  DataUnpack* dup = modem->getDataUnpack();
  if (dup) {
    char str[256];
    dup->getString(str, 256);
    Serial.print("REQ: ");
    Serial.println(str);
    delete dup;

    char* rep = "REPLY";
    DataPack dp(1);
    dp.appendString(rep);
    modem->sendPack(&dp);
  }
}
