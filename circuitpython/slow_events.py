import board
import digitalio
import keypad
import time

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

keys = keypad.Keys(
    (board.GP15, board.GP14),
    value_when_pressed=False
)

reset_button = keypad.Keys(
    (board.GP18,),
    value_when_pressed=False
)

counter = 0


def slow_process(source):
    global counter
    steps = ["A", "B", "C", "D"]

    led.value = True
    for step in steps:
        print(f"[Button {source}] Step {step}")
        time.sleep(1)
    led.value = False

    counter += 1
    print(f"[Button {source}] Process complete - run {counter} times")


print("Waiting for button press...")

while True:
    reset_event = reset_button.events.get()
    if reset_event and reset_event.pressed:
        counter = 0
        keys.events.clear()
        print("Reset - counter zeroed, queue cleared")

    event = keys.events.get()
    if event and event.pressed:
        if event.key_number == 0:
            slow_process("A")
        elif event.key_number == 1:
            slow_process("B")

    time.sleep(0.01)
