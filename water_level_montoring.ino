#define TRIG_PIN 9 // Trigger pin of HC-SR04
#define ECHO_PIN 8 // Echo pin of HC-SR04
#define BUZZER_PIN 3 // Pin for buzzer or LED

// Variables to store the duration and distance
long duration;
float distance;
float maxDistance = 30.0; // Maximum distance of water level (e.g., 30 cm for the tank)

void setup() {
// Initialize Serial Monitor for debugging
Serial.begin(9600);

// Define pin modes for HC-SR04 and Buzzer/LED
pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
// Send a 10us pulse to trigger the ultrasonic sensor
digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN, LOW);

// Read the echo pin, which returns the duration of the pulse in microseconds
duration = pulseIn(ECHO_PIN, HIGH);

// Calculate distance in cm (Sound speed: 34300 cm/s, round trip so divide by 2)
distance = (duration * 0.0343) / 2;

// Print distance to the Serial Monitor

Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");

// Check if the water level is below the threshold
if (distance > maxDistance) {
// If water level is low, turn on the buzzer or LED
digitalWrite(BUZZER_PIN, HIGH);
Serial.println("Water level is low! Refill the tank.");
} else {
// Otherwise, turn off the buzzer or LED
digitalWrite(BUZZER_PIN, LOW);
Serial.println("Water level is sufficient.");
}

// Delay for a second before taking another reading
delay(1000);
}