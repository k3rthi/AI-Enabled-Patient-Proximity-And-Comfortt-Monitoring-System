#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define TRIG 5
#define ECHO 18
#define BUZZER 23

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Try 0x27 first. If LCD not showing, change to 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- AI (simple learning) ----------------
float meanT = 0, meanH = 0, meanD = 0;
float varT  = 1, varH  = 1, varD  = 1;
int aiCount = 0;
// ------------------------------------------------------

unsigned long outStart = 0;
bool patientOut = false;

long getDistance()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 25000);
  if (duration == 0) return 300;

  long distance = duration * 0.034 / 2;
  return distance;
}

// -------- simple online AI anomaly check --------
bool aiAnomaly(float t, float h, float d)
{
  if (isnan(t) || isnan(h)) return false;

  aiCount++;

  float alpha = 0.05;

  meanT += alpha * (t - meanT);
  meanH += alpha * (h - meanH);
  meanD += alpha * (d - meanD);

  varT += alpha * ((t - meanT) * (t - meanT) - varT);
  varH += alpha * ((h - meanH) * (h - meanH) - varH);
  varD += alpha * ((d - meanD) * (d - meanD) - varD);

  if (aiCount < 30) return false;   // learning time

  float zT = abs(t - meanT) / sqrt(varT + 0.01);
  float zH = abs(h - meanH) / sqrt(varH + 0.01);
  float zD = abs(d - meanD) / sqrt(varD + 0.01);

  float score = zT + zH + zD;

  return (score > 6.0);
}
// ------------------------------------------------

void setup()
{
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);

  Wire.begin(21, 22);   // SDA, SCL

  lcd.init();
  lcd.backlight();

  dht.begin();

  lcd.setCursor(0,0);
  lcd.print("System Ready");
  delay(1500);
}

void loop()
{
  long dist = getDistance();
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  bool inBed = dist < 80;

  bool badComfort = false;
  if (!isnan(temp) && !isnan(hum))
  {
    if (temp > 30 || hum > 75)
      badComfort = true;
  }

  bool aiAlert = aiAnomaly(temp, hum, dist);

  // patient out logic
  if (!inBed)
  {
    if (outStart == 0)
      outStart = millis();

    if (millis() - outStart > 10000)
      patientOut = true;
  }
  else
  {
    outStart = 0;
    patientOut = false;
  }

  lcd.clear();

  if (patientOut)
  {
    lcd.setCursor(0,0);
    lcd.print("PATIENT OUT");
    lcd.setCursor(0,1);
    lcd.print("ALERT");

    digitalWrite(BUZZER, HIGH);
  }
  else if (aiAlert)
  {
    lcd.setCursor(0,0);
    lcd.print("AI ALERT");
    lcd.setCursor(0,1);
    lcd.print("ENV CHANGE");

    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
  }
  else if (badComfort)
  {
    lcd.setCursor(0,0);
    lcd.print("BAD COMFORT");
    lcd.setCursor(0,1);

    if (!isnan(temp))
    {
      lcd.print("T:");
      lcd.print(temp,1);
      lcd.print(" ");
    }

    if (!isnan(hum))
    {
      lcd.print("H:");
      lcd.print(hum,0);
    }

    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("PATIENT IN");
    lcd.setCursor(0,1);
    lcd.print("OK");

    digitalWrite(BUZZER, LOW);
  }

  delay(1000);
}