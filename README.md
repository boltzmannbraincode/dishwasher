This is an arduino programm to cotrol the relay board of a dishwasher. After my dishwasher's cotrol PCB failed twice, I had to replace 
it with something less costly than an official cotrol PCB which costs around 40 times more than an arduino (Pro Mini in my case). 
All i did was keep the existing relays (de-soldered from the PCB of the dishwasher) and connect them to the arduino using some diodes 
flyback protection, and connected the temperature and water-level sensors to the arduino using some resistors.I also added a button to 
initiate the dishwashing program. This project is all about the "software", the dishwashing time-table. I have defined the inputs 
and the outputs at the beginning(using #define) so that anyone can configure the pins with a different order(each pin corresponds to 
one relay, as the comments in the code suggest).
To start the diswasher, just press the push-button (be aware that the button must return to its initial state after the click, or if 
you use a toggle switch you have to double-toggle it, because if it is left closed, the program will repeatedly run until you open it).
