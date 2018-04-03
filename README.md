# Wi-Fi Nightlight

A Wi-Fi-enabled Arduino-powered nightlight with an Ionic mobile application that enables you to control it remotely.

## Parts List
Part | Price/Source
-----|-------------
Arduino Uno Wi-Fi | [AU$61.45](https://www.littlebirdelectronics.com.au/arduino-uno-wifi) |
Neopixel Shield | [US$27.95](https://www.adafruit.com/product/1430) |

## Arduino
### Light Configuration

Change these variables under `arduino/src/configuration.ino`a to alter how the light works.

**float theta** (Default: 0.025)

A number which determines the speed of the colour transitions. The lower the number, the slower it goes.
Number should be between 0 and 1.

**int contrast** (Default: 10)

Increases the contrast between 1 pixel and the next when transitioning. The lower the number, the lower the contrast.
Number should be between 1 and 50.

**int brightness** (Default: 64)

Sets the brightness of the LEDS. Use an integer between 1 and 255. WARNING: Setting the brightness to high could result in the board freezing as it drains a lot of power.

Number should be between 1 and 255.

**Pattern pattern** (Default: DIAGONAL_WIPE)

An enumerator that determines how the LEDs animate. There are 4 options.
+ WIPE (left to right)
+ DIAGONAL_WIPE (top left to bottom right)
+ RADIAL (center to outside)
+ and RAINBOW_STRIPE (each row cycles through, starting at a different fifth of the spectrum giving a rainbow effect)

### Wi-Fi/DNS configuration

To enable Wi-Fi connectivity, you will need to rename `credentials.sample` to `credentials.ino` and update the variables within.

```c
char ssid[] = "YOUR NETWORK NAME";
char pass[] = "YOUR NETWORK PASSWORD";
```

The nightlight is discoverable via a free dynamic DNS service hosted by [Dynu](http://dynu.net/). Once it connects to your Wi-Fi, it will send a request to a dynamic DNS service to report its new IP address. The hostname is what the Ionic application uses to connect to the nightlight.

```c
char dynamic_hostname_password[] = "YOUR DDNS PASSWORD";
char dynamic_hostname[] = "YOUR_HOSTNAME.dynu.net";
```

**Do not commit this file to source control**


## Mobile App

The mobile application is an [Ionic Framework](https://ionicframework.com/) application. If you are familiar with Angular, then this should be easy for you to customise.

### Configuration

To update the nightlight's hostname, you will need to update the `api_url` variable in `app/src/services/arduino.service.ts`.
