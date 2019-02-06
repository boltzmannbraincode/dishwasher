/*Febryary of 2019
 * This is a sketch for the arduino to act as a dishwasher brain circuit
 * using 4 relays as control devices(controlling motors,heaters etc.),
 * a thermometer(,thermistor, for measuring the temperature of the water)  
 * and switches, for the user to be able to enter some basic settings
 * (such as economic mode or rinse-only). There can be 3 more sensors added 
 * in the near future(water transparency,door opened etc.)
 */
//here you can define the pins that control your elements
#define main_pump 2
#define drain_pump 3
#define heating_element 4
#define inlet_valve 5

#define floater 6
#define power_switch 7
#define thermometer A2

#define green_led 10
#define red_led 11


void setup() {
pinMode(main_pump,OUTPUT);
pinMode(drain_pump,OUTPUT);
pinMode(heating_element, OUTPUT);
pinMode(inlet_valve,OUTPUT);
pinMode(floater,INPUT);
pinMode(power_switch,INPUT);
pinMode(thermometer, INPUT);
pinMode(green_led,OUTPUT);
pinMode(red_led, OUTPUT);
}

void loop() {


}

//F U N C T I O N S !

void start_main_pump(){
  delay(100);
  digitalWrite(main_pump,HIGH);
}

void stop_main_pump(){
  delay(100);
  digitalWrite(main_pump,LOW);
}

void start_heating_element(){
  delay(100);
  digitalWrite(heating_element,HIGH);
}

void stop_heating_element(){
  delay(100);
  digitalWrite(heating_element,LOW);
}

void start_drain_pupm(){
  delay(100);
  digitalWrite(drain_pump,HIGH);
}

void stop_drain_pump(){
  delay(100);
  digitalWrite(drain_pump,LOW);
}

void start_green_led(){
  digitalWrite(green_led,HIGH);
}

void stop_green_led(){
  digitalWrite(green_led,LOW);
}
void start_red_led(){
  digitalWrite(red_led,HIGH);
}

void stop_red_led(){
  digitalWrite(red_led,LOW  );
}

float get_temperature(){
  float sensor_value = 0,Vout = 0, Vin = 5, resistance = 0, Rref = 10000;  //Rref is the reference resistor(10kΩ)
  sensor_value = analogRead(thermometer);  
  Vout = (Vin * sensor_value) / 1023;    // Convert Vout to volts
  resistance = Rref * (1 / ((Vin / Vout) - 1));
  return resistance;  //returns the Ohms of resistance of the thermocouple(NOT CELCIOUS)
}

int get_switch(){
  int switch_state;
  switch_state = digitalRead(power_switch);
  return switch_state;
}

int get_floater(){
  int floater_state;
  floater_state = digitalRead(floater);
  return floater_state; //returns 1 if floater is activated(full tank)
}







