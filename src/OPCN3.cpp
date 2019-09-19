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
    Serial.println("Serial Number:");
    Serial.println(getSerialNumber());
    delay(1000);
    Serial.println("DACandPowerStatus");
    readDACandPowerStatus();
    delay(1000);
    Serial.println("ConfigurationVariables");
    readConfigurationVariables();
    delay(4000);
    Serial.println("");
    delay(10000);
    Serial.println("Turn Fan on");
    struct FanDigitalPotShutdownState fanState = setFanDigitalPotShutdownState(true);
    delay(1000);
    Serial.println("Turn Laser on");
    struct LaserDigitalPotShutdownState laserState = setLaserDigitalPotShutdownState(true);
    delay(1000);
    Serial.println("Turn Laser Switch on");
    struct LaserPowerSwitchState laserPowerState = setLaserPowerSwitchState(true);
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
    Serial.println(dACandPowerStatus.toString());
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

struct LaserPowerSwitchState OPCN3::setLaserPowerSwitchState(bool status)
{
    byte commandByte = status ? 0X07 : 0X06;
    LaserPowerSwitchState laserPowerSwitchState = sendCommand<LaserPowerSwitchState>(0X03, commandByte, 1);
    laserPowerSwitchState.laserOn = status;
    Serial.print("Validity: ");
    Serial.println(laserPowerSwitchState.valid);
    Serial.print(laserPowerSwitchState.laserOn);
    Serial.print(" ");
    return laserPowerSwitchState;
}

struct HighLowGainState OPCN3::setHighLowGainState(bool status)
{
    byte commandByte = status ? 0X10 : 0X11;
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

bool OPCN3::resetHistogram()
{
    HistogramData data = readHistogramData();
    return data.valid;
}

struct SerialNumber OPCN3::readSerialNumber()
{
    SerialNumber serialNumber = sendCommand<SerialNumber>(0X10, 0X10, 60);
    Serial.print("Validity: ");
    Serial.println(serialNumber.valid);
    String info = "";
    for (int i = 0; i < 60; i++)
    {
        info += String(serialNumber.serial[i]);
    }
    serial = info;
    return serialNumber;
}

String OPCN3::getSerialNumber()
{
    return serial;
}

struct ConfigurationVariables OPCN3::readConfigurationVariables()
{
    ConfigurationVariables configurationVariables = sendCommand<ConfigurationVariables>(0X3C, 0X3C, 163);

    Serial.print("Validity: ");
    Serial.println(configurationVariables.valid);
    Serial.println("Bin Boundries ADC");
    Serial.print(configurationVariables.binBoundriesADC0);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC1);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC2);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC3);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC4);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC5);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC6);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC7);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC8);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC9);
    Serial.println(" ");
    Serial.print(configurationVariables.binBoundriesADC10);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC11);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC12);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC13);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC14);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC15);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC16);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC17);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC18);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC19);
    Serial.println(" ");
    Serial.print(configurationVariables.binBoundriesADC20);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC21);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC22);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC23);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesADC24);
    Serial.println(" ");

    Serial.println("-------------------------------------------------");
    Serial.println("Bin Boundries Diametors");
    Serial.print(configurationVariables.binBoundriesDiametor0);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor1);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor2);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor3);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor4);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor5);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor6);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor7);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor8);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor9);
    Serial.println(" ");
    Serial.print(configurationVariables.binBoundriesDiametor10);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor11);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor12);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor13);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor14);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor15);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor16);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor17);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor18);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor19);
    Serial.println(" ");
    Serial.print(configurationVariables.binBoundriesDiametor20);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor21);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor22);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor23);
    Serial.print(" ");
    Serial.print(configurationVariables.binBoundriesDiametor24);
    Serial.println(" ");

    Serial.println("-------------------------------------------------");
    Serial.println("Bin Weights");
    Serial.print(configurationVariables.binWeightings0);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings1);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings2);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings3);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings4);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings5);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings6);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings7);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings8);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings9);
    Serial.println(" ");
    Serial.print(configurationVariables.binWeightings10);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings11);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings12);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings13);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings14);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings15);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings16);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings17);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings18);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings19);
    Serial.println(" ");
    Serial.print(configurationVariables.binWeightings20);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings21);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings22);
    Serial.print(" ");
    Serial.print(configurationVariables.binWeightings23);
    Serial.println(" ");
    Serial.println("-------------------------------------------------");
    Serial.println("PM Diametors");
    Serial.print(configurationVariables.pmDiametorA);
    Serial.print(" ");
    Serial.print(configurationVariables.pmDiametorB);
    Serial.print(" ");
    Serial.print(configurationVariables.pmDiametorC);
    Serial.println(" ");
    Serial.println("-------------------------------------------------");
    Serial.println("PM MSLNS");
    Serial.print(configurationVariables.maximumTimeOfFlight);
    Serial.print(" ");
    Serial.print(configurationVariables.AMSamplingIntervalCount);
    Serial.print(" ");
    Serial.print(configurationVariables.AMIdleIntervalCount);
    Serial.print(" ");
    Serial.print(configurationVariables.AMMaxDataArraysInFile);
    Serial.print(" ");
    Serial.print(configurationVariables.AMOnlySavePMData);
    Serial.print(" ");
    Serial.print(configurationVariables.AMFanOnInIdle);
    Serial.print(" ");

    return configurationVariables;
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
    for (int i = 0; i < size; i++)
    {
        if (arrayOne[i] != arrayTwo[i])
        {
            valid = false;
        }
    }

    return valid;
}
