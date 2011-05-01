
import java.util.Set;
import java.util.HashSet;

import com.rapplogic.xbee.api.*;
import com.rapplogic.xbee.api.wpan.*;

public class RxListener implements Runnable {

  //This is a count of packets that were successfully sent,
  //ie, the XBee got an ACK
  int successfulPackets;

  //A count of packets that were not successfully sent
  int failedPackets;

  //A set of packets for which no response, ACK or error,
  //has been received
  Set<Integer> unreturnedPackets;

  XBee xbee;
  XBeeResponse rx;



  //XBee must be open()
  public RxListener(XBee xbee) {
    successfulPackets = 0;
    failedPackets = 0;

    this.unreturnedPackets = new HashSet<Integer>();
    this.xbee = xbee;
  }

  
  public final void run() {
    while(true) {
      try {
        
        //Blocking call (synchronous) - waits 100ms, then throws an exception.
        rx = xbee.getResponse(100);

        if(rx.getApiId() == ApiId.TX_STATUS_RESPONSE) {
          TxStatusResponse txrs = (TxStatusResponse) rx;

          if(unreturnedPackets.contains(txrs.getFrameId())) {
            unreturnedPackets.remove(txrs.getFrameId());
          }

          if(txrs.getStatus() == TxStatusResponse.Status.SUCCESS) {
            successfulPackets++;
          } else {
            failedPackets++;           
          }
        } else if(rx.getApiId() == ApiId.RX_16_RESPONSE) {
          for (Integer i : rx.getProcessedPacketBytes()){
            print(hex(i)+" ");
          }  
          println();
        }
        
        
          
      } catch(XBeeTimeoutException e) {
       //print(".");
      } catch(XBeeException e) {
        println("RxListener XBeeException");
      } catch(NullPointerException e) {
        println("Null pointer in RXProcessing");  
      }  
        
      try {
        println("success: " + getSuccessfulPackets() + " failure: " + getFailedPackets());
        Thread.sleep(100);
      } catch(InterruptedException e) {
          print("RxListener sleep interrupted");
      }
    }
  }


  public void register(int frameId) {
    unreturnedPackets.add(frameId);
  }
  
  public void error() {
    failedPackets++;
  }

  public int getSuccessfulPackets() {
    return successfulPackets;
  }
  public int getFailedPackets() {
    return failedPackets;
  }
  public int getUnreturnedPackets() {
    return unreturnedPackets.size();
  }
}
