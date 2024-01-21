// Purpose of code: This arduino code will emulate a burglar alarm system using object oriented programming. This piece of code will make use of classes
                  //that represent physcial objects in the system, and then insantiate these classes inside the 'Session' class which is used to manage
                  //the entire system. The 'Actuator' class will be in charge of controlling the buzzer, solenoid, and the LED's. The 'Buzzer' class will
                  //be in charge of sounding the alarm as well as inheriting the 'Beep()' function from the 'Actuator' class. The 'Sensor' class will be managing
                  //as well as controlling the magnetic contacts, PIR sensor, and the button. The 'MatlabComms' is responsible for sending and receiving information
                  //from MATLAB. The 'Session' class will be used to manage the entire system, as well as to insantiate the other classes within itself.

// Authors: Ignacio Vegas De Los Rios, Zaid Daghash, Santosh Somayajula, Harsh Machhiyava, Aleksander Siwiaszczyk (Group: 3)

// Written: 01/05/2023

class Actuator{ //Controls the buzzer, solenoid, and LED's
  private:
    int ActuatorPin;
  public:
    Actuator(int pin){
      ActuatorPin = pin;
      pinMode(ActuatorPin, OUTPUT);   
    }
    void turnON(){
      digitalWrite(ActuatorPin, HIGH);
    }
    void turnOFF(){
      digitalWrite(ActuatorPin, LOW);
    }
    void Beep(){
      tone(ActuatorPin,150);
      delay(500);
      noTone(ActuatorPin);
      delay(500);
    }
};

class Buzzer : public Actuator{ //Used for triggering the alarm and inherits the 'Beep()' function from the 'Actuator' class
  private:
      int buzzerPIN;
      unsigned long tik = 0;
  public:
      Buzzer(int buzzerpin) : Actuator(buzzerpin){
        buzzerPIN = buzzerpin;
        pinMode(buzzerPIN,OUTPUT);
      }
      void TriggerBuzzer(){
        Actuator led(36);
        tik = millis();
        while(millis() - tik < 400){
          if(millis() - tik < 200){
            led.turnON();
            tone(buzzerPIN,275);
          }
          else{
            led.turnOFF();
            noTone(buzzerPIN);
          }
        }
      }   
};

class Sensor{ //Controls the magnetic contacts, PIR sensor, and the button
  private:
    int sensorPin;
    int sensorStatus;
  public:
    Sensor(int pin){
      sensorPin = pin;
      if(pin==34){
      pinMode(sensorPin, INPUT);
      }
      else{
        pinMode(sensorPin, INPUT_PULLUP);
      }
    }
    int readSensor(){
      sensorStatus = digitalRead(sensorPin);
      return sensorStatus;
    }
};

class MatlabComms{ //Responsible for sending and receiving information from MATLAB
  private:
      char sentChar;
      char receivedChar;
      unsigned int sentInt;
      unsigned int receivedInt;
  public:
      sendChar(char inputChar){
        Serial.print(inputChar);
      }
      char getChar(){
        if(Serial.available()>0){ //Waits until there is input to be read
        receivedChar = Serial.read();
        return receivedChar;
        }
      }
      char wait4Char(){
        while(Serial.available()==0){} //Waits until there is input to be read
        receivedChar = Serial.read();
        return receivedChar;
      }
      sendInt(char sentInt){
        Serial.print(sentInt);
      }
      char getInt(){
        if(Serial.available()>0){ //Checks if there is input to be read
        receivedInt = Serial.read();
        return receivedInt;
        }
      }
      char wait4Int(){
        while(Serial.available()==0){} //Waits until there is input to be read
        receivedInt = Serial.read();
        return receivedInt;
      }
};

class Session{ //Manages the entire system
  //Insantiating 'Sensor' objects
  Sensor contactWindow;
  Sensor contactDoor;
  Sensor PIR;
  Sensor Button;

  //Instantiating 'Actuator' objects
  Actuator solenoid;
  Actuator led[3];

  //Communication
  MatlabComms Coms;

  //Insantiating the buzzer
  Buzzer buzzer;
  
  //Declaring variables
  unsigned long tic = 0;
  int verifyUser = 0;
  unsigned long Timer = 10000;
  int option = 0, LeftOpen;
  int SessionStatus = 2;
  
  public:
      Session():contactWindow(53),contactDoor(44),PIR(34),Button(42),solenoid(32),buzzer(12),led{Actuator(38),Actuator(36),Actuator(9)}{ //Assigning pins
        Serial.flush();
      }

    void systemIdle(){ //Idle state
      buzzer.Beep(); 
      led[0].turnOFF();
      led[1].turnOFF();
      led[2].turnON();
      solenoid.turnOFF();
        option = 0;
        while(SessionStatus == 2){
          option = Coms.wait4Int();
          switch(option){
            case 1: //Active state
              buzzer.Beep();
              verifyUser = 0;
              tic = millis();
              LeftOpen = 0;
              while(millis() - tic < Timer){
                if(Button.readSensor() == LOW){ //Button pressed
                  solenoid.turnON(); //Unlock the door
                }
                if(contactDoor.readSensor() == HIGH || contactWindow.readSensor() == HIGH){ //Checking if the door or window has been left open
                  while(contactDoor.readSensor() == HIGH || contactWindow.readSensor() == HIGH){
                    if(millis() - tic >= Timer){
                        if(contactDoor.readSensor() == HIGH){
                          Coms.sendChar('O');//Door is open
                          LeftOpen = 1;
                        }
                        else{
                          Coms.sendChar('Z');//Window is open
                          LeftOpen = 1;
                        }
                      }
                   }
                  if(contactDoor.readSensor() == LOW && contactWindow.readSensor() == LOW){ //Window and door are closed
                    if(LeftOpen){
                      delay(200);
                      Coms.sendChar('T');
                      solenoid.turnOFF();
                      delay(Timer);
                    }
                    else{
                      delay(200);
                      solenoid.turnOFF();
                    }
                  }
                }
              }
              Coms.sendChar('C');
              SessionStatus = 1;
              systemActive(); //Go into active state
              break;
            case 4: //Changing the timer
              Timer = 0;
              while(Timer == 0){
                Timer = Coms.wait4Int();
                Timer = Timer * 1000;
              }
              break;
            case 6:
              buzzer.Beep();
              delay(1000);
              led[0].turnOFF();
              led[1].turnOFF();
              led[2].turnOFF();
              break;
          }
        }
    }
    void systemActive(){ //Active state
      SessionStatus = 1;
      int verifyPIN = 0;
      int verifyUser = 0;
      buzzer.Beep();
      led[2].turnOFF();
      led[1].turnOFF();
      led[0].turnON();
      
      while(SessionStatus == 1){
        if(PIR.readSensor() == HIGH && verifyUser == 0){ //PIR detects motion
          tic = millis();  
          Coms.sendChar('M'); //Telling MATLAB motion is detected
          verifyUser = Coms.wait4Int();
          if(verifyUser == 1){
            led[2].turnON();
            solenoid.turnON(); //Unlock door
          }
          while(millis() - tic<8000){
          }
          Coms.sendChar('E'); //Telling MATLAB procedure is complete
          led[2].turnOFF();
        }
        if(contactDoor.readSensor() == HIGH && verifyUser == 1){ //User verified by Facial Recognition and the door is opened
          verifyPIN = 0;
          Coms.sendChar('D');
          tic = millis();
          while(!verifyPIN){
            Coms.sendChar('B');
            verifyPIN = Coms.getInt(); 
            if(millis() - tic >= Timer){ //If Timer has passed
              Coms.sendChar('A'); // To MATLAB indicating alarm is sounding
              led[0].turnOFF();
              tic = millis();
              while(verifyPIN != 2){  
                verifyPIN = Coms.getInt();
                while(verifyPIN != 2){
                  verifyPIN = Coms.getInt();
                  if(millis() - tic < 20000){
                    buzzer.TriggerBuzzer(); // Sound the alarm until timer expires or if the correct PIN has been entered
                  }
                }
              }
            }
          }
          SessionStatus = 2;
          systemIdle(); //Go into idle state
        }
        else if(contactDoor.readSensor() == HIGH && verifyUser == 0){ //Person wasn't recognised by facial recognition and the doo has been opened(broken into)
          led[0].turnOFF();
          Coms.sendChar('L');
          tic = millis();
          do{
            buzzer.TriggerBuzzer(); //Trigger the alarm until 20 seconds have passed
          }while(millis() - tic < 20000);
          led[1].turnOFF();
          Coms.sendChar('E');
          SessionStatus = 2;
          systemIdle();
        }
        if(contactWindow.readSensor() == HIGH){ //Window has been opened
          Coms.sendChar('W');
          tic = millis();
          do{
            buzzer.TriggerBuzzer(); //Trigger the alarm until 20 seconds have passed
          }while(millis() - tic < 20000);
          led[0].turnOFF();
          Coms.sendChar('E'); 
          SessionStatus = 2;
          systemIdle(); //Go back to idle state
        }
      } 
    }
};

Session BurglarAlarmSession; //Insantiating the session

void setup(){
  Serial.begin(9600);
  BurglarAlarmSession.systemIdle();
}

void loop(){
}
