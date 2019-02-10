//here you can define the pins that control your elements
#define main_pump 2  //RELAY 3
#define drain_pump 3  //RELAY 2
#define heating_element 4  //RELAY 1
// #define sinlet_valve 5  //RELAY 0
#define secondary_coil 5  //RELAY 0

#define floater 6
#define power_switch 7
#define thermometer A2

#define green_led 10
#define red_led 11

unsigned long elapsed_time,current_time,start_time;
float volt_temp_limit = 3; //IMPORTANT:  the voltage that the thermometer pin has when peak temperature is reached

void setup() {
pinMode(main_pump,OUTPUT);
pinMode(drain_pump,OUTPUT);
pinMode(heating_element, OUTPUT);
pinMode(secondary_coil,OUTPUT);
pinMode(floater,INPUT);
pinMode(power_switch,INPUT);
pinMode(thermometer, INPUT);
pinMode(green_led,OUTPUT);
pinMode(red_led, OUTPUT);
start_green_led(); //indicating that no program is currently running
}

void loop() { // here lies the first simple wahsing program!

 if(get_switch() == 1){ // if someone opens the switch, the program starts
  stop_green_led();
  start_red_led(); //showing that a program has started running
  
  

  //start of washing phase
  start_time = millis();//get the time that the washing mode started
  start_main_pump();
  start_heating_element();
  unsigned long time_limit = 300000;  //for how many ms the washing phase will run
  while( elapsed_time < time_limit){//while the washing mode hasn't run for a full 10 miniutes(i've put half of the ms bcoz arduino pro mini has some sort of a problem with millis() )
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
  delay(10000);  //10 sec delay so that the shelves can drain

  //rinsing phase
  drain_tank();
  fill_tank();
  delay(500);
  
  start_main_pump();
  delay(100000);  //rinse the dishes for 3-4 mins
  stop_main_pump();
  
  drain_tank();

  //green led indicates that no program is currently running
  start_green_led();
 }
}

//F U N C T I O N S ! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_main_pump(){
  start_secondary_coil()
  digitalWrite(main_pump,HIGH);
  delay(2000);
  stop_secondary_coil();
  /*here could be a while loop that uses the pressure switch(located at the heating element in my model)
   * that stops the seondary coil only when the pressure switch is activated, telling us that the motor 
   * has started running at close-to-full rpm.
   */
  
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



void start_secondary_coil(){
  digitalWrite(secondary_coil,HIGH);
}

void stop_secondary_coil(){
  digitalWrite(secondary_coil,LOW);
}

void drain_tank(){
  start_drain_pump();
  delay(10000);
  stop_drain_pump();
}

