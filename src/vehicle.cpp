#include "../include/vehicle.h"
#include "../include/target.h"
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <iostream>


void vehicle::random_start(int id_given){
id = id_given;
srand((unsigned)time(NULL)*(id+4));
x = rand() % 101;
srand(x);
y = rand() % 101;
altitude = 0;
}

std::vector<int> vehicle::aim(std::vector<int> targets){
	if (targets.size() >0){
		targeted = targets[0];
		targets.erase(targets.begin());
	}
	else{
		targeted = -2;
	}
	
	return targets;
//targeted = target;

}
