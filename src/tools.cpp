#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;
using std::cerr;
using std::endl;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  VectorXd rmse(4);
  rmse << 0,0,0,0;
  //basic input checking
  if (estimations.empty())
  {
    cerr << "empty input" << endl;
    return rmse;
  }
  if (estimations.size() != ground_truth.size())
  {
    cerr << "Input Size mismatch between estimation and ground truth" << endl;
    return rmse;
  }
  for (unsigned int i = 0; i < estimations.size(); ++i)
  {
    VectorXd residual = estimations[i] - ground_truth[i];
    residual = residual.array()*residual.array();
    rmse += residual;
  }
  //calculate root mean square of the residual
  rmse = rmse/estimations.size();
  rmse = rmse.array().sqrt();
  return rmse;
}

double Tools::adjustRange(double theta) {
  if (theta < -M_PI)
  {
    while (theta < -M_PI)
    {
      theta += 2*M_PI;
    }
  } else if (theta >= M_PI) {
    while (theta > M_PI)
    {
      theta -= 2*M_PI;
    }
  }
  return theta;
}

