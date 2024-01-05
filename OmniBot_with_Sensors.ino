#include <AFMotor.h> 
#include <Servo.h>

Servo myservo; //servo
int pos = 0; //servo position

AF_DCMotor motor1(1); //Front Left Wheel
AF_DCMotor motor2(2); //Back Left Wheel
AF_DCMotor motor3(3); //Front Right Wheel
AF_DCMotor motor4(4); //Back Right Wheel

String readString;
char character;

//PIR sensor
int inputPin = A5;//input pin
int pirState = LOW;//assuming no motion detected
int val = 0;//variable for reading the pin status

//Flame sensor
const int flamePin = A4;//input pin
int Flame = HIGH;//flame

//Smoke sensor
int smokeA3 = A3;//input pin
int sensorThres = 275;//threshold value

//ultrasonic
#define echoPin A2 //pin Echo of HC-SR04
#define trigPin A1 //pin Trig of HC-SR04
// defines variables
long duration; //duration of sound wave travel
int distance; //distance measurement


void setup() {
pinMode(2, OUTPUT);//LEDs
digitalWrite(2, LOW);
  
    myservo.attach(10);// servo on pin 10
    Serial.begin(9600);

    //Motor Speed
    motor1.setSpeed(250);
    motor2.setSpeed(250);
    motor3.setSpeed(250);
    motor4.setSpeed(250);
    
    //PIR
    pinMode(A5, INPUT);//sensor input

    //Flame
    pinMode(flamePin, INPUT);//sensor input

     //smoke
    pinMode(smokeA3, INPUT);//sensor input

     //ultrasonic
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  Serial.begin(9600);
}

void loop() {
int analogSensor = analogRead(smokeA3);
String PIR;
String smoke;
String fire; 
    if (Serial.available() > 0) {
        int input = Serial.read();

        switch (input) {
        case 'w':
            motor1.run(FORWARD);
            motor2.run(FORWARD);
            motor3.run(FORWARD);
            motor4.run(FORWARD);
            break;
        case 's':
            motor1.run(BACKWARD);
            motor2.run(BACKWARD);
            motor3.run(BACKWARD);
            motor4.run(BACKWARD);
            break;
        case 'a':
            motor1.run(BACKWARD);
            motor2.run(FORWARD);
            motor3.run(FORWARD);
            motor4.run(BACKWARD);
            break;
        case 'd':
            motor1.run(FORWARD);
            motor2.run(BACKWARD);
            motor3.run(BACKWARD);
            motor4.run(FORWARD);
            break;
        case 'q':
            motor1.run(RELEASE);
            motor2.run(FORWARD);
            motor3.run(FORWARD);
            motor4.run(RELEASE);
            break;
        case 'e':
            motor1.run(FORWARD);
            motor2.run(RELEASE);
            motor3.run(RELEASE);
            motor4.run(FORWARD);
            break;
        case 'z':
            motor1.run(BACKWARD);
            motor2.run(RELEASE);
            motor3.run(RELEASE);
            motor4.run(BACKWARD);
            break;
        case 'c':
            motor1.run(RELEASE);
            motor2.run(BACKWARD);
            motor3.run(BACKWARD);
            motor4.run(RELEASE);
            break;
        case 'r':
            motor1.run(BACKWARD);
            motor2.run(BACKWARD);
            motor3.run(FORWARD);
            motor4.run(FORWARD);
            break;
        case 'f':
            motor1.run(FORWARD);
            motor2.run(FORWARD);
            motor3.run(BACKWARD);
            motor4.run(BACKWARD);
            break;
        case 'x':
            motor1.run(RELEASE);
            motor2.run(RELEASE);
            motor3.run(RELEASE);
            motor4.run(RELEASE);
            break;
        case 'j':
            myservo.write(135);
            break;
        case 'k':
            myservo.write(90);
            break;
        case 'l':
            myservo.write(45);
            break;
        case 'p':
            digitalWrite(2, HIGH);
            break;
        case 'o':
            digitalWrite(2, LOW);
            break;
        case 't':
        //Ultrasonic
            digitalWrite(trigPin, LOW);
            delayMicroseconds(2);
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);
            duration = pulseIn(echoPin, HIGH);
            distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
            Serial.println(String(distance));
            Serial.println("cm ");
            break;
        case 'u':
        //smoke
            Serial.print("Pin A3: ");
            Serial.println(analogSensor);
            if (analogSensor > sensorThres)
            {
              //digitalWrite(redLed, HIGH);
              //digitalWrite(greenLed, LOW);
              //tone(buzzer, 1000, 200);
              smoke="Smoke Detected! ";
            }
            else
            {
              //digitalWrite(redLed, LOW);
              //digitalWrite(greenLed, HIGH);
              //noTone(buzzer);
              smoke="No Smoke";
            }Serial.println(smoke);
            break;
        case 'i':
        //flame
            Flame = digitalRead(flamePin);
            if (Flame== LOW)
            {
              fire="Fire Detected! ";
              //digitalWrite(Pin, HIGH);
            }
            else
            {
              fire="No Fire";
            // digitalWrite(Pin, LOW);
            }Serial.println(fire);
            break;    
        }
     }

//PIR            
val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH){
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
}
