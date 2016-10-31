#include <rips.hpp>
#include <parser++.hpp>

using namespace imcmc::parser;

rips::rips(){
//  initialize the arrays and maritx to NULL pointers
    this->array_k       = NULL;
    this->array_tau     = NULL;
    this->matrix_Y2     = NULL;
    this->matrix_P2     = NULL;
    this->matrix_sigma  = NULL;

//  initialize cuba settings to their default values.
    this->cuba_config();

    this->sigma_scale = 1.0;
    this->solver_id = 0;
}

rips::~rips(){
    if( this->array_k != NULL ){
        delete[] this->array_k;
        this->array_k = NULL;
    }

    if( this->array_tau != NULL ){
        delete[] this->array_tau;
        this->array_tau = NULL;
    }

    if( this->matrix_Y2 != NULL ){
        delete[] this->matrix_Y2;
        this->matrix_Y2 = NULL;
    }

    if( this->matrix_P2 != NULL ){
        delete[] this->matrix_P2;
        this->matrix_P2 = NULL;
    }

    if( this->matrix_sigma != NULL ){
        delete[] this->matrix_sigma;
        this->matrix_sigma = NULL;
    }
}

int rips::init( int argc, char *argv[] ){

    if( argc <= 1 ){
        std::cout << "usage of rips: \n" << "\t" << argv[0] << " *.ini" << std::endl;
        exit(0);
    }
    else{
        this->config_file = std::string(argv[1]);
        std::cout << "rips: find input parameter file: " << this->config_file << std::endl;
    }

    this->cuba_config( this->config_file );
    this->rips_config( this->config_file );

    return 0;
}

int rips::rips_config( std::string& inifile ){

    this->use_logscale_in_k = Read::Read_Bool_from_File(inifile, "use_logscale_in_k");
    this->k_num = Read::Read_Int_from_File(inifile, "k_num");
    this->k_min = Read::Read_Double_from_File(inifile,"k_min");
    this->k_max = Read::Read_Double_from_File(inifile,"k_max");

    this->m_max = Read::Read_Int_from_File(inifile, "m_max");
    this->n_max = Read::Read_Int_from_File(inifile, "n_max");

    this->l1 = Read::Read_Double_from_File(inifile, "l1");
    this->l2 = Read::Read_Double_from_File(inifile, "l2");

    this->c0    = Read::Read_Double_from_File(inifile,"c0");
    this->rho0  = Read::Read_Double_from_File(inifile,"rho0");
    this->d     = Read::Read_Double_from_File(inifile,"d");
    this->E     = Read::Read_Double_from_File(inifile,"E");
    this->Q     = Read::Read_Double_from_File(inifile,"Q");
    this->eta_s = Read::Read_Double_from_File(inifile,"eta_s");

    this->rho   = Read::Read_Double_from_File(inifile,"rho");
    this->mu    = this->rho*this->d;

    this->mu_b  = Read::Read_Double_from_File(inifile,"mu_b");
    this->D     = this->E*pow(this->d,3)/12./(1.-this->mu_b*this->mu_b);

    double tga = 0.5*this->l1/this->d;
    double tgb = 0.5*this->l2/this->d;
    double cos_a = cos(atan(tga));
    double cos_b = cos(atan(tgb));
    this->A = 4.*( atan(tgb/tga) + atan(tga/tgb) - asin(cos_a*sin(atan(tgb/tga))) - asin(cos_b*sin(atan(tga/tgb))) );

    this->array_k   = new double[this->k_num];
    this->array_tau = new double[this->k_num];

    this->matrix_sigma  = new double[this->m_max*this->n_max];
    this->matrix_Y2     = new double[this->m_max*this->n_max];
    this->matrix_P2     = new double[this->m_max*this->n_max];

    if( this->use_logscale_in_k ){
        double lnk_min = log(this->k_min);
        double lnk_max = log(this->k_max);
        double dlnk = (lnk_max - lnk_min) / (this->k_num - 1.0);
        for( int i=0; i<this->k_num; ++i )
            this->array_k[i] = exp(lnk_min + i*dlnk);
    }
    else{
        double dk = (this->k_max - this->k_min) / (this->k_num - 1.0);
        for( int i=0; i<this->k_num; ++i )
            this->array_k[i] = this->k_min + i*dk;
    }

    this->solver_id     = Read::Read_Int_from_File(inifile,"solver_id");
    this->sigma_scale   = Read::Read_Double_from_File(inifile,"sigma_scale");
    this->output_filename = Read::Read_String_from_File(inifile,"output_filename");

    return 0;
}
