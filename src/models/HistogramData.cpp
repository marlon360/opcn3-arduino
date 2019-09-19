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