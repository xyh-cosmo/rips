#include <integrands.hpp>
#include <rips.hpp>

int integrand_sigma( const int     *ndim,
                     const double  x[],
                     const int     *ncomp,
                     double        f[],
                     void          *userdata   ){

    rips *r = static_cast<rips*>(userdata);

    double theta  = x[0]*_pi_/2.0;
    double phi    = x[1]*_pi_/2.0;

    double alpha  = r->k_current*r->l1*sin(theta)*cos(phi);
    double beta   = r->k_current*r->l2*sin(theta)*sin(phi);
    double sigma_scale  = r->sigma_scale;
    double numerator    = 1.0;
    double denominator  = 1.0;

    if( r->m_current%2 == 0 )
        numerator *= sin(0.5*alpha);
    else
        numerator *= cos(0.5*alpha);

    if( r->n_current%2 == 0 )
        numerator *= sin(0.5*beta);
    else
        numerator *= cos(0.5*beta);

    denominator *= (pow(alpha/r->m_current/_pi_, 2) - 1.0);
    denominator *= (pow(beta/r->n_current/_pi_, 2) - 1.0);

    f[0] = pow(numerator/denominator,2)*sin(theta);
    f[0] = f[0]*_pi_*_pi_/4.0/sigma_scale;
    f[0] = f[0]*64.*r->k_current*r->k_current*r->l1*r->l2/pow(_pi_,6)/r->m_current/r->m_current/r->n_current/r->n_current;

    return 0;
}
