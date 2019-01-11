//
// Created by zzz on 19-1-11.
//

#include "visualize/visualize.h"
namespace PointnetVlad {
  namespace visualize {
    Visualize::Visualize() {
      ros::NodeHandle nh("~");
      pub_query_pose_path_ = nh.advertise<nav_msgs::Path>("query_pose_path",10);
      pub_database_pose_path_ = nh.advertise<nav_msgs::Path>("database_pose_path",10);

      pub_query_pose_ = nh.advertise<geometry_msgs::PoseArray>("query_pose",10);
      pub_database_pose_ = nh.advertise<geometry_msgs::PoseArray>("database_pose",10);

      pub_database_cloud_ = nh.advertise<sensor_msgs::PointCloud>("database_cloud",10);

      pub_wloop_line_ = nh.advertise<visualization_msgs::MarkerArray>("wloop_line",10);
    }

    void Visualize::addDatabasePose(const std::vector<DataType::poseIndex>& database_pose,
                                    const std::string& frame_id){
      for(int i=0; i<database_pose.size(); i++){
        geometry_msgs::PoseStamped pose_stamped;
        pose_stamped.header.frame_id=frame_id;
        pose_stamped.header.stamp = ros::Time::now();
        pose_stamped.pose.position.x = database_pose[i].p.x();
        pose_stamped.pose.position.y = database_pose[i].p.y();
        pose_stamped.pose.position.z = database_pose[i].p.z();

        pose_stamped.pose.orientation.x = database_pose[i].q.x();
        pose_stamped.pose.orientation.y = database_pose[i].q.y();
        pose_stamped.pose.orientation.z = database_pose[i].q.z();
        pose_stamped.pose.orientation.w = database_pose[i].q.w();

        database_pose_path_.header = pose_stamped.header;
        database_pose_path_.poses.push_back(pose_stamped);
        database_pose_.poses.push_back(pose_stamped.pose);
        database_pose_.header = pose_stamped.header;
      }
    }
    void Visualize::addDatabasePointCloud(const std::vector<std::vector<Eigen::Vector3f>>& database_points,
                                          const std::vector<DataType::poseIndex>& database_pose,
                                          const std::string& frame_id){
      database_pointcloud_.points.clear();
      database_pointcloud_.header.frame_id = frame_id;
      database_pointcloud_.header.stamp = ros::Time::now();
      for(int i=0; i<database_pose.size(); i++){
        for(int j=0; j<database_points[i].size(); j++){
          Eigen::Vector3f points_in_world = database_pose[i].q.cast<float>() * database_points[i][j] + database_pose[i].p.cast<float>();
          geometry_msgs::Point32 p;
          p.x = points_in_world.x();
          p.y = points_in_world.y();
          p.z = points_in_world.z();
          database_pointcloud_.points.push_back(p);
        }
      }
      if(pub_database_cloud_.getNumSubscribers()>0){
        pub_database_cloud_.publish(database_pointcloud_);
      }
    }
    void Visualize::addQueryPose(DataType::poseIndex query_pose,
                                 const std::string& frame_id){
      geometry_msgs::PoseStamped pose_stamped;
      pose_stamped.header.frame_id=frame_id;
      pose_stamped.header.stamp = ros::Time::now();
      pose_stamped.pose.position.x = query_pose.p.x();
      pose_stamped.pose.position.y = query_pose.p.y();
      pose_stamped.pose.position.z = query_pose.p.z();

      pose_stamped.pose.orientation.x = query_pose.q.x();
      pose_stamped.pose.orientation.y = query_pose.q.y();
      pose_stamped.pose.orientation.z = query_pose.q.z();
      pose_stamped.pose.orientation.w = query_pose.q.w();

      query_pose_path_.header = pose_stamped.header;
      query_pose_path_.poses.push_back(pose_stamped);
      query_pose_.poses.push_back(pose_stamped.pose);
      query_pose_.header = pose_stamped.header;
    }

    void Visualize::addWrongLoopLine(const DataType::poseIndex& pose_1,
                                     const DataType::poseIndex& pose_2,
                                     const std::string& frame_id){
      visualization_msgs::Marker w_line;

      geometry_msgs::Point point1, point2;
      point1.x = pose_1.p.x();
      point1.y = pose_1.p.y();
      point1.z = pose_1.p.z();
      point2.x = pose_2.p.x();
      point2.y = pose_2.p.y();
      point2.z = pose_2.p.z();

      w_line.header.stamp = ros::Time::now();
      w_line.header.frame_id = frame_id;
      w_line.type = visualization_msgs::Marker::LINE_LIST;
      w_line.action = visualization_msgs::Marker::ADD;
      w_line.ns = "wrong_loop_match";
      w_line.id = wloop_line_.markers.size();
      w_line.points.push_back(point1);
      w_line.points.push_back(point2);
      w_line.scale.x = 0.05;
      w_line.color.a = 1.0; // Don't forget to set the alpha!
      w_line.color.r = 0.0;
      w_line.color.g = 1.0;
      w_line.color.b = 1.0;
      wloop_line_.markers.push_back(w_line);
    }

    void Visualize::addRightLoopLine(const DataType::poseIndex& pose_1,
                                     const DataType::poseIndex& pose_2,
                                     const std::string& frame_id){
      visualization_msgs::Marker w_line;

      geometry_msgs::Point point1, point2;
      point1.x = pose_1.p.x();
      point1.y = pose_1.p.y();
      point1.z = pose_1.p.z();
      point2.x = pose_2.p.x();
      point2.y = pose_2.p.y();
      point2.z = pose_2.p.z();

      w_line.header.stamp = ros::Time::now();
      w_line.header.frame_id = frame_id;
      w_line.type = visualization_msgs::Marker::LINE_LIST;
      w_line.action = visualization_msgs::Marker::ADD;
      w_line.ns = "right_loop_match";
      w_line.id = wloop_line_.markers.size();
      w_line.points.push_back(point1);
      w_line.points.push_back(point2);
      w_line.scale.x = 0.05;
      w_line.color.a = 1.0; // Don't forget to set the alpha!
      w_line.color.r = 1.0;
      w_line.color.g = 1.0;
      w_line.color.b = 0.0;
      wloop_line_.markers.push_back(w_line);
    }

    void Visualize::addText(const DataType::poseIndex& pose,
                            int pose_index,
                            double similar,
                            const std::string& frame_id){
      geometry_msgs::Point point1;
      point1.x = pose.p.x();
      point1.y = pose.p.y();
      point1.z = pose.p.z();
      visualization_msgs::Marker text_marker;

      text_marker.id = wloop_line_.markers.size();
      text_marker.ns = "text";
      text_marker.action = visualization_msgs::Marker::ADD;
      text_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
      text_marker.header.stamp = ros::Time::now();
      text_marker.header.frame_id = "/world";
      text_marker.scale.z = 0.2;
      text_marker.color.b = 0;
      text_marker.color.g = 0;
      text_marker.color.r = 255;
      text_marker.color.a = 1;
      std::ostringstream str;
      str<<pose_index<<"-"<<similar;
      text_marker.text = str.str();
      geometry_msgs::Pose text_pose;
      text_pose.position = point1;
      text_marker.pose = text_pose;

      wloop_line_.markers.push_back(text_marker);
    }
    void Visualize::publish(){

      pub_database_pose_.publish(database_pose_);
      pub_database_pose_path_.publish(database_pose_path_);
      pub_query_pose_.publish(query_pose_);
      pub_query_pose_path_.publish(query_pose_path_);
      pub_wloop_line_.publish(wloop_line_);
    }
  }
}