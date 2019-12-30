---
layout: post
title: How to get Rent Zestimate using PyZillow (Zillow API)
image: /img/hello_world.jpeg
---

Zillow's API is a great tool to quickly retrieve real estate data to help calculate ROI on a potential property. If you haven't used the API, you should check it out [here](https://www.zillow.com/howto/api/APIOverview.htm).

I use the PyZillow python wrapper for Zillow's API because it makes it seamless to pull Zillow data straight into Python with a few simple functions. If you are not new to the PyZillow package and you have ran into issues pulling rent data, then look no further as I have your simple solution right here!


**Step 1:** Download the pyzillow package:

Open command line or terminal and type the following line:
```pip install pyzillow```

**Step 2:** We need to open up the pyzillow.py file and add the rent zestimate parameter:

If you don't know where your pyzillow file is, you can search for the file "pyzillow.py". I know if you have a Mac, then you can press cmd + space and type in pyzillow.py and it should appear. You can do the same thing with windows and search for the file by typing pyzillow.py in the start menu


Once you have opened the file, find the `get_deep_search_results` function and inside the function, you should see the `params`. We are going to add the rent zestimate parameter inside here to be able to access the data.

```
def get_deep_search_results(self, address, zipcode):
    """
    GetDeepSearchResults API
    """

    url = 'http://www.zillow.com/webservice/GetDeepSearchResults.htm'
    params = {
        'address': address,
        'citystatezip': zipcode,
        'zws-id': self.api_key,
        'rentzestimate': True # This is the only line we add
    }
    return self.get_data(url, params)
 ```
    
** Step 3 ** We add the rent zestimate to the attribute mapping dictionary:

Find the `lass GetDeepSearchResults(ZillowResults)` and add the following:
``
'rentzestimate_amount': 'result/rentzestimate/amount'
``

```
class GetDeepSearchResults(ZillowResults):
    """
    """
    attribute_mapping = {
        'zillow_id': 'result/zpid',
        'home_type': 'result/useCode',
        'home_detail_link': 'result/links/homedetails',
        'graph_data_link': 'result/links/graphsanddata',
        'map_this_home_link': 'result/links/mapthishome',
        'latitude': 'result/address/latitude',
        'longitude': 'result/address/longitude',
        'tax_year': 'result/taxAssessmentYear',
        'tax_value': 'result/taxAssessment',
        'year_built': 'result/yearBuilt',
        'property_size': 'result/lotSizeSqFt',
        'home_size': 'result/finishedSqFt',
        'bathrooms': 'result/bathrooms',
        'bedrooms': 'result/bedrooms',
        'last_sold_date': 'result/lastSoldDate',
        'last_sold_price': 'result/lastSoldPrice',
        'zestimate_amount': 'result/zestimate/amount',
        'zestimate_last_updated': 'result/zestimate/last-updated',
        'zestimate_value_change': 'result/zestimate/valueChange',
        'zestimate_valuation_range_high':
        'result/zestimate/valuationRange/high',
        'zestimate_valuationRange_low': 'result/zestimate/valuationRange/low',
        'zestimate_percentile': 'result/zestimate/percentile',
        'rentzestimate_amount': 'result/rentzestimate/amount', # add this in the script
    }
```

** Test out the results! **

```
from pyzillow.pyzillow import ZillowWrapper, GetDeepSearchResults

address = ['11 Avenue B, Johnson City, NY']
zip_code = ['13790']

zillow_data = ZillowWrapper('X1-ZWz1835knufc3v_38l6u')
deep_search_response = zillow_data.get_deep_search_results(address, zip_code)
result = GetDeepSearchResults(deep_search_response)

print(result.rentzestimate_amount)
```
