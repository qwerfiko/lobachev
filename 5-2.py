import RPi.GPIO as GPIO
from time import sleep

def decimal2binary(value):
    return [int(bit) for bit in bin(value)[2:].zfill(8)]

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

GPIO.setmode(GPIO.BCM)

dac = [8, 11, 7, 1, 0, 5, 12, 6]
comp = 14
troyka = 13

GPIO.setup(dac, GPIO.OUT)
GPIO.setup(troyka, GPIO.OUT)
GPIO.setup(comp, GPIO.IN)


try:
    GPIO.output(troyka, 1)
    while True:
        out = adc(comp, dac)
        voltage = out / 256 * 3.3
        print(voltage, 'V')

finally:
    GPIO.output(troyka, 0)
    GPIO.output(dac, 0)
    GPIO.cleanup()