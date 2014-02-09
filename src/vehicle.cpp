#include "../include/vehicle.h"
#include "../include/target.h"
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <iostream>

/*
std::vector<int> vehicle::visible_targets(int n, int threshold){
	std::vector<int> visible;
	std::stringstream ss;
	std::map<std::string,target> targetMap;
	std::cout << std::endl << x << " " << y << std::endl << std::endl;
	for (int i=0;i<n;i++){
		ss.str("");
		ss<<i;
		std::string name = 't'+ ss.str();
		int xdiff = targetMap[name].x-x;
		int ydiff = targetMap[name].y-y;
	std::cout << name << ": " << xdiff << " " << ydiff << std::endl;
		if (xdiff*xdiff + ydiff*ydiff <threshold*threshold){
			visible.push_back(i);
		}
	}
	return visible;
}
*/
std::vector<int> vehicle::local_vehicles(int n, int threshold){
	std::vector<int> local;
	std::map<std::string,vehicle> vehicleMap;
	for (int i = 0;i<n;i++){
		std::stringstream ss;
	ss.str("");
		ss << i;
		std::string name = 'v'+ ss.str();
		int xdiff = vehicleMap[name].x-x;
		int ydiff = vehicleMap[name].y-y;
		if (xdiff*xdiff + ydiff*ydiff < threshold*threshold){
			local.push_back(i);
		}
	}
	return local;
}
void vehicle::random_start(int id_given){
//std::cout << time(NULL)<< "    " << (unsigned)time(NULL) << std::endl << std::endl;
id = id_given;
srand((unsigned)time(NULL)*(id+4));
x = rand() % 101;
srand(x);
y = rand() % 101;
altitude = 0;

	
}