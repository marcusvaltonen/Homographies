#!/usr/bin/env python3

import numpy as np
from solver_homography_planar import minimal


def solver_homography_planar_complete(x1, x2):
    """Estimate a planar motion compatible homography."""

    nbr_pts = 3
    if x1.shape[0] != nbr_pts or x1.shape[0] != nbr_pts:
        raise RuntimeError('Only three point correspondences accepted.')

    # Construct 2.5 pt DLT system
    dlt = np.zeros((6, 9))
    for k in range(nbr_pts):
        tmp = np.kron(x1[:, k].T, _crossm(x2[:, k]))
        dlt[2*k:2*(k+1),:] = tmp[:2, :]

    # Throw away one equation
    dlt = dlt[:5, :]
    basis = _null(dlt)

    # Sanity check
    if basis.size != 9 * 4:
        return None

    # Find coefficients
    sols = minimal(np.reshape(basis.T, 9 * 4))

    # Discard complex-valued solutions and reshape
    sols = np.reshape(sols, (-1, 3))
    thresh = 1e-5  # Allow small complex-part, TODO: Investigate this further
    idx = np.sum(np.abs(sols.imag) < thresh, 1) == 3
    real_sols = sols[idx,:].real
    nbr_real_sols = real_sols.shape[0]

    # Generate putative solutions
    H = np.zeros((nbr_real_sols, 3, 3))
    for k, s in enumerate(real_sols):
        coeffs = np.append(s, 1)
        H[k] = np.reshape(np.sum(np.tile(coeffs,(9,1)) * basis, 1), (3, 3)).T

    return H

def _crossm(k):
    """Cross-product matrix."""
    if k.size != 3:
       raise RuntimeError('Incorrect size of input vector.')

    return np.array([[0, -k[2], k[1]], [k[2], 0, -k[0]], [-k[1], k[0], 0]]);

def _null(A, atol=1e-12, rtol=1e-14):
    """Returns the null space."""
    u, s, vh = np.linalg.svd(A)
    tol = max(atol, rtol * s[0])
    nnz = (s >= tol).sum()
    ns = vh[nnz:].conj().T
    return ns

if __name__ == '__main__':
    x1 = np.array([[-1.1, 1.5, 2.6], [3.1, 4.5, 5.2], [4.1, 7.6, 1.2]])
    x2 = np.array([[ 4.3, 3.5, 6.4], [3.7, 8.1, 4.4], [5.6, 5.3, 2.3]])

    H = solver_homography_planar_complete(x1, x2)
    H = np.array([h / h[-1, -1] for h in H])

    expected_H = np.array([[[ 0.56537343, -0.77681774,  0.74401647],
                            [ 1.38610449, -1.62139184,  1.60209801],
                            [ 0.92558254, -0.98556885,  1.        ]],
                           [[ 1.89148551,  5.37093047, -3.55347571],
                            [-1.0182971 , -2.89148551,  1.91304348],
                            [-0.53229167, -1.51145833,  1.        ]],
                           [[ 1.89148551,  5.37093047, -3.55347571],
                            [-1.0182971 , -2.89148551,  1.91304348],
                            [-0.53229167, -1.51145833,  1.        ]],
                           [[ 1.272896  ,  4.24066441, -2.74219731],
                            [-1.12146172, -2.82244584,  1.93870051],
                            [-0.76512591, -1.38282078,  1.        ]]])

    # TODO: Should probably check norm instead.
    assert(np.all([h in expected_H for h in H]))
