/*** 
 * @Author: Dafu Wang
 * @Date: 2022-04-05 20:56:49
 * @LastEditTime: 2022-04-06 19:13:10
 * @LastEditors: Dafu Wang
 * @FilePath: \MQTT_emqx\src\MQTT.cpp
 */
#include "MQTT.h"

void callback(char* topic, byte* payload, unsigned int length)
{
    Serial.print("[");
    Serial.print(topic);
    Serial.println("]");
    //c基础知识 字符串最后一位为null 否则乱码
    payload[length]='\0';
    Serial.println((char*)payload);
}

MQTT::MQTT(char *WIFISSID,char *WIFIPSWD,char *MQTTServer,u16_t MQTTPort,char *ClientID,char *MQTTUser,char *MQTTPSWD)
{
    PubSubClient client(wifiClient);
    this->client=client;
    strcpy(this->WIFISSID,WIFISSID);
    strcpy(this->WIFIPSWD,WIFIPSWD);
    strcpy(this->MQTTServer,MQTTServer);
    this->MQTTPort=MQTTPort;
    strcpy(this->ClientID,ClientID);
    strcpy(this->MQTTUser,MQTTUser);
    strcpy(this->MQTTPSWD,MQTTPSWD);
}

void MQTT::wifiConnect()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFISSID, WIFIPSWD);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi not Connect");   
    }
}

void MQTT::mqttConnect()
{
    client.setServer(MQTTServer, MQTTPort);
    while (!client.connected())
    {
        client.connect(ClientID, MQTTUser, MQTTPSWD);
        Serial.println("MQTT Not Connected");
    }
    if(client.connected())
    {
        //绑定回调函数，提供服务器下发消息的处理接口
        client.setCallback(callback);
        Serial.println("MQTT Connected");   
    }
}

void MQTT::publish(char *topic,char *payload)
{
    //验证wifi和MQTT服务器是否连接，若掉线重连再发布
    while(WiFi.status()!=WL_CONNECTED)
    {
        wifiConnect();
    }
    while(!client.connected())
    {
        mqttConnect();
    }
    client.publish(topic,payload);
}

void MQTT::subscribe(char *topic)
{
    //验证wifi和MQTT服务器是否连接，若掉线重连再取消订阅
    while(WiFi.status()!=WL_CONNECTED)
    {
        wifiConnect();
    }
    while(!client.connected())
    {
        mqttConnect();
    }
    client.subscribe(topic);
}

void MQTT::unSubscribe(char *topic)
{
    //验证wifi和MQTT服务器是否连接，若掉线重连再取消订阅
    while(WiFi.status()!=WL_CONNECTED)
    {
        wifiConnect();
    }
    while(!client.connected())
    {
        mqttConnect();
    }
    client.unsubscribe(topic);
}

void MQTT::loop()
{
    client.loop();
}





