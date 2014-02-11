#ifndef VEHICLE_H
#define VEHICLE_H
#include<vector>
#include"target.h"

class vehicle{
public:
int x,y,altitude,id;
int targeted;
std::vector<int> visible_targets;
std::vector<int> local_vehicles;

void random_start(int);
std::vector<int> aim(std::vector<int>);
};

#endif
