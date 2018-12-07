# electric_piano
An implementation for an electric piano using a Sparkfun Redboard, capable of playing all notes in the C4 Octave.

# Hardware

The 7 buttons, from left to right, represent letter notes C4, D4, E4, F4, G4, A4, and B4. The next 2 buttons are for HalfStep Up or HalfStep Down (these need to be pressed simultaneously as you press the note buttons.

The next button is used for pre-recorded songs - currently my code plays Fur Elise by Beethoven on it. 

The next button turns on the UltraSonic Sensor, which can be used to change the frequency of your sounds by virtue of object distances from the sensor. While the sensor is on, if you press the pre-recorded song button, it'll save the frequency permanently, and all notes will get shifted by the amount stored in memory.
If you close the UltraSonic sensor, again by pressing the UltraSonic button, the sesnor will turn off, and any saved frequencies will be lost.

The next 2 buttons in line are used for Recording and Playing. If you press the record button, the Green LED on the right breadboard will light up, indicating recording has begun. You can stop recording by pressing the same button again, and the LED will turn off.
You can then use the last button - the Playback Button - to playback whatever you have recorded.

# Software

pitches.h

It contains all the pre-defined note frequencies.

electronic_keyboard

This is an arduino extension .iso file where the main code runs.

On the top you'll find all the pins. You can change pin values to whatever your implementation uses.
Struct node and Class arr implement a Linked List for song recording.
Void Setup initializes all pins as input or output.

Void Loop starts by checking if the song button has been pressed, and plays the song only if the ultrasonic sensor is off.
It then checks if the record button has been pressed, and either starts or stops recording. If something has been recording playback becomes true, which allows you to play the song using the playback button.
It then moves on to check if the ultrasonic button has been pressed, and then again either starts or stops it. If UltraOn, it gets a value to shift the frequency by using the getShift() function.

We then read the data incoming from the pins using an analogRead(). Each button corresponds to a different resistance, and therefore different analog values. The halfStepUp and HalfStepDown buttons here can be used to push up or down frequency by HalfStep.
The if conditions finally execute the tone() function which sends data to the speaker.

![alt text](https://raw.githubusercontent.com/ananmay3/electric_piano/master/images/circuit_img.jpg)
