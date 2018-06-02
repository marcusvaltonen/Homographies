from setuptools import setup
from setuptools.extension import Extension
from Cython.Build import cythonize

import eigency

extensions = [
    Extension("solver_homography_planar.solver_homography_planar", ["solver_homography_planar.pyx"],
        include_dirs = [".", "../c++"] + eigency.get_includes()
    ),
]

dist = setup(
    name = "solver_homography_planar",
    version = "0.1",
    ext_modules = cythonize(extensions),
    packages = ["solver_homography_planar"]
)
