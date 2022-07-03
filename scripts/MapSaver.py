#!/usr/bin/env python

import rospy
from std_msgs.msg import String
import numpy as np
import cv2
from nav_msgs.msg import OccupancyGrid
import os
from project2.srv import MapSaverService, MapSaverServiceResponse
from hector_nav_msgs.srv import GetRobotTrajectory, GetRobotTrajectoryRequest
from nav_msgs.msg import Path
import rospkg

#cwd = os.getcwd()

#rospack = rospkg.RosPack()

#pack_dir = rospack.get_path('project2')

cwd = os.path.expanduser('~') + "/Downloads"

image = []


def map_callback(data):
    global width
    width = data.info.width
    global height
    height = data.info.height
    global resolution 
    resolution = data.info.resolution
    global x_ini 
    x_ini = data.info.origin.position.x
    global y_ini 
    y_ini = data.info.origin.position.y
    size = (width , height)
    global image 
    image = np.zeros(size)

    counter = 0
    #print (len(data.data))
    for p in data.data:
      image[counter%width][int(counter/width)] = p
      counter+=1



    kernel = np.ones((2,2),np.uint8)
    image = cv2.dilate(image,kernel,iterations = 1)         #removes noisy points due to sensors errors
    image = cv2.morphologyEx(image, cv2.MORPH_OPEN, kernel) #combines areas that are close togheter, due to some sensor errors



    #image = cv2.rotate(image, cv2.ROTATE_180)
    #due to how data are stored, you have to rotate the image of 180 degrees
    #and change the values as fllows
    image[image == -1] = 150            #if the value is -1 than substitute with 150
    image[image == 0] = 255
    image[image == 100] = 0


    rospy.loginfo(rospy.get_caller_id() + " I received the map")
    rospy.loginfo("map dimension: (%s, %s) (w, h)", width, height)  
    rospy.loginfo("origin: (%s,%s)", x_ini, y_ini)

def map_saver_service(req):
   
    if image.any():

        path = Path()
        
        try:
            resp = trajectory_service()
            path = resp.trajectory
            rospy.loginfo("Node " + rospy.get_caller_id() + " has received the path")

            for i in range(len(path.poses)-1):
                point1 = (int((path.poses[i].pose.position.y-y_ini)/resolution), int((path.poses[i].pose.position.x-x_ini)/resolution))
                point2 = (int((path.poses[i+1].pose.position.y-y_ini)/resolution),int((path.poses[i+1].pose.position.x-x_ini)/resolution))
                color = (0, 0, 255)
                cv2.line(image, point1, point2, color, 1)
            rospy.loginfo("Node " + rospy.get_caller_id() + " has saved the map with trajectory")

        except rospy.ServiceException as exc:
            print("Service did not process request: " + str(exc))                     
        

        if os.path.isdir(req.str):
            filename = req.str+'/map_and_trajectory.png'
            message = "image saved in " + req.str
        else:
            filename = cwd+'/map_and_trajectory.png'
            message = "image saved in current directory:" + cwd
        
        cv2.imwrite (filename,image)

    else:
        message = "nothing saved: no map received"

    return MapSaverServiceResponse(message)

def map_saver():

    rospy.init_node('map_saver', anonymous=False)

    rospy.Subscriber("map", OccupancyGrid, map_callback)
    
    server = rospy.Service('map_saver_service', MapSaverService, map_saver_service)

    rospy.loginfo("Waiting for trajectory service")
    rospy.wait_for_service('trajectory')
    global trajectory_service
    trajectory_service = rospy.ServiceProxy('trajectory', GetRobotTrajectory)
    rospy.loginfo("Node " + rospy.get_caller_id() + " is running")

    rospy.spin()

    rospy.loginfo("Node " + rospy.get_caller_id() + " is shutting down")

if __name__ == '__main__':
    try:
        map_saver()

    except rospy.ROSInterruptException:
        pass
