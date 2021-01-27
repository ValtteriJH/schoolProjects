#include "weather.h"


Weather::Weather()
{

}

Weather::Weather(int year_, std::string rainfall_, std::string aveTempt_, std::string snowLevel_, std::string minTempt_, std::string maxTempt_)
{
    year = year_;
    aveTempt = aveTempt_;
    snowLevel = snowLevel_;
    minTempt = minTempt_;
    maxTempt = maxTempt_;
    //if(rainfall_ != NO_DATA && std::stof(rainfall_) < 0) rainFall = NO_RAIN;
    //else
    rainFall = rainfall_;
}
