//
// Created by zzz on 19-1-10.
//
#include "loopclosure/loop_closure.h"

namespace PointnetVlad{
  LoopClosure::LoopClosure(const std::string &base_path, double loop_similar){
    base_file_path_ = base_path;
    pn_vlad_data_ptr_ = std::make_shared<DataType::PointNetVladType>(base_file_path_);
    pn_vlad_data_ptr_->readData();

    visual_ptr_ = std::make_shared<visualize::Visualize>();
    loop_similar_threshold_ = loop_similar;
  }

  std::pair<std::vector<int>, std::vector<double>> LoopClosure::loop(int database_trajectory, int query_trajectory){
    std::cout<<"[LoopClosure::loop] in"<<std::endl;
    const std::vector<std::vector<double>>& database_desc = pn_vlad_data_ptr_->getTrajectoryDesc(database_trajectory);
    const std::vector<std::vector<double>>& query_desc = pn_vlad_data_ptr_->getTrajectoryDesc(query_trajectory);
    std::vector<int> loop_index_vec;
    std::vector<double> loop_similar_vec;

    for(size_t i=0; i<query_desc.size(); i++){
        int max_index=-1;
        double max_similar=0;
        for(size_t j=0; j< database_desc.size(); j++){
//          std::cout<<"i="<<i<<"j="<<j<<std::endl;
//          std::cout<<"query_desc[i]="<<query_desc[i][0]<<std::endl;
//          std::cout<<"database_desc[j]="<<database_desc[j][0]<<std::endl;
          double similar = calSimilarity(query_desc[i], database_desc[j]);
          if(similar > max_similar){
            max_similar = similar;
            max_index = j;
          }
        }
        if(max_index>=0){
          loop_index_vec.push_back(max_index);
          loop_similar_vec.push_back(max_similar);
//          std::cout<<"i="<<i<<" j="<<max_index<<" similar="<<max_similar<<std::endl;
        }
    }
    return std::make_pair(loop_index_vec, loop_similar_vec);
  }

  double LoopClosure::calSimilarity(const std::vector<double>& desc_1,
                                    const std::vector<double>& desc_2){
    double similar=0;
    for(size_t i=0; i<desc_1.size(); i++){
      similar+=desc_1[i] * desc_2[i];
    }
    return similar;
  }

  void LoopClosure::visulizeLoopClosure(int database_trajectory,
                                        int query_trajectory,
                                        const std::vector<int>& loop_index_vec,
                                        const std::vector<double>& loop_similar_vec){
    std::cout<<"[LoopClosure::visulizeLoopClosure] in"<<std::endl;
    const std::vector<DataType::poseIndex>& database_pose = pn_vlad_data_ptr_->getTracjectoryPose(database_trajectory);
    const std::vector<DataType::poseIndex>& query_pose = pn_vlad_data_ptr_->getTracjectoryPose(query_trajectory);
    const std::vector<std::vector<Eigen::Vector3f>>& database_pointcloud = pn_vlad_data_ptr_->getTracjectoryPoints(database_trajectory);
    visual_ptr_->addDatabasePose(database_pose,"world");
    for(size_t i=0; i<loop_index_vec.size(); i++){
      int database_index = loop_index_vec[i];
      int query_index = i;
//      std::cout<<"[visulizeLoopClosure]loopclosure result: query=" <<query_index
//               <<" database_index="<<database_index<<std::endl;
      visual_ptr_->addQueryPose(query_pose[query_index],"world");
      if(loop_similar_vec[i] < loop_similar_threshold_){
        continue;
      }
      double delta = (query_pose[query_index].p - database_pose[database_index].p).norm();
      if(delta > 10 ){
        std::cout<<"[visulizeLoopClosure wrong query]"<<" database_index="<<database_index
                 <<" query_index="<<query_index<<" similar="<<loop_similar_vec[i]<<std::endl;
        visual_ptr_->addWrongLoopLine(database_pose[database_index], query_pose[query_index], "world");
        visual_ptr_->addText(query_pose[query_index], query_index, loop_similar_vec[i], "world");
      }else{
        visual_ptr_->addRightLoopLine(database_pose[database_index], query_pose[query_index], "world" );
        visual_ptr_->addText(query_pose[query_index], query_index, loop_similar_vec[i], "world");
      }
      visual_ptr_->publish();
      usleep(5000);
    }
    visual_ptr_->addDatabasePointCloud(database_pointcloud,database_pose,"world");
  }
}