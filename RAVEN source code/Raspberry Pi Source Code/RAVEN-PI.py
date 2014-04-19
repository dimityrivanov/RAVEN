import serial
import time
import picamera
ser = serial.Serial('/dev/ttyACM0',115200)
camera = picamera.PiCamera()
while 1:
	arduinoData = str(ser.readline())
	print arduinoData
	timestamp = int(time.time())
	isIt = arduinoData == 'pick\r\n'	
	camera.vflip = True
	camera.hflip = True	
	if not isIt:
		f = open('/var/www/buffer.txt','a')
		f.write(arduinoData)
		f.close()
	else:		
		f = open('/var/www/buffer.txt','a')
		f.write('p:'+str(timestamp))
		camera.capture('/var/www/images/'+str(timestamp)+'.jpg')
		f.close()		
	
		
	
