#include <iostream>
#include "../include/LidarDriver.h"

int main(){
  LidarDriver Lidar(1);
  std::vector<double> temp(181);

  for (int j = 0; j < 101; j++) {
    for (int i = 0; i < temp.size(); i++) {
      temp[i] = i * j;
    }
    Lidar.new_scan(temp);
    std:: cout << "Print " << j << " line.\n";
    std::cout << Lidar << std::endl;
  }

  temp = Lidar.get_scan();
  for (int i = 0; i < temp.size(); i++) {
    std::cout << temp[i] << "\t";
  }
  std::cout << std::endl;

  return 0;
}

