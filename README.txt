A wireless sensor use ESP8266 and STM32
This is a electronic process pratice project.
We use STM32 and ESP8266 to establish a wireless sensor based on HTTP.
STM32:
STM32 get raw imformation for sensors. Sensors we use are MQ4,DHT11,LM75A and photoresistance. And it can display some raw information from sensors. And it supports error detecting. If any sensor is offline, the blue light will be on. 

The communication we used between STM32 and esp8266 is Uart communication metion. The STM32 will send imformation to esp8266 at regular time. 

ESP8266:
ESP8266 will connect wifi whose ssid and password are flashed to its flash. And arter power on, it will execute init.lua to get information from adc uart. This action can update the information from sensors. And then it will execute httpServer.lua to establish a http server. We designed a html webpage to make the interface more beautiful. And the other guests connected the same wifi can visit URL to get sensor information. But the IP address is still automatically assigned and you have to view your router to get the target IP address. 
