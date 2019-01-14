//
// Created by zzz on 19-1-10.
//

#ifndef POINTNETVLAD_ROS_LOOP_CLOSURE_H
#define POINTNETVLAD_ROS_LOOP_CLOSURE_H
#include "datatype/pointnet_vlad_type.h"
#include "visualize/visualize.h"

namespace PointnetVlad{
  class LoopClosure{
  public:
    LoopClosure(const std::string &base_path, double loop_similar);
    explicit LoopClosure(LoopClosure const &) = delete;
    void operator=(LoopClosure const &) = delete;
    std::pair<std::vector<int>, std::vector<double>> loop(int database_trajectory,
                                                          int query_trajectory);

    void visulizeLoopClosure(int database_trajectory,
                             int query_trajectory,
                             const std::vector<int>& loop_index_vec,
                             const std::vector<double>& loop_similar_vec);

    double calSimilarity(const std::vector<double>& desc_1,
                         const std::vector<double>& desc_2);
  private:
    std::shared_ptr<DataType::PointNetVladType> pn_vlad_data_ptr_;
    std::string base_file_path_;
    double loop_similar_threshold_;
    std::shared_ptr<visualize::Visualize> visual_ptr_;
  };
}

#endif //POINTNETVLAD_ROS_LOOP_CLOSURE_H
