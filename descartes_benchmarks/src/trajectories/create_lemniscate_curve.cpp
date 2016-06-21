#include "descartes_benchmarks/trajectories/create_lemniscate_curve.h"
#include <ros/console.h>

const double ORIENTATION_INCREMENT = 0.5f;
const double EPSILON = 0.0001f;

namespace descartes_benchmarks
{

bool createLemniscateCurve(double foci_distance, double sphere_radius,
                             int num_points, int num_lemniscates,
                             const Eigen::Vector3d& sphere_center,
                             EigenSTL::vector_Affine3d& poses)
{
  double a = foci_distance;
  double ro = sphere_radius;
  int npoints = num_points;
  int nlemns = num_lemniscates;
  Eigen::Vector3d offset(sphere_center[0],sphere_center[1],sphere_center[2]);
  Eigen::Vector3d unit_z,unit_y,unit_x;

  // checking parameters
  if(a <= 0 || ro <= 0 || npoints < 10 || nlemns < 1)
  {
    ROS_ERROR_STREAM("Invalid parameters for lemniscate curve were found");
    return false;
  }

  // generating polar angle values
  std::vector<double> theta(npoints);

  // interval 1 <-pi/4 , pi/4 >
  double d_theta = 2*M_PI_2/(npoints - 1);
  for(unsigned int i = 0; i < npoints/2;i++)
  {
    theta[i] = -M_PI_4  + i * d_theta;
  }
  theta[0] = theta[0] + EPSILON;
  theta[npoints/2 - 1] = theta[npoints/2 - 1] - EPSILON;

  // interval 2 < 3*pi/4 , 5 * pi/4 >
  for(unsigned int i = 0; i < npoints/2;i++)
  {
    theta[npoints/2 + i] = 3*M_PI_4  + i * d_theta;
  }
  theta[npoints/2] = theta[npoints/2] + EPSILON;
  theta[npoints - 1] = theta[npoints - 1] - EPSILON;

  // generating omega angle (lemniscate angle offset)
  std::vector<double> omega(nlemns);
  double d_omega = M_PI/(nlemns);
  for(unsigned int i = 0; i < nlemns;i++)
  {
     omega[i] = i*d_omega;
  }

  Eigen::Affine3d pose;
  double x,y,z,r,phi;

  poses.clear();
  poses.reserve(nlemns*npoints);
  for(unsigned int j = 0; j < nlemns;j++)
  {
    for(unsigned int i = 0 ; i < npoints;i++)
    {
      r = std::sqrt( std::pow(a,2) * std::cos(2*theta[i]) );
      phi = r < ro ? std::asin(r/ro):  (M_PI - std::asin((2*ro - r)/ro) );

      x = ro * std::cos(theta[i] + omega[j]) * std::sin(phi);
      y = ro * std::sin(theta[i] + omega[j]) * std::sin(phi);
      z = ro * std::cos(phi);

      // determining orientation
      unit_z <<-x, -y , -z;
      unit_z.normalize();

      unit_x = (Eigen::Vector3d(0,1,0).cross( unit_z)).normalized();
      unit_y = (unit_z .cross(unit_x)).normalized();

      Eigen::Matrix3d rot;
      rot << unit_x(0),unit_y(0),unit_z(0)
         ,unit_x(1),unit_y(1),unit_z(1)
         ,unit_x(2),unit_y(2),unit_z(2);

      pose = Eigen::Translation3d(offset(0) + x,
                                  offset(1) + y,
                                  offset(2) + z) * rot;

      poses.push_back(pose);
    }
  }

  return true;
}

} // end descartes_benchmarks