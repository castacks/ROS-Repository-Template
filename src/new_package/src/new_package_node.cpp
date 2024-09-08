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

#include <rclcpp/rclcpp.hpp>

#include "file_utils/Files.hpp"
#include "new_package/NewPackageLibrary.hpp"

using namespace std;
using namespace rclcpp;
using namespace new_project;

int main(const int iArgC, const char* ppcArgV[])
{
    google::InitGoogleLogging(ppcArgV[0]);
    FLAGS_logtostderr = 1;  // Log to standard error instead of files

    int iRosArgC = iArgC;
    char** ppcRosArgV = (char**)ppcArgV;
    init(iRosArgC, ppcRosArgV);
    auto node = make_shared<rclcpp::Node>("new_package_node");

    string S_CONFIG_PATH = "";
    node->declare_parameter<string>("config_path", "");
    node->get_parameter("config_path", S_CONFIG_PATH);
    CHECK(S_CONFIG_PATH != "") << "Config file path is not provided!";
    RCLCPP_INFO_STREAM(get_logger("new_package"), "Config file path: " << S_CONFIG_PATH);

    const File& fConfig(S_CONFIG_PATH);

    NewPackageNode newPackageNode(fConfig);

    spin(node);
}
