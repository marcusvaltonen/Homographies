#ifndef SOLVER_HOMOGRAPHY_PLANARH

#include <Eigen/Dense>

#ifdef MATLAB_MEX_FILE /* This macro is defined automatically when using MATLAB */
#include "mex.h"
#endif

using namespace Eigen;

VectorXcd minimal(const VectorXd &vec);

MatrixXcd solver_homography_planar(const VectorXd& data);

#ifdef MATLAB_MEX_FILE
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);
#endif

#endif /* SOLVER_HOMOGRAPHY_PLANARH */
