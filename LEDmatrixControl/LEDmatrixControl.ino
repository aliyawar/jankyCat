#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define MAX_DEVICES 8
#define CLK_PIN   7
#define DATA_PIN  6
#define CS_PIN    5

EthernetClient client;

byte mac[] = {
  0xEC, 0xAA, 0xBB, 0xCC, 0xDE, 0x43
};
//IPAddress ip(172, 28, 140, 157);

// HARDWARE SPI
// MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);
// SOFTWARE SPI
MD_Parola P = MD_Parola(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

#define PAUSE_TIME    500
#define SPEED_DEADBAND  5

// Scrolling parameters
#if USE_UI_CONTROL
#define SPEED_IN    A5
#define DIRECTION_SET 8 // change the effect
#define INVERT_SET    9 // change the invert

#endif // USE_UI_CONTROL

uint8_t frameDelay = 25;  // default frame delay value
textEffect_t  scrollEffect = PA_SCROLL_LEFT;

// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  75
char curMessage[BUF_SIZE+1];
char newMessage[BUF_SIZE];
bool newMessageAvailable = false;

unsigned int localPort = 8888;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[BUF_SIZE];  //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup()
{
  Serial.begin(9600);

  P.begin();
  P.displayClear();
  P.displaySuspend(false);

  Ethernet.begin(mac);
  IPAddress ip = Ethernet.localIP();
  Serial.print(ip);


  Udp.begin(localPort);

  P.displayScroll(curMessage, PA_LEFT, scrollEffect, frameDelay);

  strcpy(curMessage, "get off of facebook");
  newMessage[0] = '\0';


}

void loop()
{

  int packetSize = Udp.parsePacket();
  if (packetSize) {

    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i = 0; i < 4; i++) {
      Serial.print(remote[i], DEC);
      if (i < 3) {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());
    
    // read the packet into packetBufffer
    
    Udp.read(packetBuffer, packetSize-1);
    Serial.println(packetBuffer);

    // send a reply to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();

    strcpy(curMessage, packetBuffer);
//    curMessage[packetSize+1] = '\0';

//    for(int i=0;i<packetSize-1;i++) 
//    {
//      curMessage[i] = packetBuffer[i];
//    }
//    curMessage[packetSize+1] = '0';
    Serial.println(curMessage);

//    curMessage = packetBuffer;
    for(int i=0;i<BUF_SIZE;i++) packetBuffer[i] = 0;
//    for(int i=0;i<BUF_SIZE;i++) curMessage[i] = 0;

    
    delay(10);
  }

  if (P.displayAnimate())
  {

    P.displayReset();
    
  }
  
}
