#!/usr/bin/env python

import rospy
from neatness_estimator_msgs.srv import GetDifference, GetDifferenceResponse

def gomibako_client():
    try:
        client = rospy.ServiceProxy('/estimation_module_interface_color_and_geometry/call', GetDifference)
        res = client(task='two_scene')
        print(res)
    except rospy.ServiceException, e:
        print "service exception failed"

#if __name__ == "__main__":
    #rospy.init_node('difference_estimation_client')
    #client = rospy.ServiceProxy('/estimation_module_interface_color_and_geometry/call', GetDifference)
    #res = client(task='two_scene')
    #print(res)
