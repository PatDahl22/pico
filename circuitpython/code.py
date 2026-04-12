import os
import time
import board
import digitalio
import keypad
import wifi
import socketpool
import adafruit_requests

SERVER = "http://192.168.1.100:8080"

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

keys = keypad.Keys(
    (board.GP15, board.GP14),
    value_when_pressed=False
)

print("Connecting to Wi-Fi...")
wifi.radio.connect(
    os.getenv("CIRCUITPY_WIFI_SSID"),
    os.getenv("CIRCUITPY_WIFI_PASSWORD")
)
print(f"Connected - IP: {wifi.radio.ipv4_address}")

pool = socketpool.SocketPool(wifi.radio)
requests = adafruit_requests.Session(pool)


def send(payload):
    try:
        led.value = True
        response = requests.post(SERVER, json=payload)
        print(f"Server responded: {response.status_code}")
        response.close()
    except Exception as e:
        print(f"Request failed: {e}")
    finally:
        led.value = False


print("Waiting for button press...")

while True:
    event = keys.events.get()
    if event and event.pressed:
        if event.key_number == 0:
            print("Button A pressed")
            send({"button": "A", "message": "hello from button A"})
        elif event.key_number == 1:
            print("Button B pressed")
            send({"button": "B", "message": "hello from button B"})

    time.sleep(0.01)
