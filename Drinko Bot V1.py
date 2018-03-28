# import the necessary packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import numpy as np
import os
import serial
#import VL53L0X


hardware = serial.Serial('/dev/tty/USB0',115200) #create serial port for controll board
print('Connected to:' + hardware.name()) # print the port being used 


 
# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 480))


w = cam.get(cv2.CV_CAP_PROP_FRAME_WIDTH)
h = cam.get(cv2.CV_CAP_PROP_FRAME_HEIGHT)
CENTER_WIDTH = w/2
CENTER_HEIGHT = h/2

#camera settings
camera.brightness = 60
camera.vflip = False
camera.hflip = True
camera.exposure_mode = 'night'
camera.awb_mode = 'fluorescent'

# define range of blue color in HSV
lower_blue = np.array([100,40,40])
upper_blue = np.array([120,255,255])


# frame tracking variables
start = True
mframe = 0

# allow the camera to warmup
time.sleep(0.1)
os.system('clear')



# Create a VL53L0X object
#tof = VL53L0X.VL53L0X()
# Start ranging
#tof.start_ranging(VL53L0X.VL53L0X_BETTER_ACCURACY_MODE)


# Cup detection and location variables
locked = False
locating = False
intialTrans = False


 
# capture frames from the camera
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    # grab the raw NumPy array representing the image, then initialize the timestamp
    # and occupied/unoccupied text
	image = frame.array


	
	if locating == False:
	
		gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
		if start:
			preframe = gray.copy()
			start = False
		# compare frames
		delta = cv2.absdiff(gray,preframe)
		thresh = cv2.threshold(delta, 25, 255, cv2.THRESH_BINARY)[1]
		thresh = cv2.dilate(thresh, None, iterations=2)
	
	
	
	
	
		# find contours and compare size for motion threshold
		cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)[-2]
		center = None
		if len(cnts) > 0:
			c = max(cnts, key=cv2.contourArea)
			(x, y, w, h) = cv2.boundingRect(c)
			#compare area of movement
			area = w*h
			if area >= 2000:
				cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 2)
				#print("Motion dectected!  ")
				#print("Area:" + str(area))
				mframe = mframe + 1
				#print(mframe)
			else:
				mframe = 0
		

		
		# motion must happen for 8 consecutive frames before trigger
		if mframe > 8:
			print("motion triggered now detecting cup placement....")
			hardare.write('M400 R20 B20 G20 ') #send g code to turn on camera light for color detection
			locating = True
			mframe = 0
			intialTrans = True
			
		
		cv2.imshow("raw frame",image)
		cv2.imshow("Gray",gray)
		cv2.imshow("diff",delta)
		cv2.imshow("Thresh",thresh)
		key = cv2.waitKey(1) & 0xFF
	
		if intialTrans:
			cv2.destroyAllWindows()
			intialTrans = False
			
		# store current frame to compare to next frame
		preframe = gray.copy()
	
		#************************************************************* END OF MOTION DETECTION ***********************************************************************
	
	
	
	else:
		#print("now detecting color")
		hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    
    
		mask = cv2.inRange(hsv,lower_blue, upper_blue)
		mask = cv2.erode(mask, None, iterations=2)
		mask = cv2.dilate(mask, None, iterations=1)
    
    
    
		# Bitwise-AND mask and original image
		res = cv2.bitwise_and(image,image, mask= mask)
    
		cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)[-2]
		center = None
    
		if len(cnts) > 0:
			#print("Contour area found")
			c = max(cnts, key=cv2.contourArea)
			((x,y), radius) = cv2.minEnclosingCircle(c)
			m = cv2.moments(c)
			center = (int(m["m10"] / m["m00"]), int(m["m01"] / m["m00"]))
        
			if radius > 15:
				cv2.circle(image, (int(x), int(y)), int(radius),(36,255,255),2)
				cv2.circle(image, center,5,(0,0,255),-1)
				os.system('clear')
				print("Center:")
				print("X:" + str(x))
				print("Y:" + str(y))

				x = x-CENTER_WIDTH # calculate cups horizontal distance to center of image
				y = y-CENTER_HEIGHT	# calculate cups verticle distance to center of image


				hardware.write('G1 X' + x +' Y' + y + ' ' ) # send gcode to move robot to coordinates this is incorrect we will need to calculate distance from center of image
    
 
		# show the frame
		cv2.imshow("Frame", image)
		cv2.imshow("Mask", mask)
		cv2.imshow("res",res)
		key = cv2.waitKey(1) & 0xFF
	
	
	
	
 
	
    # clear the stream in preparation for the next frame
	rawCapture.truncate(0)
 
    # if the `x` key was pressed, break from the loop
	if key == ord("x"):
		hardware.close()
		break
		
		

