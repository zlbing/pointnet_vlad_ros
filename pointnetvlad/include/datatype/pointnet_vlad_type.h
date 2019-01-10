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

namespace DataType{
  class PointNetVladType{
  public:
    struct poseIndex{
      std::string timestamp;
      Eigen::Vector3d p;
      Eigen::Quaterniond q;
    };
    PointNetVladType(const std::string& base_path);
    explicit PointNetVladType(PointNetVladType const&) = delete;
    void operator=(PointNetVladType const&) = delete;

    void readData();


  private:
    std::string base_path_;
    std::vector<std::vector<poseIndex>> trajectory_pose_vec_;
    std::vector<std::vector<Eigen::Vector3f>> trajectory_pointcloud_vec_;
    std::vector<std::vector<double>> trajectory_desc_;
  };
}
#endif
