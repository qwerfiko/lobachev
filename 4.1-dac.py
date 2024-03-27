import RPi.GPIO as GPIO

dac = [26, 19, 13, 6, 5, 11, 9, 10]  # список GPIO-пинов в области DAC
GPIO.setmode(GPIO.BCM)
GPIO.setup(dac, GPIO.OUT)

def decimal_to_binary(value):
    return [int(bit) for bit in bin(value)[2:].zfill(8)]

try:
    while True:
        input_value = input("Введите число от 0 до 255 (или 'q' для выхода): ")
        if input_value.lower() == 'q':
            break
        try:
            value = int(input_value)
            if value < 0 or value > 255:
                print("Значение должно быть в диапазоне от 0 до 255.")
                continue
            binary_value = decimal_to_binary(value)
            GPIO.output(dac, binary_value)
            voltage = value / 255 * 3.3
            print(f"Предполагаемое напряжение: {voltage:.2f} В")
        except ValueError:
            print("Введено не числовое значение.")
except KeyboardInterrupt:
    print("Программа прервана пользователем.")
finally:
    GPIO.output(dac, [0]*8)
    GPIO.cleanup(dac)