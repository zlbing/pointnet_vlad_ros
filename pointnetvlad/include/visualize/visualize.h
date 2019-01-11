//
// Created by zzz on 19-1-11.
//

#ifndef POINTNETVLAD_ROS_VISUALIZE_H
#define POINTNETVLAD_ROS_VISUALIZE_H
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Point32.h>
#include <sensor_msgs/PointCloud.h>
#include <geometry_msgs/PoseArray.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>

#include "datatype/pointnet_vlad_type.h"

namespace PointnetVlad{
  namespace visualize{
    class Visualize {
    public:
      Visualize();
      explicit Visualize(Visualize const&) = delete;
      void operator=(Visualize const&) = delete;
      void addDatabasePose(const std::vector<DataType::poseIndex>& database_pose,
                           const std::string& frame_id);

      void addDatabasePointCloud(const std::vector<std::vector<Eigen::Vector3f>>& database_points,
                                 const std::vector<DataType::poseIndex>& database_pose,
                                 const std::string& frame_id);

      void addQueryPose(DataType::poseIndex query_pose,
                        const std::string& frame_id);

      void addWrongLoopLine(const DataType::poseIndex& pose_1,
                   const DataType::poseIndex& pose_2,
                   const std::string& frame_id);

      void addRightLoopLine(const DataType::poseIndex& pose_1,
                            const DataType::poseIndex& pose_2,
                            const std::string& frame_id);

      void addText(const DataType::poseIndex& pose,
                   int pose_index,
                   double similar,
                   const std::string& frame_id);

      void publish();
    private:
      nav_msgs::Path query_pose_path_;
      nav_msgs::Path database_pose_path_;
      geometry_msgs::PoseArray database_pose_,query_pose_;
      sensor_msgs::PointCloud database_pointcloud_, query_pointcloud_;
      visualization_msgs::MarkerArray wloop_line_;

      ros::Publisher pub_query_pose_path_,pub_database_pose_path_;
      ros::Publisher pub_query_pose_,pub_database_pose_;

      ros::Publisher pub_database_cloud_, pub_query_cloud_;

      ros::Publisher pub_wloop_line_;
    };
  }
}
#endif //POINTNETVLAD_ROS_VISUALIZE_H
