from selenium import webdriver
from time import sleep
from bs4 import BeautifulSoup
import io   ## UTF 8
import hashlib
from selenium.webdriver.chrome.options import Options




def nextYear():
    with open(__file__, 'r') as f:
        lines = f.read().split('\n')
        val = int(lines[25].split(' = ')[-1])
        new_line = '        self.yearIndexOnMenu = {}'.format(val+1)
        new_file = '\n'.join(lines[0:25]+ [new_line] + lines[26:])

    with open(__file__, 'w') as f:
        f.write(new_file)
    
class DataScraper:
    def __init__(self, amount):

        self.driver = webdriver.Chrome()
        self.driver.get("https://www.finlandiahiihto.fi/Tulokset/Tulosarkisto")
        self.yearIndexOnMenu = 1
        #5
        self.qPerYear = amount + 1
        self.__sorted = 0
        sleep(2)
        chrome_options = Options()
        chrome_options.add_argument("--headless")




    def scrapeData(self, choice):
    
        yearSelector = self.driver.find_element_by_id('dnn_ctr1025_Etusivu_ddlVuosi2x')


         
        year = yearSelector.find_elements_by_tag_name('option')[self.yearIndexOnMenu]  
        year.click()
        routeSelector = self.driver.find_element_by_id('dnn_ctr1025_Etusivu_ddlMatka2x')
        route = routeSelector.find_elements_by_tag_name('option')[0]
        route.click()

        '''
        # activate for years 84 - 82
        if choice == 0:
            choiceMen = '/html/body/form/div[4]/div/div[6]/div/div[1]/div[1]/div/div[2]/div/div/table/tbody/tr[4]/td/div/table/tbody/tr[1]/td/table/tbody/tr[3]/td[2]/table/tbody/tr/td[2]/input'
            choice = choiceMen
        else:
            choiceWomen = '/html/body/form/div[4]/div/div[6]/div/div[1]/div[1]/div/div[2]/div/div/table/tbody/tr[4]/td/div/table/tbody/tr[1]/td/table/tbody/tr[3]/td[2]/table/tbody/tr/td[3]/input'
            choice = choiceWomen
        
        choiceButton = self.driver.find_element_by_xpath(choice)
        choiceButton.click()

        '''

        self.driver.find_element_by_id('dnn_ctr1025_Etusivu_cmdHaeTulokset').click() #sivun päivitys
        sleep(10)
        

        # Ei tarvita vuoden 90 jälkeen kun ainoa kisa on P75
        if self.__sorted == 0:      # Järjestellään reittien mukaan kerran koska valinta säilyy sivujen välillä
            sleep(15)
            sortButton = self.driver.find_element_by_xpath("/html/body/form/div[4]/div/div[6]/div/div[1]/div[1]/div/div[2]/div/div/table/tbody/tr[4]/td/div/table/tbody/tr[2]/td/div/table/tbody/tr[3]/td/div/table/thead/tr/th[2]/a")
            # By name sortButton = self.driver.find_element_by_xpath('/html/body/form/div[4]/div/div[6]/div/div[1]/div[1]/div/div[2]/div/div/table/tbody/tr[4]/td/div/table/tbody/tr[2]/td/div/table/tbody/tr[3]/td/div/table/thead/tr/th[8]/a')
            sortButton.click()

            self.__sorted = 1
        

        masterTableId = 'dnn_ctr1025_Etusivu_dgrTulokset_ctl00'
        soup = BeautifulSoup(self. driver.page_source, 'html.parser')       #BS TESTI
                 
        table = soup.find(id = masterTableId).tbody.find_all('tr')
        yearResults = []
        for one in table:
            parts = one.find_all('td')
            result = []
            for index in range(len(parts)):
                ingredient = parts[index].get_text()
                ingredient.replace("&nbsp", "0")

                if index == 0:
                    continue
                ingredient = ingredient.title()
                result.append(ingredient)
            
            atheleteData = createID(result)
            yearResults.append(atheleteData)


        return yearResults
        # print(table)
        #84 83 82 vajaat tulokset


                
def writer(allData, currentYear):
    #file = open("skiDataByYearAndRoutes.txt", "a")
    numbersCheck = 0

    with io.open("skiDataByYearAndRoutes2.txt", 'a', encoding='utf8') as file:
        file.write("~{}\n".format(currentYear))
        currentYear = currentYear - 1
        currentRoute = ""
        for result in allData:
            if result[1] != currentRoute:
                currentRoute = result[1]
                file.write("#{}\n".format(currentRoute))
            numbersCheck += 1
            stringForm = ";".join(result)
            file.write('{}\n'.format(stringForm))
    print(numbersCheck)
    file.close()

def createID(result):
    ingredients = "".join(result[6] + result[7] + result[9])
    ID = str(hashlib.md5(ingredients.encode('utf-8', errors='replace')).hexdigest())
    result = [ID] + result
    return result


def main():
    #                         v Kuinka monta tulosta haetaan per sivu
    datascraper = DataScraper(float('inf')) # 1700 reaches out to 2nd race of the year
    # float('inf')
    currentYear = 2020 - datascraper.yearIndexOnMenu
    # if mem < yearSelector.find_elements_by_tag_name('option'): # kaikki vuodet
    curYearData = datascraper.scrapeData(0) # 0 miehet 1 naiset

    writer(curYearData, currentYear)


    sleep(10)
    nextYear()
    
    
main()
