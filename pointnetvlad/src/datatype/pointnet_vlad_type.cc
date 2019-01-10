//
// Created by zzz on 19-1-10.
//

#include "datatype/pointnet_vlad_type.h"
namespace DataType{
  PointNetVladType::PointNetVladType(const std::string& base_path){
    base_path_ = base_path;
  }

  void PointNetVladType::readData(){
    namespace bf = boost::filesystem;
    std::vector<bf::path> file_day_vec;
    if(bf::is_directory(base_path_)){
      std::copy(bf::directory_iterator(base_path_), bf::directory_iterator(), std::back_inserter(file_day_vec));
      std::sort(file_day_vec.begin(), file_day_vec.end());
    }
    std::ifstream pose_data_file;
    Eigen::Quaterniond rotation;
    Eigen::Vector3d position;
    //read position index
    for(size_t i=0; i<file_day_vec.size(); i++){
      std::string pose_file_path = file_day_vec[i].string() + "/pose.csv";
      std::cout<<"pose_file_path="<<pose_file_path<<std::endl;
      pose_data_file.open(pose_file_path.c_str(), std::ios::in);

      if(pose_data_file.is_open()){
        std::vector<poseIndex> pose_vec;
        std::string str;
        std::getline(pose_data_file, str, '\n');
        std::cout<<"headline="<<str;
        while(std::getline(pose_data_file, str, '\n')){
          std::vector<std::string> str_vec;
          boost::split(str_vec,str,boost::is_any_of(","));
          std::string timestamp = str_vec[0];
          position = Eigen::Vector3d(boost::lexical_cast<double>(str_vec[1]),
                                     boost::lexical_cast<double>(str_vec[2]),
                                     boost::lexical_cast<double>(str_vec[3]));
          rotation = Eigen::Quaterniond(boost::lexical_cast<double>(str_vec[4]),
                                        boost::lexical_cast<double>(str_vec[5]),
                                        boost::lexical_cast<double>(str_vec[6]),
                                        boost::lexical_cast<double>(str_vec[7]));
          poseIndex pose;
          pose.timestamp =timestamp;
          pose.p = position;
          pose.q = rotation;
          pose_vec.push_back(pose);
        }
        pose_data_file.close();
        trajectory_pose_vec_.push_back(pose_vec);
      }else{
        std::cerr<<"pose_data_file="<<pose_file_path<<" is not opened"<<std::endl;
        exit(-1);
      }
    }
    //read pointcloud
    for(size_t i=0; i<trajectory_pose_vec_.size(); i++){
      const auto& pose_vec = trajectory_pose_vec_[i];
      for(size_t j=0; j<pose_vec.size(); j++){
        std::string pose_pointcloud_file_path = file_day_vec[i].string()+"/pointcloud/"+ pose_vec[j].timestamp + ".bin";
        std::ifstream data_file;
        data_file.open(pose_pointcloud_file_path.c_str(), std::ios::in | std::ios::binary);
        if(data_file.is_open()){
          std::vector<Eigen::Vector3f> pointcloud_vec;
          Eigen::Vector3f point_data;
          while(data_file.read((char*)point_data.data(), 3 * sizeof(typename Eigen::Vector3f::Scalar))){
            pointcloud_vec.push_back(point_data);
          }
          trajectory_pointcloud_vec_.push_back(pointcloud_vec);
          data_file.close();
        }else{
          std::cerr<<"data_file="<<pose_pointcloud_file_path<<" is not opened"<<std::endl;
          exit(-1);
        }
      }
    }

    //read descriptor
    for(size_t i=0; i<trajectory_pose_vec_.size(); i++) {
      std::string desc_file_path = file_day_vec[i].string() + "/descriptor.txt";
      std::ifstream desc_file;
      desc_file.open(desc_file_path.c_str(), std::ios::in);
      if(desc_file.is_open()) {
        std::string str;
        std::vector<double> desc;
        while (std::getline(desc_file, str, '\n')) {
          std::vector<std::string> str_vec;
          boost::split(str_vec,str,boost::is_any_of(","));
          for(size_t j=0; j< str_vec.size(); j++){
            double data = boost::lexical_cast<double>(str_vec[j]);
            desc.push_back(data);
          }
          trajectory_desc_.push_back(desc);
        }
      }
    }
  }
}