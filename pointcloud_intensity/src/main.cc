//
// Created by zzz on 19-2-21.
//


#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <ros/ros.h>
#include <gs/gs.h>
#include <Eigen/Dense>

#include <sensor_msgs/PointCloud.h>
//#include "intensity_grid.h"
//#include "cluster.h"
//#include "submap.h"
#include "intensity_map.h"

std::vector<::ros::WallTimer> wall_timers_;

int main(int argc, char **argv) {
  gs::init(argc, argv, "intensity_test");
  ros::NodeHandle nh("~");
  GS::IntensityMap intensity_map;
  intensity_map.run_optimize();
//  std::string filename;
//  filename = "/home/zzz/ground_point/submap/submap_groundpoints_0010.bin";
//  GS::Submap submap(filename);
//  wall_timers_.push_back(nh.createWallTimer(::ros::WallDuration(1), &GS::Submap::publish, &submap));

  ros::spin();
}