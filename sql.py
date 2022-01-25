import MySQLdb
import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600)
db =MySQLdb.connect("localhost", "pi", "elektromechanika", "systemdata")

cursor =db.cursor()

while 1:
        print("Várok az adatra...")
        print("")
        """x = ser.readline()"""
        print("adatok gyűjtése")
        print("")
        time.sleep(1)
        x = ser.readline()
        x = x.strip()
        y = ser.readline()
        y = y.strip()
        z = ser.readline()
        z = z.strip()
        a = ser.readline()
        a = a.strip()
        time.sleep(1)
        x = int(float(x))
        y = int(float(y))
        z = float(z)
        a = float(a)
        print("Beillesztés az adatbázisba...")
        print("")
        time.sleep(1)
        sql = "INSERT INTO ontozorendszer(feny, vizmelyseg, paratartalom, homerseklet) VALUES (%d, %d, %d, %d)" %(x,y,z,a)
        cursor.execute(sql)
        db.commit()
