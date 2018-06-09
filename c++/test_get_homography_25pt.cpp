#include <iostream>
#include <Eigen/Dense>
#include "get_homography_25pt.h"

using namespace Eigen;
using namespace std;

int main()
{
    // Define input
    Matrix3d x1, x2;
    x1 << -1.1, 1.5, 2.6,
           3.1, 4.5, 5.2,
           4.1, 7.6, 1.2;
    x2 <<  4.3, 3.5, 6.4,
           3.7, 8.1, 4.4,
           5.6, 5.3, 2.3;

    cout << "x1 =\n" << x1 << endl;
    cout << "x2 =\n" << x2 << endl;

    MatrixXd H;
    H = get_homography_25pt(x1, x2);

    int nbr_homs = H.cols() / 3;
    Matrix3d Htmp;

    for (int i = 0; i < nbr_homs; i++) {
        cout << "Homography " << i + 1 << endl;
        Htmp =  H.block<3,3>(0,3 * i);
        Htmp = Htmp / Htmp(2,2);
        cout << Htmp << endl;
    }

    return 0;
}
