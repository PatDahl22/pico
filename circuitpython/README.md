# CircuitPython Examples for Raspberry Pi Pico 2 W

This folder contains small CircuitPython prototypes created for learning embedded systems concepts on the Raspberry Pi Pico 2 W.

The examples are structured as separate files so each concept can be tested in isolation before combining them into a larger IoT system.

## Contents

- `blink.py`  
  Basic onboard LED blinking.

- `log.py`  
  LED blinking with serial logging.

- `button.py`  
  Read a button and control the LED.

- `watchdog.py`  
  Demonstrates watchdog reset behavior.

- `slow_events.py`  
  Simulates queued button events and reset handling.

- `code.py`  
  Wi-Fi button event sender using HTTP requests.

- `settings.toml`  
  Stores Wi-Fi credentials for CircuitPython.

## Hardware

Target board:
- Raspberry Pi Pico 2 W

Typical wiring used in the examples:
- Onboard LED
- Button A on `GP15`
- Button B on `GP14`
- Reset button on `GP18` (for `slow_events.py`)

## Requirements

Install CircuitPython on the board first.

For the HTTP example in `code.py`, install the required library bundle:

- `adafruit_requests`

You can install libraries with:

``bash
circup install adafruit_requests


## How to run
Run a specific example

Copy the file you want to test and rename it to code.py on the CIRCUITPY drive.

Example:

test blink.py → copy its contents into code.py
test button.py → copy its contents into code.py

CircuitPython automatically runs code.py on boot or after saving.

## Wi-Fi configuration

Create a settings.toml file on the CIRCUITPY drive:

CIRCUITPY_WIFI_SSID="your_wifi_name"
CIRCUITPY_WIFI_PASSWORD="your_wifi_password"


### Notes
- code.py is the active runtime file used by CircuitPython.
- The other files are kept as separate prototypes for testing and learning.
- Do not commit real Wi-Fi credentials to Git.

### Suggested workflow
1. Test each file separately.
2. Confirm serial output in the terminal.
3. Verify button input and LED behavior.
4. Move on to HTTP/Wi-Fi once the local hardware examples work.


