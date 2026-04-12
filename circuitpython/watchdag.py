import board
import digitalio
import keypad
import microcontroller
import watchdog
import time

wdt = microcontroller.watchdog
wdt.timeout = 5
wdt.mode = watchdog.WatchDogMode.RESET

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

keys = keypad.Keys((board.GP15,), value_when_pressed=False)

print("Watchdog armed - 5 second timeout")
print("Press button to freeze and trigger watchdog reset")

while True:
    wdt.feed()

    event = keys.events.get()
    if event and event.pressed:
        print("Freezing - watchdog will reset in 5 seconds...")
        led.value = True
        while True:
            pass

    time.sleep(0.1)
