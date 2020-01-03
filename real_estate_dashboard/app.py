#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec 13 10:49:02 2019

@author: Bobby
"""

# importing flask module fro
from flask import Flask, render_template,request
import delete

# initializing a variable of Flask
app = Flask(__name__)


# decorating index function with the app.route with url as /login
@app.route('/login')
def index():
    return render_template('login.html')

@app.route('/FlaskTutorial',  methods=['POST'])
def success():
    if request.method == 'POST':
        #email = request.form['email']
        #return render_template('success.html', email=email)
        address = request.form['address']
        zipcode = request.form['zipcode']
        zestimate = delete.zillow_info(address, zipcode) 
        return render_template('success.html', zestimate = zestimate)
    else:
        pass

if __name__ == "__main__":
    app.run()
