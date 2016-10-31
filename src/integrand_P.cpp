#include <integrands.hpp>
#include <rips.hpp>

int integrand_P( const int     *ndim,
                 const double  x[],
                 const int     *ncomp,
                 double        f[],
                 void          *userdata   ){

    rips *rp = static_cast<rips*>(userdata);
    double l1 = rp->l1;
    double l2 = rp->l2;
    double k = rp->k_current;
    double m = rp->m_current;
    double n = rp->n_current;

    double x1 = x[0]*l1;
    double x2 = x[1]*l2;

    double r = sqrt(x1*x1+x2*x2+rp->d*rp->d);
    double omega = k*rp->c0;

    double phi_mn = 2.0*sin(m*_pi_*x1/l1)*sin(n*_pi_*x2/l2)/sqrt(l1*l2);

    f[0] = phi_mn*omega*rp->rho0*rp->Q*sin(k*r)*l1*l2/4./_pi_/r;
    f[1] =-phi_mn*omega*rp->rho0*rp->Q*cos(k*r)*l1*l2/4./_pi_/r;

    return 0;
}
