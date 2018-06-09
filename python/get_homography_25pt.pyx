# distutils: language = c++
# distutils: sources = ../c++/get_homography_25pt.cpp  ../c++/solver_homography_planar.cpp

from eigency.core cimport *

cdef extern from "../c++/get_homography_25pt.h":
    cdef VectorXd _get_homography_25pt_wrapper "get_homography_25pt_wrapper" (Map[Matrix3d] &, Map[Matrix3d] &)

def get_homography_25pt_wrapper(np.ndarray[np.float64_t, ndim=2] x1, np.ndarray[np.float64_t, ndim=2] x2):
    return ndarray(_get_homography_25pt_wrapper(Map[Matrix3d](x1), Map[Matrix3d](x2)))
