# Sudoku board.

## Introduction 

All along, digital forms of games have replaced the physical ones. Although that has improved convenience, it has reduced if not removed, the human involvement or interaction. This version of Sudoku is a fun attempt at bringing the popular puzzle Sudoku into the physical form. 
A solution for a geometric problem can be found out more easily when the scale of the figure is increased. Similarly, the Sudoku puzzle becomes clearer and more fun when scaled.


## Components Used

* NodeMCU microcontroller
* Seven segment displays

[//] # ( * 3 motors for linear actuation (Stepper Motors))

[//] # ( * Motor Drivers)

* Capacitive sensor

## Working

### Overview

The microcontroller connects to the internet and downloads a puzzle. The pre-defined values are displayed, using the Seven Segment displays.
The microcontroller senses the input from the user through the capacitive sensor.
Based on the current positions of the numbers, the microcontroller determines if the placement of a particular number is valid. If the position is not valid, it blinks the RED LED indicating invalid move.
If the position is valid, it turns on the GREEN LED for 2 seconds. (This can be disabled)

At the end of the game, if played correctly, the GREEN LED blinks for a period of 10 seconds, indicating successful completionkkkkk
