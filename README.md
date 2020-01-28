# IOT426-smart-lights
A project created with the goal to employ automation using social media.
The unit is an embedded system that allows you to control section of your home lights remotely using a twitter account. 
Technologies used: Python, C, Fujitsu MCU

## Features:
1. Live tweet scanning
2. Activity Log
3. Twitter software interpreter
4. LCD status display
5. Implementation of the electrical circuitry

## Conceptual framework.

![alt text](https://i.ibb.co/1JXQPSp/conceptual-framework.png "conceptual framework")

## System Block Diagram

![alt text](https://i.ibb.co/1JtS8VT/system-block-diagram.png "system block diagram")


## Hardware Design
The hardware consists primarily of a Fujitsu microcontroller and the subsequent sensors. A PC/laptop running the tweet interpreter application would be able to send signals to the MCU through the RS-232 converter cable. The signal being sent to the MCU has a unique value that determines how a specific light switches. The status of the four lights are displayed in the LCD. 

## Software Design

The tweet interpreter program is designed with the use of the python software with additional libraries installed for the python–twitter integration. The tweet interpreter will send a signal to the MCU through the serial port with a value from 1-8. Each value sent will be received by the MCU and will decode and respond to how each of the individual lights will perform.


## Data Presentation and Analysis

The table below shows the operation and interpretation of signals sent from the transmitter(Python) to the receiver side(C).
![alt text](https://i.ibb.co/NyQTCSt/table.png "table image")


Based on the table above, the receiver side identifies the value transmitted as hex values. As it confirms that the microcontroller receives a match on a certain hex value, it will perform a specific output task.
