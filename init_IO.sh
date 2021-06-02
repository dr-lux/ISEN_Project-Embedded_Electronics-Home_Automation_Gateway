#!/bin/sh

# Red LED
echo 1 > /sys/class/gpio/gpio50/unexport
echo 1 > /sys/class/gpio/gpio50/export
echo out > /sys/class/gpio/gpio50/direction

# Green LED
echo 1 > /sys/class/gpio/gpio60/unexport
echo 1 > /sys/class/gpio/gpio60/export
echo out > /sys/class/gpio/gpio60/direction

# Blue LED
echo 1 > /sys/class/gpio/gpio3/unexport
echo 1 > /sys/class/gpio/gpio3/export
echo out > /sys/class/gpio/gpio3/direction

# Button
echo 1 > /sys/class/gpio/gpio48/unexport
echo 1 > /sys/class/gpio/gpio48/export
echo in > /sys/class/gpio/gpio48/direction

# QAM
echo 1 > /sys/class/gpio/gpio48/unexport
echo 1 > /sys/class/gpio/gpio48/export
echo in > /sys/class/gpio/gpio48/direction


