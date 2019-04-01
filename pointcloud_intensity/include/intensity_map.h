//
// Created by zzz on 19-3-13.
//

#ifndef POINTNETVLAD_ROS_OPTIMIZE_H
#define POINTNETVLAD_ROS_OPTIMIZE_H

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>

#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>

#include "submap.h"
#include "global_map.h"
#include "visualize.h"
namespace GS{
  class IntensityMap {
  public:
    IntensityMap();

    explicit IntensityMap(IntensityMap const &) = delete;
    void operator=(IntensityMap const &) = delete;
    void run_optimize();
    void icp_optimize(std::shared_ptr<Submap> submap_ptr);
    void publish(std::shared_ptr<Submap> current_submap);

  private:
    std::vector<std::shared_ptr<Submap>> submap_vec_;
    std::shared_ptr<GlobalMap> global_map_ptr_;
    Visualize visual_pub_;

    pcl::PointCloud<pcl::PointXYZ> global_point_cloud_;
  };
}

#endif //POINTNETVLAD_ROS_OPTIMIZE_H
