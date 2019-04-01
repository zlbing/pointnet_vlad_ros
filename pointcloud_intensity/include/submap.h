//
// Created by zzz on 19-3-12.
//

#ifndef POINTNETVLAD_ROS_SUBMAP_H
#define POINTNETVLAD_ROS_SUBMAP_H
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <ros/ros.h>
#include <gs/gs.h>
#include <Eigen/Dense>

#include <sensor_msgs/PointCloud.h>
#include "intensity_grid.h"
#include "cluster.h"
#include "visualize.h"
namespace GS {
  class Submap {
  public:
    Submap(const std::string& file_name);

    explicit Submap(Submap const &) = delete;
    void operator=(Submap const &) = delete;

    void publish(const ::ros::WallTimerEvent& unused_timer_event);
  private:
    float min_x_=1e6, max_x_=-1e6, min_y_=1e6, max_y_=-1e6;
    // We have to keep the timer handles of ::ros::WallTimers around, otherwise
    // they do not fire.
    Visualize visual_handle_;
  public:
    std::vector<Eigen::Vector4f> origin_points_;
    std::vector<Eigen::Vector4f> extracted_points_;

    Eigen::Vector3f translator_;
    Eigen::Quaternionf rotation_;
  };
}

#endif //POINTNETVLAD_ROS_SUBMAP_H
