//
// Created by zzz on 19-3-12.
//

#ifndef POINTNETVLAD_ROS_GLOBAL_MAP_H
#define POINTNETVLAD_ROS_GLOBAL_MAP_H
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <ros/ros.h>
#include <gs/gs.h>
#include <Eigen/Dense>

#include <sensor_msgs/PointCloud.h>
#include "intensity_grid.h"
#include "cluster.h"

namespace GS {
  class GlobalMap {
  public:
    GlobalMap(const std::string &file_name);

    explicit GlobalMap(GlobalMap const &) = delete;

    void operator=(GlobalMap const &) = delete;

  public:
    std::vector<Eigen::Vector4f> g_origin_points;
    std::vector<Eigen::Vector4f> extracted_points;

    float g_min_x, g_max_x, g_min_y, g_max_y;
  };
}

#endif //POINTNETVLAD_ROS_GLOBAL_MAP_H
