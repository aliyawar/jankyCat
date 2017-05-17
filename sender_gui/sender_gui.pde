// Processing UDP example to send and receive string data from Arduino
// press any key to send the "Hello Arduino" message

// walter hostname: WIZnetCCDE08.central.yale.internal
// ali hostname: WIZnetCCDE03.central.yale.internal

import hypermedia.net.*;
import java.net.InetAddress;
import java.net.UnknownHostException;

UDP udp;  // define the UDP object

import controlP5.*;

ControlP5 cp5;

String textValue = "";

Textfield myTextfield;
Button myButton;

//String ip       = "172.28.140.157";  // the remote IP address
int port        = 8888;    // the destination port
InetAddress ip = null;

void setup() {
 

    try {
      ip = InetAddress.getByName("WIZnetCCDE08.central.yale.internal");
    } catch (UnknownHostException e) {
      //System.exit(2);
    }
    System.out.println(ip.getHostName() + "="
        + ip.getHostAddress());
    //System.exit(0);
    
    
  
 udp = new UDP( this, 6000 );  // create a new datagram connection on port 6000
 //udp.log( true );     // <-- printout the connection activity
 udp.listen( true );

 size(400, 600);

 cp5 = new ControlP5(this);
 myTextfield = cp5.addTextfield("textinput")
                  .setPosition(100, 200)
                  .setSize(200, 20)
                  .setFocus(true)
                  ;

 // use setAutoClear(true/false) to clear a textfield or keep text displayed in
 // a textfield after pressing return.
 //myTextfield.setAutoClear(true).keepFocus(true);

 //myButton = cp5.addButton("clear", 0, 20, 200, 70, 20);
 myButton = cp5.addButton("submit")
    .setPosition(100,100)
    .setSize(200,19);
    
 //cp5.addButton("performTextfieldActions", 0, 20, 100, 150, 20);
 //cp5.addToggle("toggleAutoClear", true, 180, 100, 90, 20).setCaptionLabel("Auto Clear");
 //cp5.addToggle("toggleKeepFocus", true, 280, 100, 90, 20).setCaptionLabel("Keep Focus");
//if (myButton.isOn()){
//udp.send(myTextfield.getText(), ip, port );   // the message to send
//}
 
}



void draw()
{
}



public void submit() {
  
      udp.send(myTextfield.getText(), ip.getHostAddress(), port );   // the message to send

}