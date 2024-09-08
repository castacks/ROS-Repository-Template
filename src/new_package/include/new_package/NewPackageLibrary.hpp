// =============================================================================
// Created on Wed Sep 04 2024 21:09:58
// Author: Mukai (Tom Notch) Yu
// Email: mukaiy@andrew.cmu.edu
// Affiliation: Carnegie Mellon University, Robotics Institute
//
// Copyright Ⓒ 2024 Mukai (Tom Notch) Yu
// =============================================================================

#pragma once

#include <new_package/visibility_control.h>

#include <iostream>
#include <filesystem>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "file_utils/Files.hpp"

using namespace std;
using namespace cv;
using namespace rclcpp;

namespace new_project
{
class NewPackageNode
{
  public:
    NewPackageNode() = delete;
    NewPackageNode(const File& fConfig);

    ~NewPackageNode() = default;

  private:
    const File& fConfig;
};
}  // namespace new_project
