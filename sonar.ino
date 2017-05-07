// code from 
//https://forum.arduino.cc/index.php?topic=89524.0
const int trigPin = 13; 
const int echoPin = 12; 
const int led = 7;

void setup() {
 // initialize serial communication:
 Serial.begin(9600);
 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 digitalWrite(trigPin, LOW);
}

void loop()
{
 // establish variables for duration of the ping, 
 // and the distance result in inches and centimeters:
 long duration, inches, cm;
 
 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);

// https://www.arduino.cc/en/Reference/pulseIn
 duration = pulseIn(echoPin, HIGH);

 // convert the time into a distance
 inches = microsecondsToInches(duration);
 cm = microsecondsToCentimeters(duration);
 
 Serial.println(String(inches) + " inches | " + String(cm) + " cm");

 if (cm < 15) {
   digitalWrite(led, HIGH);
 }
 else {
    digitalWrite(led, LOW);
 }

 delay(500);
}

long microsecondsToInches(long microseconds)
{
 // According to Parallax's datasheet for the PING))), there are
 // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
 // second).  This gives the distance travelled by the ping, outbound
 // and return, so we divide by 2 to get the distance of the obstacle.
 // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
 return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
 // The speed of sound is 340 m/s or 29 microseconds per centimeter.
 // The ping travels out and back, so to find the distance of the
 // object we take half of the distance travelled.
 return microseconds / 29 / 2;
}
