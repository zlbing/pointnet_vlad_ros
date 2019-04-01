//
// Created by zzz on 19-3-12.
//

#include "global_map.h"

namespace GS{
  GlobalMap::GlobalMap(const std::string &file_name){
    g_min_x=1e6;
    g_max_x=-1e6;
    g_min_y=1e6;
    g_max_y=-1e6;

    std::ifstream pointcloud_file;
    pointcloud_file.open(file_name.c_str(), std::ios::in);
    if(pointcloud_file.is_open()){
      std::string str;
      while (std::getline(pointcloud_file, str, '\n')) {
        std::vector<std::string> str_vec;
        boost::split(str_vec, str, boost::is_any_of(" "));
        if(str_vec[0] == "DATA"){
          break;
        }
      }

      while (std::getline(pointcloud_file, str, '\n')) {
        std::vector<std::string> str_vec;
        boost::split(str_vec, str, boost::is_any_of(" "));
        Eigen::Vector4f p;
        p[0] = boost::lexical_cast<float>(str_vec[0]);
        p[1] = boost::lexical_cast<float>(str_vec[1]);
        p[2] = boost::lexical_cast<float>(str_vec[2]);
        p[3] = boost::lexical_cast<float>(str_vec[3]);
        g_origin_points.emplace_back(p);
        g_min_x = (g_min_x < p[0])?g_min_x:p[0];
        g_max_x = (g_max_x > p[0])?g_max_x:p[0];
        g_min_y = (g_min_y < p[1])?g_min_y:p[1];
        g_max_y = (g_max_y > p[1])?g_max_y:p[1];
      }
      pointcloud_file.close();
    }else{
      LOG(ERROR)<<" lane line file can't open "<<file_name;
    }

    GS::IntensityGrid grid(g_min_x,g_max_x,
                           g_min_y,g_max_y, 1);
    grid.addPoints(g_origin_points);
    LOG(INFO)<<"g_origin_points size="<<g_origin_points.size();
    GS::Cluster cluster;
    extracted_points = cluster.runCluster(&grid, g_origin_points);
  }
}