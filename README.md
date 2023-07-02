# Automated Curtain Opener  
This project was done for UCR's EE128: Sensing and Actuation for Embedded Systems. 
## Background  
This mini-project was completed in one week.
The purpose was to simulate smart home technology use cases for embedded systems.
The sensing and actuation logic is carried out on the FDRM-64F deveoplment board.  

## Parts  
- K64F Board  
- Stepper Motor
- L298N Motor Driver  
- 1N4148 Diodes (8 count)
- KY-038 Microphone Module  
- Passive Buzzer  
- Generic LED  
- 9V Battery
- Wires (Dupont male/male and male/female)
- Some string, fishing line, or wire (for pulley system)
## Wiring  

Motor driver general wiring schematic.  
<img width="405" alt="motor_driver_wiring" src="https://github.com/lpurgitoryl/FRDM-K64F-CurtainOpener/assets/23303005/0282d3e1-ee6f-4dbc-962e-5208b17cf6db">

In the final version, the following pins are used.
- IN1-IN4 are connected to Port D pins 0-3
- ENA and ENB are connected to Port D pins 4-5
  
The microphone module is connected to PORT A pin 1.  
The passive buzzer is connected to PORT C pin 10.

## Demo

<img width="405" alt="motor_driver_wiring" src="https://github.com/lpurgitoryl/FRDM-K64F-CurtainOpener/assets/23303005/0c7d4c3d-2e84-4001-bf54-69d9ae9e6f7d">  

[Video Link](https://youtu.be/sEjKm0Vb6mc)  

## Other Links and Information
[FRDM-64F](https://www.nxp.com/design/development-boards/freedom-development-boards/mcu-boards/freedom-development-platform-for-kinetis-k64-k63-and-k24-mcus:FRDM-K64F)  
[Pulley system inspiration](https://youtu.be/JtYdPwO65WI?t=792)  
[Project Report](https://docs.google.com/document/d/1dzci8ntVVdhlUHROj9Acoytm7zOB9gnHJzhSDY8bff8/edit?usp=sharing)

