
In this course a universal DCC decoder for signals and switches is build step by step. This course is to encourage everyone to start loving the Arduino platform to be used in model railroad automation. This is part 3 of the course containing examples using external hardware to overcome performance problems with the Arduino and/or to have more and powerfull IO.

* MCP23017 16 channel IO multiplexer
* TLC5947 24 channel PWM LED driver
* PCA9685 16 channel PWM driver for servos and LEDs
* LED ring with WS2812

## MCP23017

The MCP23017 is a powerfull I2C 16 channel input and output multiplexer. It contains no functionality for fading. Connecting LEDs to the MCP23017 still requires an additional resistor per LED.

The first example is a demo of blinking LEDs using the MCP23017 still using delays. The schematic was drawn using Fritzing.
The code:
