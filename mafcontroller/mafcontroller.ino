#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 32

#define OLED_ADDR   0x3C

const int mafPin = A0;
const int tempPin = A1;

// MAF sensor voltage to value table
const int CONVERSION_TABLE_SIZE = 128;

/*
const float conversionVoltageTable[CONVERSION_TABLE_SIZE] = {
    0.00, 0.04, 0.08, 0.12, 0.16, 0.20, 0.23, 0.27, 0.31, 0.35, 0.39, 0.43, 0.47, 0.51, 0.55, 0.59,
    0.63, 0.66, 0.70, 0.74, 0.78, 0.82, 0.86, 0.90, 0.94, 0.98, 1.02, 1.05, 1.09, 1.13, 1.17, 1.21,
    1.25, 1.29, 1.33, 1.37, 1.41, 1.45, 1.48, 1.52, 1.56, 1.60, 1.64, 1.68, 1.72, 1.76, 1.80, 1.84,
    1.88, 1.91, 1.95, 1.99, 2.03, 2.07, 2.11, 2.15, 2.19, 2.23, 2.27, 2.30, 2.34, 2.38, 2.42, 2.46,
    2.50, 2.54, 2.58, 2.62, 2.66, 2.70, 2.73, 2.77, 2.81, 2.85, 2.89, 2.93, 2.97, 3.01, 3.05, 3.09,
    3.13, 3.16, 3.20, 3.24, 3.28, 3.32, 3.36, 3.40, 3.44, 3.48, 3.52, 3.55, 3.59, 3.63, 3.67, 3.71,
    3.75, 3.79, 3.83, 3.87, 3.91, 3.95, 3.98, 4.02, 4.06, 4.10, 4.14, 4.18, 4.22, 4.26, 4.30, 4.34,
    4.38, 4.41, 4.45, 4.49, 4.53, 4.57, 4.61, 4.65, 4.69, 4.73, 4.77, 4.80, 4.84, 4.88, 4.92, 4.96
};

const float conversionValueTable[CONVERSION_TABLE_SIZE] = {
    -34.5, -32.5, -30.7, -29.0, -27.0, -25.5, -23.7, -22.0, -20.5, -19.0, -17.5, -16.2, -14.7, -13.5, -12.2, -11.2,
    -10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -2.7, -1.7, -0.5, 0.5, 1.8, 2.8, 3.8, 5.0, 6.0,
    7.0, 8.0, 9.0, 10.0, 11.3, 12.3, 13.5, 15.0, 16.3, 17.5, 19.0, 20.5, 22.0, 23.8, 25.3, 27.0,
    28.8, 30.5, 32.5, 34.3, 36.3, 38.5, 40.5, 42.8, 44.4, 46.3, 48.5, 51.0, 53.8, 56.3, 59.0, 62.0,
    65.0, 68.0, 71.3, 74.5, 78.0, 81.5, 85.3, 89.0, 92.8, 96.8, 101.0, 105.3, 109.5, 114.0, 118.8, 123.5,
    128.3, 133.5, 138.8, 144.3, 149.8, 155.8, 162.0, 168.3, 175.0, 181.8, 188.8, 196.3, 203.8, 211.8, 219.8, 228.3,
    236.8, 245.8, 255.0, 264.5, 274.5, 284.8, 295.5, 306.8, 318.0, 329.8, 341.8, 354.3, 367.3, 380.5, 394.3, 408.5,
    423.3, 438.3, 453.8, 470.0, 486.8, 504.0, 522.0, 540.5, 559.8, 579.8, 600.5, 621.8, 643.8, 666.5, 689.8, 713.5
};

float voltageToValue(float voltage) {
  if (voltage <= conversionVoltageTable[0]) return conversionValueTable[0];
  if (voltage >= conversionVoltageTable[CONVERSION_TABLE_SIZE - 1]) return conversionValueTable[CONVERSION_TABLE_SIZE - 1];
  
  for (int i = 1; i < CONVERSION_TABLE_SIZE; i++) {
    if (voltage <= conversionVoltageTable[i]) {
      return interpolate(voltage, conversionVoltageTable[i-1], conversionValueTable[i-1], conversionVoltageTable[i], conversionValueTable[i]);
    }
  }
  return 0;
}

*/

float interpolate(float x, float x0, float y0, float x1, float y1) {
  return y0 + (x - x0) * ((y1 - y0) / (x1 - x0));
}

float voltageToValue(float voltage) {
  if (voltage <= 0.00) return -34.5;
  if (voltage <= 0.04) return interpolate(voltage, 0.00, -34.5, 0.04, -32.5);
  if (voltage <= 0.08) return interpolate(voltage, 0.04, -32.5, 0.08, -30.7);
  if (voltage <= 0.12) return interpolate(voltage, 0.08, -30.7, 0.12, -29.0);
  if (voltage <= 0.16) return interpolate(voltage, 0.12, -29.0, 0.16, -27.0);
  if (voltage <= 0.20) return interpolate(voltage, 0.16, -27.0, 0.20, -25.5);
  if (voltage <= 0.23) return interpolate(voltage, 0.20, -25.5, 0.23, -23.7);
  if (voltage <= 0.27) return interpolate(voltage, 0.23, -23.7, 0.27, -22.0);
  if (voltage <= 0.31) return interpolate(voltage, 0.27, -22.0, 0.31, -20.5);
  if (voltage <= 0.35) return interpolate(voltage, 0.31, -20.5, 0.35, -19.0);
  if (voltage <= 0.39) return interpolate(voltage, 0.35, -19.0, 0.39, -17.5);
  if (voltage <= 0.43) return interpolate(voltage, 0.39, -17.5, 0.43, -16.2);
  if (voltage <= 0.47) return interpolate(voltage, 0.43, -16.2, 0.47, -14.7);
  if (voltage <= 0.51) return interpolate(voltage, 0.47, -14.7, 0.51, -13.5);
  if (voltage <= 0.55) return interpolate(voltage, 0.51, -13.5, 0.55, -12.2);
  if (voltage <= 0.59) return interpolate(voltage, 0.55, -12.2, 0.59, -11.2);
  if (voltage <= 0.63) return interpolate(voltage, 0.59, -11.2, 0.63, -10.0);
  if (voltage <= 0.66) return interpolate(voltage, 0.63, -10.0, 0.66, -9.0);
  if (voltage <= 0.70) return interpolate(voltage, 0.66, -9.0, 0.70, -8.0);
  if (voltage <= 0.74) return interpolate(voltage, 0.70, -8.0, 0.74, -7.0);
  if (voltage <= 0.78) return interpolate(voltage, 0.74, -7.0, 0.78, -6.0);
  if (voltage <= 0.82) return interpolate(voltage, 0.78, -6.0, 0.82, -5.0);
  if (voltage <= 0.86) return interpolate(voltage, 0.82, -5.0, 0.86, -4.0);
  if (voltage <= 0.90) return interpolate(voltage, 0.86, -4.0, 0.90, -2.7);
  if (voltage <= 0.94) return interpolate(voltage, 0.90, -2.7, 0.94, -1.7);
  if (voltage <= 0.98) return interpolate(voltage, 0.94, -1.7, 0.98, -0.5);
  if (voltage <= 1.02) return interpolate(voltage, 0.98, -0.5, 1.02, 0.5);
  if (voltage <= 1.05) return interpolate(voltage, 1.02, 0.5, 1.05, 1.8);
  if (voltage <= 1.09) return interpolate(voltage, 1.05, 1.8, 1.09, 2.8);
  if (voltage <= 1.13) return interpolate(voltage, 1.09, 2.8, 1.13, 3.8);
  if (voltage <= 1.17) return interpolate(voltage, 1.13, 3.8, 1.17, 5.0);
  if (voltage <= 1.21) return interpolate(voltage, 1.17, 5.0, 1.21, 6.0);
  if (voltage <= 1.25) return interpolate(voltage, 1.21, 6.0, 1.25, 7.0);
  if (voltage <= 1.29) return interpolate(voltage, 1.25, 7.0, 1.29, 8.0);
  if (voltage <= 1.33) return interpolate(voltage, 1.29, 8.0, 1.33, 9.0);
  if (voltage <= 1.37) return interpolate(voltage, 1.33, 9.0, 1.37, 10.0);
  if (voltage <= 1.41) return interpolate(voltage, 1.37, 10.0, 1.41, 11.3);
  if (voltage <= 1.45) return interpolate(voltage, 1.41, 11.3, 1.45, 12.3);
  if (voltage <= 1.48) return interpolate(voltage, 1.45, 12.3, 1.48, 13.5);
  if (voltage <= 1.52) return interpolate(voltage, 1.48, 13.5, 1.52, 15.0);
  if (voltage <= 1.56) return interpolate(voltage, 1.52, 15.0, 1.56, 16.3);
  if (voltage <= 1.60) return interpolate(voltage, 1.56, 16.3, 1.60, 17.5);
  if (voltage <= 1.64) return interpolate(voltage, 1.60, 17.5, 1.64, 19.0);
  if (voltage <= 1.68) return interpolate(voltage, 1.64, 19.0, 1.68, 20.5);
  if (voltage <= 1.72) return interpolate(voltage, 1.68, 20.5, 1.72, 22.0);
  if (voltage <= 1.76) return interpolate(voltage, 1.72, 22.0, 1.76, 23.8);
  if (voltage <= 1.80) return interpolate(voltage, 1.76, 23.8, 1.80, 25.3);
  if (voltage <= 1.84) return interpolate(voltage, 1.80, 25.3, 1.84, 27.0);
  if (voltage <= 1.88) return interpolate(voltage, 1.84, 27.0, 1.88, 28.8);
  if (voltage <= 1.91) return interpolate(voltage, 1.88, 28.8, 1.91, 30.5);
  if (voltage <= 1.95) return interpolate(voltage, 1.91, 30.5, 1.95, 32.5);
  if (voltage <= 1.99) return interpolate(voltage, 1.95, 32.5, 1.99, 34.3);
  if (voltage <= 2.03) return interpolate(voltage, 1.99, 34.3, 2.03, 36.3);
  if (voltage <= 2.07) return interpolate(voltage, 2.03, 36.3, 2.07, 38.5);
  if (voltage <= 2.11) return interpolate(voltage, 2.07, 38.5, 2.11, 40.3);
  if (voltage <= 2.15) return interpolate(voltage, 2.11, 40.3, 2.15, 42.3);
  if (voltage <= 2.19) return interpolate(voltage, 2.15, 42.3, 2.19, 44.5);
  if (voltage <= 2.23) return interpolate(voltage, 2.19, 44.5, 2.23, 46.8);
  if (voltage <= 2.27) return interpolate(voltage, 2.23, 46.8, 2.27, 49.0);
  if (voltage <= 2.31) return interpolate(voltage, 2.27, 49.0, 2.31, 51.0);
  if (voltage <= 2.34) return interpolate(voltage, 2.31, 51.0, 2.34, 52.8);
  if (voltage <= 2.38) return interpolate(voltage, 2.34, 52.8, 2.38, 55.0);
  if (voltage <= 2.42) return interpolate(voltage, 2.38, 55.0, 2.42, 57.2);
  if (voltage <= 2.46) return interpolate(voltage, 2.42, 57.2, 2.46, 59.5);
  if (voltage <= 2.50) return interpolate(voltage, 2.46, 59.5, 2.50, 61.8);
  if (voltage <= 2.54) return interpolate(voltage, 2.50, 61.8, 2.54, 64.0);
  if (voltage <= 2.58) return interpolate(voltage, 2.54, 64.0, 2.58, 66.5);
  if (voltage <= 2.62) return interpolate(voltage, 2.58, 66.5, 2.62, 69.0);
  if (voltage <= 2.66) return interpolate(voltage, 2.62, 69.0, 2.66, 71.5);
  if (voltage <= 2.70) return interpolate(voltage, 2.66, 71.5, 2.70, 74.0);
  if (voltage <= 2.74) return interpolate(voltage, 2.70, 74.0, 2.74, 76.3);
  if (voltage <= 2.78) return interpolate(voltage, 2.74, 76.3, 2.78, 78.8);
  if (voltage <= 2.82) return interpolate(voltage, 2.78, 78.8, 2.82, 81.3);
  if (voltage <= 2.86) return interpolate(voltage, 2.82, 81.3, 2.86, 84.0);
  if (voltage <= 2.89) return interpolate(voltage, 2.86, 84.0, 2.89, 86.5);
  if (voltage <= 2.93) return interpolate(voltage, 2.89, 86.5, 2.93, 89.3);
  if (voltage <= 2.97) return interpolate(voltage, 2.93, 89.3, 2.97, 92.0);
  if (voltage <= 3.01) return interpolate(voltage, 2.97, 92.0, 3.01, 94.8);
  if (voltage <= 3.05) return interpolate(voltage, 3.01, 94.8, 3.05, 97.8);
  if (voltage <= 3.09) return interpolate(voltage, 3.05, 97.8, 3.09, 100.8);
  if (voltage <= 3.13) return interpolate(voltage, 3.09, 100.8, 3.13, 103.8);
  if (voltage <= 3.17) return interpolate(voltage, 3.13, 103.8, 3.17, 107.0);
  if (voltage <= 3.21) return interpolate(voltage, 3.17, 107.0, 3.21, 110.3);
  if (voltage <= 3.25) return interpolate(voltage, 3.21, 110.3, 3.25, 113.7);
  if (voltage <= 3.29) return interpolate(voltage, 3.25, 113.7, 3.29, 117.2);
  if (voltage <= 3.32) return interpolate(voltage, 3.29, 117.2, 3.32, 120.5);
  if (voltage <= 3.36) return interpolate(voltage, 3.32, 120.5, 3.36, 123.8);
  if (voltage <= 3.40) return interpolate(voltage, 3.36, 123.8, 3.40, 127.2);
  if (voltage <= 3.44) return interpolate(voltage, 3.40, 127.2, 3.44, 130.7);
  if (voltage <= 3.48) return interpolate(voltage, 3.44, 130.7, 3.48, 134.3);
  if (voltage <= 3.52) return interpolate(voltage, 3.48, 134.3, 3.52, 137.8);
  if (voltage <= 3.56) return interpolate(voltage, 3.52, 137.8, 3.56, 141.5);
  if (voltage <= 3.60) return interpolate(voltage, 3.56, 141.5, 3.60, 145.2);
  if (voltage <= 3.64) return interpolate(voltage, 3.60, 145.2, 3.64, 148.7);
  if (voltage <= 3.68) return interpolate(voltage, 3.64, 148.7, 3.68, 152.3);
  if (voltage <= 3.72) return interpolate(voltage, 3.68, 152.3, 3.72, 156.0);
  if (voltage <= 3.76) return interpolate(voltage, 3.72, 156.0, 3.76, 159.7);
  if (voltage <= 3.80) return interpolate(voltage, 3.76, 159.7, 3.80, 163.3);
  if (voltage <= 3.84) return interpolate(voltage, 3.80, 163.3, 3.84, 166.7);
  if (voltage <= 3.88) return interpolate(voltage, 3.84, 166.7, 3.88, 170.2);
  if (voltage <= 3.91) return interpolate(voltage, 3.88, 170.2, 3.91, 173.7);
  if (voltage <= 3.95) return interpolate(voltage, 3.91, 173.7, 3.95, 177.0);
  if (voltage <= 3.99) return interpolate(voltage, 3.95, 177.0, 3.99, 180.3);
  if (voltage <= 4.03) return interpolate(voltage, 3.99, 180.3, 4.03, 183.7);
  if (voltage <= 4.07) return interpolate(voltage, 4.03, 183.7, 4.07, 187.2);
  if (voltage <= 4.11) return interpolate(voltage, 4.07, 187.2, 4.11, 190.7);
  if (voltage <= 4.15) return interpolate(voltage, 4.11, 190.7, 4.15, 194.0);
  if (voltage <= 4.19) return interpolate(voltage, 4.15, 194.0, 4.19, 197.3);
  if (voltage <= 4.23) return interpolate(voltage, 4.19, 197.3, 4.23, 200.5);
  if (voltage <= 4.27) return interpolate(voltage, 4.23, 200.5, 4.27, 203.8);
  if (voltage <= 4.31) return interpolate(voltage, 4.27, 203.8, 4.31, 207.3);
  if (voltage <= 4.34) return interpolate(voltage, 4.31, 207.3, 4.34, 210.5);
  if (voltage <= 4.38) return interpolate(voltage, 4.34, 210.5, 4.38, 213.7);
  if (voltage <= 4.42) return interpolate(voltage, 4.38, 213.7, 4.42, 217.0);
  if (voltage <= 4.46) return interpolate(voltage, 4.42, 217.0, 4.46, 220.3);
  if (voltage <= 4.50) return interpolate(voltage, 4.46, 220.3, 4.50, 223.7);
  if (voltage <= 4.54) return interpolate(voltage, 4.50, 223.7, 4.54, 227.2);
  if (voltage <= 4.58) return interpolate(voltage, 4.54, 227.2, 4.58, 230.5);
  if (voltage <= 4.62) return interpolate(voltage, 4.58, 230.5, 4.62, 233.8);
  if (voltage <= 4.66) return interpolate(voltage, 4.62, 233.8, 4.66, 237.0);
  if (voltage <= 4.70) return interpolate(voltage, 4.66, 237.0, 4.70, 240.2);
  if (voltage <= 4.74) return interpolate(voltage, 4.70, 240.2, 4.74, 243.5);
  if (voltage <= 4.77) return interpolate(voltage, 4.74, 243.5, 4.77, 246.8);
  if (voltage <= 4.81) return interpolate(voltage, 4.77, 246.8, 4.81, 250.2);
  if (voltage <= 4.85) return interpolate(voltage, 4.81, 250.2, 4.85, 253.7);
  if (voltage <= 4.89) return interpolate(voltage, 4.85, 253.7, 4.89, 257.0);
  if (voltage <= 4.93) return interpolate(voltage, 4.89, 257.0, 4.93, 260.3);
  if (voltage <= 4.97) return interpolate(voltage, 4.93, 260.3, 4.97, 263.7);
  if (voltage <= 5.00) return interpolate(voltage, 4.97, 263.7, 5.00, 267.0);

  // Extrapolate for voltage > 5.00 if needed
  return 267.0 + (voltage - 5.00) * ((267.0 - 263.7) / (5.00 - 4.97));
}

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}

void loop() {
  int mafRaw = analogRead(mafPin);
  
  float mafVoltage = mafRaw * (5.0 / 4096.0);
  
  float mafValue_kg_h = voltageToValue(mafVoltage);
  float mafValue_g_s = (mafValue_kg_h * 1000.0) / (60 * 60);

  display.clearDisplay();
  display.setCursor(0,0);

  display.print(mafValue_g_s, 2);
  display.println(" g");
  
  display.print(mafValue_kg_h, 2);
  display.println(" kg");
  
  display.display();
  
  delay(100);
}