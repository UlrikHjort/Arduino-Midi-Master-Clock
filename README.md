# Arduino Midi Master Clock

Midi master clock for Arduino. 
Connect midi OUT from the UNO to the midi IN on the slave chain and specify the device and the tempo (in bpm) by the potentiometer. Read out the actual value on the OLED display.

## Hardware:
* Arduino UNO
* SparkFun MIDI Shield DEV-12898
* 0.96" OLED display I2C

## Wiring:
The MIDI shield is mounted on breadboard since not all pins are used by the shield and free pins to mount the OLED are needed. 
Pins between Shield and UNO is mapped "one to one" as stated below.



| Midi Shield  |  UNO |
| --- | --- |
|GND | GND |
|VCC | +5V |
|A1 (POT) | A1 |
|Tx | Tx  |


| OLED  |  UNO |
| --- | --- |
|GND | GND |
|VCC | +5V |
|SCL | A5  |
|SDA | RxD  |


It is possible to wire a DIN directly to the TX  on the UNO with a 220 ohm resistor at the VCC line. But for saftely it 
is recommend to use opto isolation as provided with the shield.

Optional stand alone DIN wiring:

| PIN  | Description | UNO |
| --- | --- | --- |
|1 | Not connected | - |
|2 | Shield | GND |
|3 | Not connected  | . |
|4 | VCC (add a R220)  | +5V |
|5 | Data line  | Tx|





