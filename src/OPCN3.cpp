#include "OPCN3.h"

#include <Arduino.h>
#include <SPI.h>

OPCN3::OPCN3(uint8_t pinSelect, uint32_t speedSelect)
{
    _ssPin = pinSelect;
    _speedMaximum = speedSelect;
}

// Alpha Sensor Functions
void OPCN3::begin()
{
    Serial.println("Initiating SPI ");
    // set ss pin to output
    pinMode(_ssPin, OUTPUT);
    SPI.begin();
    // set speed, order and mode
    SPI.beginTransaction(SPISettings(_speedMaximum, MSBFIRST, SPI_MODE1));
    delay(1000);
}

void OPCN3::initialize()
{
    delay(1000);
    Serial.println("Initilize");
    delay(1000);
    begin();
    delay(1000);
    readSerialNumber();
    Serial.println("DACandPowerStatus");
    readDACandPowerStatus();
    delay(10000);
    Serial.println("Turn Fan on");
    struct FanDigitalPotShutdownState fanState = setFanDigitalPotShutdownState(true);
    delay(1000);
    Serial.println("Turn Laser on");
    struct LaserDigitalPotShutdownState laserState = setLaserDigitalPotShutdownState(true);
    delay(1000);
    Serial.println("High Gain");
    struct HighLowGainState gainState = setHighLowGainState(true);
    delay(2000);
    bool reset = resetHistogram();
    delay(2000);
}

struct DACandPowerStatus OPCN3::readDACandPowerStatus()
{
    DACandPowerStatus dACandPowerStatus = sendCommand<DACandPowerStatus>(0X13, 0X13, 6);
    Serial.print("Validity: ");
    Serial.println(dACandPowerStatus.valid);
    Serial.print(dACandPowerStatus.fanOn);
    Serial.print(" ");
    Serial.print(dACandPowerStatus.laserDACOn);
    Serial.print(" ");
    Serial.print(dACandPowerStatus.fanDACVal);
    Serial.print(" ");
    Serial.print(dACandPowerStatus.laserDACVal);
    Serial.print(" ");
    Serial.print(dACandPowerStatus.laserSwitch);
    Serial.print(" ");
    Serial.print(dACandPowerStatus.gainAndAutoGainToggleSetting);
    Serial.print(" ");
    return dACandPowerStatus;
}

struct FanDigitalPotShutdownState OPCN3::setFanDigitalPotShutdownState(bool status)
{
    byte commandByte = status ? 0X03 : 0X02;
    FanDigitalPotShutdownState fanDigitalPotShutdownState = sendCommand<FanDigitalPotShutdownState>(0X03, commandByte, 1);
    fanDigitalPotShutdownState.fanOn = status;
    Serial.print("Validity: ");
    Serial.println(fanDigitalPotShutdownState.valid);
    Serial.print(fanDigitalPotShutdownState.fanOn);
    Serial.print(" ");
    return fanDigitalPotShutdownState;
}

struct LaserDigitalPotShutdownState OPCN3::setLaserDigitalPotShutdownState(bool status)
{
    byte commandByte = status ? 0X05 : 0X04;
    LaserDigitalPotShutdownState laserDigitalPotShutdownState = sendCommand<LaserDigitalPotShutdownState>(0X03, commandByte, 1);
    laserDigitalPotShutdownState.laserOn = status;
    Serial.print("Validity: ");
    Serial.println(laserDigitalPotShutdownState.valid);
    Serial.print(laserDigitalPotShutdownState.laserOn);
    Serial.print(" ");
    return laserDigitalPotShutdownState;
}

struct HighLowGainState OPCN3::setHighLowGainState(bool status)
{
    byte commandByte = status ? 0X07 : 0X06;
    HighLowGainState highLowGainState = sendCommand<HighLowGainState>(0X03, commandByte, 1);
    highLowGainState.highLow = status;
    Serial.print("Validity: ");
    Serial.println(highLowGainState.valid);
    Serial.print(highLowGainState.highLow);
    Serial.print(" ");
    return highLowGainState;
}

struct HistogramData OPCN3::readHistogramData()
{
    HistogramData histogramData = sendCommand<HistogramData>(0X30, 0X30, 86);
    Serial.print("Validity: ");
    Serial.println(histogramData.valid);
    Serial.println("Bin Counts");
    Serial.print(histogramData.binCount0);
    Serial.print(" ");
    Serial.print(histogramData.binCount1);
    Serial.print(" ");
    Serial.print(histogramData.binCount2);
    Serial.print(" ");
    Serial.print(histogramData.binCount3);
    Serial.print(" ");
    Serial.print(histogramData.binCount4);
    Serial.print(" ");
    Serial.print(histogramData.binCount5);
    Serial.print(" ");
    Serial.print(histogramData.binCount6);
    Serial.print(" ");
    Serial.print(histogramData.binCount7);
    Serial.print(" ");
    Serial.print(histogramData.binCount8);
    Serial.print(" ");
    Serial.print(histogramData.binCount9);
    Serial.println(" ");
    Serial.print(histogramData.binCount10);
    Serial.print(" ");
    Serial.print(histogramData.binCount11);
    Serial.print(" ");
    Serial.print(histogramData.binCount12);
    Serial.print(" ");
    Serial.print(histogramData.binCount13);
    Serial.print(" ");
    Serial.print(histogramData.binCount14);
    Serial.print(" ");
    Serial.print(histogramData.binCount15);
    Serial.print(" ");
    Serial.print(histogramData.binCount16);
    Serial.print(" ");
    Serial.print(histogramData.binCount17);
    Serial.print(" ");
    Serial.print(histogramData.binCount18);
    Serial.print(" ");
    Serial.print(histogramData.binCount19);
    Serial.println(" ");
    Serial.print(histogramData.binCount20);
    Serial.print(" ");
    Serial.print(histogramData.binCount21);
    Serial.print(" ");
    Serial.print(histogramData.binCount22);
    Serial.print(" ");
    Serial.print(histogramData.binCount23);
    Serial.println(" ");

    Serial.println("-------------------------------------------------");
    Serial.println("Time To Cross");
    Serial.print(histogramData.bin1TimeToCross);
    Serial.print(" ");
    Serial.print(histogramData.bin3TimeToCross);
    Serial.print(" ");
    Serial.print(histogramData.bin5TimeToCross);
    Serial.print(" ");
    Serial.print(histogramData.bin7TimeToCross);
    Serial.println(" ");

    Serial.println("-------------------------------------------------");
    Serial.println("Sampling Period");
    Serial.println(histogramData.samplingPeriod);
    Serial.println("-------------------------------------------------");
    Serial.println("Sample Flow Rate");
    Serial.println(histogramData.sampleFlowRate);
    Serial.println("-------------------------------------------------");
    Serial.println("Temperature");
    Serial.println(histogramData.temperature);
    Serial.println("-------------------------------------------------");
    Serial.println("Humidity");
    Serial.println(histogramData.humidity);
    Serial.println("-------------------------------------------------");
    Serial.println("pm1");
    Serial.println(histogramData.pm1);
    Serial.println("-------------------------------------------------");
    Serial.println("pm2.5");
    Serial.println(histogramData.pm2_5);
    Serial.println("-------------------------------------------------");
    Serial.println("pm10");
    Serial.println(histogramData.pm10);
    Serial.println("-------------------------------------------------");

    Serial.println("-------------------------------------------------");
    Serial.println("MSLNS");

    Serial.print(histogramData.rejectCountGlitch);
    Serial.print(" ");
    Serial.print(histogramData.rejectCountLongTOF);
    Serial.print(" ");
    Serial.print(histogramData.rejectCountRatio);
    Serial.print(" ");
    Serial.print(histogramData.rejectCountOutOfRange);
    Serial.print(" ");
    Serial.print(histogramData.fanRevCount);
    Serial.print(" ");
    Serial.print(histogramData.laserStatus);
    Serial.print(" ");
    Serial.print(histogramData.checkSum);
    Serial.print(" ");

    return histogramData;
}

bool OPCN3::resetHistogram() {
    HistogramData data = readHistogramData();
    return data.valid;
}

struct SerialNumber OPCN3::readSerialNumber()
{
    SerialNumber serialNumber = sendCommand<SerialNumber>(0X10, 0X10, 60);
    Serial.print("Validity: ");
    Serial.println(serialNumber.valid);
    for (int i = 0; i < 60; i++) {
        Serial.print(serialNumber.serial[i]);
    }
    Serial.println("");
}

void OPCN3::beginTransfer()
{
    digitalWrite(_ssPin, LOW);
    delay(1);
}

void OPCN3::endTransfer()
{
    delay(1);
    digitalWrite(_ssPin, HIGH);
}

bool OPCN3::validate(byte arrayOne[], byte arrayTwo[], int size)
{
    bool valid = true;
    for (int i = 0; i < size; i++) {
        if (arrayOne[i] != arrayTwo[i]) {
            valid = false;
        }
    }

    return valid;
}