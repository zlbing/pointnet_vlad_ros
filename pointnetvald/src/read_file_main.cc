//
// Created by zzz on 19-1-10.
//

#include <ros/ros.h>
#include <gs/gs.h>


int main(int argc, char **argv) {
  gs::init(argc, argv, "PointNetVlad");

  ros::NodeHandle nh("~");
  std::string file_path;
  nh.param(std::string("file_path"),file_path,std::string("/home/zzz/work-space/benchmark_datasets/kaicheng"));

  FeatNet::FeatNetFrame feat_net_frames;
  bool load_success = feat_net_frames.LoadDataFromFile(file_path);
  if(load_success){
    feat_net_frames.feature_tracking();
  }else{
    std::cout<<"data file load failed"<<std::endl;
  }

  ros::spin();
  return 0;
}