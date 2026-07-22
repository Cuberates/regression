import requests

API_KEY = ''
SYMBOL = 'IBM'


with open("api_key.env", "r", encoding="utf-8") as file: 
  API_KEY = file.read()
  print(API_KEY)

url = 'https://www.alphavantage.co/query?function=REALTIME_OPTIONS&symbol='+SYMBOL+'&apikey='+API_KEY
print(url)

r = requests.get(url)
market_data = r.json()

