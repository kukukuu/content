#ifndef _ZBICGSTAB_H
#define _ZBICGSTAB_H
#include "./zvector.h"
#include "./zdslash.h"
class zbicgstab
{
public:
    zbicgstab(int MAX_ITER, double &TOL, zvector &b, zdslash &Zdslash) : MAX_ITER(MAX_ITER), TOL(TOL), Zdslash(Zdslash), dimensions(b.dimensions)
    {
        this->b = &b;
    }

    ~zbicgstab()
    {
    }

    // solve the linear system Ax = b
    void solve()
    {
        std::complex<double> rho_prev(1.0, 0.0);
        std::complex<double> rho(0.0, 0.0);
        std::complex<double> alpha(1.0, 0.0);
        std::complex<double> omega(1.0, 0.0);
        std::complex<double> beta(0.0, 0.0);
        zvector x(dimensions);
        zvector r = *b;
        zvector r_tilde(dimensions);
        zvector p(dimensions);
        zvector v(dimensions);
        zvector s(dimensions);
        zvector t(dimensions);
        // x.rand(); // initial guess
        // Zdslash.dslash(x, r_tilde);
        // // zvector r = b - A * x;
        // r = r - r_tilde;
        x.assign_zero(); // if x=0;r_tilde=r0=b;
        r_tilde = r;
        p.assign_zero();
        v.assign_zero();
        s.assign_zero();
        t.assign_zero();
        for (int i = 0; i < MAX_ITER; i++)
        {
            rho = r_tilde.dot(r);
            beta = (rho / rho_prev) * (alpha / omega);
            p = r + (p - v * omega) * beta;
            // v = A * p;
            Zdslash.dslash(p, v);
            alpha = rho / r_tilde.dot(v);
            s = r - v * alpha;
            // t = A * s;
            Zdslash.dslash(s, t);
            omega = t.dot(s) / t.dot(t);
            x = x + p * alpha + s * omega;
            r = s - t * omega;
            if (r.norm2() < TOL)
            {
                std::cout << "#End-loop: "
                          << i
                          << std::endl;
                break;
            }
            rho_prev = rho;
        }
        std::cout << "#End-Residual: "
                  << r.norm2()
                  << std::endl;
        x.display();
    }

private:
    int MAX_ITER;
    double TOL;
    zvector *b;
    zdslash Zdslash;
    std::vector<int> dimensions;
};
#endif