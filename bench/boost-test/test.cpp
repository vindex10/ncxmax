#include <cstdlib>
#include <string.h>
#include <sys/time.h>
#include <iostream>
#include <boost/math/distributions/non_central_chi_squared.hpp>
#include <boost/math/distributions/detail/generic_mode.hpp>

using std::cout, std::endl;
using boost::math::non_central_chi_squared_distribution;
using boost::math::detail::generic_find_mode;

int main(int argc, char** argv) {
    // helper for generic_find_mode
    static const char* function = "mode(non_central_chi_squared_distribution<%1%> const&)";

    // timer setup
    struct timeval time;
    long start_musec, stop_musec;

    // ncx init
    double dof = strtod(argv[2], NULL);
    double nc = strtod(argv[3], NULL);
    bool run_new = strcmp(argv[1], "new") == 0;
    cout << (run_new ? "new" : "old") << "\t" << dof << "\t" <<  nc;
    non_central_chi_squared_distribution<long double> ncx2(dof, nc);

    double res, guess;
    if (run_new) {
        gettimeofday(&time, NULL);
        start_musec = ((unsigned long long)time.tv_sec * 1000000) + time.tv_usec;
        double scale = dof/nc < 0.25;
        res = generic_find_mode(ncx2, scale ? nc + dof - 3.0 : dof + 1.0, function);
        gettimeofday(&time, NULL);
        stop_musec = ((unsigned long long)time.tv_sec * 1000000) + time.tv_usec;
    } else {
        gettimeofday(&time, NULL);
        start_musec = ((unsigned long long)time.tv_sec * 1000000) + time.tv_usec;
        res = generic_find_mode(ncx2, dof + 1.0, function);
        gettimeofday(&time, NULL);
        stop_musec = ((unsigned long long)time.tv_sec * 1000000) + time.tv_usec;
    }
    cout << "\t" << stop_musec-start_musec << "\t" << res << endl;
}
