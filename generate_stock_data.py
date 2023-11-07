import csv
import random
import os
from datetime import datetime, timedelta

# List of company names
companies = ['CompanyA', 'CompanyB', 'CompanyC', 'CompanyD', 'CompanyE']

# Function to generate random stock prices for 500 days
def generate_stock_data(days=500):
    start_date = datetime(2023, 1, 1)  # Start date for the stock prices
    end_date = start_date + timedelta(days=days - 1)  # End date for the stock prices
    
    dates = [start_date + timedelta(days=i) for i in range(days)]
    prices = [random.uniform(50, 500) for _ in range(days)]
    
    # Combine dates and prices into a list of tuples
    stock_data = list(zip(dates, prices))
    stock_data.sort(key=lambda x: x[0])  # Sort stock data by dates
    
    return stock_data

# Create a directory to store CSV files
if not os.path.exists('stock_data'):
    os.makedirs('stock_data')

# Generate and save stock prices for each company
for company in companies:
    stock_data = generate_stock_data()
    csv_file_path = f'stock_data/{company}_stock_prices.csv'
    
    with open(csv_file_path, 'w', newline='') as csvfile:
        csvwriter = csv.writer(csvfile)
        csvwriter.writerow(['Date', 'Stock Price'])
        
        for date, price in stock_data:
            formatted_date = date.strftime('%Y-%m-%d')
            csvwriter.writerow([formatted_date, price])
    
    print(f'Stock prices for {company} generated and saved to {csv_file_path}')
