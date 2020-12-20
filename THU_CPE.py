from bs4 import BeautifulSoup
import requests

# fetch the web source
url = "http://140.128.102.136/Ranking"
req = requests.get (url)
soup = BeautifulSoup (req.text, "html.parser")



# fetch the data from the soup object
grade = 0
percentage = ''
for AC in soup.find_all ('a'):
	if (str (AC.get ('href'))[20:29] == 's08351050'):
		grade = int (str (AC.text))
		div_tag = AC.parent
		percentage = str (div_tag.find_next ('span').text).strip ().split ()[1]
		break


# output
print ("THU CPE: {:d} AC".format (grade) + '(' + percentage + ')')
