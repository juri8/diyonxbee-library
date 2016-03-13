#include <DHT.h>

#include <AnalogSensor.h>
#include <GenericSensor.h>
#include <Dimmer.h>
#include <Sensors.h>
#include <RGB.h>
#include <Switch.h>
#include <Button.h>

#define FOTOPIN 0
#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)


Sensors sensors(Serial, 3, 3);

DHT dht(DHTPIN, DHTTYPE);

void printDhtTemperature(Stream& stream) {
  stream.println(dht.readTemperature());
}

void printDhtHumidity(Stream& stream) {
  stream.println(dht.readHumidity());
}
AnalogSensor brightness("Brightness", FOTOPIN, 5000);
GenericSensor temperature ("Temperature", 3000, &printDhtTemperature);
GenericSensor humidity("Humidity", 3000, &printDhtHumidity);
Dimmer dimmer("Dimmer", 10);
RGB stripe("Stripe", 7, 8, 9);
Switch switch1("Switch", 13);

void setup() {
  dht.begin();
  Serial.begin(115200);

  int i = -1;
  sensors.setSensor(++i, &brightness);
  sensors.setSensor(++i, &temperature);
  sensors.setSensor(++i, &humidity);

  i = -1;
  sensors.setActor(++i, &dimmer);
  sensors.setActor(++i, &stripe);
  sensors.setActor(++i, &switch1);
}

void loop() {
  sensors.process();
}
