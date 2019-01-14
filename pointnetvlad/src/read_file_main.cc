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
  double par_loop_similar = 0.85;
  nh.param(std::string("file_path"),file_path,std::string("/home/zzz/work-space/benchmark_datasets/kaicheng_5"));
  nh.param(std::string("loop_similar"),par_loop_similar,0.85);

  PointnetVlad::LoopClosure loop_closure(file_path,par_loop_similar);
  std::pair<std::vector<int>, std::vector<double>> result = loop_closure.loop(0,1);
  std::vector<int> loop_database_index = result.first;
  std::vector<double> loop_similar = result.second;
  loop_closure.visulizeLoopClosure(0,1,loop_database_index,loop_similar);
  ros::spin();
  return 0;
}