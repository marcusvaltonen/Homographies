#!/usr/bin/env python3

import numpy as np
from get_homography_25pt import get_homography_25pt_wrapper


def get_homography_25pt(x1, x2):
    """Wrapper to reshape the output and take care of Fortan order."""
    x1 = np.asfortranarray(x1)
    x2 = np.asfortranarray(x2)
    H = get_homography_25pt_wrapper(x1, x2)
    H = np.reshape(H, (-1, 3, 3))
    return np.array([np.ascontiguousarray(h).T / h[-1, -1] for h in H])

if __name__ == '__main__':
    x1 = np.array([[-1.1, 1.5, 2.6], [3.1, 4.5, 5.2], [4.1, 7.6, 1.2]])
    x2 = np.array([[ 4.3, 3.5, 6.4], [3.7, 8.1, 4.4], [5.6, 5.3, 2.3]])

    H = get_homography_25pt(x1, x2)
    print(H)

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
