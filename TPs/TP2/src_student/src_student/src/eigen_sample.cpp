#include <iostream>
#include <iomanip>      // std::setprecision
#include <Eigen/Dense>
#include <chrono>
#include <random>

void exo2_q6();
void exo3_q2();
void exo3_q5();

double dot_product(const Eigen::VectorXd &v1, const Eigen::VectorXd &v2)
{
    assert(v1.size() == v2.size());

    double result = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        result += v1(i) * v2(i);
    }

    return result;

}

Eigen::MatrixXd matrix_product(const Eigen::MatrixXd &m1, const Eigen::MatrixXd &m2)
{
    Eigen::MatrixXd A;
    Eigen::MatrixXd B;
    if (m1.cols() > m2.cols())
    {
        // si m1 a plus de colonnes que m2, dans ce cas, m2 a sûrement ce nombre de ligne
        assert(m1.cols() == m2.rows()); // on test si c'est le cas, sinon, KO
        // std::cout << "poire" << std::endl;


        A = m2;
        B = m1;

    }
    else
    {
        // sinon, c'est le contraire
        assert(m2.cols() == m1.rows());
        // std::cout << "pomme" << std::endl;

        A = m1;
        B = m2;
    }

    Eigen::MatrixXd res = Eigen::MatrixXd(B.cols(), A.rows());



    // on parcourt les colonnes de M2
    for (int i = 0; i < B.cols(); i++)
    {

        // on parcourt les lignes de M1
        for (int j = 0; j < A.rows(); j++)
        {

            double resCase = 0;

            // on va calculer le nombre pour l'emplacement res
            for (int k = 0; k < A.cols(); k++)
            {
                resCase += A(j, k) * B(k, i);
                // std::cout << m1(j, k) << " --- " << m2(k, i) << std::endl;
            }

            res(j, i) = resCase;
        }
    }

    // std::cout << res << std::endl;

    return res;
}


Eigen::MatrixXd matrix_product_scalaire(const Eigen::MatrixXd &m1, const Eigen::MatrixXd &m2)
{
    Eigen::MatrixXd A;
    Eigen::MatrixXd B;
    if (m1.cols() > m2.cols())
    {
        // si m1 a plus de colonnes que m2, dans ce cas, m2 a sûrement ce nombre de ligne
        assert(m1.cols() == m2.rows()); // on test si c'est le cas, sinon, KO
        // std::cout << "poire" << std::endl;


        A = m2;
        B = m1;

    }
    else
    {
        // sinon, c'est le contraire
        assert(m2.cols() == m1.rows());
        // std::cout << "pomme" << std::endl;

        A = m1;
        B = m2;
    }

    Eigen::MatrixXd res = Eigen::MatrixXd(B.cols(), A.rows());



    // on parcourt les colonnes de M2
    for (int i = 0; i < B.cols(); i++)
    {

        // on parcourt les lignes de M1
        for (int j = 0; j < A.rows(); j++)
        {
            res(j, i) = A.row(j).dot(B.col(i));
        }
    }

    // std::cout << res << std::endl;

    return res;
}

int main()
{
  // build a seed
  unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
  srand(seed);

  // vectors dynamic size
  Eigen::VectorXd v1(5);
  v1 << 1, 2, 3, 4, 5;
  v1(2) = 42;
  std::cout << "v1 size : " << v1.size() << std::endl;
  std::cout << "v1[2]   : " << v1(2) << std::endl;
  std::cout << "v1 : " << v1.transpose() << std::endl << std::endl;

  Eigen::VectorXd v2 = Eigen::VectorXd::Random(5);
  std::cout << "v2 : " << v2.transpose() << std::endl << std::endl;

  // vector static size
  Eigen::Vector4f v3 = Eigen::Vector4f::Zero();
  std::cout << "v3 : " << v3.transpose() << std::endl << std::endl;

  v3 = Eigen::Vector4f::Ones();
  std::cout << "v3 : " << v3.transpose() << std::endl << std::endl;

  Eigen::Vector4f v4 = Eigen::Vector4f::Random();
  std::cout << "v4 : " << v4.transpose() << std::endl << std::endl;
  v4 = v4 + v3;
  std::cout << "v4 : " << v4.transpose() << std::endl << std::endl;

  // matrices dynamic size
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(3,4);
  std::cout << "A size : " << A.rows() << " x " << A.cols() << std::endl;
  std::cout << "A(1,2) : " << A(1,2) << std::endl;
  std::cout << "A :\n" << A << std::endl << std::endl;

  // matrices static size
  Eigen::Matrix4d B = Eigen::Matrix4d::Random();  
  std::cout << "B :\n" << B << std::endl << std::endl;

  // time computation
  const unsigned int iter = 100000;
  Eigen::MatrixXd C(3,4);
  auto start = std::chrono::steady_clock::now();
  for(unsigned int i=0; i<iter; ++i)
      C = A*B;
  auto stop = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = stop-start;
  std::cout << "temps calcul du produit matriciel: " << elapsed_seconds.count() << " s" << std::endl;
  
  // print samples
  std::cout << "A + 2*A :\n" << A + 2*A << std::endl << std::endl;
  std::cout << "A * B :\n" << A * B << std::endl << std::endl;


    Eigen::VectorXd vA(5);
    vA << 1, 2, 3, 4, 5;

    Eigen::VectorXd vB(5);
    vB << 1, 2, 3, 4, 5;

    double res = dot_product(vA, vB);
    std::cout << "res : " << res << std::endl;
    std::cout << "dot d'Eigen : " << vA.dot(vB) << std::endl;


    unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
    srand (seed2);
    Eigen::VectorXd x1 = Eigen::VectorXd::Random(10000);
    Eigen::VectorXd x2 = Eigen::VectorXd::Random(10000);

    std::cout << "dot d'Eigen : " << x1.dot(x2) << std::endl;

    // exo2_q6();
    // exo3_q2();
    exo3_q5();

  return 0;
}

void exo3_q5()
{
    // fondé sur du code généré par ChatGPT
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    auto start = std :: chrono :: steady_clock :: now (); // on lance le chrono ?


    for (int i = 0; i < 1000000; ++i)
    {
        // Matrice 3x2
        Eigen::MatrixXd A(3, 2);

        // Matrice 2x3
        Eigen::MatrixXd B(2, 3);

        // Génération aléatoire
        A = A.unaryExpr([&](double) {
            return dist(gen);
        });

        B = B.unaryExpr([&](double) {
            return dist(gen);
        });

        // Produit : (3x2) * (2x3) = (3x3)
        Eigen::MatrixXd C = matrix_product(A, B);

    }

    auto end = std::chrono::steady_clock::now(); // fin du chrono
    std :: chrono::duration<double> elapsed_seconds = end - start ;
    std :: cout << " elapsed time : " << elapsed_seconds . count () << " s " << std :: endl ;

    start = std :: chrono :: steady_clock :: now (); // on lance le chrono ?


    for (int i = 0; i < 1000000; ++i)
    {
        // Matrice 3x2
        Eigen::MatrixXd A(3, 2);

        // Matrice 2x3
        Eigen::MatrixXd B(2, 3);

        // Génération aléatoire
        A = A.unaryExpr([&](double) {
            return dist(gen);
        });

        B = B.unaryExpr([&](double) {
            return dist(gen);
        });

        // Produit : (3x2) * (2x3) = (3x3)
        Eigen::MatrixXd C = matrix_product_scalaire(A, B);

    }

    end = std::chrono::steady_clock::now(); // fin du chrono
    elapsed_seconds = end - start ;
    std :: cout << " elapsed time : " << elapsed_seconds . count () << " s " << std :: endl ;


}

void exo2_q6()
{
    const unsigned int iter = 10000;
    auto start = std :: chrono :: steady_clock :: now (); // on lance le chrono ?
    for ( unsigned int i =0; i < iter ; ++ i )
    {
        // on calcul iter fois ma fonction
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        srand (seed);
        Eigen::VectorXd x1 = Eigen::VectorXd::Random(10000);
        Eigen::VectorXd x2 = Eigen::VectorXd::Random(10000);
        double res = dot_product(x1, x2);
    }
    auto end = std::chrono::steady_clock::now(); // fin du chrono
    std :: chrono::duration<double> elapsed_seconds = end - start ;
    std :: cout << " elapsed time : " << elapsed_seconds . count () << " s " << std :: endl ;



    start = std::chrono::steady_clock::now(); // on lance le chrono ?
    for ( unsigned int i =0; i < iter ; ++ i )
    {
        // on calcul iter fois ma fonction
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        srand (seed);
        Eigen::VectorXd x1 = Eigen::VectorXd::Random(10000);
        Eigen::VectorXd x2 = Eigen::VectorXd::Random(10000);
        double res = x1.dot(x2);
    }
    end = std::chrono::steady_clock::now(); // fin du chrono
    elapsed_seconds = end - start ;
    std::cout << " elapsed time : " << elapsed_seconds.count () << " s " << std :: endl ;
}


void exo3_q2()
{
    Eigen::MatrixXd B(2, 3);
    B << 1, 2, 3,
         3, 4, 5;

    Eigen::MatrixXd A(3, 2);
    A << 1, 2,
         3, 4,
         5, 6;


    matrix_product(A, B);
    matrix_product_scalaire(A, B);

}



// linux  : g++ -Wall -O2 -I /usr/include/eigen3 eigen_sample.cpp -o eigen_sample
// mac    : g++ -Wall -O2 -Wno-unknown-warning-option -std=c++11 -I /usr/local/include/eigen3 eigen_sample.cpp -o eigen_sample
// mac M1 : g++ -Wall -O2 -I /opt/homebrew/include/eigen3 eigen_sample.cpp -o eigen_sample

