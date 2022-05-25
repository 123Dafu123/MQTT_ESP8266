/*** 
 * @Author: Dafu Wang
 * @Date: 2022-04-05 20:45:31
 * @LastEditTime: 2022-05-25 12:27:59
 * @LastEditors: Dafu Wang
 * @FilePath: \MQTT_emqx\src\main.cpp
 */

#include <Arduino.h>
#include "MQTT.h"

#define WIFISSID "wangdafu"
#define WIFIPSWD "12345678"
#define MQTTSERVER "192.168.137.1"
#define MQTTPort 1883
#define ClientID "2022040501"
#define MQTTUser "esp8266"
#define MQTTPSWD "MzA0MjE2ODczNjQzODQwNjE1Mzk5Njk3ODQyNTcxODM3NDE"

#define pubTopic "esp8266"
#define subTopic "web"
#define pubPayload "{\"msg\",\"hello\"}"

int lastMS=0;
MQTT mqtt(WIFISSID,WIFIPSWD,MQTTSERVER,MQTTPort,ClientID,MQTTUser,MQTTPSWD);

void setup() 
{
  Serial.begin(115200);
  mqtt.wifiConnect();
  mqtt.mqttConnect();
  mqtt.subscribe(subTopic);  
}

void loop()
{
  if(millis()-lastMS>=1000)
  {
    lastMS=millis();
    mqtt.publish(pubTopic,pubPayload);
  }
  mqtt.loop();
}