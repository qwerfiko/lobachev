import RPi.GPIO as GPIO
import time

# Настройка GPIO
GPIO.setmode(GPIO.BCM)

# Список пинов ЦАП
dac = [8, 11 ,7, 1, 0 ,5, 12 ,6]
GPIO.setup(dac, GPIO.OUT, initial=GPIO.LOW)

def dec2bin(n):
    return [int(bit) for bit in bin(n)[2:].zfill(len(dac))]

def dac_data(data):
    signal = dec2bin(data)
    GPIO.output(dac, signal)
    return signal

try:
    # Период сигнала задается через input
    period = float(input("Введите период треугольного сигнала: "))
    while True:
        # Формирование треугольного сигнала
        for i in range(256):
            dac_data(i)
            time.sleep(period / 512)
        for i in range(255, -1, -1):
            dac_data(i)
            time.sleep(period / 512)
finally:
    # Очистка настроек GPIO
    GPIO.output(dac, GPIO.LOW)
    GPIO.cleanup(dac)