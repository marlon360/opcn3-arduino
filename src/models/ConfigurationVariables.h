#include <Arduino.h>

struct ConfigurationVariables
{

    uint16_t binBoundriesADC0;
    uint16_t binBoundriesADC1;
    uint16_t binBoundriesADC2;
    uint16_t binBoundriesADC3;
    uint16_t binBoundriesADC4;
    uint16_t binBoundriesADC5;
    uint16_t binBoundriesADC6;
    uint16_t binBoundriesADC7;
    uint16_t binBoundriesADC8;
    uint16_t binBoundriesADC9;
    uint16_t binBoundriesADC10;
    uint16_t binBoundriesADC11;
    uint16_t binBoundriesADC12;
    uint16_t binBoundriesADC13;
    uint16_t binBoundriesADC14;
    uint16_t binBoundriesADC15;
    uint16_t binBoundriesADC16;
    uint16_t binBoundriesADC17;
    uint16_t binBoundriesADC18;
    uint16_t binBoundriesADC19;
    uint16_t binBoundriesADC20;
    uint16_t binBoundriesADC21;
    uint16_t binBoundriesADC22;
    uint16_t binBoundriesADC23;
    uint16_t binBoundriesADC24;

    uint16_t binBoundriesDiametor0;
    uint16_t binBoundriesDiametor1;
    uint16_t binBoundriesDiametor2;
    uint16_t binBoundriesDiametor3;
    uint16_t binBoundriesDiametor4;
    uint16_t binBoundriesDiametor5;
    uint16_t binBoundriesDiametor6;
    uint16_t binBoundriesDiametor7;
    uint16_t binBoundriesDiametor8;
    uint16_t binBoundriesDiametor9;
    uint16_t binBoundriesDiametor10;
    uint16_t binBoundriesDiametor11;
    uint16_t binBoundriesDiametor12;
    uint16_t binBoundriesDiametor13;
    uint16_t binBoundriesDiametor14;
    uint16_t binBoundriesDiametor15;
    uint16_t binBoundriesDiametor16;
    uint16_t binBoundriesDiametor17;
    uint16_t binBoundriesDiametor18;
    uint16_t binBoundriesDiametor19;
    uint16_t binBoundriesDiametor20;
    uint16_t binBoundriesDiametor21;
    uint16_t binBoundriesDiametor22;
    uint16_t binBoundriesDiametor23;
    uint16_t binBoundriesDiametor24;

    uint16_t binWeightings0;
    uint16_t binWeightings1;
    uint16_t binWeightings2;
    uint16_t binWeightings3;
    uint16_t binWeightings4;
    uint16_t binWeightings5;
    uint16_t binWeightings6;
    uint16_t binWeightings7;
    uint16_t binWeightings8;
    uint16_t binWeightings9;
    uint16_t binWeightings10;
    uint16_t binWeightings11;
    uint16_t binWeightings12;
    uint16_t binWeightings13;
    uint16_t binWeightings14;
    uint16_t binWeightings15;
    uint16_t binWeightings16;
    uint16_t binWeightings17;
    uint16_t binWeightings18;
    uint16_t binWeightings19;
    uint16_t binWeightings20;
    uint16_t binWeightings21;
    uint16_t binWeightings22;
    uint16_t binWeightings23;

    uint16_t pmDiametorA;
    uint16_t pmDiametorB;
    uint16_t pmDiametorC;

    uint16_t maximumTimeOfFlight;
    uint16_t AMSamplingIntervalCount;
    uint16_t AMIdleIntervalCount;
    uint16_t AMMaxDataArraysInFile;

    uint8_t AMOnlySavePMData;
    uint8_t AMFanOnInIdle;

    bool valid;

    String toString();
};