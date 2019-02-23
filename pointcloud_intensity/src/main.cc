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
#include "intensity_grid.h"
#include "cluster.h"

std::vector<Eigen::Vector4f> g_origin_points;
float g_min_x=1e6, g_max_x=-1e6, g_min_y=1e6, g_max_y=-1e6;

ros::Publisher pub_all_points, pub_extracted_points;


void EigenVectorToMsg(const std::vector<Eigen::Vector4f>& points,
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

int main(int argc, char **argv) {
  gs::init(argc, argv, "intensity_test");
  ros::NodeHandle nh("~");

  std::string filename;
  filename="/home/zzz/ground_point/groundTexture.pcd";
  LOG(INFO)<<"filename="<<filename<<" in";

  std::ifstream pointcloud_file;
  pointcloud_file.open(filename.c_str(), std::ios::in);
  if(pointcloud_file.is_open()){
    std::string str;
    while (std::getline(pointcloud_file, str, '\n')) {
      std::vector<std::string> str_vec;
      boost::split(str_vec, str, boost::is_any_of(" "));
      if(str_vec[0] == "DATA"){
        break;
      }
    }

    while (std::getline(pointcloud_file, str, '\n')) {
      std::vector<std::string> str_vec;
      boost::split(str_vec, str, boost::is_any_of(" "));
      Eigen::Vector4f p;
      p[0] = boost::lexical_cast<float>(str_vec[0]);
      p[1] = boost::lexical_cast<float>(str_vec[1]);
      p[2] = boost::lexical_cast<float>(str_vec[2]);
      p[3] = boost::lexical_cast<float>(str_vec[3]);
      g_origin_points.emplace_back(p);
      g_min_x = (g_min_x < p[0])?g_min_x:p[0];
      g_max_x = (g_max_x > p[0])?g_max_x:p[0];
      g_min_y = (g_min_y < p[1])?g_min_y:p[1];
      g_max_y = (g_max_y > p[1])?g_max_y:p[1];
    }
    pointcloud_file.close();
  }else{
    LOG(ERROR)<<" lane line file can't open "<<filename;
  }
  std::cout<<"g_min_x="<<g_min_x<<" g_max_x="<<g_max_x
           <<"g_min_y="<<g_min_y<<" g_max_y="<<g_max_y<<std::endl;
  pub_all_points = nh.advertise<sensor_msgs::PointCloud>("all_origin_points",10);
  pub_extracted_points = nh.advertise<sensor_msgs::PointCloud>("extracted_points",10);
  GS::IntensityGrid grid(g_min_x,g_max_x,
                         g_min_y,g_max_y, 1);
  grid.addPoints(g_origin_points);
  std::cout<<"g_origin_points size="<<g_origin_points.size()<<std::endl;
  GS::Cluster cluster;
  std::vector<Eigen::Vector4f> result = cluster.runCluster(&grid,
                                                           g_origin_points);
  std::cout<<"extracted points size="<<result.size()<<std::endl;
  int total_number = 10;
  for(int i=0; i<total_number; i++)
  {
    sensor_msgs::PointCloud all_point_cloud;
    all_point_cloud.header.stamp = ::ros::Time::now();
    all_point_cloud.header.frame_id = "world";
    all_point_cloud.channels.resize(1);
    all_point_cloud.channels[0].name = "intensity";

    EigenVectorToMsg(g_origin_points, all_point_cloud);
    pub_all_points.publish(all_point_cloud);

    sensor_msgs::PointCloud point_cloud;
    point_cloud.header.stamp = ::ros::Time::now();
    point_cloud.header.frame_id = "world";
    point_cloud.channels.resize(1);
    point_cloud.channels[0].name = "intensity";
    EigenVectorToMsg(result, point_cloud);
    pub_extracted_points.publish(point_cloud);
  }

  ros::spin();
}