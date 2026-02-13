#include "LowPassFilter.hpp"

void LowPassFilter::configure(double samp_freq, double damp_freq, double damp_intens)
{
    bool ok = false;
    double Nyq = damp_freq/(samp_freq/2);
    if(Nyq > 0 && Nyq <= 1){ // Nyquist freq respected
        double exponent = (-1/samp_freq)*((2*M_PI*damp_freq)/(std::pow(10, damp_intens/-10.0)));

        fbc = std::exp(exponent);
        ffc = 1 - fbc;

        std::cout << fbc << " ////// " << ffc << std::endl;
        
        yp = Eigen::Vector3d::Zero();
        xp = Eigen::Vector3d::Zero();
        ok = true;
    }
    confCheck = ok;
}

Eigen::Vector3d LowPassFilter::filter(Eigen::Vector3d input)
{
    if(confCheck){
        yp = ffc*xp + fbc*yp;
        xp = input;
        return yp;
    }
}