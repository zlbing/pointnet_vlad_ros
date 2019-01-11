//
// Created by zzz on 19-1-10.
//
#ifndef INCLUDE_DATATYPE_POINTNETVLADTYPE_H
#define INCLUDE_DATATYPE_POINTNETVLADTYPE_H
#include <Eigen/Dense>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
namespace PointnetVlad {
  namespace DataType {
    struct poseIndex {
      std::string timestamp;
      Eigen::Vector3d p;
      Eigen::Quaterniond q;
    };
    class PointNetVladType {
    public:
      PointNetVladType(const std::string &base_path);

      explicit PointNetVladType(PointNetVladType const &) = delete;

      void operator=(PointNetVladType const &) = delete;

      void readData();

      const std::vector<std::vector<double>>& getTrajectoryDesc(int i){
        if(i>=trajectory_desc_vec_.size()){
          return std::vector<std::vector<double>>();
        }

          return trajectory_desc_vec_[i];
      }
      const std::vector<std::vector<Eigen::Vector3f>>& getTracjectoryPoints(int i){
        if(i>=trajectory_pointcloud_vec_.size()){
          return std::vector<std::vector<Eigen::Vector3f>>();
        }
        return trajectory_pointcloud_vec_[i];
      }
      const std::vector<poseIndex>& getTracjectoryPose(int i){
        if(i>=trajectory_pose_vec_.size()){
          return std::vector<poseIndex>();
        }
        return trajectory_pose_vec_[i];
      }
    private:
      std::string base_path_;
      std::vector<std::vector<poseIndex>> trajectory_pose_vec_;
      std::vector<std::vector<std::vector<Eigen::Vector3f>>> trajectory_pointcloud_vec_;
      std::vector<std::vector<std::vector<double>>> trajectory_desc_vec_;
    };
  }
}
#endif
