//
// Created by zzz on 19-1-10.
//

#include <ros/ros.h>
#include <gs/gs.h>
#include "loopclosure/loop_closure.h"

int main(int argc, char **argv) {
  gs::init(argc, argv, "PointNetVlad");

  ros::NodeHandle nh("~");
  std::string file_path;
  nh.param(std::string("file_path"),file_path,std::string("/home/zzz/work-space/benchmark_datasets/kaicheng"));
  PointnetVlad::LoopClosure loop_closure(file_path);
  std::pair<std::vector<int>, std::vector<double>> result = loop_closure.loop(0,2);
  std::vector<int> loop_database_index = result.first;
  std::vector<double> loop_similar = result.second;
  loop_closure.visulizeLoopClosure(0,2,loop_database_index,loop_similar);
  ros::spin();
  return 0;
}