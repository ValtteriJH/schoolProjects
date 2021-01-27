#include "controller.h"

Controller::Controller(TableModel *tbmodel, QStringListModel *rctagModel, ChartModel *chmodel, QObject *parent) : QObject (parent)
{
    racetagModel = rctagModel;
    tableModel = tbmodel;
    chartmodel = chmodel;
}

std::vector<QString> Controller::getEveryYear()
{
    auto var = dataHandler.raceTagsYearly();
    std::vector<QString> toReturn;
    for(auto i : var)
    {
        toReturn.push_back(QString::number(i.first));
    }
    return toReturn;
}

class timeFormatException: public std::exception
{
  virtual const char* what() const noexcept
  {
    return "Time given in wrong format";
  }
} timeFormatEx;


void Controller::logError(std::string msg)
{
    std::cout << msg << std::endl;
}

void Controller::callShowResultsInQML(int tableType)
{
    // Tabletypes:
    // 1 : Table
    // 2 : Chart
    emit showResults(tableType);
}

void Controller::callShowWeather(Weather weather)
{
    QString rain = QString::fromStdString(weather.rainFall);
    QString temp = QString::fromStdString(weather.aveTempt);
    QString snow = QString::fromStdString(weather.snowLevel);
    QString minTemp = QString::fromStdString(weather.minTempt);
    QString maxTemp = QString::fromStdString(weather.maxTempt);

    emit showWeather(rain, temp, snow, minTemp, maxTemp);
}


TimeT Controller::convertToTimeT(QString str)
{
    // time as string in form h:mm:ss.ss
    std::string s = str.toStdString();


    size_t n = static_cast<unsigned int>(std::count(s.begin(), s.end(), ':'));
    if(n != 2)
    {
        throw timeFormatEx;
    }

    std::string delimiter = ":";
    size_t pos = 0;
    std::vector<std::string> token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    token.push_back(s);

    // time as string in form h:mm:ss.ss
    return TimeT(token[0],token[1],token[2]);
}



void Controller::search(QString state, QString year1, QString year2, QString starttime,
                        QString endtime, QString racetag1, QString racetag2,
                        QString athletename, QString sizeofranking, QString gender, QString choice)
{
    // Different state IDs:
    // readbytime = 1
    // compareresultbyyear = 2
    // comparedistancebyyear = 3
    // showstatsbyeachyear = 4
    // athletetimedevelopment= 5
    // averagespeedbyranking = 6
    // bestathletebygenderinperiod = 7
    // showsortedresultsbyclubname = 8
    // showathletedistributionbycountry = 9
    // showtenbestteams = 10

    if(state == "1")
    {
        if(year1 == "" || starttime == "" || endtime == "" || racetag1 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int year = std::stoi(year1.toStdString());
            TimeT stime = convertToTimeT(starttime);
            TimeT etime = convertToTimeT(endtime);
            std::string rctag = racetag1.toStdString();
            if(stime > etime)
            {
                QString message = "Start time cannot be greater than finish time.";
                emit badInputSignal(message);
            }
            else
            {
                auto var = dataHandler.readByTime(year,stime,etime,rctag);
                auto result = dataconverter.readbytime(var);
                tableModel->changeData(result);
                callShowResultsInQML(1);

                Weather weather = dataHandler.getWeather(year);
                callShowWeather(weather);

            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else if(state == "2")
    {
        if(year1 == "" || year2 == "" || racetag1 == "" || sizeofranking == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int firstyear = std::stoi(year1.toStdString());
            int secondyear = std::stoi(year2.toStdString());
            int sizeOfList = std::stoi(sizeofranking.toStdString());
            std::string rctag = racetag1.toStdString();
            if(firstyear > secondyear)
            {
                QString message = "First year cannot be greater than second year.";
                emit badInputSignal(message);
            }
            else
            {
                auto var = dataHandler.compareResultByYear(rctag,firstyear,secondyear,sizeOfList);
                auto result = dataconverter.compareResultByYear(var);
                tableModel->changeData(result);
                callShowResultsInQML(1);
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else if(state == "3")
    {
        if(racetag1 == "" || racetag2 == "" || year1 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int year = std::stoi(year1.toStdString());
            std::string rctag1 = racetag1.toStdString();
            std::string rctag2 = racetag2.toStdString();
            if(rctag1 == rctag2)
            {
                QString message = "Racetags cannot be same.";
                emit badInputSignal(message);
            }
            else
            {
                auto var = dataHandler.compareDistanceByYear(rctag1,rctag2,year);
                auto result = dataconverter.compareDistanceByYear(var);
                tableModel->changeData(result);
                callShowResultsInQML(1);

                Weather weather = dataHandler.getWeather(year);
                callShowWeather(weather);
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else if(state == "4")
    {
        auto var = dataHandler.statsByEachYear();
        auto result = dataconverter.statsByEachYear(var);
        tableModel->changeData(result);
        callShowResultsInQML(1);
    }
    else if(state == "5")
    {
        if(athletename == "" || year1 == "" || year2 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int firstyear = std::stoi(year1.toStdString());
            int secondyear = std::stoi(year2.toStdString());
            std::string athName = athletename.toStdString();
            if(firstyear > secondyear)
            {
                QString message = "First year cannot be greater than second year.";
                emit badInputSignal(message);
            }
            else
            {
                auto var = dataHandler.athleteTimeDevelopment(athName,firstyear,secondyear);
                auto result = dataconverter.athleteTimeDevelopment(var);
                tableModel->changeData(result);
                chartmodel->addAtheleteDevelopmentData(result);
            }
            if(choice == "Chart")
            {
                callShowResultsInQML(2);
            }
            else if(choice == "Table")
            {
                callShowResultsInQML(1);
            }
            else
            {
                // Error
            }

        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else if(state == "6")
    {
        if(sizeofranking == "" || year1 == "" || year2 == "" || racetag1 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int firstyear = std::stoi(year1.toStdString());
            int secondyear = std::stoi(year2.toStdString());
            int sizeOfList = std::stoi(sizeofranking.toStdString());
            std::string rctag = racetag1.toStdString();
            if(firstyear > secondyear)
            {
                QString message = "First year cannot be greater than second year.";
                emit badInputSignal(message);
            }
            else
            {
                auto var = dataHandler.averageSpeedByRanking(firstyear,secondyear,sizeOfList,rctag);
                auto result = dataconverter.averageSpeedByRanking(var,rctag);
                tableModel->changeData(result);
                callShowResultsInQML(1);
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else if(state == "7")
    {
        // View: Table
        // year1, year2, gender, racetag
        // std::shared_ptr<Athlete>
        if(gender == "" || year1 == "" || year2 == "" || racetag1 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int firstyear = std::stoi(year1.toStdString());
            int secondyear = std::stoi(year2.toStdString());
            std::string athletegender = gender.toStdString();
            std::string rctag = racetag1.toStdString();
            if(firstyear > secondyear)
            {
                QString message = "First year cannot be greater than second year.";
                emit badInputSignal(message);
            }
            else
            {
                auto var = dataHandler.bestAthleteByGenderInPeriod(athletegender,firstyear,secondyear,rctag);
                auto result = dataconverter.bestAthleteByGenderInPeriod(var);
                tableModel->changeData(result);
                callShowResultsInQML(1);
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }
    else if(state == "8")
    {
        // View: Table
        if(year1 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            // Time Conversion
            int firstyear = std::stoi(year1.toStdString());
            auto var =  dataHandler.sortedResultsByClubName(firstyear);
            auto result = dataconverter.sortedResultsByClubName(var, firstyear);
            tableModel->changeData(result);
            callShowResultsInQML(1);

            Weather weather = dataHandler.getWeather(firstyear);
            callShowWeather(weather);
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else if(state == "9")
    {
        auto var =  dataHandler.athleteDistributionByCountry();
        auto result = dataconverter.athleteDistributionByCountry(var);
        tableModel->changeData(result);
        callShowResultsInQML(1);
    }
    else if(state == "10")
    {
        // View: Table
        if(year1 == "" || racetag1 == "")
        {
            logError("Not enough parameters");
            return;
        }
        try
        {
            int firstyear = std::stoi(year1.toStdString());
            std::string rctag = racetag1.toStdString();

            auto var =  dataHandler.tenBestTeams(firstyear,rctag);
            auto result = dataconverter.tenBestTeams(var);
            tableModel->changeData(result);
            callShowResultsInQML(1);

            Weather weather = dataHandler.getWeather(firstyear);
            callShowWeather(weather);
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';;
        }
    }
    else
    {
        // Throw error
    }
}

void Controller::setNewRaceTags(int searchType, QString year1, QString year2)
{
    // searchtypes that have two inputs 2,5,6,7
    // If there is two years in input, newracetags is populated
    // with racetags that exists in both years
    if(searchType == 2 || searchType == 5 || searchType == 6 || searchType == 7)
    {
        int firstyear = std::stoi(year1.toStdString());
        int secondyear = std::stoi(year2.toStdString());
        auto data = dataHandler.raceTagsYearly();
        QStringList newRaceTags;
        newRaceTags.append("");
        for(auto firstRacetag : data[firstyear])
        {
            for(auto secondRacetag : data[secondyear])
            {
                if(secondRacetag == firstRacetag)
                {
                    newRaceTags.append(QString::fromStdString(firstRacetag));
                    break;
                }
            }
        }
        racetagModel->setStringList(newRaceTags);
    }
    else
    {
        int year = std::stoi(year1.toStdString());
        auto data = dataHandler.raceTagsYearly();
        QStringList newRaceTags;
        newRaceTags.append("");
        for(auto i : data[year])
        {
            newRaceTags.append(QString::fromStdString(i));
        }
        racetagModel->setStringList(newRaceTags);
    }
}



