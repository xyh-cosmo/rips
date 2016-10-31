#include <rips.hpp>
#include <parser++.hpp>

using namespace imcmc::parser;

int rips::cuba_config(){

    std::cout << "==========================================================\n";
    std::cout << "==>   setting cuba parameters to their defualt values ";

    this->ndim         = 2;
    this->ncomp        = 1;
    this->nvec         = 1;
    this->verbose      = 2;
    this->last         = 4;
    this->speed        = 0;
    this->min_eval     = 0;
    this->max_eval     = 50000;
    this->n_start      = 1000;
    this->n_increase   = 500;
    this->n_batch      = 1000;
    this->grid_num     = 0;
    this->n_new        = 1000;
    this->n_min        = 2;

    this->key          = 0;
    this->key1         = 47;
    this->key2         = 1;
    this->key3         = 1;

    this->max_pass     = 5;
    this->n_given      = 0;
    this->ldx_given    = this->ndim;
    this->n_extra      = 0;

    this->eps_rel      = 1E-6;
    this->eps_abs      = 1E-6;
    this->flatness     = 25.0;
    this->border       = 0.0;
    this->max_chisq    = 10.0;
    this->min_deviation= 0.25;

    this->state_file   = "";
    this->spin         = "";

    std::cout << "\n .... done" << std::endl;
    return 0;
}

int rips::cuba_config( std::string& inifile ){

    std::cout << "===========================================================\n";
    std::cout << "==>   updating cuba parameters";

    if( Read::Has_Key_in_File(inifile,"ndim"))
        this->ndim         = Read::Read_Int_from_File(inifile, "ndim");
    if( Read::Has_Key_in_File(inifile,"ncomp"))
        this->ncomp        = Read::Read_Int_from_File(inifile, "ncomp");
    if( Read::Has_Key_in_File(inifile,"nvec"))
        this->nvec         = Read::Read_Int_from_File(inifile, "nvec");
    if( Read::Has_Key_in_File(inifile,"verbose"))
        this->verbose      = Read::Read_Int_from_File(inifile, "verbose");
    if( Read::Has_Key_in_File(inifile,"last"))
        this->last         = Read::Read_Int_from_File(inifile, "last");
    if( Read::Has_Key_in_File(inifile,"speed"))
        this->speed        = Read::Read_Int_from_File(inifile, "speed");
    if( Read::Has_Key_in_File(inifile,"min_eval"))
        this->min_eval     = Read::Read_Int_from_File(inifile, "min_eval");
    if( Read::Has_Key_in_File(inifile,"max_eval"))
        this->max_eval     = Read::Read_Int_from_File(inifile, "max_eval");
    if( Read::Has_Key_in_File(inifile,"n_start"))
        this->n_start      = Read::Read_Int_from_File(inifile, "n_start");
    if( Read::Has_Key_in_File(inifile,"n_increase"))
        this->n_increase   = Read::Read_Int_from_File(inifile, "n_increase");
    if( Read::Has_Key_in_File(inifile,"n_batch"))
        this->n_batch      = Read::Read_Int_from_File(inifile, "n_batch");
    if( Read::Has_Key_in_File(inifile,"grid_num"))
        this->grid_num     = Read::Read_Int_from_File(inifile, "grid_num");
    if( Read::Has_Key_in_File(inifile,"n_new"))
        this->n_new        = Read::Read_Int_from_File(inifile, "n_new");
    if( Read::Has_Key_in_File(inifile,"n_min"))
        this->n_min        = Read::Read_Int_from_File(inifile, "n_min");

    if( Read::Has_Key_in_File(inifile,"key"))
        this->key          = Read::Read_Int_from_File(inifile, "key");
    if( Read::Has_Key_in_File(inifile,"key1"))
        this->key1         = Read::Read_Int_from_File(inifile, "key1");
    if( Read::Has_Key_in_File(inifile,"key2"))
        this->key2         = Read::Read_Int_from_File(inifile, "key2");
    if( Read::Has_Key_in_File(inifile,"key3"))
        this->key3         = Read::Read_Int_from_File(inifile, "key3");

    if( Read::Has_Key_in_File(inifile,"max_pass"))
        this->max_pass     = Read::Read_Int_from_File(inifile, "max_pass");
    if( Read::Has_Key_in_File(inifile,"n_given"))
        this->n_given      = Read::Read_Int_from_File(inifile, "n_given");
    this->ldx_given    = this->ndim;
    if( Read::Has_Key_in_File(inifile,"n_extra"))
        this->n_extra      = Read::Read_Int_from_File(inifile, "n_extra");

    if( Read::Has_Key_in_File(inifile,"eps_rel")){
        this->eps_rel      = Read::Read_Double_from_File(inifile, "eps_rel");
        // std::cout << " eps_rel updated to " << this->eps_rel << std::endl;
    }

    if( Read::Has_Key_in_File(inifile,"eps_abs"))
        this->eps_abs      = Read::Read_Double_from_File(inifile, "eps_abs");
    if( Read::Has_Key_in_File(inifile,"flatness"))
        this->flatness     = Read::Read_Double_from_File(inifile, "flatness");
    if( Read::Has_Key_in_File(inifile,"border"))
        this->border       = Read::Read_Double_from_File(inifile, "border");
    if( Read::Has_Key_in_File(inifile,"max_chisq"))
        this->max_chisq    = Read::Read_Double_from_File(inifile, "max_chisq");
    if( Read::Has_Key_in_File(inifile,"min_deviation"))
        this->min_deviation= Read::Read_Double_from_File(inifile, "min_deviation");

    if( Read::Has_Key_in_File(inifile,"state_file"))
        this->state_file   = Read::Read_String_from_File(inifile, "state_file");
    if( Read::Has_Key_in_File(inifile,"spin"))
        this->spin         = Read::Read_String_from_File(inifile, "spin");

    std::cout << "\n .... done" << std::endl;

    return 0;
}
