/*

UNIVERSITY OF WASHINGTON FIRST ROBOTICS
               DAWG BYTES
         
      GROUND VEHICLE CONTROL CODE

                  BY
               
              JOHN CHILTON
             JOE GODLEWSKI
              RYAN BURNETT
               
         WORLD COMPETITION VERSION
              APRIL 28, 2011
                  v1.0
              

*/


//Loggers for XBee Library
import org.apache.log4j.*;
import gnu.io.*;

//XBee Library
import com.rapplogic.xbee.api.*;
import com.rapplogic.xbee.api.wpan.*;

//Procontroll for XBox Controller
import procontroll.*;


//Hexadecimal Addresses for the XBee are the paramaters - High First, then Low
XBeeAddress64 robotXbee = new XBeeAddress64(0x00, 0x13, 0xa2, 0x00, 0x40, 0x6e, 0x7d, 0x49);


RxListener rxListener;
TxSender txSender;


MotorCalculator mc;
GUI gui;

XBee xbee;

Packet packet;

void setup() {
  packet = new Packet();
  mc = new MotorCalculator(packet, this);
  gui = new GUI(this, packet);

  /***************
   Setup XBee communication
   ***************/

  xbee = new XBee();

  try {
    //Windows
    xbee.open("COM7", 57600);
    //Linux
    //xbee.open("/dev/ttyUSB0", 115200);
  } 
  catch(XBeeException e) {
    println("XBeeException from OI Init");
  }  

  rxListener = new RxListener(xbee);
  Thread rxListenerThread = new Thread(rxListener);
  rxListenerThread.start();

  txSender = new TxSender(100, robotXbee, rxListener, packet);
  Thread txSenderThread = new Thread(txSender);
  txSenderThread.start();
}

void draw() {

 mc.getValues();
 mc.computeMotors();
 gui.update();
}

