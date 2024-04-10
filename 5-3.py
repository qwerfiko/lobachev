import RPi.GPIO as GPIO
from time import sleep

def decimal2binary(value):
    return [int(bit) for bit in bin(value)[2:].zfill(8)]

# def adc(comp, dac):
#     for val in range(256):
#         GPIO.output(dac, decimal2binary(val))
#         sleep(.01)
#         compVal = GPIO.input(comp)
#         if compVal == 1:
#             return val
#     return 256 

def adc(comp, dac):
    binVal = [0 for i in range(8)]
    for i in range(8):
        binVal[i] = 1
        GPIO.output(dac, binVal)
        sleep(.01)
        compVal = GPIO.input(comp)
        if compVal == 1:
            binVal[i] = 0
    val = 0
    for i in range(8):
        val += binVal[i] * (2**(7-i))
    return val

def decimal2volume(val):
    volume = [0 for i in range(8)]
    step = 256 / 8
    for i in range(8):
        if val > step * i:
            volume[i] = 1
    return volume

GPIO.setmode(GPIO.BCM)

dac = [8, 11, 7, 1, 0, 5, 12, 6]
leds = [2, 3, 4, 17, 27, 22, 10, 9]
comp = 14
troyka = 13

GPIO.setup(dac, GPIO.OUT)
GPIO.setup(troyka, GPIO.OUT)
GPIO.setup(leds, GPIO.OUT)
GPIO.setup(comp, GPIO.IN)

try:
    GPIO.output(troyka, 1)
    while True:
        out = adc(comp, dac)
        GPIO.output(leds, decimal2volume(out))

finally:
    GPIO.output(troyka, 0)
    GPIO.output(dac, 0)
    GPIO.output(leds, 0)
    GPIO.cleanup()