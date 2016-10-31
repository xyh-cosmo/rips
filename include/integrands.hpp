#ifndef __INTEGRANDS__
#define __INTEGRANDS__

// extern "C"{
int integrand_sigma( const int *ndim, const double x[], const int *ncomp, double f[], void *userdata );
int integrand_P( const int *ndim, const double x[], const int *ncomp, double f[], void *userdata );
// }

#endif // __INTEGRANDS__
