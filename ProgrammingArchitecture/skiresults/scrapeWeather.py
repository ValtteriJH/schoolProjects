import io   
import os
import urllib3
from bs4 import BeautifulSoup


def makeSoup(url):
    http = urllib3.PoolManager()
    r = http.request("GET", url)
    return BeautifulSoup(r.data,'lxml')



def writer(Data):

    numbersCheck = 0

    with io.open("weatherData.txt", 'w', encoding='utf8') as file:
        for year in Data:
            file.write("\n~{}\n".format(year))
            statList = []
            for i in Data[year]:
                if Data[year][i] != 'NaN':
                    statList.append("{}:{:.2f}".format(i, Data[year][i]))
                else:
                    statList.append("{}:{}".format(i, Data[year][i]))
            stringForm = ";".join(statList)
            file.write(stringForm)
    print(numbersCheck)
    file.close()



def main():
    years = {}
    with io.open('dates.txt', 'r', encoding='utf8') as file:
        for line in file:
            line = line.strip()
            listForm = line.split('-')
            if listForm[0] not in years:
                years[listForm[0]] = [line]
                years[listForm[0]].append(line)
            else:
                if years[listForm[0]][1] != line:
                    parts = years[listForm[0]][1].split('-')
                    if int(listForm[2]) > int(parts[2]):
                        years[listForm[0]][1] = line


        file.close()
    
    # Debug
    """     for i in years:
        print(i)
        print(years[i])
    print(len(years))  """
   

    

    url = '''
            http://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=fmi::observations::weather::daily::simple&place=lahti&::&starttime={}T00:00:00Z&::&endtime={}T20:00:00Z&
            '''.format(years['1997'][0],years['1997'][1]).strip()

    allowedTags = ['rrday', 'tday', 'snow', 'tmin', 'tmax']

    Data = {}
    for year in years:
        url = '''
            http://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id=fmi::observations::weather::daily::simple&place=lahti&::&starttime={}T00:00:00Z&::&endtime={}T00:00:00Z&
            '''.format(years[year][0],years[year][1]).strip()
        curWeatherData = makeSoup(url)
        
        weatherElements = {}
        print(year)
        for i in curWeatherData.findAll("wfs:member"):
            element = i.find("bswfs:bswfselement")
            piece = element.find("bswfs:parametername")
            value = element.find("bswfs:parametervalue")
            piece = piece.text
            value = value.text
            if value == 'NaN':
                continue
            value = float(value)
            
            if piece not in allowedTags:
                continue

            if piece not in weatherElements:
                if value == 'nan':
                    weatherElements[piece] = [0]
                else:
                    weatherElements[piece] = [value]
            elif weatherElements[piece] != ['nan']:
                weatherElements[piece].append(value)

            print(piece, value)
        
        for stat in weatherElements:
            if len(weatherElements[stat]) == 1:
                weatherElements[stat] = weatherElements[stat][0]
            else:
                weatherElements[stat] = sum(weatherElements[stat]) / len(weatherElements[stat])   # Averaging the results
        for i in allowedTags:
            if i not in weatherElements:
                weatherElements[i] = 'NaN'

        Data[year] = weatherElements
    
    for i in Data:
        print(i)
        print(Data[i])

    writer(Data)

    

main()