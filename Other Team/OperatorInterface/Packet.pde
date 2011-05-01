public class Packet {

  //Order is FL, FR, BR, BL - MOTORS ARE 2,3,4,5 
  //Correspond to Pin Values on Arduino Chip; 
  //MP[5] is the Shooting Mechanism, 
  //hence no Corresponding Direction
  int[] MP;
  int[] MD;

  boolean intake;
  boolean intakeDirection;
  boolean feed;
  boolean Kill;

  float leftXBoxX;
  float leftXBoxY;
  float rightXBoxX;
  float rightXBoxY;

  //CONSTRUCTOR
  public Packet() {
    MP = new int[5];
    MD = new int[4];
    MP[4] = 0;
  }

  public int[] getSendPacket() {
    for(int i=0;i<MD.length;i++) {
      if(MD[i]<0) {
        MD[i] = 0;
      }
    }
    int[] sendPacket = new int[14];
    sendPacket[0]=11;
    
    //These are full functionality values - beware high speed.
//    sendPacket[1]=(int)(map(MP[0],0,255,30,255));
//    sendPacket[2]=(int)(map(MP[1],0,255,30,255));
//    sendPacket[3]=(int)(map(MP[2],0,255,30,255));
//    sendPacket[4]=(int)(map(MP[3],0,255,30,255));


    //Lower values, for testing purposes.
    sendPacket[1]=(int)(map(MP[0],0,255,0,100));
    sendPacket[2]=(int)(map(MP[1],0,255,0,100));
    sendPacket[3]=(int)(map(MP[2],0,255,0,100));
    sendPacket[4]=(int)(map(MP[3],0,255,0,100));
    
    
    sendPacket[5]=(MD[0]);
    sendPacket[6]=(MD[1]);
    sendPacket[7]=(MD[2]);
    sendPacket[8]=(MD[3]);
    sendPacket[9]=toInt(intake);
    sendPacket[10]=toInt(intakeDirection);
    sendPacket[11]=toInt(feed);
    sendPacket[12]=(int)(map(MP[4],0,255,30,255));
    
    //Kill switch
    sendPacket[13]=toInt(Kill);

    return sendPacket;
  }  
  
  /*It is necessary to ensure that a 'True' resolves to 1, and
   not any other positive number. */
  public int toInt(boolean b) {
    if (b) {
      return 1;
    } 
    else {
      return 0;
    }
  }
  
}  

