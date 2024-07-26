import sys
import plotext as plt
import yfinance as yf

file = open(".stock.txt", "r")
stock = file.read(20)
plt.date_form("d/m/Y")
start = plt.string_to_datetime("01/01/2023")
end = plt.today_datetime()
data = yf.download(stock, start, end)
dates = plt.datetimes_to_string(data.index)

plt.clf()
plt.theme("dark")
plt.candlestick(dates, data)
plt.title("Press Enter to Return...")
plt.show()
file.close()
input("")