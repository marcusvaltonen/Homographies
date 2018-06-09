#ifndef GET_HOMOGRAPHY_25PTH

#include <Eigen/Dense>
#include "solver_homography_planar.h"

#ifdef MATLAB_MEX_FILE /* This macro is defined automatically when using MATLAB */
#include "mex.h"
#endif

Eigen::MatrixXd get_homography_25pt(const Eigen::Matrix3d &x1, const Eigen::Matrix3d &x2);
Eigen::VectorXd get_homography_25pt_wrapper(const Eigen::Matrix3d &x1, const Eigen::Matrix3d &x2);

#ifdef MATLAB_MEX_FILE
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);
#endif

#endif /* GET_HOMOGRAPHY_25PTH */
