/*
  udp_Transmit_Receive.pde
  This sketch creates a udp communication link between Processing and an ESP8266
  and sends curser position data to control the colours of a rgb led.
  A small companion sketch (AP_udp_Receive_Reply.ino) running on the ESP8266 
  for data exchange.
  -- note that all input/output packets end with the characters ";\n".
  Created: 7 Dec, 2018 by wolfpaw98
  This code adapted from examples is in the public domain.
*/

import hypermedia.net.*; // import UDP library

UDP udp;  // define UDP object

char space = ' '; // define delimiter
String lineEnd = ";\n"; // define line terminator
String ip = "192.168.4.1";  // remote IP address
int port = 8888;    // destination port

void setup() {
  size(255, 255);
  udp = new UDP( this, port ); // create a new connection on port
  udp.listen( true ); // wait for incomming packet
}

void draw() { //process events
  String red  = str( mouseX ); // assign red value
  String green = str( mouseY ); // assign green value
  String blue = str( ( mouseX + mouseY ) / 2 ); // assign blue value
  String spaceS = str( space ); // delimiter
  String packet = red + spaceS + green + spaceS + blue; // build packet to send
  println(packet);
  packet = packet + lineEnd; // format packet
  udp.send( packet, ip, port ); // send udp packet   
}

/*
This method is automatically called by the UDP object each time a non-null packet
is received. By default, this method needs one argument (packet recevied as 
byte[] array), but two additional arguments (representing in order the 
sender IP address and its port) can be set.
*/
void receive( byte[] data, String ip, int port ) { // receive packet
  data = subset( data, 0, data.length - 2 ); // remove the line terminator ";\n" at the end
  String packet = new String( data ); // turn packet into a string
  println( "reply " + packet + " from " + ip + " on port " + port ); // print result
}
