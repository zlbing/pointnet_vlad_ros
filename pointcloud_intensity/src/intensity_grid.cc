//
// Created by zzz on 19-2-22.
//

#include "intensity_grid.h"
namespace GS {
  IntensityGrid::IntensityGrid(float min_x, float max_x,
                               float min_y, float max_y,
                               float resolution) :
          min_x_(min_x), max_x_(max_x), min_y_(min_y), max_y_(max_y),
          resolution_(resolution) {
    width_ = (max_x_ - min_x_ + 1)/resolution_;
    height_ = (max_y_ - min_y_ + 1)/resolution_;
    int length = width_ * height_;
    grid_.resize(length);
//    std::cout<<"width_="<<width_<<" height_="<<height_<<std::endl;
  };

  void IntensityGrid::addPoints(const std::vector<Eigen::Vector4f> &points) {
    for (int i = 0; i < static_cast<int>(points.size()); i++) {
      int index = getIndex(points[i]);
      grid_[index].emplace_back(i);
    }
  };

  int IntensityGrid::getIndex(const Eigen::Vector4f point){
    int w = (point[0] - min_x_)/resolution_;
    int h = (point[1] - min_y_)/resolution_;
    return h*width_+w;
  };

}


