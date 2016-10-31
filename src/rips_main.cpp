#include <rips.hpp>

int main( int argc, char *argv[] ) {

    rips r;
    r.init(argc, argv);
    r.solve();

    return 0;
}
