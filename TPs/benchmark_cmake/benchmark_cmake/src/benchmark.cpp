#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
#include <chrono>
#include <cassert>
#include <iomanip>      // std::setprecision


// for multi threading with openmp
// mac     : brew install libomp
//           brew install llvm
//           xcode-select --install
//           g++-14 -fopenmp -L/usr/local/opt/llvm/lib -I/usr/local/opt/llvm/include -I /usr/local/include/eigen3 benchmark.cpp
//           if problems:
//             export PATH="/usr/local/opt/llvm/bin:$PATH"
//             export LDFLAGS="-L/usr/local/opt/llvm/lib"
//             export CPPFLAGS="-I/usr/local/opt/llvm/include"
// linux   : g++ -Wall -O2 -std=c++11 -fopenmp -I /usr/include/eigen3 benchmark.cpp 
// windows : 
//           - Ouvrir le MinGW Installation Manager
//           - Chercher le package "mingw-pthreads-w32"
//           - Cocher la version dev
//           - Cliquer "Mark for Installation"
//           - Cliquer sur Installation dans le coin supérieur gauche
//           - Cliquer sur "Apply Changes"
//           - Valider l'installation
//
//           Dans le terminal (VSCode) :
//           - Compiler avec la commande du prof en ajoutant -fopenmp :
//           g++ -Wall -O2 -fopenmp -I C:\path\to\eigen benchmark.cpp -o 




Eigen::MatrixXd matrix_product(const Eigen::MatrixXd &m1, const Eigen::MatrixXd &m2){

  assert(m1.cols() == m2.rows() && "matrix_product: error: matrices incompatible size");

  Eigen::MatrixXd m3 = Eigen::MatrixXd::Zero(m1.rows(), m2.cols());
  for(unsigned int i=0; i<m3.rows(); ++i)
    for(unsigned int j=0; j<m3.cols(); ++j)
      for(unsigned int k=0; k<m1.cols(); ++k)
        m3(i,j) += m1(i,k) * m2(k,j);
  
  return m3;  
}



// with const reference on submatrices for readability
Eigen::MatrixXd strassen(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B)
{
  // if A or B too small
  if(A.rows() < 128) return matrix_product(A,B);
  
  const unsigned int rows = A.rows()/2;
  const unsigned int cols = A.cols()/2;

  const Eigen::MatrixXd &a = A.topLeftCorner(rows,cols);
  const Eigen::MatrixXd &b = A.topRightCorner(rows,cols);
  const Eigen::MatrixXd &c = A.bottomLeftCorner(rows,cols);
  const Eigen::MatrixXd &d = A.bottomRightCorner(rows,cols);
  const Eigen::MatrixXd &e = B.topLeftCorner(rows,cols);
  const Eigen::MatrixXd &f = B.topRightCorner(rows,cols);
  const Eigen::MatrixXd &g = B.bottomLeftCorner(rows,cols);
  const Eigen::MatrixXd &h = B.bottomRightCorner(rows,cols);

  Eigen::MatrixXd P1(strassen(a , f-h)); // a(f-h)
  Eigen::MatrixXd P2(strassen(a+b , h)); // (a+b)h
  Eigen::MatrixXd P3(strassen(c+d,e));   // (c+d)e
  Eigen::MatrixXd P4(strassen(d, g-e));  // d(g-e)
  Eigen::MatrixXd P5(strassen(a+d,e+h)); // (a+d)(e+h)
  Eigen::MatrixXd P6(strassen(b-d,g+h)); // (b-d)(g+h)
  Eigen::MatrixXd P7(strassen(a-c,e+f)); // (a-c)(e+f)
 
  Eigen::MatrixXd C(A.rows(),A.cols());
  C.topLeftCorner(rows,cols)     = P5 + P4 - P2 + P6;
  C.topRightCorner(rows,cols)    = P1 + P2;
  C.bottomLeftCorner(rows,cols)  = P3 + P4;
  C.bottomRightCorner(rows,cols) = P1 + P5 - P3 - P7;
  
  return C;
}




int main()
{
  unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
  srand(seed);

  const unsigned int matrixSize = 256;
  const unsigned int nbRuns = 10;

  // 3 random matrices
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(matrixSize,matrixSize); 
  Eigen::MatrixXd B = Eigen::MatrixXd::Random(matrixSize,matrixSize); 
  Eigen::MatrixXd C = Eigen::MatrixXd::Random(matrixSize,matrixSize); 


  // numerical accuracy test
  std::cout << "\naccuracy ...\n";
  std::cout << "for loop residual = " << std::setprecision(10) << (matrix_product(A,B)-(A*B)).norm() / (A.rows()*A.cols()) << std::endl;
  std::cout << "strassen residual = " << std::setprecision(10) << (strassen(A,B)-(A*B)).norm() / (A.rows()*A.cols()) << std::endl;


  // start time benchmark
  std::cout << "\nbenchmark (on " << nbRuns << " runs) ..." << std::endl;

  // eigen multitreads
#if 0 // put 0 if openMP is not supported, 1 otherwize
  {
    const int nbProc = 8; // choose accordingly to the number of cores on your machine 
    Eigen::setNbThreads(nbProc);
    auto start = std::chrono::steady_clock::now();
    for(unsigned int i=0; i<nbRuns; ++i){
      C = A*B;
    }
    auto stop = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = stop -start;
    std::cout << "eigen Multi : " << elapsed.count() << " s" << std::endl;
    Eigen::setNbThreads(1);
    }
#endif

  // eigen  
  {
    auto start = std::chrono::steady_clock::now();
    for(unsigned int i=0; i<nbRuns; ++i){
     C = A*B;
    }
    auto stop = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = stop-start;
    std::cout << "eigen       : " << elapsed_seconds.count() << " s" << std::endl;
  }
  
  // strassen
  {
    auto start = std::chrono::steady_clock::now();
    for(unsigned int i=0; i<nbRuns; ++i){
      Eigen::MatrixXd C = strassen(A,B); 
    }
    auto stop = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = stop-start;
    std::cout << "strassen    : " << elapsed_seconds.count() << " s" << std::endl;
  }

  // our 3 loops  
  {
    auto start = std::chrono::steady_clock::now();
    for(unsigned int i=0; i<nbRuns; ++i){
      Eigen::MatrixXd C = matrix_product(A,B);
    }
    auto stop = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = stop-start;
    std::cout << "3 loops     : " << elapsed_seconds.count() << " s" << std::endl;    
  }


  return 0;
}



// result 2048x2048 (4 runs)
// thread   :   1.3 s
// eigen    :   4 s
// strassen :  41 s
// standard : 270 s

// result 1024x1024 (10 runs)
// thread   :  0.9 s
// eigen    :  3 s
// strassen : 30 s
// standard : 98 s

// result 512x512 (50 runs)
// thread   :  0.3 s
// eigen    :  1 s
// strassen : 10 s
// standard : 19 s
