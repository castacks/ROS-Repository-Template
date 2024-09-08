#!/usr/bin/env python3
#
# Created on Wed Sep 04 2024 21:06:22
# Author: Mukai (Tom Notch) Yu
# Email: mukaiy@andrew.cmu.edu
# Affiliation: Carnegie Mellon University, Robotics Institute
#
# Copyright Ⓒ 2024 Mukai (Tom Notch) Yu
#
import rclpy
from new_package.action import NewAction
from new_package.msg import NewActionGoal
from rclpy.action import ActionClient
from rclpy.node import Node


class NewActionClient(Node):
    def __init__(self):
        self.client = ActionClient(self, NewAction, "new_action_driver")
        # self.client.wait_for_server() # should wait in the real scenario
