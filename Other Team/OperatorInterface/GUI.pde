import gnu.io.*;
import guicomponents.*;
import processing.net.*;


public class GUI {

  Packet packet;

  //MP = MotorPower 
  
  GTextField inlog, outlog, strafeXField, 
  strafeYField, rotField, fireField, packTotal, 
  packSnF, FLMPfield, FRMPfield, BLMPfield, BRMPfield, 
  shootPowfield, intakeDirectionfield, intakefield;
  
  
  GLabel titleLabel, inlogLabel, outlogLabel, 
  xBoxLabel, packLabel, motorSubLabel, UILabel, 
  UILabel2, motoPowLabel;
  
  
  String outText, inText;
  GWSlider powerSlider;
  PApplet plet;


  public GUI(PApplet plet, Packet packet) {
    this.plet = plet;
    this.packet = packet;
    size(800, 560);

    GComponent.globalColor = GCScheme.getColor(plet, GCScheme.GREY_SCHEME);

    GComponent.globalFont = GFont.getFont(plet, "Times New Roman", 12);

    UILabel = new GLabel(plet, "U.W. DawgBytes 2011", 250, 5, 250, 5); //5, 5, 250, 5
    UILabel.setFont("Digital-7", 34);
    UILabel2 = new GLabel(plet, "GROUND VEHICLE UI", 265, 5, 250, 120);
    UILabel2.setFont("Digital-7", 34);

    xBoxLabel = new GLabel(plet, "XBox Controller:", 520, 168, 250, 12); //660, 24, 250, 12
    xBoxLabel.setFont("Digital-7", 18);
    strafeXField = new GTextField(plet, "Strafe X: ", 530, 194, 100, 12, true);
    strafeXField.setFont("Times New Roman", 14);
    strafeYField = new GTextField(plet, "Strafe Y: ", 530, 210, 100, 12, true);
    strafeYField.setFont("Times New Roman", 14);
    rotField =  new GTextField(plet, "Rotation: ", 530, 226, 100, 12, true);
    rotField.setFont("Times New Roman", 14);
    fireField = new GTextField(plet, "Fire: ", 530, 242, 100, 12, true);
    fireField.setFont("Times New Roman", 14);
    intakefield= new GTextField(plet, "Intake: ", 530, 258, 100, 12, true);
    intakefield.setFont("Times New Roman", 14);
    intakeDirectionfield = new GTextField(plet, "Intake Dir: ", 530, 274, 100, 12, true);
    intakeDirectionfield.setFont("Times New Roman", 14);
    
    
      
//    shootPowfield = new GTextField(plet, "SHOOTING POWER: ", 670, 140, 250, 18, true);
//    shootPowfield.setFont("Times New Roman", 14);
    
    


    //    inlogLabel = new GLabel(plet, "Input Log:", 10, 125, 250, 12);
    //    inlogLabel.setFont("Digital-7", 14);
    //    inlog =  new GTextField(plet, "No Text yet", 10, 146, 630, 350, true);
    //    inlog.setFont("Times New Roman", 12);

//    packLabel = new GLabel(plet, "Packets: ", 10, 510, 630, 12);
//    packLabel.setFont("Digital-7", 12);
//    packTotal = new GTextField(plet, "Total Packets Sent: ",10, 530, 630, 12, false);
//    packTotal.setFont("Times New Roman", 12);
//    packSnF = new GTextField(plet, "Successes: #, Failures: #",10, 550, 630, 12, false);
//    packSnF.setFont("Times New Roman", 12);

    motorSubLabel = new GLabel(plet, "Our Drives:         ", 120, 168, 250, 12); //355, 28, 250, 12
    motorSubLabel.setFont("Digital-7", 18);
    FLMPfield = new GTextField(plet, "FL:          ", 125, 190, 100, 12, true);
    FLMPfield.setFont("Times New Roman", 12);
    FRMPfield = new GTextField(plet, "FR:          ", 125, 206, 100, 12, true);
    FRMPfield.setFont("Times New Roman", 12);
    BLMPfield = new GTextField(plet, "BL:          ", 125, 222, 100, 12, true);
    BLMPfield.setFont("Times New Roman", 12);
    BRMPfield = new GTextField(plet, "BR:          ", 125, 238, 100, 12, true);
    BRMPfield.setFont("Times New Roman", 12);

    //    outlogLabel = new GLabel(plet, "Output Log:", 660, 125, 250, 16);
    //    outlogLabel.setFont("Digital-7", 14);
    //    outlog = new GTextField(plet, "No Text Yet", 660, 146, 630, 500, true);
    //    outlog.setFont("Times New Roman", 12);
    
    motoPowLabel = new GLabel(plet, "Shooter Motor Powers", 300, 350, 200, 20);//originally 65, 180, 200, 20
    motoPowLabel.setFont("Digital-7", 16);
    
    powerSlider = new GWSlider(plet,250,380,260);
    powerSlider.setRenderValueLabel(false);  //hides value label
    String[] powerSliderTickLabels = new String[] {"0", "50", "100", "150", "200", "250"};
    powerSlider.setLimits(0, 0, 250);
    powerSlider.setTickLabels(powerSliderTickLabels);
    
    
  }

  void handleTextFieldEvents(GTextField textfield) {
    update();
  }


  void update() {
    //outtext += "
    strafeXField.setText("Strafe X: "+packet.leftXBoxX);
    strafeYField.setText("Strafe Y: "+packet.leftXBoxY);
    rotField.setText("Rotation: "+packet.rightXBoxX);
    fireField.setText("Fire: "+packet.feed);
    FLMPfield.setText("FL: "+packet.MP[0]*packet.MD[0]);
    FRMPfield.setText("FR: "+packet.MP[1]*packet.MD[1]);
    BRMPfield.setText("BR: "+packet.MP[2]*packet.MD[2]);
    BLMPfield.setText("BL: "+packet.MP[3]*packet.MD[3]);
    intakefield.setText("Intake: "+packet.intake);
    intakeDirectionfield.setText("Intake Dir: "+packet.intakeDirection);
//    shootPowfield.setText("SHOOTING POWER: "+packet.MP[4]);
    
    powerSlider.setValue(packet.MP[4]); 
    
  }
}


/*Field Oriented Drive*/
//TODO: IMPLEMENT//
//  for (int i = 0; i < OFFSETS.size(); i++){
//    mp[i] = (((sin(position - atan(leftStickY/LeftStickx)))*(sqrt(leftStickX^2+leftStickY^2))+rightStickX)/(abs(((sin(position - atan(leftStickY/LeftStickx)))*(sqrt(leftStickX^2+leftStickY^2))
//  
/*Vehicle-Oriented Drive*/
