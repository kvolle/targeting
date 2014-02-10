#include "../include/target.h"
#include "../include/vehicle.h"
#include <iostream>
#include <string>
#include <cmath>


const int numTargets = 8;
const int numVehicles = 15;
const int threshold = 50; 
using namespace std;

vector<int> visible_targets(int x, int y, vector<target> targets){
	vector<int> visible;
	vector<int> distance;
	int dist;
	int holder;
	int ctr;
	for (int i=0;i<numTargets;i++){

		int xdiff = targets[i].x-x;
		int ydiff = targets[i].y-y;
		dist = xdiff*xdiff + ydiff*ydiff;
		if (dist <threshold*threshold){
			visible.push_back(i);
			distance.push_back(sqrt(dist));
		}
	}
	ctr = distance.size();
	if (ctr != 0){
		for (int k=0;k<distance.size()-1;k++){
			for (int j = 0;j<ctr-1;j++){
				if (distance[j] > distance[j+1]){
					holder = distance[j];
					distance[j] = distance[j+1];
					distance[j+1] = holder;
					holder = visible[j];
					visible[j] = visible[j+1];
					visible[j+1] = holder;
				}
			}
			ctr = ctr-1;
		}
	}
	return visible;
}
vector<int> local_vehicles(int x, int y, vector<vehicle> vehicles, int same){
	vector<int> local;
	
	for (int i=0;i<numVehicles;i++){
		if (i != same){
			int xdiff = vehicles[i].x-x;
			int ydiff = vehicles[i].y-y;

			if (xdiff*xdiff + ydiff*ydiff <threshold*threshold){
				local.push_back(i);
			}
		}
	}
	return local;
}

int main() {

	vector <target> targets;
	vector <vehicle> vehicles;

	for (int i=0;i<numTargets;i++){
		target temp;
		temp.random_start(i);
		targets.push_back(temp);
	}

//cout << targets[0].x << " " << targets[1].x << " " << targets[2].x << " " << targets[3].x << " " << targets[4].x << " " << targets.size() << endl;
	for (int j = 0;j<numVehicles;j++){
		vehicle temp;
		temp.random_start(j);
		vehicles.push_back(temp);
	}
	for (int v=0;v<numVehicles;v++){
		vehicles[v].visible_targets = visible_targets(vehicles[v].x, vehicles[v].y, targets);
		vehicles[v].local_vehicles = local_vehicles(vehicles[v].x, vehicles[v].y, vehicles, v);
		if (vehicles[v].visible_targets.size()>0 && vehicles[v].visible_targets.size()<numVehicles+1){
			vehicles[v].aim(vehicles[v].visible_targets[0]);
		}
		else{
			vehicles[v].aim(-1);
		}
		cout << vehicles[v].targeted << " ";
	}

	return 0;
}	
