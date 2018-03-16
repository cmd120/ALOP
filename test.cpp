#include <iostream>
#include "Eigen/Dense"
// using Eigen::MatrixXd;
int main()
{
	int array[8];
	for(int i = 0; i < 8; ++i) array[i] = i;
	// Matrix<float,2,4> data;
	std::cout << "Column-major:\n" << Eigen::Map<Eigen::Matrix<int,2,4>>(array) << std::endl;
	// double i;
 //  MatrixXd m(2,2);
 //  MatrixXd n(2,1);
 //  m(0,0) = 3;
 //  m(1,0) = 2.5;
 //  m(0,1) = -1;
 //  m(1,1) = m(1,0) + m(0,1);
 //  m = m.array() + 1 ;
  // n = m.rowwise().mean();
  // i = n.array().sum();
  // std::cout << m << std::endl;
  // std::cout << i << std::endl;
}