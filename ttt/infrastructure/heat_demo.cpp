#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <omp.h>

// Load the multidimensional array template
#include "arrayff.hxx"

#define Nthread 4
// Load the template functions to draw the hot and cold spots
#include "draw.hxx"

int main(int argc, char* argv[])
{
  const float tol = 0.00001; //误差
  const int npix = 100; //允许的最大未知数个数
  const int npixx = npix;
  const int npixy = npix;
//  const int ntotal = npixx * npixy;
  std::string path = "plate0.fit";
  Array<float, 2> h(npixy, npixy), g(npixy, npixx); //h：表示上一次迭代的结果，g：表示这一次迭代的结果

  const int nrequired = (npixx-2) * (npixy-2); //允许最大的系数的个数
  const int ITMAX = 1000000; //最大迭代次数 ITER
    
  int iter = 0; //迭代的次数
  int nconverged = 0; //未知数的个数

  fix_boundaries2(h);
  dump_array<float, 2>(h, path);
    
  double starttime = omp_get_wtime();
  float dhg;
    
omp_set_num_threads(Nthread);
#pragma omp parallel
{
      do
      {
         #pragma omp for
         for (int y = 1; y < npixy-1; y++)
         {
             for (int x = 1; x < npixx-1; x++)
             {
                // finite difference method Jacobi Method
                 g(y, x) = 0.25 * (h(y, x-1) + h(y, x+1) + h(y-1, x) + h(y+1,x));
             }
         }
          
         #pragma omp barrier
         #pragma omp single
         {
             fix_boundaries2(g);
             nconverged = 0;
         }

          
         #pragma omp for reduction(+:nconverged) private(dhg)
         for (int y = 0; y < npixy; y++)
         {
             for (int x = 0; x < npixx; x++)
             {
                 dhg = std::fabs(g(y, x) - h(y, x));
                 if (dhg < tol)
                 {
                     ++nconverged;
                 }
                 h(y, x) = g(y, x);
             }
         }

         #pragma omp single
         {
             ++iter;
         }

    } while (nconverged < nrequired && iter < ITMAX);
}
  double endtime = omp_get_wtime();
  std::cout<<"time: "<<endtime-starttime<<std::endl;
    
    
  path = "plate1.fit";
  dump_array<float, 2>(h, path);
  std::cout << "Required " <<"nconverged "<<nconverged<<" , "<< iter << " iterations" << std::endl;
}
