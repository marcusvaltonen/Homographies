# Homographies

C++ implementation of 2.5 point solver based on the work by Wadenback et al.,
"Recovering Planar Motion from Homographies Obtained using a 2.5-point Solver
for a polynomial system", in the Proceedings of the Internation Conference on
Image Processing (ICIP), 2016.

## ADDITIONAL INFORMATION
The solver is not identical to the one proposed in the article, and uses
another elimination template. It is, however, comparable in terms of
noise sensitivity and mean re-projection error, as demonstrate in Fig. 2
and Fig. 3 of the report.

The solver was generated using the automatic generator proposed by
Larsson et al. "Efficient Solvers for Minimal Problems by Syzygy-based
Reduction" (CVPR 2017)

## DEPENDENCIES
The implementation uses Eigen 3 (older versions are not compatible), which is
a C++ template library for linear algebra: matrices, vectors,
numerical solvers, and related algorithms.

Installation for Ubuntu/Debian:

    $ apt-get install libeigen3-dev

Tested on version 3.3.3.

## Using the solver in MATLAB
It is possible to MEX-compile the solver and use it in MATLAB. The
following line in the `c++` subdirectory

    mex('-I/path/to/eigen_dir', '-I.', 'get_homography_25pt.cpp', 'solver_homography_planar.cpp')

where `/path/to/eigen_dir` is your local path, e.g. `/usr/local/include/eigen3`.

The expected input is two 3x3 matrices (double) containing the point correspondences.
The output is a 3x3N matrix where N is the number of putative real homographies, i.e.
the homography matrices Hi are stored as [ H1 H2 ... HN ]. The homographies can e.g. be
stored in a cell object using the following approach

    H = get_homography_25pt(x1, x2);
    H_cell = mat2cell(H, 3, 3*ones(1,size(H2,2)/3));

Tested on Matlab R2017b, Linux (64-bit).

## Using the solver in Python
The Python wrapper uses eigency, which can be downloaded using pip

    $ pip install eigency

In order to compile and wrap the C++ code go to the `python` subdirectory and
issue

    $ python setup.py build_ext

Expected input is the same as in the MATLAB function described above.
Be careful with the order, as Fortran order is used. To avoid this, and use
contiguous (C order), an example wrapper is found in the `python` subdirectory,
`test_get_homography_25pt.py`. All tests have been done using Python 3.5.3.
