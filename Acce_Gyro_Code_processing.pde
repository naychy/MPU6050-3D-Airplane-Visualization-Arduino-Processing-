import processing.serial.*;

Serial myPort;
float roll  = 0.0;
float pitch = 0.0;
float yaw   = 0.0;

PShape airplane; // Variable to store the 3D airplane model

void setup() {
  // size(width, height, renderer)
  size(1000, 700, P3D); 
  
  // loadShape(filename)
  airplane = loadShape("F-16C.obj"); 
  
  try {
    // Serial(parent, portName, baudRate)
    myPort = new Serial(this, "COM7", 115200);
    
    // bufferUntil(character)
    myPort.bufferUntil('\n');
  } catch (Exception e) {
    // println(message)
    println("Error: Could not connect to the COM Port.");
  }
}

void draw() {
  // background(red, green, blue)
  background(135, 206, 235); 
  
  lights(); 
  
  // directionalLight(red, green, blue, directionX, directionY, directionZ)
  directionalLight(255, 255, 255, -1, 1, -1); 
  
  // 1. Move the main origin to the exact center of the screen
  // translate(x, y, z)
  translate(width/2, height/2, 0); 
  
  // -------------------------------------------------------------
  // 2. APPLY SENSOR ROTATIONS (Correct Order: Yaw -> Pitch -> Roll)
  // -------------------------------------------------------------

 
  
  // 1st: rotateY(angle) -> YAW (Heading)
  rotateY(radians(yaw));
  
  // 2nd: rotateX(angle) -> PITCH (Elevation)
  rotateX(radians(pitch));
  
  // 3rd: rotateZ(angle) -> ROLL (Bank)
  rotateZ(radians(roll));
  
  // -------------------------------------------------------------
  
  // 3. Draw a small red sphere to mark the TRUE (0,0,0) center point
  // fill(red, green, blue)
  fill(255, 0, 0); 
  
  // noStroke()
  noStroke(); 
  
  // sphere(radius)
  sphere(5); 
  
  // 4. Draw the airplane model
  drawUAV(); 
}

void serialEvent(Serial myPort) {
  // readStringUntil(character)
  String inString = myPort.readStringUntil('\n');
  
  if (inString != null) {
    // trim(string)
    inString = trim(inString); 
    
    // split(string, delimiter)
    // float(stringArray)
    float[] values = float(split(inString, ',')); 
    
    if (values.length >= 3) {
      roll  = values[0];
      pitch = values[1];
      yaw   = values[2];
    }
  }
}

void drawUAV() {
  // pushMatrix()
  pushMatrix();
  
  // scale(percentage_size)
  scale(6.0); 
  
  // Shift the airplane model so its BODY aligns exactly with the red sphere
  // translate(x, y, z)
  translate(50, 0, 50); 
  
  // radians(degrees) converts degree value to radians
  // rotateX(angle) rotates the coordinate system around the X-axis
  rotateX(radians(90));
  
  // shape(shapeObject, x, y)
  shape(airplane, 0, 0); 
  
  // popMatrix()
  popMatrix();
}
