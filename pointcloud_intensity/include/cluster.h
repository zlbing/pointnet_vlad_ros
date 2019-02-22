//
// Created by zzz on 19-2-22.
//

#ifndef POINTNETVLAD_ROS_CLUSTER_H
#define POINTNETVLAD_ROS_CLUSTER_H

namespace GS{
  class Cluster{
  public:
    Cluster();
    explicit Cluster(Cluster const &) = delete;
    void operator=(Cluster const &) = delete;

    std::vector<Eigen::Vector4f> Otsu(std::vector<Eigen::Vector4f> points);
  };
}
#endif //POINTNETVLAD_ROS_CLUSTER_H
