#ifndef VEHICLE_H
#define VEHICLE_H
#include<vector>

class vehicle{
public:
int x,y,altitude,id;
int targeted;

//std::vector <int> visible_targets(int, int);
std::vector <int> local_vehicles(int, int);
void random_start(int);
};

#endif
