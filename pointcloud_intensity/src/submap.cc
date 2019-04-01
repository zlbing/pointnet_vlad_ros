//
// Created by zzz on 19-3-12.
//

#include "submap.h"
namespace GS{
  Submap::Submap(const std::string& file_name){
    std::ifstream pose_data_file;
    pose_data_file.open(file_name.c_str(), std::ios::in);

    if(pose_data_file.is_open()) {
      std::string str;
      std::getline(pose_data_file, str, '\n');
      std::vector<std::string> str_vec;
      boost::split(str_vec, str, boost::is_any_of(","));

      translator_ = Eigen::Vector3f(boost::lexical_cast<float>(str_vec[0]),
                                    boost::lexical_cast<float>(str_vec[1]),
                                    boost::lexical_cast<float>(str_vec[2]));

      rotation_ = Eigen::Quaternionf(
              boost::lexical_cast<float>(str_vec[3]),
              boost::lexical_cast<float>(str_vec[4]),
              boost::lexical_cast<float>(str_vec[5]),
              boost::lexical_cast<float>(str_vec[6]));

      min_x_ = 1e6, max_x_ = -1e6, min_y_ = 1e6, max_y_ = -1e6;
      while (std::getline(pose_data_file, str, '\n')) {
        std::vector<std::string> str_vec;
        boost::split(str_vec, str, boost::is_any_of(","));
        Eigen::Vector4f point = Eigen::Vector4f(
                boost::lexical_cast<float>(str_vec[0]),
                boost::lexical_cast<float>(str_vec[1]),
                boost::lexical_cast<float>(str_vec[2]),
                boost::lexical_cast<float>(str_vec[3]));

        origin_points_.push_back(point);

        min_x_ = (min_x_ < point[0]) ? min_x_ : point[0];
        max_x_ = (max_x_ > point[0]) ? max_x_ : point[0];
        min_y_ = (min_y_ < point[1]) ? min_y_ : point[1];
        max_y_ = (max_y_ > point[1]) ? max_y_ : point[1];
      }
      pose_data_file.close();
      LOG(INFO) << "read filename=" << file_name << " points size="
                << origin_points_.size();
    }else{
      LOG(ERROR)<<file_name<<" file can't open ";
    }

    GS::IntensityGrid grid(min_x_,max_x_,
                           min_y_,max_y_, 1);
    grid.addPoints(origin_points_);
    LOG(INFO)<<"origin_points size="<<origin_points_.size();
    GS::Cluster cluster;
    extracted_points_ = cluster.runCluster(&grid, origin_points_);
    LOG(INFO)<<"extracted_points_ size="<<extracted_points_.size();
  }

  void Submap::publish(const ::ros::WallTimerEvent& unused_timer_event){
    visual_handle_.pubSubmapPoints(origin_points_);
    visual_handle_.pubSubmapExtractedPoints(extracted_points_);
  }
}
