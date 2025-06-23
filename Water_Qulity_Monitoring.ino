#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// LCD Setup (address, columns, rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Use your confirmed address

// DHT11 Setup
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Turbidity Sensor Pin
#define TURBIDITY_PIN A0
int ntu;

void setup() {
  lcd.init();           
  lcd.backlight();      

  // --- Show project title ---
  lcd.setCursor(0, 0);
  lcd.print("Water Quality");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring Sys");
  delay(3000); // Show for 3 seconds
  lcd.clear();

  Serial.begin(9600);   
  dht.begin();          
}

void loop() {
  // Read DHT11
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Read Turbidity sensor
  int turbidityRaw = analogRead(TURBIDITY_PIN);
  float voltage = turbidityRaw * (5.0 / 1023.0);

//  // Estimate NTU (Nephelometric Turbidity Units)
//  float ntu = -1120.4 * voltage * voltage + 5742.3 * voltage - 4352.9;
//  if (ntu < 0) ntu = 0;

  // Convert to Clarity %
  float clarityPercent = map(turbidityRaw, 0, 1023, 100, 0);

  // Debug info
  Serial.print("Temp: "); 
  Serial.print(temp); 
  Serial.print(" C\t");
  Serial.print("Humidity: "); 
  Serial.print(hum); 
  Serial.print(" %\t");
  Serial.print("Turbidity (NTU): "); 
  Serial.print(ntu); 
  Serial.print("\t");
  Serial.print("Clarity: "); 
  Serial.print(clarityPercent); 
  Serial.println(" %");

  // LCD Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:"); 
  lcd.print(temp, 1); 
  lcd.print((char)223); 
  lcd.print("C ");
  lcd.print("H:"); 
  lcd.print(hum, 0); 
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Clarity: ");
  lcd.print(clarityPercent, 0);
  lcd.print("%");

  delay(2000);
}
