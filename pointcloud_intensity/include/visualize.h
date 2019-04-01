//
// Created by zzz on 19-3-13.
//

#ifndef POINTNETVLAD_ROS_VISUALIZE_H
#define POINTNETVLAD_ROS_VISUALIZE_H

#include <sensor_msgs/PointCloud.h>
#include <ros/ros.h>
#include <gs/gs.h>
#include <Eigen/Dense>
namespace GS{
  class Visualize {
  public:
    Visualize();

    explicit Visualize(Visualize const &) = delete;
    void operator=(Visualize const &) = delete;

    void EigenVectorToMsg(const std::vector<Eigen::Vector4f>& points,
                          sensor_msgs::PointCloud& points_msg);

    void pubGlobalPoints(const std::vector<Eigen::Vector4f>& points);
    void pubGlobalExtractedPoints(const std::vector<Eigen::Vector4f>& points);

    void pubSubmapPoints(const std::vector<Eigen::Vector4f>& points);
    void pubSubmapExtractedPoints(const std::vector<Eigen::Vector4f>& points);

  private:
    ros::Publisher pub_global_points_, pub_global_extracted_points_;
    ros::Publisher pub_points_, pub_extracted_points_;

  };
}



#endif //POINTNETVLAD_ROS_VISUALIZE_H
