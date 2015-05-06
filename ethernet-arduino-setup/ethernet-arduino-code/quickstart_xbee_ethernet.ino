#include <SPI.h>
#include <Ethernet.h>
#include <IPStack.h>
#include <Countdown.h>
#include <MQTTClient.h>
#define MS_PROXY "quickstart.messaging.internetofthings.ibmcloud.com"
#define MQTT_PORT 1883
#define MQTT_MAX_PACKET_SIZE 100
byte mac[] = { 0x12, 0xFF, 0xBB, 0xCC, 0xDE, 0x11 };
#define MQTT_CLIENTID "d:quickstart:iotsample-arduino:12ffbbccde11"
#define MQTT_TOPIC "iot-2/evt/status/fmt/json"
EthernetClient c; 
IPStack ipstack(c);
MQTT::Client<IPStack, Countdown, 100, 1> client = MQTT::Client<IPStack, Countdown, 100, 1>(ipstack);
int incomingByte = 11;
String deviceEvent;
int pin;

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac); 
  pinMode(2, INPUT);
  delay(2000);
}

void loop() {
  int rc = -1;
  if (!client.isConnected()) {
    Serial.println("Connecting to IoT Foundation");
    while (rc != 0) {
      rc = ipstack.connect(MS_PROXY, MQTT_PORT);
    }
    
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = MQTT_CLIENTID;
    rc = -1;
    while ((rc = client.connect(data)) != 0)
    ;
    Serial.println("Connected successfully\n");
    Serial.println("Value\tDevice Event (JSON)");
    Serial.println("____________________________________________________________________________");
  }

  MQTT::Message message;
  message.qos = MQTT::QOS0;
  message.retained = false;
  deviceEvent = String("{\"d\":{\"myName\":\"Arduino Uno\",\"value\":");
  char buffer[60];
  //   if(Serial.available()>0) {
	//incomingByte = Serial.read();
 // }
  dtostrf(getValue(),1,2, buffer);
  deviceEvent += buffer;
  deviceEvent += "}}";
  Serial.print("\t");
  Serial.print(buffer);
  Serial.print("\t\t");
  deviceEvent.toCharArray(buffer, 60);
  Serial.println(buffer);
  message.payload = buffer;
  message.payloadlen = strlen(buffer);
  rc = client.publish(MQTT_TOPIC, message);
  
  if (rc != 0) {
    Serial.print("return code from publish was ");
    Serial.println(rc);
  }
  client.yield(1000);
}

double getValue(void) { 
  pin = digitalRead(2);
  return (pin);
}
