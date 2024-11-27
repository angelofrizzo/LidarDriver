#include "../include/LidarDriver.h"

#include <iostream>
#include <cmath>

LidarDriver::LidarDriver(const double& step) {
    if (step>1 || step<0.1) {
        throw std::invalid_argument("step must be included between 0.1 and 1.0");
    }
    step_ = step;
    nSteps_ = static_cast<int>(TOT_ANGLE/step_) + 1;
    buffer_ = std::vector<std::vector<double>>(BUFFER_DIM);

    for (unsigned int i = 0; i < BUFFER_DIM; i++) {
        buffer_[i].resize(nSteps_);
    }
}

void LidarDriver::new_scan(const std::vector<double>& scan) {
    //_front point to next elem position.
    front_ = (front_ + 1) % BUFFER_DIM;

    //Increment number of elements.
    if (nElem_ < BUFFER_DIM) {
        nElem_++;
    }

    if (scan.size() <= nSteps_) {
        std::copy(scan.begin(), scan.end(), buffer_[front_].begin());
        for (unsigned int i = scan.size(); i < nSteps_; i++) {
            buffer_[front_][i] = 0.0;
        }
    }
    else {
        std::copy_n(scan.begin(), nSteps_, buffer_[front_].begin());
    }
}

std::vector<double> LidarDriver::last_scan() const {
    errEmpty();
    return buffer_[front_];
}

std::vector<double> LidarDriver::get_scan() {
    errEmpty();
    nElem_--;
    return buffer_[((front_-nElem_) + BUFFER_DIM) % BUFFER_DIM];
}

void LidarDriver::clear_buffer() {
    front_ = 0;
    nElem_ = 0;
}

const double &LidarDriver::get_distance(const double &angle) const {
    errEmpty();
    int x = static_cast<int>(std::round(angle/step_));
    return buffer_[front_][x];
}

void LidarDriver::errEmpty() const{
    if (nElem_ == 0) {
        throw std::out_of_range("LidarDriver:: buffer is empty");
    }
}

std::ostream& operator<<(std::ostream& os, const LidarDriver& in) {
    const std::vector<double>& last_data = in.last_scan();
    for (const double& elem : last_data) {
        os << elem << "\t";
    }
    return os;
}
