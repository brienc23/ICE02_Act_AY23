# USNA SY202 ICE 02 Actuators
CDR Brien Croteau, 02 Mar 2023


This is an example program that will drive a DC motor via an H-Bridge using the [Motor mbed library](https://os.mbed.com/users/simon/code/Motor/)

## Application functionality

The `main()`  will prompt the user for a desired control frequency rate, then enter a while loop where it will calculate the speed and direction for a motor input from a potentionmeter connected to p19 via the [mbed LPC1768 Application Board](https://os.mbed.com/cookbook/mbed-application-board).  It will stop the motor and exit when the joystick button is pressed down, p14=1.

## Expected output
When connected to a DC Motor via H-bridge it will turn the motor and print out times and requested duty cycle value (between [-1, 1]) to the PC connected via USB serial.


## Troubleshooting
If you have problems, you can review the [documentation](https://os.mbed.com/docs/latest/tutorials/debugging.html) for suggestions on what could be wrong and how to fix it.

## Related Links

* [Mbed OS Stats API](https://os.mbed.com/docs/latest/apis/mbed-statistics.html).
* [Mbed OS Configuration](https://os.mbed.com/docs/latest/reference/configuration.html).
* [Mbed OS Serial Communication](https://os.mbed.com/docs/latest/tutorials/serial-communication.html).
* [Mbed boards](https://os.mbed.com/platforms/).

### License and contributions

The software is provided under Apache-2.0 license. Contributions to this project are accepted under the same license. Please see contributing.md for more info.

This project contains code from other projects. The original license text is included in those source files. They must comply with our license guide.
