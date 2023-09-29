#include <LiquidCrystal.h>
#include <Servo.h>

// Define the IR sensor, servo motor, and LCD pins
const int irSensorPin = 2;    // IR sensor's signal pin (connect to digital pin 2)
const int servoMotorPin = 3;  // Servo motor control pin (connect to digital pin 3)
const int rs = 8;             // LCD RS pin
const int en = 9;             // LCD Enable pin
const int d4 = 4;             // LCD data pin 4
const int d5 = 5;             // LCD data pin 5
const int d6 = 6;             // LCD data pin 6
const int d7 = 7;             // LCD data pin 7
const int lcdColumns = 16;   // Number of columns on the LCD
const int lcdRows = 2;       // Number of rows on the LCD

// Create objects for LCD and servo motor
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo binServo;

bool binOpened = false;  // Flag to track the state of the bin

void setup() {
  // Initialize the serial communication for debugging (optional)
  Serial.begin(9600);

  // Initialize the IR sensor pin as an input
  pinMode(irSensorPin, INPUT);

  // Initialize the servo motor
  binServo.attach(servoMotorPin);

  // Initialize the LCD
  lcd.begin(lcdColumns, lcdRows);

  // Display the initial message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Only plastic");
  lcd.setCursor(0, 1);
  lcd.print("bottles accepted");
}

void loop() {
  // Read the state of the IR sensor
  int irSensorValue = digitalRead(irSensorPin);

  // If the IR sensor detects an object (LOW signal) and the bin is closed
  if (irSensorValue == LOW && !binOpened) {
    // Activate the servo motor to open the bin
    openBin();
    
    // Delay to allow the bin to open (adjust as needed)
    delay(2000); // 2 seconds delay

    // Generate and display a voucher code
    String voucherCode = generateRandomCode();
    displayVoucherCode(voucherCode);

    // Close the bin after displaying the voucher
    closeBin();
  }

  // You can add additional logic or actions here as needed.
}

void openBin() {
  // Set the servo motor angle to open the bin
  binServo.write(90); // Adjust the angle as needed
  binOpened = true;
}

void closeBin() {
  // Set the servo motor angle to close the bin
  binServo.write(0); // Adjust the angle as needed
  binOpened = false;
}

String generateRandomCode() {
  String characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  String code = "";
  for (int i = 0; i < 6; i++) {
    int randomIndex = random(characters.length());
    code += characters.charAt(randomIndex);
  }
  return code;
}

void displayVoucherCode(String code) {
  // Clear the LCD and display the voucher code
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voucher Code:");
  lcd.setCursor(0, 1);
  lcd.print(code);
}
