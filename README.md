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

The input to the solver is the basis for the null space of the corresponding
2.5 DLT system reshaped as a 36-vector, and the output is the three
coefficients.

## DEPENDENCIES
The implementation uses Eigen, which is a C++ template library for linear
algebra: matrices, vectors, numerical solvers, and related algorithms.

Installation for Ubuntu/Debian:

    $ apt-get install libeigen3-dev

## Using the solver in MATLAB
It is possible to MEX-compile the solver and use it in MATLAB. The
following line

    mex('-I/path/to/eigen_dir', 'c++/solver_homography_planar.cpp')

where `/path/to/eigen_dir` is your local path, e.g. `/usr/local/include/eigen3`.

For MATLAB users an additional function is available that accepts point
correspondences and returns the putative real homographies. It has the
convenient name `solver_homography_planar_complete.m`

Tested on Matlab R2017b, Linux (64-bit).

## Using the solver in Python
The Python wrapper uses eigency, which can be downloaded using pip

    $ pip install eigency

In order to compile and wrap the C++ code go to the `python` subdirectory and
issue

    $ python setup.py build_ext

Similar to the MATLAB function described above there is a function
for computing putative homographies from point correspondences directly,
and it is available as `solver_homography_planar_complete.py`. All tests have
been done using Python 3.5.3.
