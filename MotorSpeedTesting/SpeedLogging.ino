volatile unsigned long prevSampleTime = micros();
volatile unsigned long currSampleTime = micros();

volatile unsigned int interruptCount = 0;
volatile unsigned int prevInterruptCount = 0;

double sampleTime = 0.0;
double measuredSpeed = 0.0;

#define USECTOSEC 1000000

// Multiplied by the final speed in Hz before being output
#define CONVERSIONFACTOR 2.0
const byte speedSensorPin = 2;

void calculateSpeed();

void setup() {
    pinMode(speedSensorPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(speedSensorPin), measureSpeed, FALLING);

    Serial.begin(9600);
}

void loop() {
    calculateSpeed();

    Serial.print(sampleTime);
    Serial.print(",");
    Serial.println(measuredSpeed);

    delay(100);
}

void measureSpeed() {
    currSampleTime = micros();
    interruptCount++;
}

void calculateSpeed() {
    const unsigned long currTime = currSampleTime;
    const unsigned long prevTime = prevSampleTime;
    const unsigned long currInterruptCount = interruptCount;
    if (currTime != prevTime){
        /*Serial.print(currTime);
        Serial.print("   ");
        Serial.println(prevTime);
        Serial.print(interruptCount);
        Serial.print("---");
        Serial.println(prevInterruptCount);*/

        // Divide by 1,000,000 to convert microseconds to seconds, multiply by our conversion factor
        double timeDelta = (double)(currTime - prevTime) / (double)(USECTOSEC / CONVERSIONFACTOR);
        measuredSpeed = (double)(currInterruptCount - prevInterruptCount) / timeDelta;
        sampleTime = currTime / USECTOSEC;

        prevSampleTime = currSampleTime;
        prevInterruptCount = interruptCount;
    } else {
        measuredSpeed = 0;
        interruptCount = 0;
    }
}
