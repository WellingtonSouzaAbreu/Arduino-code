/************************** Ewings Esp8266 Stack ******************************
This file is part of the Ewings Esp8266 Stack.

This is free software. you can redistribute it and/or modify it but without any
warranty.

Author          : Suraj I.
created Date    : 1st June 2019
******************************************************************************/

#ifndef _EWINGS_ESP8266_STACK_H_
#define _EWINGS_ESP8266_STACK_H_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <config/Config.h>

#ifdef ENABLE_EWING_HTTP_SERVER
#include <webserver/EwingsWebServer.h>
#endif

#include <database/DefaultDatabase.h>
#include <service_provider/NtpServiceProvider.h>
#include <service_provider/HttpServiceProvider.h>
#include <service_provider/OtaServiceProvider.h>
#include <service_provider/WiFiServiceProvider.h>
#include <service_provider/EventServiceProvider.h>

#ifdef ENABLE_ESP_NOW
#include <service_provider/ESPNOWServiceProvider.h>
#endif

#ifdef ENABLE_GPIO_SERVICE
#include <service_provider/GpioServiceProvider.h>
#endif

#ifdef ENABLE_MQTT_SERVICE
#include <service_provider/MqttServiceProvider.h>
#endif

#ifdef ENABLE_EMAIL_SERVICE
#include <service_provider/EmailServiceProvider.h>
#endif

#ifdef ENABLE_EXCEPTION_NOTIFIER
#include <helpers/ExceptionsNotifier.h>
#endif

#if defined( ENABLE_NAPT_FEATURE )
#include "lwip/lwip_napt.h"
#include "lwip/app/dhcpserver.h"
#elif defined( ENABLE_NAPT_FEATURE_LWIP_V2 )
#include <lwip/napt.h>
#include <lwip/dns.h>
#include <dhcpserver.h>
#endif

/**
 * EwingsEsp8266Stack class
 */
class EwingsEsp8266Stack {

  public:
    void initialize( void );
    void serve( void );

  protected:
    /**
		 * @var	ESP8266WiFiClass*|&WiFi wifi
		 */
    ESP8266WiFiClass* wifi = &WiFi;
    /**
		 * @var	WiFiClient  wifi_client
		 */
    WiFiClient wifi_client;

    #ifdef EW_SERIAL_LOG
    static void handleLogPrints( void );
    #endif
    #if defined( ENABLE_NAPT_FEATURE ) || defined( ENABLE_NAPT_FEATURE_LWIP_V2 )
    void enable_napt_service( void );
    #endif
};

extern EwingsEsp8266Stack EwStack;

#endif
