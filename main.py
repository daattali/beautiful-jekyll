from flask import Flask, render_template, request
import sqlite3

app = Flask(__name__)

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

    # Returning the results
    return render_template('results.html', name=name, email=email)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=81, debug=True)
