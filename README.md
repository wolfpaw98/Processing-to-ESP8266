# Processing to ESP8266
These sketches are a proof-of-concept to demonstrate communications over udp between a Processing sketch and an ESP8266. The processing sketch reads the X and Y positions of the mouse, stores them in a string and sends the packet to the ESP8266. The arduino sketch initializes the ESP8266 as an access point and waits to receive data. Upon receipt of the packet, the data is extracted and used to change the colour of an rgb LED. Finally, a receipt acknowledgement is sent back to the processing sketch.

Processing Requirements

UDP library - installed via the Import Libary feature.

Arduino Requirements

ESP8266 Modules installed. ESP8266WiFi.h and WiFiUdp.h libraries installed.

