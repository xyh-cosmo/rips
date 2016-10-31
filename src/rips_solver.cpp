#include <rips.hpp>
#include <integrands.hpp>
#include <parser++.hpp>
#include <iostream>
#include <fstream>

#include "cuba.h"

int rips::solve(){
    double sum = 0;
    int matrix_id;

    std::ofstream of(this->output_filename.c_str());

    for( int i=0; i<this->k_num; ++i ){

        this->k_current = this->array_k[i];

        std::cout << "rips:: computing "
                  << (i+1) << " of " << this->k_num
                  << " k-tau" << std::endl;

        if( this->solver_id == 0 )
            this->run_vegas();
        else if( this->solver_id == 1 )
            this->run_suave();
        else if( this->solver_id == 2 )
            this->run_chure();

        sum = 0.0;
        for( int m=0; m<this->m_max; ++m ){
            for( int n=0; n<this->n_max; ++n ){
                matrix_id = this->n_max*m + n;
                sum += this->matrix_sigma[matrix_id]*this->matrix_Y2[matrix_id]*this->matrix_P2[matrix_id];
                this->matrix_sigma[matrix_id] = 0.0;
                this->matrix_Y2[matrix_id]    = 0.0;
                this->matrix_P2[matrix_id]    = 0.0;
            }
        }

        this->array_tau[i] = 16.*_pi_*_pi_/this->A/pow(this->Q*this->array_k[i],2)*sum;

        of << std::setw(16) << std::setprecision(10) << this->array_k[i]
           << std::setw(16) << std::setprecision(10) << this->array_tau[i] << std::endl;

       std::cout  << std::setw(16) << std::setprecision(10) << this->array_k[i]
              << std::setw(16) << std::setprecision(10) << this->array_tau[i] << std::endl;
    }

    // save result into *txt.

    of.close();

    return 0;
}

int rips::run_vegas(){
//  Note: Y_mn and P_mn are complex numbers.
    double sigma_mn;
    double Ymn_r, Ymn_i;
    double Pmn_r, Pmn_i;

    int neval, fail;
    double integral[2], error[2], prob[2];

    for( int m=1; m<=this->m_max; ++m ){
        for( int n=1; n<=this->n_max; ++n ){
            int matrix_id = this->n_max*(m-1) + (n-1);  // be careful here
            //  step 1: compute P_mn
            //  step 2: compute sigma_mn
            //  step 3: compute Y_mn

            this->m_current = m;
            this->n_current = n;

            // Vegas(NDIM, NCOMP, Integrand, USERDATA, NVEC,
            // EPSREL, EPSABS, VERBOSE, SEED,
            // MINEVAL, MAXEVAL, NSTART, NINCREASE, NBATCH,
            // GRIDNO, STATEFILE, SPIN,
            // &neval, &fail, integral, error, prob);

           Vegas(  2, 2, &integrand_P, this, 1,
                   this->eps_rel, this->eps_abs,
                   this->verbose, this->speed,
                   this->min_eval, this->max_eval,
                   this->n_start, this->n_increase,
                   this->n_batch, this->grid_num,
                   NULL, NULL,
                   &neval, &fail, integral, error, prob );

            Pmn_r = integral[0];
            Pmn_i = integral[1];
            // std::cout << "P^2_mn = " << Pmn_r*Pmn_r + Pmn_i*Pmn_i << std::endl;

            Vegas(  2, 1, &integrand_sigma, this, 1,
                    this->eps_rel, this->eps_abs,
                    this->verbose, this->speed,
                    this->min_eval, this->max_eval,
                    this->n_start, this->n_increase,
                    this->n_batch, this->grid_num,
                    NULL, NULL,
                    &neval, &fail, integral, error, prob );
            sigma_mn = integral[0];

            this->function_Y( m, n, this->k_current, sigma_mn*this->sigma_scale, Ymn_r, Ymn_i );

            this->matrix_sigma[matrix_id] = sigma_mn;
            this->matrix_P2[matrix_id] = Pmn_r*Pmn_r + Pmn_i*Pmn_i;
            this->matrix_Y2[matrix_id] = Ymn_r*Ymn_r + Ymn_i*Ymn_i;

            std::cout << " k = " << this->k_current << ", m = " << m << ", n = " << n << std::endl;
            std::cout << " sigma_mn = " << sigma_mn*this->sigma_scale << std::endl;
            std::cout << " P2_mn* = " << this->matrix_P2[matrix_id] << std::endl;
            std::cout << " Y2_mn* = " << this->matrix_Y2[matrix_id] << std::endl << std::endl;
            //
            // exit(0);
        }
    }

    return 0;
}

int rips::run_suave(){
//  Note: Y_mn and P_mn are complex numbers.
    double sigma_mn;
    double Ymn_r, Ymn_i;
    double Pmn_r, Pmn_i;

    int neval, fail, nregions;
    double integral[2], error[2], prob[2];

    for( int m=1; m<=this->m_max; ++m ){
        for( int n=1; n<=this->n_max; ++n ){
            int matrix_id = this->n_max*(m-1) + (n-1);  // be careful here
            //  step 1: compute P_mn
            //  step 2: compute sigma_mn
            //  step 3: compute Y_mn

            this->m_current = m;
            this->n_current = n;

            Suave( 2, 2, &integrand_P, this, 1,
                   this->eps_rel, this->eps_abs,
                   this->verbose | this->last, rand(),
                   this->min_eval, this->max_eval,
                   this->n_new, this->n_min, this->flatness,
                   NULL, NULL,
                   &nregions, &neval, &fail, integral, error, prob);

            Pmn_r = integral[0];
            Pmn_i = integral[1];

            Suave( 2, 1, &integrand_sigma, this, 1,
                   this->eps_rel, this->eps_abs,
                   this->verbose | this->last, rand(),
                   this->min_eval, this->max_eval,
                   this->n_new, this->n_min, this->flatness,
                   NULL, NULL,
                   &nregions, &neval, &fail, integral, error, prob);
            sigma_mn = integral[0];

            this->function_Y( m, n, this->k_current, sigma_mn*this->sigma_scale, Ymn_r, Ymn_i );

            this->matrix_sigma[matrix_id] = sigma_mn;
            this->matrix_P2[matrix_id] = Pmn_r*Pmn_r + Pmn_i*Pmn_i;
            this->matrix_Y2[matrix_id] = Ymn_r*Ymn_r + Ymn_i*Ymn_i;

            std::cout << " k = " << this->k_current << ", m = " << m << ", n = " << n << std::endl;
            std::cout << " sigma_mn = " << sigma_mn*this->sigma_scale << std::endl;
            std::cout << " P2_mn* = " << this->matrix_P2[matrix_id] << std::endl;
            std::cout << " Y2_mn* = " << this->matrix_Y2[matrix_id] << std::endl << std::endl;
            // exit(0);
        }
    }

    return 0;
}

int rips::run_chure(){
//  Note: Y_mn and P_mn are complex numbers.
    double sigma_mn;
    double Ymn_r, Ymn_i;
    double Pmn_r, Pmn_i;

    int neval, fail, nregions;
    double integral[2], error[2], prob[2];

    for( int m=1; m<=this->m_max; ++m ){
        for( int n=1; n<=this->n_max; ++n ){
            int matrix_id = this->m_max*(m-1) + (n-1);  // be careful here
            //  step 1: compute P_mn
            //  step 2: compute sigma_mn
            //  step 3: compute Y_mn

            this->m_current = m;
            this->n_current = n;

            // Cuhre(NDIM, NCOMP, Integrand, USERDATA, NVEC,
            //   EPSREL, EPSABS, VERBOSE | LAST,
            //   MINEVAL, MAXEVAL, KEY,
            //   STATEFILE, SPIN,
            //   &nregions, &neval, &fail, integral, error, prob);

            Cuhre( 2, 2, &integrand_P, this, 1,
                   this->eps_rel, this->eps_abs,
                   this->verbose | this->last,
                   this->min_eval, this->max_eval, this->key,
                   NULL, NULL,
                   &nregions, &neval, &fail, integral, error, prob);

            Pmn_r = integral[0];
            Pmn_i = integral[1];

            Cuhre( 2, 1, &integrand_sigma, this, 1,
                   this->eps_rel, this->eps_abs,
                   this->verbose | this->last,
                   this->min_eval, this->max_eval, this->key,
                   NULL, NULL,
                   &nregions, &neval, &fail, integral, error, prob);

            sigma_mn = integral[0];

            this->function_Y( m, n, this->k_current, sigma_mn*this->sigma_scale, Ymn_r, Ymn_i );

            this->matrix_sigma[matrix_id] = sigma_mn;
            this->matrix_P2[matrix_id] = Pmn_r*Pmn_r + Pmn_i*Pmn_i;
            this->matrix_Y2[matrix_id] = Ymn_r*Ymn_r + Ymn_i*Ymn_i;

            // std::cout << " k = " << this->k_current << ", m = " << m << ", n = " << n << std::endl;
            // std::cout << " sigma_mn = " << sigma_mn*this->sigma_scale << std::endl;
            // std::cout << " P2_mn* = " << this->matrix_P2[matrix_id] << std::endl;
            // std::cout << " Y2_mn* = " << this->matrix_Y2[matrix_id] << std::endl << std::endl;
            // exit(0);
        }
    }

    return 0;
}
