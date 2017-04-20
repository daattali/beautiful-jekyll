import gmplot
import mysql.connector
from mysql.connector import Error
from pythonToMySQL import dbController



class drawMap(object):
        
    def createMaps(self):
        longQuery = ('SELECT Longitude, Latitude \
                        FROM markets')

        self.dbConnector.crs.execute(longQuery)
        lonList = []
        latList = []
        for lon, lat in self.dbConnector.crs:
            lonList.append(float(lon.replace(u'\N{MINUS SIGN}', '-')))
            latList.append(float(lat.replace(u'\N{MINUS SIGN}', '-')))

        print(lonList[1])
        
        #NOTE: The lat and long are reverse on the database
        # MUST CHANGE, I think

        #Heat Map
        self.gmap.heatmap(latList,lonList)
        self.gmap.draw("heatMap.html")

        #Plot
        self.gmap.scatter(latList, lonList, 'k', marker=True)
        self.gmap.draw("scatterMap.html")

    

    def draw(self):
        self.createMaps()
        
        

    dbConnector = dbController()
    dbConnector.connect()
    gmap = gmplot.GoogleMapPlotter(42.70149, -74.03254, 8)

if __name__ == '__main__':
    draw = drawMap()
    draw.draw()
