/*Febryary of 2019
 * This is a sketch for the arduino to act as a dishwasher brain circuit
 * using 4 relays as control devices(controlling motors,heaters etc.),
 * a thermometer(,thermistor, for measuring the temperature of the water)  
 * and switches, for the user to be able to enter some basic settings
 * (such as economic mode or rinse-only). There can be 3 more sensors added 
 * in the near future(water transparency,door opened etc.)
 */
#define REL0 5
#define REL1 4
#define REL2 3
#define REL3 2

#define SWI1 6
#define SWI2 7

#define THERM A2

int switch1 = 0;
int switch2 = 0;

int temperature = 0;

void setup() {
  pinMode(REL0, OUTPUT);
  pinMode(REL1, OUTPUT);
  pinMode(REL2, OUTPUT);
  pinMode(REL3, OUTPUT);
  pinMode(SWI1,INPUT);
  pinMode(SWI2, INPUT);
  pinMode(THERM, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  //getting the state of the switch 1
  switch1 = digitalRead(SWI1);

  //measuring Temperature of the water
  temperature = analogRead(THERM);
  
  //opening and closing a device(through RELAY 1)
  digitalWrite(REL1, HIGH);   
  delay(1000);                      
  digitalWrite(REL1, LOW);

  
 /*
  digitalWrite(REL1, HIGH);   
  delay(1000);                      
  digitalWrite(REL1, LOW);  
  digitalWrite(REL2, HIGH);   
  delay(1000);                       
  digitalWrite(REL2, LOW);   
  digitalWrite(REL3, HIGH);   
  delay(1000);                      
  digitalWrite(REL3, LOW);    
  digitalWrite(REL0, HIGH);  
  delay(1000);                      
  digitalWrite(REL0, LOW);   
  */
}
