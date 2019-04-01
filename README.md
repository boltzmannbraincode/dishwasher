This is an arduino program to <b>cotrol the relay board of a dishwasher</b>. After my dishwasher's cotrol PCB failed twice, I had to replace 
it with something less costly than an official cotrol PCB which costs around 40 times more than an arduino (Pro Mini in my case). 
All i did was keep the existing relays (de-soldered from the PCB of the dishwasher) and connect them to the arduino using some diodes 
flyback protection, and connected the temperature and water-level sensors to the arduino using some resistors.I also added a button to 
initiate the dishwashing program. This project is all about the "software", the dishwashing time-table. I have defined the inputs 
and the outputs at the beginning(using #define) so that anyone can configure the pins with a different order(each pin corresponds to 
one relay, as the comments in the code suggest).
<b>To start the diswasher, just press the push-button</b>(be aware that the button must return to its initial state after the click, or if 
you use a toggle switch you have to double-toggle it, because if it is left closed, the program will repeatedly run until you open it).
You can use the control functions <b>buzz(),hotwash(),start_green_led(),stop_green_led,start_red_led(),stop_red_led(),rinse(),drain_tank()</b>
and <b>fill_tank()</b> to make whatever program you want.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
buzz(int times):
  it makes a series of "beeps", depending on the number you specify at the function argument.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 hotwash(int time, float volt_temp_limit):
  it washes the dishes with hot water,with the time depending on the time variable, and the temperature depending on the volt_temp_limit
  variable. Be careful: it means that when the pin that the thermometer is connected to reaches that voltage(or drops below it) the 
  temperature is equal or higher than our limit, so it stops the heating element.You have to calculate it depending on your thermometer
  using simple Ohm's law.(the one end of the thermo-resistor is connected to 5V, the other end to the reading analog pin,and the pin is   
  connected to the ground with a 10K resistor).
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
start_green_led() / start_red_led():
  it powers the green or the red led.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stop_green_led() / stop_red_led():
  it stops the green or red led.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
rinse():
  it rinses the contents of the dishwasher with cold water(tank temperature) for 1 miniute.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
drain_tank():
  it activates the drain pump for 15 seconds to empty the dishwasher from any remaining water.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fill_tank():
  it opens the inlet valve until the limit floater gets activated(meaning that the water tank is full).
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<b>Bonus Info:                                                                                                                  </b>
  <b>secondary_coil , has_secondary_coil</b>: the dishwasher in my case, has an AC motor with 2 coils, the primary and the secondary.
  The primary coil is used to constantly power the motor, and the secondary it is used in combination with the primary just to start it.
  In most cases while the secondary coil is running, the motor is producing excessive heat so you want to stop it after the motor 
  starts spinning. To do this, set has_secondary_coil = 1, and configure the relay of your secondary coil with #define secondary_coil.
  After that, the start_main_pump() function will use the secondary coil to start the motor for 5 seconds,and then it will shut it off.
  <b>get_temperature()</b>: the dishwasher uses a thermistor(a resistor whose value changes vigorously with fluctuations of the 
  temperature) to get the temperature of the water in its tank. The one end of the thermistor is connecetd to the 5V of the arduino, and 
  its other end is connected to the *thermometer* pin(defined as thermometer, the pin must be capable of analog read).The thermometer 
  pin must be also grounded using a  resistor(the value of the resistor depends on your thermistor. See
  learn.adafruit.com/thermistor/using-a-thermistor or a similar website for more info).The pin reads a value between 0 and 5 Volts, and
  it converts it to an integer between 0 and 1024(you can use the map() function to change it), and in the get_temperature() we use the 
  formula *reference_resistance * (1 / ((Vin / Vout) - 1))* from Ohm Law to measure the value of our thermistor. The function then 
  <b>returns the resistance</b>! You have to test your thermistor or get its temperature-to-resistance graph from its datasheet to 
  theoretically determine your desired resistance limit.
  
