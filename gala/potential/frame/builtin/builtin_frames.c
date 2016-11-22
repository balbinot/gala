#include <math.h>
#include <string.h>

/*
    Static, inertial frame
*/
double static_frame_hamiltonian(double t, double *pars, double *qp, int n_dim) {
    int i;
    double E = 0.;

    for (i=0; i<n_dim; i++) {
        E += qp[i+n_dim]*qp[i+n_dim]; // p^2
    }
    return 0.5*E; // kinetic term
}

void static_frame_gradient(double t, double *pars, double *qp, int n_dim, double *dH) {
    int i;

    for (i=0; i < n_dim; i++) {
        dH[i] = qp[n_dim+i]; // qdot = p
    }
}

void static_frame_hessian(double t, double *pars, double *qp, int n_dim, double *d2H) {
    /* TODO: this is just potential Hessian and identity matrix for d2H/dp2*/
}

/*
    Constantly rotating frame
*/
double constant_rotating_frame_hamiltonian(double t, double *pars, double *qp, int n_dim) {
    /*
        Omega = pars
    */
    int i;
    double E = 0.;
    double Lx, Ly, Lz;

    for (i=0; i<n_dim; i++) {
        E += qp[i+n_dim]*qp[i+n_dim]; // p^2
    }

    Lx = qp[1]*qp[2+n_dim] - qp[2]*qp[1+n_dim];
    Ly = -qp[0]*qp[2+n_dim] + qp[2]*qp[0+n_dim];
    Lz = qp[0]*qp[1+n_dim] - qp[1]*qp[0+n_dim];

    // kinetic term and effective potential for rotation:
    //  - Omega dot L
    return 0.5*E - (pars[0]*Lx + pars[1]*Ly + pars[2]*Lz);
}

void constant_rotating_frame_gradient(double t, double *pars, double *qp, int n_dim, double *dH) {
    double Cx, Cy, Cz; // used in cross-products below

    // printf("%f %f %f\n", pars[0], pars[1], pars[2]);

    // Omega x q
    Cx = pars[1]*qp[2] - pars[2]*qp[1];
    Cy = -pars[0]*qp[2] + pars[2]*qp[0];
    Cz = pars[0]*qp[1] - pars[1]*qp[0];
    dH[0] = dH[0] + qp[0+n_dim] - Cx;
    dH[1] = dH[1] + qp[1+n_dim] - Cy;
    dH[2] = dH[2] + qp[2+n_dim] - Cz;

    // Omega x p
    Cx = pars[1]*qp[2+n_dim] - pars[2]*qp[1+n_dim];
    Cy = -pars[0]*qp[2+n_dim] + pars[2]*qp[0+n_dim];
    Cz = pars[0]*qp[1+n_dim] - pars[1]*qp[0+n_dim];
    dH[3] = dH[3] + Cx;
    dH[4] = dH[4] + Cy;
    dH[5] = dH[5] + Cz;
}

void constant_rotating_frame_hessian(double t, double *pars, double *qp, int n_dim, double *d2H) {
    /* TODO: */
}