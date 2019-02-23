//
// Created by zzz on 19-2-22.
//
#include "cluster.h"

namespace GS{
  Cluster::Cluster(){
  };

  std::vector<Eigen::Vector4f> Cluster::runCluster(GS::IntensityGrid* grid,
                           const std::vector<Eigen::Vector4f>& all_points){

    std::vector<Eigen::Vector4f>selected_points;
    std::vector<Eigen::Vector4f>result;

    for(int i=0; i<grid->width_; i++){
      for(int j=0; j<grid->height_; j++){
        if(grid->grid_[j*grid->width_ + i].size()>20){
//          std::cout<<"grid["<<i<<","<<j<<"]="<<grid->grid_[j*grid->width_ + i].size()<<std::endl;
          selected_points.clear();
          for(int k=0; k<grid->grid_[j*grid->width_ + i].size(); k++){
            int index = grid->grid_[j*grid->width_ + i][k];
//            std::cout<<" "<<index;
            selected_points.emplace_back(all_points[index]);
          }
//          std::cout<<"\n"<<std::endl;
          std::vector<Eigen::Vector4f> result_tmp = Otsu(selected_points);
//          std::cout<<"result_tmp["<<i<<","<<j<<"]="<<result_tmp.size()<<std::endl;
          result.insert(result.end(), result_tmp.begin(), result_tmp.end());
        }
      }
    }
    return result;
  }

  std::vector<Eigen::Vector4f> Cluster::Otsu(std::vector<Eigen::Vector4f> points){
//    std::cout<<"Otsu in"<<std::endl;
    const int GrayScale = 256;
    std::vector<int> intensityCount(GrayScale,0);
    std::vector<float> intensityPro(GrayScale,0);
    float threshold = 0;
    for(int i=0; i<(int)points.size();i++){
      intensityCount[static_cast<int>(points[i][3]+0.5)]++;
    }

    for(int i=0; i<GrayScale;i++){
      intensityPro[i] = static_cast<float>(intensityCount[i])/points.size();
    }

    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    for(int i=0; i<GrayScale; i++){
      w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
      for(int j=0; j<GrayScale; j++){
        if(j<=i){
          w0+=intensityPro[j];
          u0tmp+=j*intensityPro[j];
        }else{
          w1 += intensityPro[j];
          u1tmp+=j*intensityPro[j];
        }
      }
      u0 = u0tmp / w0;
      u1 = u1tmp / w1;
      u = u0tmp + u1tmp;
      deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
      if (deltaTmp > deltaMax)
      {
        deltaMax = deltaTmp;
        threshold = i;
      }
    }

    std::vector<Eigen::Vector4f> result;

    if(deltaMax < 5){
      return result;
    }
    for(int i=0; i<(int)points.size(); i++){
      if(points[i][3]>threshold){
        result.emplace_back(points[i]);
      }
    }
//    std::cout<<"deltaMax="<<deltaMax<<" threshold="<<threshold<<" size="<<result.size()<<std::endl;
    return result;
  }
}
