//
// Created by zzz on 19-2-22.
//

#ifndef POINTNETVLAD_ROS_CLUSTER_H
#define POINTNETVLAD_ROS_CLUSTER_H
#include <Eigen/Dense>
#include "intensity_grid.h"
#include <iostream>
namespace GS{
  class Cluster{
  public:
    Cluster();
    explicit Cluster(Cluster const &) = delete;
    void operator=(Cluster const &) = delete;

    std::vector<Eigen::Vector4f> runCluster(GS::IntensityGrid* grid,
                                            const std::vector<Eigen::Vector4f>& all_points);
    std::vector<Eigen::Vector4f> Otsu(std::vector<Eigen::Vector4f> points);

  public:
  };
}
#endif //POINTNETVLAD_ROS_CLUSTER_H
