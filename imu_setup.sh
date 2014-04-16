#!/bin/sh
modprobe st_gyro_i2c
modprobe hmc5843
modprobe bmp085-i2c

#Notice that the following items' order will affect N in iio:deviceN in mainwindow.h
echo l3g4200d 0x69 > /sys/bus/i2c/devices/i2c-1/new_device

echo hmc5843 0x1e > /sys/bus/i2c/devices/i2c-1/new_device
echo 50 > /sys/bus/i2c/devices/1-001e/iio:device2/sampling_frequency

echo bmp085 0x77 > /sys/class/i2c-adapter/i2c-1/new_device
