CRGB LED Indicating System (CLIS)

Using the ESP32 popular MCU along with Arduino IDE, this code can be compiled to control two different CRGB-Led strips via WiFi.
In the source.c, the WiFi credentials (SSID and password) should be put and then the MCU will connect to your WiFi network.
Thereafter, find the MCU's IP address by reading the serial (running at baud 115200) output while it's connected to serial terminal via USB or perhaps find the IP using your router.
Enter the IP in your browser and see the available commands. You can edit the code to improve and add more commands as you prefer.

