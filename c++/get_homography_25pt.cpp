#include "get_homography_25pt.h"
#include <iostream>

using namespace Eigen;
using namespace std;


MatrixXd get_homography_25pt(const Matrix3d &x1, const Matrix3d &x2)
{
    // Setup DLT equations
    MatrixXd dlt(5, 9);
    VectorXd tmp(9);
    int k;

    // 1st point correspondence
    k = 0;
    tmp << 0, -x1(0,k) * x2(2,k), x1(0,k) * x2(1,k), 0, -x1(1,k) * x2(2,k), x1(1,k) * x2(1,k), 0, -x1(2,k) * x2(2,k), x1(2,k) * x2(1,k);
    dlt.row(2*k) = tmp;
    tmp << x1(0,k) * x2(2,k), 0, -x1(0,k) * x2(0,k), x1(1,k) * x2(2,k), 0, -x1(1,k) * x2(0,k), x1(2,k) * x2(2,k), 0, -x1(2,k) * x2(0,k);
    dlt.row(2*k+1) = tmp;

    // 2nd point correspondence
    k = 1;
    tmp << 0, -x1(0,k) * x2(2,k), x1(0,k) * x2(1,k), 0, -x1(1,k) * x2(2,k), x1(1,k) * x2(1,k), 0, -x1(2,k) * x2(2,k), x1(2,k) * x2(1,k);
    dlt.row(2*k) = tmp;
    tmp << x1(0,k) * x2(2,k), 0, -x1(0,k) * x2(0,k), x1(1,k) * x2(2,k), 0, -x1(1,k) * x2(0,k), x1(2,k) * x2(2,k), 0, -x1(2,k) * x2(0,k);
    dlt.row(2*k+1) = tmp;

    // 3rd point correspondence (only first eq)
    k = 2;
    tmp << 0, -x1(0,k) * x2(2,k), x1(0,k) * x2(1,k), 0, -x1(1,k) * x2(2,k), x1(1,k) * x2(1,k), 0, -x1(2,k) * x2(2,k), x1(2,k) * x2(1,k);
    dlt.row(2*k) = tmp;

    // Compute basis for null space
    JacobiSVD<MatrixXd> svd(dlt, ComputeFullV);
    MatrixXd basis(9,4);
    basis = svd.matrixV().block<9,4>(0,5);

    // Vectorize basis
    const Map<VectorXd> basis_vec(basis.data(), 36);

    // Extract solution
    MatrixXcd sols = solver_homography_planar(basis_vec);

    // Pre-processing: Remove complex-valued solutions
    double thresh = 1e-5;
    ArrayXd real_sols(24);
    real_sols = sols.imag().cwiseAbs().colwise().sum();
    int nbr_real_sols = (real_sols <= thresh).count();

    /*
     * Create putative (real) homographies,
     * The homographies are stored [ H1 H2 .. Hn ]
     */
    MatrixXd H(3, 3 * nbr_real_sols);
    ArrayXd tmpH(9);
    Array3d coeffs;
    Matrix3d tmpH2;
    k = 0;
    for (int i = 0; i < real_sols.size(); i++) {
        if (real_sols(i) <= thresh) {
            coeffs = sols.col(i).real();
            tmpH = ArrayXd::Zero(9);
            for (int n = 0; n < 3; n ++) {
                tmpH = tmpH + basis.col(n).array() * coeffs(n);
            }
            tmpH = tmpH + basis.col(3).array();
            tmpH2 = Map<Matrix3d>(tmpH.data());
            H.block<3,3>(0,3*k) = tmpH2;
            k++;
        }
    }
    return H;
}

// ----------------
// MATLAB interface
// ----------------
#ifdef MATLAB_MEX_FILE
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
if (nrhs != 2) {
    mexErrMsgIdAndTxt("get_homography_25pt:nrhs", "Two input arguments required.");
}
if (nlhs != 1) {
    mexErrMsgIdAndTxt("get_homography_25pt:nlhs", "One output argument required.");
}
if (!mxIsDouble(prhs[0]) || mxIsComplex(prhs[0])) {
    mexErrMsgIdAndTxt("get_homography_25pt:notDouble", "Input data must be type double.");
}
if(mxGetNumberOfElements(prhs[0]) != 9 && mxGetNumberOfElements(prhs[1]) != 9) {
    mexErrMsgIdAndTxt("get_homography_25pt:incorrectSize", "Inputs should be of size 3x3.");
}

// Convert to desired type (don't know if this intermediate step can be avoided somehow)
VectorXd x1 = Map<VectorXd>(mxGetPr(prhs[0]), 9);
VectorXd x2 = Map<VectorXd>(mxGetPr(prhs[1]), 9);
Matrix3d x1m = Map<Matrix3d>(x1.data());
Matrix3d x2m = Map<Matrix3d>(x2.data());

// Compute putative real homographies
MatrixXd H;
H = get_homography_25pt(x1m, x2m);

// Construct Matlab compatible output
plhs[0] = mxCreateDoubleMatrix(H.rows(), H.cols(), mxREAL);
double* val = mxGetPr(plhs[0]);
for (Index i = 0; i < H.size(); i++) {
    val[i] = H(i);
}
}
#endif

// ----------------
// Python interface
// ----------------
// Wrap Python (Eigency/Cython does not handle arbitrary matrices)
VectorXd get_homography_25pt_wrapper(const Matrix3d &x1, const Matrix3d &x2) {
    MatrixXd H;
    H = get_homography_25pt(x1, x2);
    VectorXd out(Map<VectorXd>(H.data(), H.cols() * H.rows()));
    return out;
}
