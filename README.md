# MPU6050-3D-Airplane-Visualization-Arduino-Processing-
Welcome to the official GitHub repository for the **MPU6050 IMU 3D Visualization** project! This repository contains all the necessary source codes (Arduino `.ino` and Processing `.pde`) along with the 3D model required to build a real-time orientation tracking visualizer using digital signal processing (DSP) and sensor fusion algorithms.
🎥 Watch the Full Tutorial on YouTube

If you haven't seen the step-by-step tutorial and theory breakdown yet, check out the full video here:

👉 Watch the Full Tutorial on YouTube (https://www.youtube.com/watch?v=QL6LTxVpbis)

🛠️ Components Required

To build this project, you will need the following hardware components:

    Arduino Uno / Nano (or any compatible microcontroller)

    MPU-6050 IMU Module (GY-521)

    Jumper Wires & Breadboard

🔌 Circuit Wiring Diagram
Connect the MPU-6050 module to your Arduino as follows:
MPU-6050 (GY-521)  Arduino Uno / Nano  Note
VCC                         5V         Module includes built-in 3.3V regulator
GND                         GND        Ground connection
SCL                         A5         I2C Clock Line
SDA                         A4         I2C Data Line

💻 Software Required

    Arduino IDE: For uploading the sensor reading and filter code to the Arduino.

    Processing IDE (v3 or v4): For rendering the real-time 3D airplane visualizer.

🚀 How to Use the Code
Step 1: Arduino Setup

    Open the .ino file in the Arduino IDE.

    Connect your Arduino board to your computer via USB.

    Select your Board and correct COM Port under Tools menu.

    Set the Serial Monitor baud rate to 115200 baud if testing.

    Click Upload.

    Important: Note down the exact COM Port number your Arduino is connected to (e.g., COM7).

Step 2: Processing Setup

    Open the .pde file in the Processing IDE.

    Ensure the 3D model file (F-16C.obj) is saved inside the data folder of your Processing sketch folder.

    In the Processing code, locate the serial port connection line:
    Java

    myPort = new Serial(this, "COM7", 115200);

    Change "COM7" to match your Arduino's actual COM Port.

    Click the Run (Play) button in Processing.

    Move the MPU-6050 sensor, and watch the 3D airplane model rotate in real-time with smooth filtering!

✨ Key Features Implemented

    Hardware DLPF: Digital Low-Pass Filter enabled via I2C register configuration.

    Software IIR Filter: Infinite Impulse Response filter to eliminate vibration spikes.

    Complementary Filter: Combines Gyroscope fast response and Accelerometer long-term stability.

    Gimbal Lock Prevention: Proper Euler angle rotation sequence (Yaw -> Pitch -> Roll).

🤝 Support the Channel

If you found this repository and project helpful, please consider supporting the channel:

    👍 LIKE the video on YouTube

    🔔 SUBSCRIBE to EC TUTO

    💬 Drop a comment if you have questions or project suggestions!

Happy Building! 🛠️
