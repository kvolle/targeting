#ifndef VEHICLE_H
#define VEHICLE_H
#include<vector>

class vehicle{
public:
int x,y,altitude,id;
int targeted;
std::vector<int> visible_targets;
std::vector<int> local_vehicles;

//vector<int> visible_targets(int, int, vector<target>);

void random_start(int);
void aim(int);
};

#endif
