#ifndef LOW_PASS_FILTER_HPP
#define LOW_PASS_FILTER_HPP

#include <vector>
#include <string>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <fstream>
#include <cmath>

class LowPassFilter
{
    public:
        void configure(double samp_freq, double damp_freq, double damp_intens);
        Eigen::Vector3d filter(Eigen::Vector3d input);

    private:
        // filter coeff;
        double fbc;
        double ffc;
        Eigen::Vector3d xp;
        Eigen::Vector3d yp;

        // check
        bool confCheck;
};


#endif // LOW_PASS_FILTER_HPP