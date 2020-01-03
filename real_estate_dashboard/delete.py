#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jan  2 11:55:04 2020

@author: kritigupta
"""

# -*- coding: utf-8 -*-
"""
Spyder Editor

Purpose: To build a real estate dashboard.

This is a temporary script file.
"""
def zillow_info(address, zipcode):
    # import packages
    import pyzillow
    from pyzillow.pyzillow import ZillowWrapper, GetDeepSearchResults
    import pandas as pd
    import app
    
    # import address listn housing data, and neighborhood mapping
    # address_data = pd.read_csv('/Users/kritigupta/Desktop/Real Estate Dashboard/master_address_list.csv')
    housing_data = pd.read_csv('/Users/kritigupta/Desktop/Real Estate Dashboard/housing_data.csv')
    neighborhood_mapping = pd.read_csv('/Users/kritigupta/Desktop/Real Estate Dashboard/neighborhood mapping.csv')
    
    # insert address that you want to pull info for
    #address = address
    #zipcode = zipcode
    
    
    # for loop to push every address through Zillow
    #for i,x in zip(address, zipcode):
    # log into Zillow deep search
    i = address
    x= zipcode
    full_address = i + ' ' + str(x)
    #if full_address in housing_data['full_Address']:
    #    pass
    #else:
    #    continue
    zillow_data = ZillowWrapper('X1-ZWz17hux7ivthn_9myga')
    deep_search_response = zillow_data.get_deep_search_results(i,x)
    result = GetDeepSearchResults(deep_search_response)
    
    # pull all dimensions and measures from zillow api
    zestimate = result.zestimate_amount
    rent_zestimate = result.rentzestimate_amount
    zest_last_upd = result.zestimate_last_updated
    zest_value_chg = result.zestimate_value_change
    zestimate_valuation_range_high = result.zestimate_valuation_range_high
    zestimate_valuation_range_low = result.zestimate_valuationRange_low
    zestimate_percentile = result.zestimate_percentile
    home_type = result.home_type
    longitude = result.longitude
    latitude = result.latitude
    year_built = result.year_built
    property_size = result.property_size
    home_size = result.home_size
    num_of_bathrooms = result.bathrooms
    num_of_bedrooms = result.bedrooms
    tax_year = result.tax_year
    tax_value = result.tax_value
    last_sold_date = result.last_sold_date
    last_sold_price = result.last_sold_price
    
    # create values varibale to include all the data
    values = [[i, x, full_address, zestimate, rent_zestimate, property_size, home_size, zest_last_upd, zest_value_chg,
             zestimate_valuation_range_high, zestimate_valuation_range_low, zestimate_percentile,
             home_type, longitude, latitude, year_built, property_size, home_size, num_of_bathrooms,
             num_of_bedrooms, tax_year, tax_value, last_sold_date, last_sold_price]]
    
    # create the dataframe
    df = pd.DataFrame(values, columns = ['address', 'zip_code', 'full_Address', 'Home_Value_Zestimate', 'Rent_Zestimate',
                                      'Property_Size_sqft', 'Home_Size_sqft', 'Zestimate_Last_Updated',
                                      'zest_value_chg', 'Zestimate_Valuation_Range_High',
                                      'zestimate_valuation_range_low', 'zestimate_percentile',
                                      'home_type', 'longitude', 'latitude', 'year_built',
                                      'property_size', 'home_size', 'num_of_bathrooms',
                                      'num_of_bedrooms', 'tax_year', 'tax_value', 'last_sold_date',
                                      'last_sold_price'])
    housing_data = housing_data.append(df)

        
    # add neighborhoods to df
    housing_data = pd.merge(
            housing_data
            , neighborhood_mapping
            , left_on = 'zip_code'
            , right_on = 'zip_code'
            , how = 'left'
                  )
    return zestimate
    #return rent_zestimate
    #return num_of_bathrooms
    #return num_of_bedrooms
    #return property_size
    #return home_size
    #return year_built
    # export the latest df
    # housing_data.to_csv('housing_data.csv')

        





