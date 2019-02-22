//
// Created by zzz on 19-2-22.
//
namespace GS{
  Cluster::Cluster(){};
  std::vector<Eigen::Vector4f> Cluster::Otsu(std::vector<Eigen::Vector4f> points){
    const int GrayScale = 256;
    std::vector<int> intensityCount(GrayScale,0);
    std::vector<float> intensityPro(GrayScale,0);
    float threshold = 0;
    for(int i=0; i<points.size();i++){
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
    for(int i=0; i<points.size(); i++){
      if(points[i][3]>threshold){
        result.emplace_back(points[i]);
      }
    }
    return result;
  }
}
