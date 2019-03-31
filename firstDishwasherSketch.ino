//here you can define the pins that control your elements
#define secondary_coil 8  //RELAY 4
#define main_pump 2  //RELAY 3
#define drain_pump 3  //RELAY 2
#define heating_element 4  //RELAY 1
#define inlet_valve 5  //RELAY 0

#define floater 6
#define power_switch 7
#define thermometer A2

#define green_led 10
#define red_led 11
#define buzzer 9  //notification buzzer

unsigned long elapsed_time,current_time,start_time;
float volt_temp_limit = 3; //IMPORTANT:  the voltage that the thermometer pin has when peak temperature is reached

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
pinMode(secondary_coil, OUTPUT);
pinMode(buzzer, OUTPUT);
start_green_led(); //indicating that no program is currently running
}

void loop() { // here lies the first simple wahsing program!
 if(get_switch() == 1){ // if someone presses the push button, the program starts
  stop_green_led();
  start_red_led(); //showing that a program has started running
  drain_tank();  // drain the leftover water
  fill_tank(); // filling tank with water
  delay(500);
  
  buzz();  // signal the completion of the first stage

  //start of washing phase
  hotwash(600);  // hot wash for 600 sec -> 10 mins
  buzz(); delay(500); buzz();  //double buzz to show transition to rinsing phase
  
  //rinsing phase
  rinse();
  buzz(); delay(500); buzz(); delay(500); buzz(); buzz(); 
  
  drain_tank();

  //green led indicates that no program is currently running
  stop_red_led();
  start_green_led();
 }
}

//F U N C T I O N S ! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_main_pump(){
  start_secondary_coil();
  digitalWrite(main_pump,HIGH);  //start main pump
  delay(5000);  //leave the secondary coil energized for 5 sec
  stop_secondary_coil();  //stop secondary coil, now that the motor is(should be) running at a high rpm
 //TODO: add dynamic secondary coil switching using the pressure switch
}

void stop_main_pump(){
  digitalWrite(main_pump,LOW);
}

void start_heating_element(){
  digitalWrite(heating_element,HIGH);
}

void stop_heating_element(){
  digitalWrite(heating_element,LOW);
}

void start_drain_pump(){
  digitalWrite(drain_pump,HIGH);
}

void stop_drain_pump(){
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

void open_inlet_valve(){
  delay(100);
  digitalWrite(inlet_valve,HIGH);
}

void close_inlet_valve(){
  delay(100);
  digitalWrite(inlet_valve,LOW);
}

void drain_tank(){
  start_drain_pump();
  delay(15000);
  stop_drain_pump();
}

void fill_tank(){
  while(get_floater() == 0){
    open_inlet_valve();
  }
  close_inlet_valve(); //when floater clicks, it stops filling
}

void start_secondary_coil(){
  digitalWrite(secondary_coil,HIGH);
}
void stop_secondary_coil(){
  digitalWrite(secondary_coil,LOW);
}

void buzz(){
 digitalWrite(buzzer,HIGH);
 delay(1000);
 digitalWrite(buzzer,LOW);
}

void hotwash(int time){  // specify time in seconds
  start_time = millis();//get the time that the washing mode started
  start_main_pump();
  start_heating_element();
  unsigned long time_limit = time*500;  //for how many ms the washing phase will run
  while( elapsed_time < time_limit){//while the washing mode hasn't run for a full 20 SECONDS
    //(now the main pump is alread running)
    if(get_temperature()<((1024*volt_temp_limit)/5)){ //converting volt_temp_limit to a value between 0 and 1024
      stop_heating_element();
      /*if the voltage at thermometer pin is less than our defined limit voltage, it means that 
       * also the resistance has dropped, wich means that the temperature is higher than what 
       * we want.All that because hotter means less resistance.
       */
    }
    else{
      start_heating_element();
    }
    current_time = millis(); 
    elapsed_time = current_time - start_time;  //calculate how much time has passed 
    /*we calculate the elapsed time at the end of the loop so that it can be as close
     * as possible to the statement check, thus improvinf accuracy.
     */
  }
  stop_heating_element();
  stop_main_pump();
  delay(10000); 
  delay(10000);
  delay(10000);   // 30 sec delay so that the shelves can drain
}

void rinse(){
  drain_tank();
  fill_tank();
  delay(500);
  
  start_main_pump();
  delay(30000);  //rinse the dishes for 1 mins
  stop_main_pump();
}
