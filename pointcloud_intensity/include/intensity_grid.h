//
// Created by zzz on 19-2-22.
//

#ifndef POINTNETVLAD_ROS_INTENSITY_GRID_H
#define POINTNETVLAD_ROS_INTENSITY_GRID_H
#include <Eigen/Dense>
#include <iostream>
namespace GS{
class IntensityGrid{
public:
  IntensityGrid(float min_x,float max_x,
                float min_y,float max_y,
                float resolution);

  explicit IntensityGrid(IntensityGrid const &) = delete;
  void operator=(IntensityGrid const &) = delete;

  void addPoints(const std::vector<Eigen::Vector4f>& points);
  int getIndex(const Eigen::Vector4f point);

public:
  float min_x_;
  float max_x_;
  float min_y_;
  float max_y_;
  float resolution_;
  int width_,height_;
  std::vector<std::vector<int>> grid_;
};
}
#endif //POINTNETVLAD_ROS_INTENSITY_GRID_H
