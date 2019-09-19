#include <Arduino.h>

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

    float getTempC();
    float getTempF();
    float getHumidity();
};