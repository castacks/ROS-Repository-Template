// =============================================================================
// Created on Wed Sep 04 2024 21:07:48
// Author: Mukai (Tom Notch) Yu
// Email: mukaiy@andrew.cmu.edu
// Affiliation: Carnegie Mellon University, Robotics Institute
//
// Copyright Ⓒ 2024 Mukai (Tom Notch) Yu
// =============================================================================

#include <iostream>
#include <filesystem>
#include <string>

#include <ros/ros.h>

#include "file_utils/Files.hpp"
#include "new_package/NewPackageLibrary.hpp"

using namespace std;
using namespace new_project;

int main(const int iArgC, const char* ppcArgV[])
{
    google::InitGoogleLogging(ppcArgV[0]);
    FLAGS_logtostderr = 1;  // Log to standard error instead of files

    int iRosArgC = iArgC;
    char** ppcRosArgV = (char**)ppcArgV;
    ros::init(iRosArgC, ppcRosArgV, "new_package");
    ros::NodeHandle nhPrivate("~");  // Private NodeHandle to access private parameters

    string S_CONFIG_PATH = "";
    nhPrivate.param<std::string>("config_path", S_CONFIG_PATH, "");
    CHECK(S_CONFIG_PATH != "") << "Config file path is not provided!";
    ROS_INFO_STREAM("Config file path: " << S_CONFIG_PATH);

    const File& fConfig(S_CONFIG_PATH);

    NewPackageNode newPackageNode(fConfig);

    ros::spin();
}
