# Mechanical_hand

See video at Youtube: https://youtu.be/c5DVGtNNG60 

**LCD Display: Display instructions for users** <br />
*User interface for idle mode and input mode; input mode includes a controllable cursor. <br />
*Paint triangles, polygons with filling functions <br />

**LED Display: Display system states** <br />
*	GREEN: Configuration is complete <br />
*	BLUE: Input Mode <br />
*	Red: Input is sent to the robotic hand. <br />

**Keyboard: Takes user inputs of natural language characters, words, sentences** <br />
*	With four direction buttons, space button, enter button, and deletion button.
*	Characters are displayed on the screen and users select each character with the keyboard.

**STM32:		Process user inputs and output control signal to robotic hand** <br />
*	Display the input sentence and search for each word in the vocabulary date base.<br />
*	If input exists in the date base, output the corresponding gesture signal. <br />
*	If input does not match any supported word / sentence, output each character signal.<br />
*	Out put PWM to the robotic hand with different duty cycles according to input.<br />

**Robotic Hand:	Perform sign language**  <br />
*	Independent movement for each finger.  <br />
*	Sequential performance of each character for unidentified words and sentences. <br />
*(Right now "love" is the word stored only)*
![alt text](/everything.jpg)
