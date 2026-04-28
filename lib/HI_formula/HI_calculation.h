#pragma once

/*
    HEAT INDEX EQUATION is
    obtained by multiple
    regression analysis (from
    Steadman’s table) carried
    out by Rothfusz (1990)

*/

const float c1 = -42.379;
const float c2 = 2.04901523;
const float c3 = 10.14333127;
const float c4 = -0.22475541;
const float c5 = -0.00683783;
const float c6 = -0.05481717;
const float c7 = 0.00122874;
const float c8 = 0.00085282;
const float c9 = -0.00000199;

/*float term1 = c1;
float term2 = c2 * T;
float term3 = c3 * R;
float term4 = c4 * T * R;
float term5 = c5 * T * T;
float term6 = c6 * R * R;
float term7 = c7 * T * T * R;
float term8 = c8 * T * R * R;
float term9 = c9 * T * T * R * R;
*/

float convertToFahrenheit(float TempCelsius)
{
    float F = (TempCelsius * 1.8 ) + 32 ;

    return F;
}

float convertToCelsius(float TempF)
{
    float C = (TempF-32) / 1.8;

    return C;
}

// steadmansCal 

float SteadmanFormula(float T, float R)
{
    float heatIndexF;
    float HI;

    float term1 = c1;
    float term2 = c2 * T;
    float term3 = c3 * R;
    float term4 = c4 * T * R;
    float term5 = c5 * T * T;
    float term6 = c6 * R * R;
    float term7 = c7 * T * T * R;
    float term8 = c8 * T * R * R;
    float term9 = c9 * T * T * R * R;

    heatIndexF = term1 + term2 + term3 + term4 + term5 + term6 + term7 + term8 + term9;

   HI = convertToCelsius(heatIndexF);

   return HI;

}


