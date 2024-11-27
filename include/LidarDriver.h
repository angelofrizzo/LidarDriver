#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H

#include <iostream>
#include <vector>

class LidarDriver{
public:
  //The constructor takes as input the _step variable.
  //The angle between two consecutive measurements in a recording.
  LidarDriver(const double& step);

  //Record new data into memory.
  void new_scan(const std::vector<double>& scan);

  //Returns the last recording without deleting it.
  std::vector<double> last_scan() const;

  //Returns the oldest scan recorded into memory. It also deletes the scan from memory.
  std::vector<double> get_scan();

  void clear_buffer();

  //Returns the distance measured at the angle closest to the angle given in input, in the most recent recording.
  const double& get_distance(const double& angle) const;

private:
  //The distance between two consecutive measurements in a scan.
  double step_;

  //Maximum angle recorded by the Lidar during a single scan.
  const unsigned int TOT_ANGLE = 180;

  //The maximum number of records in memory.
  const unsigned int BUFFER_DIM = 100;

  //Number of measurements each scan.
  unsigned int nSteps_;

  //Scan container. Each scan is a std::vector<double>.
  std::vector<std::vector<double>> buffer_;

  //Respectively position of most recent recording in memory and number of element.
  unsigned int front_ = 0, nElem_ = 0;

  //Function that returns an error if there are no data in memory;
  void errEmpty() const;

};

//This overloading prints the last recorded scan.
std::ostream& operator<<(std::ostream& os, const LidarDriver& in);

#endif
