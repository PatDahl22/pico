import board
import digitalio
import time

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

while True:
    led.value = True
    print(f"LED is {led.value}")
    time.sleep(0.5)

    led.value = False
    print(f"LED is {led.value}")
    time.sleep(0.5)
