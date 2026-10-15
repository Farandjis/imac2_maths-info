#include <iostream>
#include <iomanip>      // std::setprecision
#include <Eigen/Dense>
#include <chrono>
#include <random>


Eigen::MatrixXd generationDeMatrice();
Eigen::MatrixXd strassen(Eigen::MatrixXd m1, Eigen::MatrixXd m2);
Eigen::MatrixXd generationMatriceAleatoire(int n);
Eigen::VectorXd gaussSeidel(Eigen::MatrixXd m, Eigen::VectorXd b, size_t iterMax);

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


  generationMatriceAleatoire(4);

    Eigen::MatrixXd M(3,3);
    Eigen::VectorXd b(3);

    M <<  5, -3,  1,
         -1,  6, -4,
          3, -3,  9;

    b << 10, 5, -7;

    std::cout << "michel" << std::endl;
   Eigen::VectorXd toto = gaussSeidel(M, b, 1);
    std::cout << toto << std::endl;

  return 0;
}


Eigen::VectorXd gaussSeidel(Eigen::MatrixXd m, Eigen::VectorXd b, size_t iterMax)
{

    Eigen::VectorXd X(3);
    X << 0, 0, 0;

    for (size_t iter = 0; iter < iterMax; ++iter)
    {
        X[0] = (b[0] - (m(0,1) * X[1]) - (m(0,2) * X[2] )) / m(0,0);
        X[1] = (b[1] - (m(1,0) * X[0]) - (m(1,2) * X[2] )) / m(1,1);
        X[2] = (b[2] - (m(2,0) * X[0]) - (m(2,1) * X[1])) / m(2,2);
    }

    return X;

    /*
     *Explication du prof :
     *On itère iter fois
     *Dans uen autre boucle for, on parcours une à une chaque ligne et on effectue le calcul
     *(par défaut, y(s), z(s) etc vaut 0 (cf vecteur X)
     *on trouve X(s+1),
     *lors du calcul de y(s+1), on utilise la nouvelle valeur X obtenu mais on a tjrs 0 en z
     *on trouve Y(s+1)
     *pour (z(s+1) on trouve sa valeur, paf, on a toutes nos valeurs pour X1
     *
     *on passe à iter++
     *on recommence mais en partant sur les valeurs qu'on a
     *
     *le résultat de la méthode gauss-seidel correspond à ce qu'on obtient à la fin de l'itération
     *
     */
}






Eigen::MatrixXd  generationMatriceAleatoire(int n)
{
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(n,n);

    for (int i = 0; i < n; i++)
    {
        A(i, i) = A(i, i) + n-1;
        // il s'agit de n-1 car le grand max des valeurs est 1, hors sur n, il y a la valeur de la diagonale,
        // donc si on additionne n-1 "1", on obtient n-1, donc la fameuse valeur
    }

    std::cout << "tacatac" << std::endl;
    std::cout << A << std::endl << std::endl;
    std::cout << "tacatac" << std::endl;

    return A;
}


Eigen::MatrixXd generationDeMatrice()
{
    Eigen::MatrixXd A(8, 8);

    // Générateur aléatoire
    std::random_device rd;
    std::mt19937 gen(rd());

    // Entiers aléatoires entre 0 et 100
    std::uniform_int_distribution<int> dist(0, 100);

    // Remplissage de la matrice
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            A(i, j) = dist(gen);
        }
    }

    std::cout << A << std::endl;

    return A;
}



Eigen::MatrixXd strassen(Eigen::MatrixXd m1, Eigen::MatrixXd m2)
{
    int n = m1.rows();

    if (n <= 2)
    {
        return matrix_product(m1, m2);
    }

    int moitierCoter = m1.rows() / 2;
    Eigen::MatrixXd a = m1.topLeftCorner(moitierCoter, moitierCoter);
    Eigen::MatrixXd b = m1.topRightCorner(moitierCoter, moitierCoter);
    Eigen::MatrixXd c = m1.bottomLeftCorner(moitierCoter, moitierCoter);
    Eigen::MatrixXd d = m1.bottomRightCorner(moitierCoter, moitierCoter);

    Eigen::MatrixXd e = m2.topLeftCorner(moitierCoter, moitierCoter);
    Eigen::MatrixXd f = m2.topRightCorner(moitierCoter, moitierCoter);
    Eigen::MatrixXd g = m2.bottomLeftCorner(moitierCoter, moitierCoter);
    Eigen::MatrixXd h = m2.bottomRightCorner(moitierCoter, moitierCoter);

    // =========== pas bon, il faut remplacer ça par les P (cf diapo 30/61)
    Eigen::MatrixXd r = strassen(a, e) + strassen(b,g);
    Eigen::MatrixXd s = strassen(a,f) + strassen(b,h);
    Eigen::MatrixXd t = strassen(c,e) + strassen(d,g);
    Eigen::MatrixXd u = strassen(c,f) + strassen(d,h);
    // ======================================================================

    Eigen::MatrixXd M(n, n);

    M.topLeftCorner(moitierCoter, moitierCoter) = r;
    M.topRightCorner(moitierCoter, moitierCoter) = s;
    M.bottomLeftCorner(moitierCoter, moitierCoter) = t;
    M.bottomRightCorner(moitierCoter, moitierCoter) = u;

    return M;
}



// linux  : g++ -Wall -O2 -I /usr/include/eigen3 eigen_sample.cpp -o eigen_sample
// mac    : g++ -Wall -O2 -Wno-unknown-warning-option -std=c++11 -I /usr/local/include/eigen3 eigen_sample.cpp -o eigen_sample
// mac M1 : g++ -Wall -O2 -I /opt/homebrew/include/eigen3 eigen_sample.cpp -o eigen_sample

