import csv
import random
from datetime import datetime, timedelta

# List of stock symbols for which data will be generated
symbols = ["AAPL", "GOOG", "AMZN", "TSLA", "MSFT"]

# Number of data points per symbol
data_points_per_symbol = 1000000

# Date range for the dataset
start_date = datetime(2023, 1, 1)
end_date = datetime(2023, 12, 31)

# Generate and write stock data to CSV file
with open('stock_data_large.csv', 'w', newline='') as csvfile:
    fieldnames = ['Date', 'Symbol', 'Price']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()

    for _ in range(data_points_per_symbol):
        date = start_date + timedelta(days=random.randint(0, (end_date - start_date).days))
        symbol = random.choice(symbols)
        price = round(random.uniform(50, 1500), 2)  # Random price between 50 and 1500
        writer.writerow({'Date': date.strftime('%Y-%m-%d'), 'Symbol': symbol, 'Price': price})

print(f"Generated {len(symbols) * data_points_per_symbol} data points. Output saved to stock_data_large.csv.")
