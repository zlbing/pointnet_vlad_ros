//
// Created by zzz on 19-3-13.
//

#include <visualize.h>
#include "visualize.h"
namespace GS{
  Visualize::Visualize(){
    ros::NodeHandle nh("~");
    pub_global_points_ = nh.advertise<sensor_msgs::PointCloud>("global_points",10);
    pub_global_extracted_points_ = nh.advertise<sensor_msgs::PointCloud>("global_extracted_points",10);
    pub_points_ = nh.advertise<sensor_msgs::PointCloud>("submap_points",10);
    pub_extracted_points_ = nh.advertise<sensor_msgs::PointCloud>("submap_extracted_points",10);
  }

  void Visualize::EigenVectorToMsg(const std::vector<Eigen::Vector4f>& points,
                                   sensor_msgs::PointCloud& points_msg){
    for(int i=0; i<points.size(); i++){
      geometry_msgs::Point32 p;
      p.x = points[i][0];
      p.y = points[i][1];
      p.z = points[i][2];
      float intensity = boost::lexical_cast<float>(points[i][3]);
      points_msg.points.push_back(p);
      points_msg.channels[0].values.push_back(intensity);
    }
  }


  void Visualize::pubGlobalPoints(const std::vector<Eigen::Vector4f>& points){
    if(pub_global_points_.getNumSubscribers() > 0){
      sensor_msgs::PointCloud point_cloud;
      point_cloud.header.stamp = ::ros::Time::now();
      point_cloud.header.frame_id = "world";
      point_cloud.channels.resize(1);
      point_cloud.channels[0].name = "intensity";

      EigenVectorToMsg(points, point_cloud);
      pub_global_points_.publish(point_cloud);
    }
  }

  void Visualize::pubGlobalExtractedPoints(const std::vector<Eigen::Vector4f>& points){
    if(pub_global_extracted_points_.getNumSubscribers() > 0) {
      sensor_msgs::PointCloud point_cloud;
      point_cloud.header.stamp = ::ros::Time::now();
      point_cloud.header.frame_id = "world";
      point_cloud.channels.resize(1);
      point_cloud.channels[0].name = "intensity";

      EigenVectorToMsg(points, point_cloud);
      pub_global_extracted_points_.publish(point_cloud);
    }
  }

  void Visualize::pubSubmapPoints(const std::vector<Eigen::Vector4f>& points){
    static int pub_count=0;
    if(pub_points_.getNumSubscribers() > 0 //&& pub_count<1
            )
    {
      sensor_msgs::PointCloud point_cloud;
      point_cloud.header.stamp = ::ros::Time::now();
      point_cloud.header.frame_id = "world";
      point_cloud.channels.resize(1);
      point_cloud.channels[0].name = "intensity";

      EigenVectorToMsg(points, point_cloud);
      pub_points_.publish(point_cloud);
      pub_count++;
    }
  }

  void Visualize::pubSubmapExtractedPoints(const std::vector<Eigen::Vector4f>& points){
    static int pub_count=0;
    if(pub_extracted_points_.getNumSubscribers()>0)
    {
      sensor_msgs::PointCloud point_cloud;
      point_cloud.header.stamp = ::ros::Time::now();
      point_cloud.header.frame_id = "world";
      point_cloud.channels.resize(1);
      point_cloud.channels[0].name = "intensity";

      EigenVectorToMsg(points, point_cloud);
      pub_extracted_points_.publish(point_cloud);
      pub_count++;
    }
  }
}
