#define ENCODEROUTPUT 663

const int HALLSEN_A = 3; // Hall sensor A connected to pin 3 (external interrupt)
const int MOTOR1A = 10;
const int MOTOR1B = 12;

//The sample code for driving one way motor encoder
volatile long encoderValue = 0;

int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;

int rpm = 0;
boolean measureRpm = false;
int motorPwm = 0;

void setup() {

  Serial.begin(57600);//Initialize the serial port
  EncoderInit();//Initialize the module
  
   pinMode( MOTOR1A , OUTPUT);
   pinMode( MOTOR1B , OUTPUT);

   digitalWrite(MOTOR1A,HIGH);
   digitalWrite(MOTOR1B,LOW);

   encoderValue = 0;
   previousMillis = millis();
}

void loop() {
  // put your main code here, to run repeatedly:

 

  // Update RPM value on every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

   

    // Revolutions per minute (RPM) =
    // (total encoder pulse in 1s / motor encoder output) x 60s
    rpm = (float)(encoderValue * 60 / ENCODEROUTPUT);

    // Only update display when there have readings
    if ( rpm > 0) {
      

      Serial.print(encoderValue);
      Serial.print(" pulse / ");
      Serial.print(ENCODEROUTPUT);
      Serial.print(" pulse per rotation x 60 seconds = ");
      Serial.print(rpm);
      Serial.println(" RPM");
    }
    
    encoderValue = 0;
  }

}

void EncoderInit()
{
 // Attach interrupt at hall sensor A on each rising signal
  attachInterrupt(digitalPinToInterrupt(HALLSEN_A), updateEncoder, RISING);
}


void updateEncoder()
{
  // Add encoderValue by 1, each time it detects rising signal
  // from hall sensor A
  encoderValue++;
}
