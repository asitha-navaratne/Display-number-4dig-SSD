# Display-number-4dig-SSD

<p align="justify">In this code a floating point value is displayed on a 4-digit Seven Segment Display. The display value is first deconstructed into the four digits to be 
displayed while the position of the decimal point is determined by comparing the value to different ranges.</p>
<p align="justify">The 4-digit SSD works by displaying only one digit during an instance and switching between showing each of the four digits rapidly, faster than the human eye 
can notice the change. This is because whatever is provided as input to the display will be shown in all four digits if they are all connected to GND or VCC (depending on whether
the display is a CC or a CA) at the same time. Therefore, during an instance, only one digit will be turned "ON" to display its number while the others will be turned OFF.</p>
<p align="justify">To begin, the first digit of the display is connected to GND or VCC  to turn that digit ON, while the remaining digits are OFF. The number corresponding to the 
first digit is then shown momentarily before the first digit is turned OFF as well. Next the second digit is turned ON and its number is displayed. In this way, the numbers 
corresponding to all four digits are shown and the process repeats in a cycle.</p>

![Circuit diagram](https://github.com/asitha-navaratne/Display-number-4dig-SSD/blob/master/4digSSD.jpg?raw=true)

<p align="justify">Transistors are used to control the connection of each digit to GND or to VCC. When using transistors, make sure to connect current limiting resistors between
the base of the transistor and the microcontroller to protect the components from sudden high currents (these resistors are not shown in the diagram).</p>
