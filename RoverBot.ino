#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
  long xcount=0;
  long ycount=0;
  
  int rAngle=0;
  int lAngle=0;
  int lsin=0;
  int rsin=0;
  
void setup()                                 // Built-in initialization block
{
  pinMode(10, INPUT);  pinMode(9, OUTPUT);   // Left IR LED & Receiver
  pinMode(3, INPUT);  pinMode(2, OUTPUT);    // Right IR LED & Receiver
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  Serial.begin (9600);
  
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  servoLeft.attach(11);                      // Attach left signal to pin 13
  servoRight.attach(12);                     // Attach right signal to pin 12
}  
 
void loop()                                  // Main loop auto-repeats
{
  delay(1000);
  Serial.print(ycount);
  Serial.print("  ");
  Serial.println(xcount);
  int irLeft = irDetect(9, 10, 38000);       // Check for object on left
  int irRight = irDetect(2, 3, 38000);       // Check for object on right

  if((irLeft == 0) && (irRight == 0))        // If both sides detect
  {
    tone(4,3500,100);
    delay(200);
    tone(4,3500,100);
    delay(100);
    digitalWrite(8, !irLeft);
    digitalWrite(7, !irRight);
 
    //backward(400);                          // Back up 1 second
    turnLeft(800);                           // Turn left about 120 degrees
  }
   if(irLeft == 0)                       // If only left side detects
  {
    digitalWrite(8, !irLeft);
      tone(4,3500,100);
    delay(100);
    //backward(400);                          // Back up 1 second
    turnRight(265); 
    lAngle +=30;
    rsin +=30;
  }
  else if(irRight == 0)                      // If only right side detects
  {
    tone(4,3500,100);
    delay(100);
    digitalWrite(7, !irRight);

    //backward(400);                          // Back up 1 second
    turnLeft(265); 
    rAngle+=30;
    lsin +=30;
  }
  else                                       // Otherwise, no IR detected
  {
   digitalWrite(7, !irLeft);
   digitalWrite(8, !irRight);
    forward(30);
    
  }
  
   if( abs(rAngle-lAngle)<90 && abs(rAngle-lAngle)>0 ){

    
    if(abs(rAngle-lAngle)==30){
   xcount +=26;
   if((rAngle-lAngle)==30){
    ycount+= 15;
   }
   else if((rAngle-lAngle)==-30){
    ycount+= -15;
   }
    }
    else if (abs(rAngle-lAngle)==60){
    xcount +=15;
     if((rAngle-lAngle)==60){
    ycount+= 26;
   }
    }
   else if ((rAngle-lAngle)==-60){
     ycount+=- 26;
   }
    
    
  }
  else if(abs(rAngle-lAngle)>90 && abs(rAngle-lAngle)<180){
    if(abs(rAngle-lAngle)==120){
       xcount -=30*1.7/2;
    
      if((rAngle-lAngle)==120){
    ycount+= 26;
    }
      else if ((rAngle-lAngle)==-120){
     ycount+=- 26;
   }
  
    }
    else if (abs(rAngle-lAngle)==150)
    xcount -=15;
        if((rAngle-lAngle)==150){
    ycount+= 15;
    }
         else if ((rAngle-lAngle)==-150){
     ycount+=- 15;
   }
  }
  
  else if ((rAngle-lAngle)==0){
    xcount +=30;
    ycount +=0;
  }
  else{
    xcount +=0;
    ycount +=30;
  }



  if(abs(rAngle-lAngle)==180){
    forward(xcount);
    if(ycount>0){
      turnLeft(500);
      forward(ycount);
    }
    else if(ycount<0){
      turnRight(500);
      forward(ycount);
    }
    else{
      servoRight.detach();
    servoLeft.detach();
    }
  }
      if(xcount<=0){
    servoRight.detach();
    servoLeft.detach();
  }

  }


int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}  

void forward(int time)                       // Forward function
{
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  delay(time);                               // Maneuver for time ms
}

void turnLeft(int time)                      // Left turn function
{
  servoLeft.writeMicroseconds(1300);         // Left wheel clockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  delay(time);                               // Maneuver for time ms
}

void turnRight(int time)                     // Right turn function
{
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1700);        // Right wheel counterclockwise
  delay(time);                               // Maneuver for time ms
}

void backward(int time)                      // Backward function
{
  servoLeft.writeMicroseconds(1300);         // Left wheel clockwise
  servoRight.writeMicroseconds(1700);        // Right wheel counterclockwise
  delay(time);                               // Maneuver for time ms
}
