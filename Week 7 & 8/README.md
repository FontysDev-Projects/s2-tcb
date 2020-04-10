# This project is a combination between Part A & B of Week 7/8 Assignment.

It is terminal controled program that allows to write/read a Register located in the memory of the Slave device.
The master Device translates the serial command send through the terminal and sends the Write command or Read request via the I2C bus to the slave.
The slave device implements a interupt for both the Write command and Read request (onReceive(), onRequest()).   