#include <Wire.h>

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050

// Variables for Software DSP (Low-Pass Filter)
float f_accel_x = 0, f_accel_y = 0, f_accel_z = 0;
float f_gyro_x = 0, f_gyro_y = 0, f_gyro_z = 0;

// Alpha value for Low-Pass Filter (0.0 to 1.0)
// Lower value = smoother but slightly slower response
const float ALPHA = 0.2; 

// Variables for final angles
float roll = 0.0;
float pitch = 0.0;
float yaw = 0.0;

// Time tracking
unsigned long loop_timer;

void setup() {
  // Serial.begin(baudRate)
  Serial.begin(115200);
  
  // Wire.begin()
  Wire.begin();

  // 1. Wake up the MPU-6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // Power Management register
  Wire.write(0x00); // Wake up
  Wire.endTransmission(true);

  // 2. Enable Hardware DSP (Digital Low Pass Filter)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1A); // CONFIG Register Address
  Wire.write(0x03); // 0x03 = DLPF Level 3 (Bandwidth ~42Hz) to reduce sensor noise
  Wire.endTransmission(true);

  // micros() returns microseconds since start
  loop_timer = micros();
}

void loop() {
  // 1. Request Data from Sensor
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // Start register for Accel
  Wire.endTransmission(false);
  
  // requestFrom(address, quantity, stop)
  Wire.requestFrom(MPU_ADDR, 14, true);

  // -------------------------------------------------------------------
  // ERROR CHECK: If wires are loose or disconnected, stop calculating
  if (Wire.available() < 14) {
    Serial.println("Error: MPU6050 not connected properly.");
    delay(1000);
    return; // Restart the loop
  }
  // -------------------------------------------------------------------

  // 2. Read Raw Data
  int16_t AcX = Wire.read() << 8 | Wire.read();
  int16_t AcY = Wire.read() << 8 | Wire.read();
  int16_t AcZ = Wire.read() << 8 | Wire.read();
  int16_t Tmp = Wire.read() << 8 | Wire.read(); // Temperature (not used)
  int16_t GyX = Wire.read() << 8 | Wire.read();
  int16_t GyY = Wire.read() << 8 | Wire.read();
  int16_t GyZ = Wire.read() << 8 | Wire.read();

  // 3. Convert to physical units (g for Accel, degrees/sec for Gyro)
  float accel_x = AcX / 16384.0;
  float accel_y = AcY / 16384.0;
  float accel_z = AcZ / 16384.0;
  
  float gyro_x = GyX / 131.0;
  float gyro_y = GyY / 131.0;
  float gyro_z = GyZ / 131.0;

  // 4. APPLY SOFTWARE DSP (IIR Low-Pass Filter)
  // This smoothly averages the new data with the old data
  f_accel_x = (ALPHA * accel_x) + ((1.0 - ALPHA) * f_accel_x);
  f_accel_y = (ALPHA * accel_y) + ((1.0 - ALPHA) * f_accel_y);
  f_accel_z = (ALPHA * accel_z) + ((1.0 - ALPHA) * f_accel_z);

  f_gyro_x = (ALPHA * gyro_x) + ((1.0 - ALPHA) * f_gyro_x);
  f_gyro_y = (ALPHA * gyro_y) + ((1.0 - ALPHA) * f_gyro_y);
  f_gyro_z = (ALPHA * gyro_z) + ((1.0 - ALPHA) * f_gyro_z);

  // 5. Calculate Accelerometer Angles using FILTERED Data
  // atan2(y, x) -> Returns the angle in radians, convert to degrees
  float accRoll = (atan2(f_accel_y, f_accel_z) * 180.0) / PI;
  float accPitch = -(atan2(f_accel_x, sqrt(f_accel_y * f_accel_y + f_accel_z * f_accel_z)) * 180.0) / PI;

  // 6. Calculate dt (elapsed time in seconds)
  float dt = (micros() - loop_timer) / 1000000.0;
  loop_timer = micros();

  // 7. COMPLEMENTARY FILTER (Combine Filtered Gyro and Filtered Accel data)
  roll = 0.96 * (roll + f_gyro_x * dt) + 0.04 * accRoll;
  pitch = 0.96 * (pitch + f_gyro_y * dt) + 0.04 * accPitch;
  
  // Yaw relies only on the filtered Z-axis gyro
  yaw = yaw + f_gyro_z * dt; 

  // 8. Print Data for Processing (Format must be strictly "roll,pitch,yaw")
  // Serial.print(value)
  Serial.print(roll);
  Serial.print(",");
  Serial.print(pitch);
  Serial.print(",");
  
  // Serial.println(value)
  Serial.println(yaw);

  // delay(milliseconds) -> Ensure steady loop frequency
  delay(10);
}
