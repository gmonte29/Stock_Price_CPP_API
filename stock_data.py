import requests

# replace the "demo" apikey below with your own key from https://www.alphavantage.co/support/#api-key
url = 'https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=MSFT&apikey=demo'
r = requests.get(url)
data = r.json()

# Extract the latest date and closing price
latest_date = max(data['Time Series (Daily)'].keys())
latest_price = float(data['Time Series (Daily)'][latest_date]['4. close'])

# Print the results
print(f"Latest Date: {latest_date}")
print(f"Latest Closing Price for IBM: ${latest_price:.2f}")
