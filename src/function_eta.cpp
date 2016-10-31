#include <rips.hpp>

int rips::function_eta( int m, int n, double k, double sigma_mn, double& eta_mn ){
    double omega, omega2_mn;
    omega = k*this->c0;
    this->function_omega2(m,n,omega2_mn);
    eta_mn  = this->eta_s + 2.0*this->rho0*this->c0*sigma_mn*omega/this->mu/omega2_mn;
    return 0;
}
