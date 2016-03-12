/*
HC-SR04 Ping distance sensor:
VCC to arduino 5v
GND to arduino GND
Echo to Arduino pin 7
Trig to Arduino pin 8

This sketch originates from Virtualmix: http://goo.gl/kJ8Gl
Has been modified by Winkle ink here: http://winkleink.blogspot.com.au/2012/05/arduino-hc-sr04-ultrasonic-distance.html
And modified further by ScottC here: http://arduinobasics.blogspot.com.au/2012/11/arduinobasics-hc-sr04-ultrasonic-sensor.html
on 10 Nov 2012.
*/


#define pulse 8 // Trigger Pin
#define LEDPin 13 // Onboard LED

int deg = 0;
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
int echoPin[8];

void setup() {
    Serial.begin (9600);
    echoPin[0] = 2;
    echoPin[1] = 7; // Echo Pin
    echoPin[2] = 4;
    echoPin[3] = 7; // Echo Pin change later
    echoPin[4] = 2;
    echoPin[5] = 7; // Echo Pin
    echoPin[6] = 2;
    echoPin[7] = 7; // Echo Pin
    pinMode(pulse, OUTPUT);
    pinMode(echoPin[0], INPUT);
    pinMode(echoPin[1], INPUT);
    pinMode(echoPin[2], INPUT);
    //pinMode(echoPin[3], INPUT);
    //pinMode(echoPin[4], INPUT);
    //pinMode(echoPin[5], INPUT);
    //pinMode(echoPin[6], INPUT);
    //pinMode(echoPin[7], INPUT);
    pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
}

void loop() {
    /* The following trigPin/echoPin cycle is used to determine the
    distance of the nearest object by bouncing soundwaves off of it. */
    digitalWrite(pulse, LOW);
    delayMicroseconds(2);

    digitalWrite(pulse, HIGH);
    delayMicroseconds(10);

    digitalWrite(pulse, LOW);
    for(int i = 0;i < 3;i++)
    {
        readDist(i);
    }
    delay(100);
}

void readDist(int direction)
{
    duration = pulseIn(echoPin[direction], HIGH);
    //Calculate the distance (in cm) based on the speed of sound.
    distance = duration / 58.2;
    if (distance >= maximumRange || distance <= minimumRange){
        /* Send a negative number to computer and Turn LED ON
        to indicate "out of range" */
        Serial.println("Sonar 1: -1");//testing
        digitalWrite(LEDPin, HIGH);
    } else {
        /* Send the distance to the computer using Serial protocol, and
        turn LED OFF to indicate successful reading. */
        if(distance <= 61)
        {
            deg = direction * 45;
            Serial.print("Sonar ");
            Serial.print(direction);
            Serial.print(": ");
            Serial.println(distance);
            //stop and move opposite direction
            //move(cm,degrees);
            //move(20,(deg + (deg >= 180) ? -180 : 180);
        }
        digitalWrite(LEDPin, LOW);
    }
}
