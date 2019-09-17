#include "wifi.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"          //https://github.com/tzapu/WiFiManager

#ifndef STASSID
	#define STASSID "SSID"
	#define STAPSK  "password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

char WiFiE::hostname[15];

void WiFiE::init()
{
	sprintf(hostname, "esp8266-%06x", ESP.getChipId()); // you can override it

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		//Serial.println("Connection Failed! Rebooting...");
		delay(1000);
		ESP.restart();
	}
	MDNS.begin(hostname);
}

void WiFiE::handle()
{
	MDNS.update();
}