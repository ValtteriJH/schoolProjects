#ifndef WEATHER_H
#define WEATHER_H
#include <string>

const std::string NO_RAIN = "-1"; // no rain at all
const std::string LITTLE_RAIN = "0"; // rainfall under 0.1 mm
//const std::string NO_DATA = "No data"; // no weather data measured

class Weather
{
public:
    Weather();

    ///
    /// \brief Weather, NaN is permitted parameter value
    /// \note rainfall values: if value less than zero -> NO_RAIN
    ///                        otherwise the value it self
    /// \param year_
    /// \param rainfall_
    /// \param aveTempt_
    /// \param snowLevel_
    /// \param minTempt_
    /// \param maxTempt_
    ///
    Weather(int year_, std::string rainfall_, std::string aveTempt_, std::string snowLevel_, std::string minTempt_, std::string maxTempt_);

    int year;
    std::string rainFall;
    std::string aveTempt;
    std::string snowLevel;
    std::string minTempt;
    std::string maxTempt;
};
const Weather NO_WEATHER(-1,"NO_DATA","NO_DATA","NO_DATA","NO_DATA","NO_DATA");

#endif // WEATHER_H
