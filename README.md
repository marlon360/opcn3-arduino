# Arduino Library for Alphasense OPC-N3

## Getting started

1. Download the [corresponding release](https://github.com/marlon360/opcn3-arduino/releases/latest)
2. Load the `.zip` with **Sketch → Include Library → Add .ZIP Library**

See [examples/main.ino](examples/main.ino)

## API

### OPCN3

#### OPCN3(`uint8_t pinSelect`, `uint32_t speedSelect`)

The constructor of the OPCN3 class.

`uint8_t pinSelect`: The number of the ss pin.

`uint32_t speedSelect`: The speed in Hz (default `500000`)

#### begin()

Setup for the spi connection.

#### initilize()

Calls `begin()`. Prints all status information. Turns on Fan and Laser. Sets mode to High Gain. Resets Histogramm.

#### readDACandPowerStatus()

Returns `DACandPowerStatus` object.

#### setFanDigitalPotShutdownState(`bool status`)

Turns fan on/off.

`bool status`: If `true` turns on fan.  If `false` turns fan off.

Returns `FanDigitalPotShutdownState` object.

#### setLaserDigitalPotShutdownState(`bool status`)

Turns laser on/off.

`bool status`: If `true` turns on laser.  If `false` turns laser off.

Returns `LaserDigitalPotShutdownState` object.

#### LaserPowerSwitchState(`bool status`)

TODO

#### setHighLowGainState(`bool status`)

Turns laser on/off.

`bool status`: If `true` set high gain.  If `false` set low gain.

Returns `HighLowGainState` object.

#### readHistogramData()

Returns [`HistogramData`](#HistogramData) object.

#### readSerialNumber()

Returns `SerialNumber` object.

#### readConfigurationVariables()

Returns `ConfigurationVariables` object.

#### resetHistogram()

Resets the histogram.

Returns a `bool` which indicates, if the reset was successfully.

---

### HistogramData

| Property | Type | Description |
|----------|------|-------------|
| binCounts | `uint16_t[24]` | Array of all bin counts |
| pm1 | `float` | PM 1 value |
| pm2_5 | `float` | PM 2.5 value |
| pm10 | `float` | PM 10 value |

#### getTempC()

Returns the temperature in Celsius.

#### getTempF()

Returns the temperature in Fahrenheit.

#### getHumidity()

Returns the humidity in percents.