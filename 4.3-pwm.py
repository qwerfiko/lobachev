import RPi.GPIO as GPIO
import time

# Настройка GPIO
GPIO.setmode(GPIO.BCM)

# Выбранный для ШИМ GPIO-пин
pwm_pin = 18
GPIO.setup(pwm_pin, GPIO.OUT)

# Создание объекта управления ШИМ
pwm = GPIO.PWM(pwm_pin, 1000)  # Частота ШИМ 1000 Гц
pwm.start(0)  # Запуск ШИМ с коэффициентом заполнения 0

try:
    while True:
        # Запрос у пользователя коэффициента заполнения
        duty_cycle = float(input("Введите коэффициент заполнения (0-100): "))
        # Задание введённого коэффициента объекту управления ШИМ
        pwm.ChangeDutyCycle(duty_cycle)
        # Расчёт и вывод в терминал предполагаемого значения напряжения на выходе RC-цепи
        voltage = 3.3 * duty_cycle / 100  # Предполагается, что питание GPIO составляет 3.3 В
        print(f"Предполагаемое значение напряжения: {voltage} В")
finally:
    # Очистка настроек GPIO
    pwm.stop()
    GPIO.cleanup()