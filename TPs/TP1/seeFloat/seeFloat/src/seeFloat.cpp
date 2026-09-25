#include <iostream>
#include <bitset>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iomanip>
using namespace std;

int main(int argc, char **argv)
{

    // DEBUT MODIF CODE ORIGINAL

    if ( (0.1 + (0.2 + 0.3) == (0.1 + 0.2) + 0.3) ) std :: cout << " true " << std :: endl ;
    else std :: cout << " false " << std :: endl ;

    cout << (0.2 + 0.3) << " " << (0.1 + 0.2) << " " << ((0.2 + 0.3) == (0.1 + 0.2)) << " " << (0.1 + (0.2 + 0.3) == (0.1 + 0.2) + 0.3) << endl;

    float aa = -5.0/0;
    std::cout << " aa " << aa << std::endl;


    float aaa = powf(2.0,40);
    std::cout << " aaa = " << aaa << std::endl;
    int b = aaa;
    std::cout << " b = " << b << std::endl;

    /*
    cout << fixed << setprecision(15);
    for(float a=0.0; a<10; a+=0.00000001)
        cout << " a = " << a << std::endl;
    std::cout << " à table ! "
    << std::endl;
    */

    double u = 1/3;
    cout << " u = " << u << std::endl;
    for (int i = 0; i < 550; i++)
    {
        u = (4 * u) - 1.0;
        cout << " u" << i << " = " << u << endl;
    }

    // FIN MODIF CODE ORIGINAL

  // read float
  float a = 0.1;
  if(argc == 2) a = atof(argv[1]);
  std::cout << "float : " << a << std::endl; 

  int x = *(int *)&a;
  std::bitset<sizeof(int) * 8> binary(x);

  std::string stringBinary;
  stringBinary = binary.to_string();
  
  // description
  std::cout << "s exponent mantiss" << std::endl;
  
  // sign
  std::cout << stringBinary[0] << " "; 

  // exponent
  for(unsigned int i=1;i<9; i++)
     std::cout << stringBinary[i]; 
  std::cout << " ";

  // mantiss
  for(unsigned int i=9;i<32; i++)
     std::cout << stringBinary[i]; 
  std::cout << std::endl;

 return 0;
}
