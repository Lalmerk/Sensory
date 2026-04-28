#pragma once
//the warning are effect-based classification by PAGASA see https://pubfiles.pagasa.dost.gov.ph/climps/climateforum/speciallecture.pdf
int Warning(float C)
{
    if (C < 27.0) 
    {
        return 0; // Normal: Below the first PAGASA threshold
    }
    else if (C < 33.0) 
    {
        return 1; // 27 to 32.99: Caution
    }
    else if (C < 42.0) 
    {
        return 2; // 33 to 41.99: Extreme Caution
    }
    else if (C < 52.0) 
    {
        return 3; // 42 to 51.99: Danger
    }
    else 
    {
        return 4; // 52 and beyond: Extreme Danger
    }
}