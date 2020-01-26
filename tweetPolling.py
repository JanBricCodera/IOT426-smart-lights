##Import Libraries

import twitter
import serial
import time

##authenticate with twitter
api = twitter.Api(consumer_key='DCJkUi2ytzMYw1Hkmv81WRGGS', consumer_secret='rqZmyb9UOlCPm1Ai15l43WY0daOvSYeHREJ1Tnzk9v8lOZPVZ2', access_token_key='313335268-hNVSGRs0lgi4w3Yyv4i9pZaUntx6cLINJsZcxPwh', access_token_secret='uXSwudr24nZm7cp0E2AWy2epaGaPjcskBE1aJxhudWNKF') 

##set serial port
#ser = serial.Serial('/dev/ttyUSB0', 19200)
locations = ['COM3'] #to use with windows

for device in locations:
        try:

                ser = serial.Serial(device, baudrate=9600, bytesize=8,

                parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE)

                print ("\nFujitsu MCU found on: " + ser.portstr + " please wait...\n")

                time.sleep(2)

                break

        except:

                print "Failed to connect on", device
                
                
## check serial port
def checkokay():
	ser.flushInput()
	time.sleep(3)
	line=ser.readline()
	time.sleep(3)

	if line == ' ':
		line=ser.readline()
	print 'here'
	
## Welcome message
print 'Welcome To Hashtag Grabber Console!'

def driptwit():
        status = [] 
	
        status = api.GetUserTimeline('Home_controller') ##grab latest statuses
                
        checkIt = [s.text for s in status] ##put status in an array

        drip = checkIt[0].split() ##split first tweet into words

                ## check for match and write to serial if match
        if drip[0] == '#ON1':
                ser.write('1')
                print 'Tweet Received. Living room light enabled.'
        elif drip[0] == '#ON2': 
                print 'Tweet Received. Bedroom light enabled.'
                ser.write('2')
        elif drip[0] == '#ON3': 
                print 'Tweet Received. Terrace area light enabled.'
                ser.write('3')
        elif drip[0] == '#ON4': 
                print 'Tweet Received. Garage area light enabled.'
                ser.write('4')
        elif drip[0] == '#OFF1':
                print 'Tweet Received. Living room light disabled.'
                ser.write('5')
        elif drip[0] == '#OFF2':
                print 'Tweet Received. Bedroom light disabled.'
                ser.write('6')
        elif drip[0] == '#OFF3':
                print 'Tweet Received. Terrace area light disabled.'
                ser.write('7')
        elif drip[0] == '#OFF4':
                print 'Tweet Received. Garage area light disabled.'
                ser.write('8')

        else:
                print 'Awaiting Tweet'
                ser.write('0')
                        
while 1:
	driptwit() ## call driptwit function
	time.sleep(2) ## sleep for 5 seconds to avoid rate limiting
	
