//joystick
const int j_up=4;
const int j_down=7;
const int j_left=5;
const int j_right=6;
//toggle switch
const int t_up=14;
const int t_down=15;
const int t_left=18;
const int t_right=17;
const int t_middle=16;

const int LED_left=33;
const int LED_right=32;

const int Lit_L=34;
const int Lit_R=35;
const int Lit_head=36;
const int Lit_flash=37;
const int Lit_break=38;
const int Lit_spare=39;

const int flashSpeed=1000;

int buttonState = 0;
int speedLeft = 90;
int speedRight = 90;

const int speedHi=140;
const int speedMh=105;
const int speedMd=90;
const int speedMl=75;
const int speedLo=40;

Servo speedPinLeft;
Servo speedPinRight;

boolean safeDrive=true;
boolean lit_L_stat=false;
boolean lit_R_stat=false;
