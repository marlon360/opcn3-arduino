#ifndef OPCN3_H
#define OPCN3_H

#include <Arduino.h>
#include <SPI.h>

class OPCN3
{
private:
    uint8_t _ssPin;
    uint32_t _speedMaximum;
    void beginTransfer();
    void endTransfer();
    bool validate(byte arrayOne[], byte arrayTwo[], int size);
    template <class ResponseType>
    ResponseType sendCommand(byte inputByte, byte commandByte, int outputSize)
    {
        byte validator[2] = {0X31, 0XF3};
        byte initial[2];
        byte dataIn[outputSize];

        beginTransfer();
        initial[0] = SPI.transfer(inputByte);
        delay(10);
        initial[1] = SPI.transfer(inputByte);
        for (int i = 0; i < outputSize; i++)
        {
            delayMicroseconds(10);
            dataIn[i] = SPI.transfer(commandByte);
        }
        endTransfer();

        ResponseType response;
        memcpy(&response, &dataIn, sizeof(response));
        response.valid = validate(initial, validator, 2);
        return response;
    };

public:
    OPCN3(uint8_t pinSelect, uint32_t speedSelect = 500000);
    void begin();
    void initialize();
    struct DACandPowerStatus readDACandPowerStatus();
    struct FanDigitalPotShutdownState setFanDigitalPotShutdownState(bool status);
    struct LaserDigitalPotShutdownState setLaserDigitalPotShutdownState(bool status);
    struct HighLowGainState setHighLowGainState(bool status);
    struct HistogramData readHistogramData();
    struct SerialNumber readSerialNumber();
    bool resetHistogram();
};

struct DACandPowerStatus
{
    uint8_t fanOn;
    uint8_t laserDACOn;
    uint8_t fanDACVal;
    uint8_t laserDACVal;
    uint8_t laserSwitch;
    uint8_t gainAndAutoGainToggleSetting;
    bool valid;
};

struct FanDigitalPotShutdownState
{
    bool fanOn;
    bool valid;
};

struct LaserDigitalPotShutdownState
{
    bool laserOn;
    bool valid;
};

struct HighLowGainState
{
    bool highLow;
    bool valid;
};

struct SerialNumber
{
    char serial[60];
    bool valid;
};

struct HistogramData
{

    uint16_t binCount0;
    uint16_t binCount1;
    uint16_t binCount2;
    uint16_t binCount3;
    uint16_t binCount4;
    uint16_t binCount5;
    uint16_t binCount6;
    uint16_t binCount7;
    uint16_t binCount8;
    uint16_t binCount9;
    uint16_t binCount10;
    uint16_t binCount11;
    uint16_t binCount12;
    uint16_t binCount13;
    uint16_t binCount14;
    uint16_t binCount15;
    uint16_t binCount16;
    uint16_t binCount17;
    uint16_t binCount18;
    uint16_t binCount19;
    uint16_t binCount20;
    uint16_t binCount21;
    uint16_t binCount22;
    uint16_t binCount23;

    uint8_t bin1TimeToCross;
    uint8_t bin3TimeToCross;
    uint8_t bin5TimeToCross;
    uint8_t bin7TimeToCross;

    uint16_t samplingPeriod;
    uint16_t sampleFlowRate;
    uint16_t temperature;
    uint16_t humidity;

    float pm1;
    float pm2_5;
    float pm10;

    uint16_t rejectCountGlitch;
    uint16_t rejectCountLongTOF;
    uint16_t rejectCountRatio;
    uint16_t rejectCountOutOfRange;
    uint16_t fanRevCount;
    uint16_t laserStatus;
    uint16_t checkSum;
    bool valid;
};

#endif