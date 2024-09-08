#!/usr/bin/env python3
#
# Created on Tue Sep 10 2024 01:38:19
# Author: Mukai (Tom Notch) Yu
# Email: mukaiy@andrew.cmu.edu
# Affiliation: Carnegie Mellon University, Robotics Institute
#
# Copyright Ⓒ 2024 Mukai (Tom Notch) Yu
#
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    # Define the path to the config file
    config_file_default = os.path.join(
        get_package_share_directory("new_package"), "config", "default.yaml"
    )

    return LaunchDescription(
        [
            # Declare the config_path argument
            DeclareLaunchArgument(
                "config_path",
                default_value=config_file_default,
                description="Path to the configuration file",
            ),
            # Define the Python node to be launched
            Node(
                package="new_package",
                executable="new_package_node.py",
                name="new_package",
                output="screen",
                parameters=[{"config_path": LaunchConfiguration("config_path")}],
            ),
        ]
    )
