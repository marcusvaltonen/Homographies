# distutils: language = c++
# distutils: sources = ../c++/solver_homography_planar.cpp

from eigency.core cimport *

cdef extern from "../c++/solver_homography_planar.h":
    cdef VectorXcd _minimal "minimal" (Map[VectorXd] &)

# Function returning vector (copy is made)
def minimal(np.ndarray[np.float64_t] array):
    return ndarray(_minimal(Map[VectorXd](array)))
