/*** 
 * @Author: Dafu Wang
 * @Date: 2022-04-05 20:56:36
 * @LastEditTime: 2022-04-06 19:08:19
 * @LastEditors: Dafu Wang
 * @FilePath: \MQTT_emqx\include\MQTT.h
 */
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//回调函数，服务器下发所有消息都在该函数中处理
void callback(char* topic, byte* payload, unsigned int length);

//MQTT客户端封装类
class MQTT
{
    private:
    WiFiClient wifiClient;
    PubSubClient client;
    char WIFISSID[100];
    char WIFIPSWD[100];
    char MQTTServer[100];
    u16_t MQTTPort;
    char ClientID[100];
    char MQTTUser[100];
    char MQTTPSWD[100];

    public:

    //构造器，初始化wifi设置以及客户端设置
    MQTT(char *WIFISSID,char *WIFIPSWD,char *MQTTServer,u16_t MQTTPort,char *ClientID,char *MQTTUser,char *MQTTPSWD);

    //wifi连接
    void wifiConnect();

    //mqtt连接
    void mqttConnect();

    //发布publish
    void publish(char *topic,char *payload);

    //订阅subscribe
    void subscribe(char *topic);

    //取消订阅
    void unSubscribe(char *topic);

    //保活
    void loop();

};