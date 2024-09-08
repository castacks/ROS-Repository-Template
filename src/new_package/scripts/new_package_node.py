#!/usr/bin/env python3
#
# Created on Wed Sep 04 2024 21:06:48
# Author: Mukai (Tom Notch) Yu
# Email: mukaiy@andrew.cmu.edu
# Affiliation: Carnegie Mellon University, Robotics Institute
#
# Copyright Ⓒ 2024 Mukai (Tom Notch) Yu
#
from curses import panel
from enum import IntEnum

import rclpy
import tf2_geometry_msgs
import tf2_ros
from file_utils.files import dict_to_string
from file_utils.files import read_file
from geometry_msgs.msg import PointStamped
from rclpy.node import Node


def main_loop():
    node.get_logger().info("Node is running")


if __name__ == "__main__":
    rclpy.init()  # Initialize ROS 2

    # Create a node
    node = Node("new_package_node")

    try:
        node.declare_parameter("config_path", "")
        config_path = (
            node.get_parameter("config_path").get_parameter_value().string_value
        )
        node.get_logger().info("Config file path: %s" % config_path)
        # Here you can add your logic to open and read the config file
    except KeyError:
        rclpy.logerr("Parameter 'config_path' not set")

    config = read_file(config_path)  # Get the file path from the first argument

    node.get_logger().info("Config file content:")
    node.get_logger().info(dict_to_string(config))  # Print the file content

    # Create a timer to simulate the loop, with 1 second interval
    timer = node.create_timer(1.0, main_loop)

    # Spin the node to keep it alive
    rclpy.spin(node)

    # Clean up after shutdown
    node.destroy_node()
    rclpy.shutdown()
