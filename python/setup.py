from setuptools import setup
from setuptools.extension import Extension
from Cython.Build import cythonize

import eigency

sourcefiles = ['get_homography_25pt.pyx', '../c++/solver_homography_planar.cpp']
extensions = [
    Extension("get_homograpy_25pt.get_homography_25pt", sourcefiles,
        include_dirs = [".", "../c++"] + eigency.get_includes()
    ),
]

dist = setup(
    name = "get_homography_25pt",
    version = "0.1",
    ext_modules = cythonize(extensions),
    packages = ["get_homography_25pt"]
)
