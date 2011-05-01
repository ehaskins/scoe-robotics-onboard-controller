import procontroll.*;


//Gathers XBox Input, Computes Motor Values
public class MotorCalculator {

  
  
  ControllDevice controller;
  ControllIO c;
  //For whatever reason, XBox 360 Sticks are mapped as a combination of 2 Sliders.  So are the Triggers.
  //Feed power is the Right Trigger (technically, both triggers are the same axis).
  ControllSlider leftJoystickX, leftJoystickY, rightJoystickX, rightJoystickY, feedPower;
  ControllButton intakePower, killSwitch, intakeDirection, feedShot;


  /*These are for Human-Error Function;
  They describe cycles of the draw-method.  */
  int runs = 0;
  int runs2 = 0;
  int runs3 = 0;

  Packet packet;

  public MotorCalculator(Packet packet, PApplet plet) {
    this.packet = packet;
    c = ControllIO.getInstance(plet);
    //Normal Xbox
    //controller = c.getDevice("Controller (XBOX 360 For Windows)");
    //Luminescent Glowing XBox Controller
    controller = c.getDevice("Controller (Afterglow Gamepad for Xbox 360)");
    
    //Tolerances set input to 0 unless it overcomes a base threshhold - in this case, .15
    leftJoystickX = controller.getSlider(1);
    leftJoystickX.setTolerance(.15);
    leftJoystickY = controller.getSlider(0);
    leftJoystickY.setTolerance(.15);
    rightJoystickX = controller.getSlider(3);
    rightJoystickX.setTolerance(.15);
    rightJoystickY = controller.getSlider(2);
    rightJoystickY.setTolerance(.15);
    
    //The Select/Back Button (Left of the Large Logo Button in the center
    killSwitch = controller.getButton(6);
    //The 'X' Button (?)
    intakePower = controller.getButton(2);
    //The 'B' Button (?)
    intakeDirection = controller.getButton(3);
    //The 'Y' Button (?)
    //Slider 4 is the Trigger Axis
    feedPower = controller.getSlider(4);
    feedPower.setTolerance(.15);
    //The Right Bumper (above the trigger, top right)
    feedShot = controller.getButton(5);
  }  
  
  //Calculates the Motor Values and stores them to the appropriate Packet Values
  public void computeMotors() {

    float x = packet.leftXBoxX;
    float y = packet.leftXBoxY;
    float rot = packet.rightXBoxX;

    //Initial Values; Order is FL, FR, BR, BL
    //They represent raw motor values
    float[] Di = {
      x+y+rot, x-y+rot, -x-y+rot, -x+y+rot
    };
    //Maximum - go figure
    float maxi = 1.0;
    
    //Gather the Maximum of all four raw values
    for(int i = 0; i<Di.length; i++) {
      maxi = max(abs(Di[i]), maxi);
    }
    
    
    //Scale all Motors to those values by dividing by maximum power.
    for(int i = 0; i<Di.length; i++) {
      Di[i] = (Di[i]/maxi);
      //Invert Motors with Negative Values (Reversed Direction
      if(Di[i]<0) {
        Di[i]=-Di[i];
        packet.MD[i]=-1;
      } 
      else {
        packet.MD[i]=1;
      }
      //Scale to Multiplication of 255;
      packet.MP[i]=(int)(Di[i]*255);
    }
    
    /*The Y-Axis of the Right Stick is a scaling value - 
    It doesn't revert even though the stick snaps back */
    packet.MP[4] += (int)((packet.rightXBoxY)*2);
    
    //Cap maximum shot power at 255
    if(packet.MP[4] > 255) {
      packet.MP[4] = 255;
    } 
    
    //Cap minimum shot power at 0
    else if (packet.MP[4] < 0) {
      packet.MP[4] = 0;
    }
    else if (packet.MP[4] == 11) {
      packet.MP[4] = 12;
    }  
  }


  //Extracts values from the XBox Controller and stores them in Packet values
  private void getValues() {
    packet.leftXBoxX = leftJoystickX.getValue();
    packet.leftXBoxY = -leftJoystickY.getValue();
    packet.rightXBoxX = rightJoystickX.getValue();
    packet.rightXBoxY = -rightJoystickY.getValue();
   
   
   /*FEED POWER TEST: This test prevents the trigger from reverting by triggering 
   more than once per loop of the code, as it cycles much more than 
   the human trigger reflex*/
    if((feedPower.getValue() < -.15) && (runs == 0)) {
      packet.feed = !packet.feed;
      runs = 10;
    } else if(runs>0){
      runs--;
    }  
      
   //This button is held, so the above test is not applicable
    if(feedShot.pressed()&&!packet.feed){
      packet.feed=true;
    }else if (!feedShot.pressed()&&packet.feed){
      packet.feed = false;
    }  
    
    //See the feed power test.
    if((intakePower.pressed()) && (runs2==0)) {
      packet.intake = !packet.intake;
      runs2 = 10;
    }else if(runs2>0){
      runs2--;  
    }  
    
    
    //See the feed power test.
    if((intakeDirection.pressed()) && (runs3==0)) {
      packet.intakeDirection = !packet.intakeDirection;
      runs3 = 10;
    }else if(runs3>0){
      runs3--;
    }  
    
    //Kill Switch Engagement
    packet.Kill = killSwitch.pressed();
      //packet.Kill = false;
  }
}

