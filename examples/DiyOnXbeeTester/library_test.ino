#include <DHT.h>

#include <AnalogSensor.h>
#include <GenericSensor.h>
#include <Dimmer.h>
#include <Sensors.h>
#include <RGB.h>

#define FOTOPIN 0
#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)


Sensors sensors(Serial, 3, 2);

DHT dht(DHTPIN, DHTTYPE);

void printDhtTemperature(Stream& stream) {
  stream.println(dht.readTemperature());
}

void printDhtHumidity(Stream& stream) {
  stream.println(dht.readHumidity());
}

void setup() {
  dht.begin();
  Serial.begin(115200);

  int i = -1;
  sensors.setSensor(++i, new AnalogSensor("Brightness", FOTOPIN, 5000));
  sensors.setSensor(++i, new GenericSensor("Temperature", 3000, &printDhtTemperature));
  sensors.setSensor(++i, new GenericSensor("Humidity", 3000, &printDhtHumidity));

  i = -1;
  sensors.setActor(++i, new Dimmer("Dimmer", 10));
  sensors.setActor(++i, new RGB("Stripe", 7, 8, 9));
}

void loop() {
  sensors.process();
}
