#include "../zh/zbicgstab.h"
#include <mpi.h>
#include <iostream>
#include <ctime>
int main()
{
    MPI_Init(NULL, NULL);
    clock_t start = clock();
    int lat_x(100);
    int lat_t(100);
    int lat_spin(2); // const lat_s=2
    int MAX_ITER(1e6);
    double TOL(1e-6);
    zvector b(lat_x, lat_t, lat_spin);
    zvector U(lat_x, lat_t, lat_spin);
    b.assign_zero();
    b(0, 0, 0) = 1.0;
    U.assign_unit();
    double mass(1);
    bool dag(true);
    zdslash Zdslash(U, lat_x, lat_t, lat_spin, mass, dag);
    zbicgstab Zbicgstab(MAX_ITER, TOL, b, Zdslash);
    Zbicgstab.solve();
    clock_t end = clock();
    std::cout
        << "################"
        << "time cost:"
        << (double)(end - start) / CLOCKS_PER_SEC
        << "s"
        << std::endl;
    MPI_Finalize();
    return 0;
}
