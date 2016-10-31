#include <rips.hpp>

int rips::function_Y( int m, int n, double k, double sigma_mn, double& Ymn_real, double& Ymn_imag ){

    double omega, omega2_mn, eta_mn;
    omega = k*this->c0;
    this->function_eta(m,n,k,sigma_mn,eta_mn);
    this->function_omega2(m,n,omega2_mn);

    double denominator_comm = pow(omega2_mn-omega*omega,2) + pow(omega2_mn*eta_mn,2);
    Ymn_real = 2.0*omega*omega2_mn*eta_mn/this->mu/denominator_comm;
    Ymn_imag = 2.0*omega*(omega2_mn-omega*omega)/this->mu/denominator_comm;

    // std::cout << "mu = " << this->mu << std::endl;
    // std::cout << "Ymn_real = " << Ymn_real << std::endl;
    // std::cout << "Ymn_imag = " << Ymn_imag << std::endl;
    // exit(0);

    return 0;
}
