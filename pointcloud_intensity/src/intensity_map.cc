//
// Created by zzz on 19-3-13.
//

#include "intensity_map.h"

namespace GS{
  IntensityMap::IntensityMap(){
    std::string global_map_path = "/home/zzz/ground_point/global_map/groundTexture.pcd";
    global_map_ptr_ = std::make_shared<GlobalMap>(global_map_path);

    std::string submap_path = "/home/zzz/ground_point/submap";
    namespace bf = boost::filesystem;
    std::vector<bf::path> file_day_vec;
    if (bf::is_directory(submap_path)) {
      std::copy(bf::directory_iterator(submap_path), bf::directory_iterator(),
                std::back_inserter(file_day_vec));
      std::sort(file_day_vec.begin(), file_day_vec.end());
    }

    for(int i=0; i<static_cast<int>(file_day_vec.size()) && i<4; i++){
      std::shared_ptr<Submap> submap_ptr = std::make_shared<Submap>(file_day_vec[i].string());
      submap_vec_.emplace_back(submap_ptr);
    }
  }


  void IntensityMap::run_optimize(){

    for(int i=0; i< static_cast<int>(global_map_ptr_->extracted_points.size()); i++){
      pcl::PointXYZ point;
      point.x = global_map_ptr_->extracted_points[i][0];
      point.y = global_map_ptr_->extracted_points[i][1];
      point.z = global_map_ptr_->extracted_points[i][2];
      global_point_cloud_.push_back(point);
    }

    std::shared_ptr<Submap> submap_ptr = submap_vec_[6];
    icp_optimize(submap_ptr);

//    for(int i=0; i<static_cast<int>(submap_vec_.size()); i++){
//      std::shared_ptr<Submap> submap_ptr = submap_vec_[i];
////      std::cout<<"submap id="<<i<<std::endl;
////      publish(submap_ptr);
////      sleep(5);
////      icp_optimize(submap_ptr);
//    }

  }

  void IntensityMap::icp_optimize(std::shared_ptr<Submap> submap_ptr){
    Eigen::Quaternionf rotation = submap_ptr->rotation_;
    Eigen::Vector3f translator = submap_ptr->translator_;
    std::cout<<"rotation="<<rotation.toRotationMatrix()
             <<"\nquaternion="<<rotation.x()<<" "<<rotation.y()<<" "<<rotation.z()<<" "<<rotation.w()
             <<"\ntranslator="<<translator.transpose()<<std::endl;

    translator[0]+=0.5;
    translator[1]+=0.5;
//    Eigen::Quaternionf delta_r = Eigen::Quaternionf(Eigen::AngleAxisf(0.10,Eigen::Vector3f::UnitZ())
//                                 * Eigen::AngleAxisf(0,Eigen::Vector3f::UnitY())
//                                 * Eigen::AngleAxisf(0,Eigen::Vector3f::UnitX()));
//    std::cout<<" delta_r="<<delta_r.vec().transpose()
//             <<" x="<<delta_r.x()<<" "<<delta_r.y()<<" "<<delta_r.z()<<" "<<delta_r.w()<<std::endl;
//    rotation = rotation * delta_r;

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out(new pcl::PointCloud<pcl::PointXYZ>);

    cloud_out = global_point_cloud_.makeShared();

    cloud_in->width = submap_ptr->extracted_points_.size();
    cloud_in->height = 1;
    cloud_in->is_dense = false;
    cloud_in->points.resize(cloud_in->width * cloud_in->height);
    for(int i=0; i<submap_ptr->extracted_points_.size(); i++){
      Eigen::Vector3f point = submap_ptr->extracted_points_[i].head<3>();
      cloud_in->points[i].x=point[0];
      cloud_in->points[i].y=point[1];
      cloud_in->points[i].z=point[2];
    }

    {
      std::vector<Eigen::Vector4f> pre_points;
      for(int i=0; i<submap_ptr->extracted_points_.size(); i++){
        Eigen::Vector4f point;
        point.head<3>() = rotation * submap_ptr->extracted_points_[i].head<3>() + translator;
        point[3]=submap_ptr->extracted_points_[i][3];
        pre_points.push_back(point);
      }
      visual_pub_.pubSubmapExtractedPoints(pre_points);
      visual_pub_.pubGlobalExtractedPoints(global_map_ptr_->extracted_points);
//      visual_pub_.pubGlobalPoints(global_map_ptr_->g_origin_points);

//      publish(submap_ptr);
    }
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
    icp.setInputSource(cloud_in);
    icp.setInputTarget(cloud_out);
    icp.setMaximumIterations(50);
    icp.setMaxCorrespondenceDistance(1);
    icp.setTransformationEpsilon(1e-8);
    icp.setEuclideanFitnessEpsilon (1e-4);
    pcl::PointCloud<pcl::PointXYZ> Final;
    Eigen::Matrix4f guess = Eigen::Matrix4f::Identity();
    guess.block<3,3>(0,0) = rotation.toRotationMatrix();
    guess.block<3,1>(0,3) = translator;
    guess(3,3) = 1;
    std::cout<<"guess pose\n"<<guess<<std::endl;
//    icp.setRANSACOutlierRejectionThreshold(0.5);
//    icp.setRANSACIterations(50);

//    for(int i=0; i<50; i++)
    {
      LOG(INFO)<<"begin time";
      icp.align(Final,guess);
      {
        std::vector<Eigen::Vector4f> next_points;
        for(int i=0; i<Final.points.size(); i++){
          Eigen::Vector4f point;
          point[0]=Final.points[i].x;
          point[1]=Final.points[i].y;
          point[2]=Final.points[i].z;
//        point[3] = 1;
//        point = icp.getFinalTransformation() * point;
          point[3]=submap_ptr->extracted_points_[i][3];
          next_points.push_back(point);
        }
        visual_pub_.pubSubmapPoints(next_points);
      }

      //Return the state of convergence after the last align run.
      //If the two PointClouds align correctly then icp.hasConverged() = 1 (true).
      std::cout << "has converged: " << icp.hasConverged() <<std::endl;
      std::cout << "ransac iteration times: "<<icp.getRANSACIterations()<<std::endl;
      std::cout << "RotationThreshold: "<<icp.getConvergeCriteria()->getRotationThreshold()
                << " TranslationThreshold: "<<icp.getConvergeCriteria()->getTranslationThreshold()<<std::endl;
      std::cout << "correspondences size: "<<icp.correspondences_->size()<<std::endl;
      std::cout << "MaxCorrespondenceDistance: "<<icp.getMaxCorrespondenceDistance()<<std::endl;
      std::cout << "correspondence_rejectors size: "<<icp.correspondence_rejectors_.size()<<std::endl;
      //Obtain the Euclidean fitness score (e.g., sum of squared distances from the source to the target)
      std::cout << "score: " <<icp.getFitnessScore() << std::endl;
      std::cout << "----------------------------------------------------------"<< std::endl;

      //Get the final transformation matrix estimated by the registration method.
      std::cout << icp.getFinalTransformation() << std::endl;
      guess = icp.getFinalTransformation();

      LOG(INFO)<<"end time";
//      std::cout<<" iterator i="<<i<<" sleep"<<std::endl;
//      sleep(1);
    }

  }

  void IntensityMap::publish(std::shared_ptr<Submap> current_submap){
    visual_pub_.pubGlobalExtractedPoints(global_map_ptr_->extracted_points);
    std::vector<Eigen::Vector4f> submap_points;
    for(int i=0; i<current_submap->extracted_points_.size(); i++){
      Eigen::Vector4f point_in_submap = current_submap->extracted_points_[i];
      Eigen::Vector4f point_in_world;
      point_in_world.head<3>() = current_submap->rotation_ * point_in_submap.head<3>() + current_submap->translator_;
      point_in_world[3] = point_in_submap[3];
      submap_points.emplace_back(point_in_world);
    }
    visual_pub_.pubSubmapExtractedPoints(submap_points);
  }
}