#include "HistogramData.h"

float HistogramData::getTempC()
{
    return -45 + 175 * (temperature / (pow(2, 16) - 1));
}
float HistogramData::getTempF()
{
    return -49 + 347 * (temperature / (pow(2, 16) - 1));
}
float HistogramData::getHumidity()
{
    return 100 * (humidity / (pow(2, 16) - 1));
}

String HistogramData::toString() {

    String info = "-----DACandPowerStatus-----\n";
    info += "Validity: ";
    info += valid;
    info += "\n";
    info += "Bin Counts\n";
    info += binCount0;
    info += " ";
    info += binCount1;
    info += " ";
    info += binCount2;
    info += " ";
    info += binCount3;
    info += " ";
    info += binCount4;
    info += " ";
    info += binCount5;
    info += " ";
    info += binCount6;
    info += " ";
    info += binCount7;
    info += " ";
    info += binCount8;
    info += " ";
    info += binCount9;
    info += " ";
    info += binCount10;
    info += " ";
    info += binCount11;
    info += " ";
    info += binCount12;
    info += " ";
    info += binCount13;
    info += " ";
    info += binCount14;
    info += " ";
    info += binCount15;
    info += " ";
    info += binCount16;
    info += " ";
    info += binCount17;
    info += " ";
    info += binCount18;
    info += " ";
    info += binCount19;
    info += " ";
    info += binCount20;
    info += " ";
    info += binCount21;
    info += " ";
    info += binCount22;
    info += " ";
    info += binCount23;
    info += " ";

    info += "-------------------------------------------------\n";
    info += "Time To Cross\n";
    info += bin1TimeToCross;
    info += " ";
    info += bin3TimeToCross;
    info += " ";
    info += bin5TimeToCross;
    info += " ";
    info += bin7TimeToCross;
    info += "\n";

    info += "-------------------------------------------------\n";
    info += "Sampling Period\n";
    info += samplingPeriod;
    info += "\n";
    info += "-------------------------------------------------\n";
    info += "Sample Flow Rate\n";
    info += sampleFlowRate;
    info += "\n";
    info += "-------------------------------------------------\n";
    info += "Temperature\n";
    info += temperature;
    info += "\n";
    info += "-------------------------------------------------\n";
    info += "Humidity\n";
    info += humidity;
    info += "\n";
    info += "-------------------------------------------------\n";
    info += "pm1\n";
    info += pm1;
    info += "\n";
    info += "-------------------------------------------------\n";
    info += "pm2.5\n";
    info += pm2_5;
    info += "\n";
    info += "-------------------------------------------------\n";
    info += "pm10\n";
    info += pm10;
    info += "\n";
    info += "-------------------------------------------------\n";

    info += "MSLNS\n";

    info += rejectCountGlitch;
    info += " ";
    info += rejectCountLongTOF;
    info += " ";
    info += rejectCountRatio;
    info += " ";
    info += rejectCountOutOfRange;
    info += " ";
    info += fanRevCount;
    info += " ";
    info += laserStatus;
    info += " ";
    info += checkSum;
    info += "\n";

    return info;
}