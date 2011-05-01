


public class TxSender implements Runnable {

  int interval;
  XBeeAddress64 destination;
  RxListener rxListener;
  Packet packet;

  public TxSender(int msInterval, XBeeAddress64 address, RxListener rx, Packet packet) {
    this.interval = msInterval;
    this.destination = address;
    this.rxListener = rx;
    this.packet = packet;
  }

  public void run() {
    while(true) {
      //packet is a member variable of the PApplet instance that is the parent
      //object of TxSender
      int[] payload = packet.getSendPacket();
      
      //print("speed: " + hex(packet.speed) + " strafe: " + hex(packet.strafe) + " turn: " + hex(packet.turn) + " fire: " + packet.fire + "\n");
      
      spawnTxThread(destination, payload, rxListener);

      try {
        Thread.sleep(interval);
      } 
      catch(InterruptedException e) {
        println("TxSender woken up");
      }
    }
  }


  private void spawnTxThread(XBeeAddress64 dest, int[] payload, RxListener rx) {

    TxRequest64 tx = new TxRequest64(dest, payload);

    try {
      xbee.sendSynchronous(tx, 50);
    } 
    catch(XBeeException e) {
      rx.error();
    }

    rx.register(tx.getFrameId());
  }
}

