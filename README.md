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

## Data Presentation and Analysis

The table below shows the operation and interpretation of signals sent from the transmitter(Python) to the receiver side(C).
![alt text](https://i.ibb.co/NyQTCSt/table.png "table image")


Based on the table above, the receiver side identifies the value transmitted as hex values. As it confirms that the microcontroller receives a match on a certain hex value, it will perform a specific output task.
