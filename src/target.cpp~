#include "../include/target.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void target::random_start(int id_given){
id = id_given;
srand((unsigned)time(NULL)*(id+23));
//std::cout << (unsigned)time(NULL) << std::endl;

x = rand() % 101;
srand((unsigned)x);
y = rand() % 101;
srand((unsigned)y);
size = 3*(rand() % 4);
}
