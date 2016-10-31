#ifndef __RIPS__
#define __RIPS__

#include <iostream>
#include <cmath>
#include <string>

#if REALSIZE == 16
    #include "cubaq.h"
#elif REALSIZE == 10
    #include "cubal.h"
#else
    #include "cuba.h"
#endif

#define _pi_ 3.1415926535

class rips{

    public:
    //  Configure filename
        std::string config_file;

    //  ======================================
    //  rips model parameters
        int    m, m_max, m_current;
        int    n, n_max, n_current;
        double l1, l2;
        double d, E, D, mu, mu_b, Q, A;
        double eta_s, rho0, rho, c0;;

        double sigma_scale; // used to re-weight sigma integrand function to avoid nan / inf.

    //  settings about the output
        std::string output_filename;
        bool   use_logscale_in_k; // if ture, then use dlnk to generate array of k
        int    k_num;
        double k, k_min, k_max, dk, dlnk, k_current;
        double* array_k;
        double* array_tau;
        double* matrix_sigma;
        double* matrix_Y2;
        double* matrix_P2;

    //  ======================================

    //  ======================================
    //  CUBA parameters
        int solver_id;          //  0=vegas; 1=suave; 2=chure;

        int verbose;            //  VERBOSE 2
        int last;               //  LAST 4
        int speed;              //  SPEDD 0
        int ndim;               //  NDIM 2
        int ncomp;              //  NCOMP 1
        int nvec;               //  NVEC 1
        int n_batch;            //  NBATCH 1000
        int grid_num;           //  GRIDNO 0
        int n_new;              //  NNEW 1000
        int n_min;              //  NMIN 2

        int min_eval;           //  MINEVAL 0
        int max_eval;           //  MAXEVAL 500000
        int n_start;            //  NSTART 1000
        int n_increase;         //  NINCREASE 500

        int key;                //  KEY 0
        int key1;               //  KEY1 47
        int key2;               //  KEY2 1
        int key3;               //  KEY3 1

        int max_pass;           //  MAXPASS 5
        int n_extra;            //  NEXTRA 0
        int n_given;            //  NGIVEN 0
        int ldx_given;          //  LDXGIVEN NDIM

        double eps_rel;         //  EPSREL 1e-6
        double eps_abs;         //  EPSABS 1e-6
        double flatness;        //  FLATNESS 25.
        double border;          //  BORDER 0.
        double max_chisq;       //  MAXCHISQ 10.
        double min_deviation;   //  MINDEVIATION .25

        std::string state_file; //  STATEFILE
        std::string spin;       //  SPIN
    //  ======================================

    //  member functions:
    //  default constructor
        rips();

    //  destructor
        ~rips();

    //  initialization
        int init( int argc, char *argv[] );

    //  set rips model parameters
        int rips_config( std::string& inifile );

    //  set cuba parameters to their default values
        int cuba_config( );

    //  re-set cuba parameters to user specified values, need a ini parameter file
        int cuba_config( std::string& inifile );

    //  Some functions donot involve real integrations
        int function_eta( int m, int n, double k, double sigma_mn, double& eta_mn );
        int function_omega2( int m, int n, double& omega2_mn );
        int function_Y( int m, int n, double k, double sigma_mn, double& Ymn_real, double& Ymn_imag );


    //  core functions calling cuba solvers
        int solve();
        int run_vegas();
        int run_suave();
        int run_chure();

    //  int save the result into *.txt file
        int save_result();
};

#endif  //  __RIPS__
