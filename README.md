# Brief
A single analog stick. Arduino reads its raw values, filters them using [radial scaling](https://www.gamasutra.com/blogs/JoshSutphin/20130416/190541/Doing_Thumbstick_Dead_Zones_Right.php) and prints to serial port when there is a change.

 # Board:
 Arduino Pro Mini ATmega328 (3.3V, 8MHz)
 
 # Connections
| Type | Pro Mini | Analog Stick |
| ---- | -------- | ------------ |
| Output | A2 | VRx |
| Output | A3 | VRy |
| Output | VCC | +5V |
| Output | GND | GND |
