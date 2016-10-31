#include <rips.hpp>

int rips::function_omega2( int m, int n, double& omega2_mn ){
    omega2_mn = (this->D/this->mu)
                *( pow(m*_pi_/this->l1,4)
                + 2.0*pow(m*_pi_/this->l1,2)*pow(n*_pi_/this->l2,2)
                + pow(m*_pi_/this->l1,4) );
    return 0;
}
