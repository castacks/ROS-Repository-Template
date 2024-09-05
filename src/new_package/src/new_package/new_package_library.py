#!/usr/bin/env python3
#
# Created on Wed Sep 04 2024 21:06:22
# Author: Mukai (Tom Notch) Yu
# Email: mukaiy@andrew.cmu.edu
# Affiliation: Carnegie Mellon University, Robotics Institute
#
# Copyright Ⓒ 2024 Mukai (Tom Notch) Yu
#
import actionlib
import rospy
from new_package.msg import new_actionAction
from new_package.msg import new_actionGoal


class NewActionClient:
    def __init__(self):
        self.client = actionlib.SimpleActionClient(
            "new_action_driver", new_actionAction
        )
        # self.client.wait_for_server() # should wait in the real scenario
