// Decalaring Variables
int motion, door, window, verifyUser = 0;
unsigned long tic = 0, tik = 0;
unsigned long Timer = 10000;
int PIN = 0000;
int STATE = 2;
int verifyPIN = 0;
int option = 0;
int runonce;
int LeftOpen;

// Defining PINS 
#define REDLED 36
#define GREENLED 38
#define Buzzer 12
#define Solenoid 32
#define PIR 34
#define Contacts 44
#define Button 42
#define builtinLED 13
#define Window 53

void setup(){
  Serial.begin(9600);
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED,OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Solenoid, OUTPUT);
  pinMode(PIR,INPUT);
  pinMode(Contacts,INPUT_PULLUP);
  pinMode(Button,INPUT_PULLUP);
  pinMode(Window,INPUT_PULLUP);
  pinMode(builtinLED,OUTPUT);
  digitalWrite(REDLED,LOW);
  digitalWrite(GREENLED,LOW);
  digitalWrite(Solenoid,LOW);
  digitalWrite(builtinLED,LOW);
}

void loop(){
  while(STATE == 1){ // Active state
      if(Serial.available()>0){
         verifyPIN = Serial.read();
         if(verifyPIN == 1){ // If User entered correct PIN
          STATE = 2; // Idle state
         }
      }
      digitalWrite(GREENLED,HIGH); // Green LED is enabled to indicate system is in active state

      // Reading from sensors
      motion = digitalRead(PIR);
      door = digitalRead(Contacts);
      window = digitalRead(Window);
      
      if(motion == HIGH && verifyUser == 0){ // Motion detected
        tic = millis();
        verifyUser = 2;
        Serial.print('M'); // Telling matlab that motion has been detected
        while(verifyUser == 2){ // Not 1 or 0
           if(Serial.available()>0){
              verifyUser = Serial.read();
              if(verifyUser == 1){ //If user has been identified
                digitalWrite(Solenoid,HIGH); //Retract solenoid
              }
           } 
        }
        while(millis()-tic<8000){ //8 second delay for PIR sensor
        }
        Serial.print('E'); // Sending a signal to matlab to indicate the procedure is complete
      }
       
      if(door == HIGH && verifyUser == 1){ // User verified & door opened
        verifyPIN = 0; // Resetting variable
        Serial.print('D'); // To MATLAB indicating door has been opened
        tic = millis();
          while(!verifyPIN){//while correct pin hasn't been entered
              Serial.print('B'); // To MATLAB indicating alarm hasn't been sound yet (NOT A)
              if(Serial.available()>0){
                verifyPIN = Serial.read();// User inputted correct PIN 
              }
              if(millis() - tic >= Timer){ //If Timer has passed
                  Serial.print('A'); // To MATLAB indicating alarm is sounding
                  digitalWrite(GREENLED,LOW); //Turning off the Green LED
                  tic = millis();
                    while(!verifyPIN){  
                      //Serial.flush();
                      if(Serial.available()>0){
                        verifyPIN = Serial.read(); // MATLAB will send a 1 if PIN is correct
                      }
                   
                      if(millis() - tic < 20000){ // Sound the alarm until timer expires
                        Serial.print('A');
                        SoundingAlarm(); // Sounding the alarm function
                      }
                      else{
                        while(!verifyPIN){
                          Serial.print('Y');//to MATLAB indicating timer has expired
                          if(Serial.available()>0){
                            verifyPIN = Serial.read(); // MATLAB will send a 1 if PIN is correct
                          } 
                        }
                      }
                    }
                }   
          }
          digitalWrite(REDLED,LOW); // Turning off the red LED
          STATE = 2; // Returning to idle state
       }
       else if(door == HIGH && verifyUser == 0){ // User NOT verified & door has been broken into
        digitalWrite(GREENLED,LOW); //Turning off the green LED
        Serial.print('L'); // To matlab indicating that a break-in is taking place
        tic = millis(); // Count for 20 seconds
           do{
             SoundingAlarm(); // Sounding the alarm function
           }while(millis() - tic < 20000);
          digitalWrite(REDLED,LOW); // Turning off the red LED
          STATE = 2; // Returning to idle state 
          Serial.print('E'); // Sending a signal to matlab to indicate the procedure is complete
       }
       
       if(window == HIGH){ // Window has been opened
          Serial.print('W'); // To matlab to indicate that the window has been opened.
          tic = millis(); //count for 20 seconds
          do{
             SoundingAlarm(); // Sounding the alarm
          }while(millis() - tic < 20000);
          STATE = 2;
          digitalWrite(GREENLED,LOW);
          Serial.print('E'); // Finished sounding alarm
       }
   }
 while(STATE == 2){ // Idle state
      digitalWrite(GREENLED,LOW); // Turn off the green LED
      digitalWrite(Solenoid,LOW); // Door locked
      if(Serial.available()>0){
          option = Serial.read(); // Choosing option from main menu
          switch(option){
              case 1: // User chooses active case
                STATE = 1;
                verifyUser = 0;
                tic = millis();
                LeftOpen = 0;
                while(millis() - tic < Timer){ // Timer
                    if(digitalRead(Button)==LOW){ // Button pressed
                      digitalWrite(Solenoid,HIGH); // Unlocking door
                    }
                    if(digitalRead(Contacts)==HIGH||digitalRead(Window)==HIGH){//Door or window open
                        while(digitalRead(Contacts)==HIGH||digitalRead(Window)==HIGH){ // While door is not closed
                            if(millis() - tic >= Timer){//Door or Window not closed and timer expired
                              if(digitalRead(Contacts)==HIGH){//Door open
                                Serial.print('O');// Door open;
                                LeftOpen = 1;
                              }
                              else{
                                Serial.print('Z');// Window open
                                LeftOpen = 1;
                              }
                            }
                        }
                        if(digitalRead(Contacts)==LOW && digitalRead(Window)==LOW){
                          if(LeftOpen){//checks if any of the entry points were not closed propperly so it can give a delay
                            delay(200);
                            Serial.print('T');
                            digitalWrite(Solenoid,LOW); // Locking door
                            delay(Timer); // Time for user to leave building
                          }
                          else{
                            delay(200);
                            digitalWrite(Solenoid,LOW); // Locking door
                          }
                        } 
                    }
                 }
                 Serial.print('C');//all entry points have been closed, ready to go to Active
                 tone(Buzzer,150);
                 delay(100);
                 noTone(Buzzer);//sound to indicate it's gone back to active
                 break;
              case 4: // User decides to change timer
                Timer = 0;
                while(Timer == 0){ // Waiting for input
                  if(Serial.available()>0){
                    Timer = Serial.read();
                    Timer = Timer * 1000; //s to ms
                  }
                }
                break;
          }
      }
  }
  Serial.flush();//clearing buffer
}

void SoundingAlarm(){ // Function for sounding the alarm
  tik = millis();
  while(millis()-tik < 400){
    if(millis() - tik < 200){
      digitalWrite(REDLED,HIGH);
      tone(Buzzer,275);
    }
    else{
      digitalWrite(REDLED,LOW);
      noTone(Buzzer);
    }
  }
}
