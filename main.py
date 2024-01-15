from flask import Flask, render_template, request
import sqlite3
from google.oauth2.service_account import Credentials
from googleapiclient.discovery import build

app = Flask(__name__)

# Google Sheets setup
SCOPES = ['https://www.googleapis.com/auth/spreadsheets']
SERVICE_ACCOUNT_FILE = 'path/to/your/service-account.json'  # Replace with your path
SPREADSHEET_ID = 'your-spreadsheet-id'  # Replace with your Spreadsheet ID

creds = None
creds = Credentials.from_service_account_file(
        SERVICE_ACCOUNT_FILE, scopes=SCOPES)

def save_to_sheet(data):
    service = build('sheets', 'v4', credentials=creds)
    sheet = service.spreadsheets()
    values = [data]  # Data should be a list
    body = {
        'values': values
    }
    result = sheet.values().append(
        spreadsheetId=SPREADSHEET_ID,
        range="Sheet1",  # Update with your sheet name
        valueInputOption="USER_ENTERED",
        body=body).execute()

# Database setup
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            email TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

# Initialize the database
init_db()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/submit-your-data', methods=['POST'])
def calculate_footprint():
    # Extracting data from form
    name = request.form.get('name')
    email = request.form.get('email')

    # Insert data into the database
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('INSERT INTO users (name, email) VALUES (?, ?)', (name, email))
    conn.commit()
    conn.close()

    # Save to Google Sheets
    save_to_sheet([name, email])

    # Returning the results
    return render_template('results.html', name=name, email=email)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=81, debug=True)
