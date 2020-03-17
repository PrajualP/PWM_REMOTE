int button=12;
int buttonaddress[10]={0,0,0,0,0,1,1,0};
int buttoncommand[10]={0,1,0,1,1,0,0,0};
void setup() {
//  Serial.begin(9600);
  // put your setup code here, to run once:
  //Maintaining 8 th pin high always ( 12 th pin listens )
  pinMode(8,OUTPUT);
  digitalWrite(8, HIGH);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button,INPUT);//Button Input

  
  pinMode(11,OUTPUT);//The IR led Output
  digitalWrite(11, LOW);
//  Serial.print(LOW);
}

void modulatedsignalgenerator(uint32_t microsec){
  //It must break after the specified millisecond
  for(uint32_t tStart = micros();  (micros()-tStart) < microsec;  ){
    digitalWrite(11, HIGH);
//    Serial.print(HIGH);
    delayMicroseconds(8);
    
    digitalWrite(11, LOW);
//    Serial.print(LOW);
    delayMicroseconds(8);
    
  }
}

void leadercodegenerator(){
  //Emit Ir at 38kHz for 9ms
  modulatedsignalgenerator(9000);
  //Sleep for 4.5ms
  digitalWrite(11, LOW);
//  Serial.print(LOW);
  delayMicroseconds(4500);
}

void pulsegenerator(int one_or_zero){

    if(one_or_zero == 0){
      //Emit Ir at 38kHz for 0.6ms
      modulatedsignalgenerator(600);
      //Sleep for 0.6ms
      digitalWrite(11, LOW);
//      Serial.print(LOW);
      delayMicroseconds(600);
    }
    if(one_or_zero == 1){
      //Emit Ir at 38kHz for 0.6ms
      modulatedsignalgenerator(600);
      //Sleep for 1.6ms
      digitalWrite(11, LOW);
//      Serial.print(LOW);
      delayMicroseconds(1600);
    }
  
}

void loop() {
  // put your main code here, to run repeatedly:
   int val = digitalRead(button);   // read the button input
    digitalWrite(13, LOW);
   if(val){
      digitalWrite(13, HIGH);  // sets the LED to High to indicate button being pressed
      delay(1000);
      leadercodegenerator();
      //Transmitting the Address
      for(int i=0;i<8;i++)
      pulsegenerator(buttonaddress[i]);
  
      //Transmitting the Negation of Address
      for(int i=0;i<8;i++)
      pulsegenerator(~buttonaddress[i]);
  
      //Transmitting the Command
      for(int i=0;i<8;i++)
      pulsegenerator(buttoncommand[i]);
  
      //Transmitting the Negation of Command
      for(int i=0;i<8;i++)
      pulsegenerator(~buttoncommand[i]);
  
      //Stop Pulse at the end
      pulsegenerator(1);
      
      digitalWrite(13, LOW); //Indicate the transmission is finished
   }
  
}
