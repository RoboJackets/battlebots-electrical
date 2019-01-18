
volatile unsigned long prevSampleTime = micros();
volatile unsigned long currSampleTime = micros();

volatile unsigned int interruptCount = 0;
volatile unsigned int prevInterruptCount = 0;

double measuredSpeed = 0.0;
const byte speedSensor = 2;
void calculateSpeed();

void setup() {
  // put your setup code here, to run once:
  pinMode(speedSensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(speedSensor), measureSpeed, FALLING);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  calculateSpeed();
  Serial.print(millis()/1000.0);
  Serial.print(",");
  Serial.println(measuredSpeed);
  delay(200);
}

void measureSpeed(){
  currSampleTime = micros();  
  interruptCount++;
}


void calculateSpeed(){
  const unsigned long currTime = currSampleTime;
  const unsigned long prevTime = prevSampleTime;
  if(currTime != prevTime){
//    Serial.print(currTime);
//    Serial.print("   ");
//    Serial.println(prevTime);
//    Serial.print(interruptCount);
//    Serial.print("---");
//    Serial.println(prevInterruptCount);
    measuredSpeed = (double)(interruptCount-prevInterruptCount)/((double)(currTime - prevTime)/500000.0);    

    //Serial.println(currTime - prevTime);
    prevSampleTime = currSampleTime;
    prevInterruptCount = interruptCount;
    
  }else{
    measuredSpeed = 0;
    interruptCount = 0;
  }
  
}
