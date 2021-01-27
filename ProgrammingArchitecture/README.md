# SkiResults-applikaatio

Tervetuloa lukemaan meidän uuden ja upean SkiResults-sovelluksen toiminnasta. 
Ohjelmointiympäristönä käytimme Qt Creatoria Qt:n versiolla 5.12 Windows:lla ja
frontend-ratkaisumme ei toimi Linux-etätyöpöydällä. QML:stä käytimme versiota 14.2.

Kaikki sovelluksen käyttämiseen tarvittava data löytyy reposta: eli ei tarvitse 
erikseen hakea dataa mistään, pelkkä kloonaaminen riittää. Mikäli kuitenkin 
haluaa hakea data erikseen, tulee ajaa datascraper.py hiihtidatan hakemiseen ja 
scrapeWeather.py säädatan hakemiseen.

Varoiksi: Datascraper ajetaan vuosikohtaisesti, eli muuttamalla yearIndexOnMenu 
arvoa riviltä 26 saadaan valittua vuosi.Jos useampi peräkkäin halutaan niin
ohjelma muuttaa onnistuneen scrapeuksen jälkeen arvoa eteenpäin, joten valitse 
haluamasi vuosi,ja aja niin monesti kun haluat scrapeta vuosia eteenpäin.
Vuodet appendataan datan loppuun.

Lisätietoa sovellusen toiminnasta löytyy dokumentaatiosta ja UML-kaaviosta.
Master haarasta löytyy "Loppupalautus" tägi.
