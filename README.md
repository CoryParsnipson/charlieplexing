# Charlieplexing

Some test programs for learning Charlieplexing using an Arduino.

## Background

## Arduino Projects

* 3pin-leds
  This is a sketch for a 3 pin, 6 led charlieplex setup. By default, this will loop across all 6 leds slowly (depending on REFRESH\_INTERVAL).

* 3pin-switches
  This is modified from the 3 pin leds sketch to use buttons in place of LEDs. See reference [1] below for some information about doing that.

* 5pin-switches
  This is modified from the 3 pin switches sketch to extend the program to support 20 switches instead of just 6.

## References

[1] https://www.embedded.com/keyboard-and-display-multiplexing-charlieplexing/
    This article is a great starting point and goes over the basics and theory of how it works. At the bottom of this article is a short description of how to adapt the LED design to use switches.

[2] https://www.electroschematics.com/arduino-charlieplexing/
    This link contains some excellent code samples to start.

[3] https://stkwans.blogspot.com/2012/05/designing-large-charlieplex.html
    Some tricks for making Chalieplexing schemes to support an arbitrary number of pins.

[4] https://www.instructables.com/Controlling-20-Leds-from-5-Arduino-pins-using-Cha/
    Not much here, but it has some diagrams for 4, 5, and 6 pin Charlieplexing setups which is useful to look at when you're wiring everything up.
