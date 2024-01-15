from flask import Flask, render_template, request
import math, sqlite3

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/submit-your-data', methods=['POST'])
def calculate_footprint():
    # Extracting data from form
    name = request.form.get('name')
    email = request.form.get('email')
    flights_short = int(request.form.get('flightsShort', 0))
    flights_long = int(request.form.get('flightsLong', 0))
    vehicle_type = request.form.get('vehicleType', 'electric') # Default to electric
    mpg = int(request.form.get('mpg', 30))
    miles_driven = int(request.form.get('milesDriven', 0))
    train_driven = int(request.form.get('trainDriven', 0))
    bus_driven = int(request.form.get('busDriven', 0))
    diet = request.form.get('diet', 'vegan') # Default to vegan
    state = request.form.get('states')
    water_bill = int(request.form.get('waterbill', 0))
    propane_bill = int(request.form.get('propanebill', 0))
    people = int(request.form.get('people', 1))

    # Vehicle type mapping
    vehicle_types = {
        "gas": 350,
        "hybrid": 260,
        "electric": 200
    }
    vehicle_type = vehicle_types.get(vehicle_type, 200) # Default to electric if unknown type

    # Diet mapping
    diet_types = {
        "meatlover": 3.3,
        "average": 2.5,
        "nobeeforlamb": 1.9,
        "vegetarian": 1.7,
        "vegan": 1.5
    }
    diet = diet_types.get(diet, 1.5) # Default to vegan if unknown type

    # State emissions factors
    state_values = {
        # ... (keep your state values here)
    }
    state_value = state_values.get(state, 0)

    # Calculate transportation
    totalflights = (flights_short * 1.35) + (flights_long * 0.9)
    totalvehicle = (vehicle_type * (miles_driven * 52)) / 1000000
    totaltrain = (train_driven * 1062 * 52) / 1000000
    totalbus = (bus_driven * 1739.52 * 52) / 1000000
    totaltransportation = totalflights + totalvehicle + totaltrain + totalbus

    # Calculate diet
    totaldiet = diet
  
    # Calculate energy
    totalwater = ((water_bill / 73) * 3) / 1000
    totalpropane = ((propane_bill * 61) * 0.0005)
    totalenergy = totalwater + totalpropane + state_value
    if people > 1:
        people_factor = 1 + math.log(people)
        totalenergy *= people_factor

    # Calculate total
    total = totaldiet + totaltransportation + totalenergy
    month = total / 12

    # Returning the results
    return render_template('results.html', name=name, email=email, total=total, month=month)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=81, debug=True)
