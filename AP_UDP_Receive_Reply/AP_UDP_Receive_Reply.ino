/*
  AP_udp_Receive_Reply.ino
  This sketch sets up and access point to receive udp packets. It parses the packets and extracts
  data to control the colour of an RGB LED and the sends an "acknowledge" packet back to the sender.
  A separate Processing sketch is used to send the udp packet and receive acknowledgement.
  Created: 7 Dec, 2018 by wolfpaw98
  This code adapted from examples is in the public domain.
*/

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

int ledPin[] = { 15, 12, 13 }; // initialize rgb output pins
int rgbValue[] = { 0, 0, 0 }; // initialize rgb values
int pinCount = 3;

WiFiUDP udp;
unsigned int localPort = 8888; // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; // incoming packet buffer
char ReplyBuffer[] = "received\r\n"; // acknowledgement string

void setup() {  
  for ( int i = 0; i < pinCount; i++ ) {
    pinMode( ledPin[i], OUTPUT ); // assign pins as outputs
    analogWrite( ledPin[i], 0 ); // Turn off all LEDs
  }

  delay( 500 ); // very important bit for Access Point to work properly...

  Serial.begin( 115200 );
  WiFi.softAP( "Connect2Me", "accessGranted" );
  udp.begin( localPort );
}

void loop() { // process events
  int packetSize = udp.parsePacket(); // if there's data available, read a packet
  if ( packetSize ) {
    udp.read( packetBuffer, UDP_TX_PACKET_MAX_SIZE ); // read packet into packetBufffer
    // parse packet contents
    char * strIndx; // this is used by strtok() as an index
    strIndx = strtok( packetBuffer, " " ); // get the first part - the string
    for ( int i = 0; i < pinCount; i++ ){
      rgbValue[i] = atoi( strIndx ); // convert this part to an integer
      strIndx = strtok( NULL, " " ); // continue where the previous call left off
      analogWrite( ledPin[i], rgbValue[i] ); // write to LED
    }
    reply(); // send reply to the IP address and port that sent the packet
  }
  delay( 10 );
}

void reply() {
  udp.beginPacket( udp.remoteIP(), udp.remotePort() );
  udp.write( ReplyBuffer );
  udp.endPacket();  
}
