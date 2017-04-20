import csv
import mysql.connector
from mysql.connector import Error



class dbController(object):    

    tableName = 'ny_markets.markets'
    databaseName = 'ny_markets'
    
    def connect(self):
        """ Connect to MySQL database """
        try:
            if self.DBconnection.is_connected():
                print('Connected to {} database'.format(self.databaseName))
 #               self.loadData()

        except Error as e:
            print(e)
    ##########################################

    def setTable(self):
        return 

    def deleteTable(self):
        try:
            add_market = ("DELETE FROM ny_markets.markets")
            self.crs.execute(add_market)
            self.DBconnection.commit()
            print("Table Deleted")
        except mysql.connector.Error as err:
            print("Failed to delete table.")
            

    ##############################################
    def loadData(self):
        with open("NY_Farmers_Market.csv", "rb") as f:
            reader = csv.reader(f)
            next(f)
            marketID = 0
            for line in enumerate(reader):
                add_market = ("INSERT INTO {} VALUES ('{}','{}','{}','{}','{}','{}','{}','{}','{}','{}','{}','{}','{}','{}','{}','{}','{}','{}','{}','{}','{}')".format(tableName,marketID,line[1][0].replace("'",""),line[1][1].replace("-"," ").replace("'",""),line[1][2].replace("'",""),line[1][3].replace("'",""),line[1][4],line[1][5],line[1][6],line[1][7],line[1][8],line[1][9],line[1][10],line[1][11],line[1][12],line[1][13],line[1][14],line[1][15],line[1][16],line[1][17],line[1][18],line[1][19]))
                marketID = marketID + 1
                self.crs.execute(add_market)
                self.DBconnection.commit()
        

    ##############################################

    def createDB(self):
        dbName = raw_input('Name Database:')
        try:
            db = 'CREATE DATABASE {}'.format(dbName) 
            self.crs.execute(db)
            self.DBconnection.commit()
            self.setDB(dbName)
        except mysql.connector.Error as err:
            print("Failed creating database: {}".format(err))
            exit(1)

    def setDB(self, dbStr):
        self.databaseName = dbStr
        return
        
    ##############################################
    
    DBconnection = mysql.connector.connect(host='127.0.0.1', user='root', password='password', database = databaseName)
    crs = DBconnection.cursor()

    
 
if __name__ == '__main__':
    dbClass = dbController()
    #dbClass.createDB()
    dbClass.connect()
