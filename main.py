from flask import Flask, render_template, request

app = Flask(__name__)


@app.route('/')
def index():
    return render_template('index.html')

@app.route('/submit-your-data', methods=['POST'])
def calculate_footprint():
    # Extracting data from form
    name = request.form.get('name')
    email = request.form.get('email')
    flights_short = int(request.form.get('flightsShort', 1))
    flights_long = int(request.form.get('flightsLong', 1))
    vehicle_type = request.form.get('vehicleType')
    mpg = int(request.form.get('mpg', 30))
    miles_driven = int(request.form.get('milesDriven', 300))
    train_driven = int(request.form.get('trainDriven', 0))
    bus_driven = int(request.form.get('busDriven', 0))
    diet = request.form.get('diet')
    state = request.form.get('states')
    water_bill = int(request.form.get('waterbill', 43))
    propane_bill = int(request.form.get('propanebill', 10))
    people = int(request.form.get('people', 1))
  
    # Calculating footprint  
    name = ""
    email = ""
    flights_short = 1
    flights_long = 1
    vehicle_type = 260
    mpg = 30
    miles_driven = 300
    train_driven = 0
    bus_driven = 0
    diet = 2.5
    state = 5
    water_bill = 43
    propane_bill = 10
    people = 1
    people_factor = 0
    total = 16

    if vehicle_type == "gas":
        vehicle_type = 350
    elif vehicle_type == "hybrid":
        vehicle_type = 260
    else: 
        vehicle_type = 200

    if diet == "meatlover":
        diet = 3.3
    elif diet == "average":
        diet = 2.5
    elif diet == "nobeeforlamb":
        diet = 1.9
    elif diet == "vegetarian":
        diet = 1.7
    else:
        diet = 1.5

    state_values = {
          'AL': 4.046,
          'AK': 4.843,
          'AZ': 3.718,
          'AR': 4.679,
          'CA': 2.412,
          'CO': 5.257,
          'CT': 2.447,
          'DE': 3.052,
          'FL': 3.778,
          'GA': 4.046,
          'HI': 7.408,
          'ID': 2.879,
          'IL': 4.745,
          'IN': 4.745,
          'IA': 4.517,
          'KS': 4.498,
          'KY': 4.226,
          'LA': 3.505,
          'ME': 2.447,
          'MD': 3.052,
          'MA': 2.447,
          'MI': 5.507,
          'MN': 4.517,
          'MS': 3.505,
          'MO': 6.999,
          'MT': 2.879,
          'NE': 4.517,
          'NV': 2.879,
          'NH': 2.447,
          'NJ': 3.052,
          'NM': 3.718,
          'NY': 3.705,
          'NC': 2.902,
          'ND': 4.517,
          'OH': 4.745,
          'OK': 4.679,
          'OR': 2.879,
          'PA': 3.052,
          'RI': 2.447,
          'SC': 2.902,
          'SD': 4.517,
          'TN': 4.226,
          'TX': 3.69,
          'UT': 2.879,
          'VT': 2.447,
          'VA': 2.902,
          'WA': 2.879,
          'WV': 4.745,
          'WI': 4.745,
          'WY': 5.257
      }
    state_selected = request.form.get('states')
    state_value = state_values.get(state_selected, 0)

    #Calculate transportation
    totalflights = (flights_short * 1.35) + (flights_long * .9)
    totalvehicle = (vehicle_type * (miles_driven * 52))/ 1000000
    totaltrain =(train_driven * 1062 * 52) /1000000
    totalbus = (bus_driven * 1739.52 * 52) / 1000000
    totaltransportation = totalflights + totalvehicle + totaltrain + totalbus

    #Calculate diet
    totaldiet = diet
  
    #Calcualte energy
    totalwater =((water_bill / 73)*3)/1000
    totalpropane = ((propane_bill* 61)* 0.0005)
    totalenergy = (totalwater + totalpropane + state_value)
    if people > 1:
      people_factor = 1 + math.log(people)
      totalenergy *= people_factor

    #Calculate total
    total = totaldiet + totaltransportation + totalenergy
    month = (total)/12
    #Returning the results
    return render_template('results.html', name=name, email=email, total=total)
    

    

if __name__ == '__main__':
  app.run(host='0.0.0.0', port=81, debug=True)
