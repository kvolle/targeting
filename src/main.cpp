#include "../include/target.h"
#include "../include/vehicle.h"
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>

const int numTargets = 4;
const int numVehicles = 25;
const int threshold = 72; 
using namespace std;

vector<int> visible_targets(int x, int y, int targeted, vector<target> targets){
	vector<int> visible;
	vector<int> distance;
	int dist;
	int holder;
	int ctr;
	for (int i=0;i<numTargets;i++){

		int xdiff = targets[i].x-x;
		int ydiff = targets[i].y-y;
		dist = xdiff*xdiff + ydiff*ydiff;
		if ((dist <threshold*threshold)&&(i!=targeted)){
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
void displayVector(vector<int> vec){

	for (int xx=0;xx<vec.size();xx++){
		cout << vec[xx] << " ";
	}
	cout << endl;
}

int main() {

	vector <target> targets;
	vector <vehicle> vehicles;
	int totals[numTargets];
	// Totals defines the total number of vehicles assigned to each target
	// TODO make it so each vehicle only seee what local vehicles are attacking
	for (int c=0;c<numTargets;c++){
		totals[c] = 0;
	}

	// Generate targets
	for (int i=0;i<numTargets;i++){
		target temp;
		temp.random_start(i);
		targets.push_back(temp);
	}
	// Generate vehicles
	for (int j = 0;j<numVehicles;j++){
		vehicle temp;
		temp.random_start(j);
		vehicles.push_back(temp);
	}
	for (int v=0;v<numVehicles;v++){
		//visible_targets is a vector of the id's of targets visible to that vehicle
		vehicles[v].visible_targets = visible_targets(vehicles[v].x, vehicles[v].y, vehicles[v].targeted, targets);
		//local_vehicles is a vector of the id's of vehicles local to a given vehicle
		vehicles[v].local_vehicles = local_vehicles(vehicles[v].x, vehicles[v].y, vehicles, v);
		
		// Display the visible target vector for each vehicle
		cout << v << endl;
		cout << "Targeted:" << vehicles[v].targeted << " Visible: ";
		displayVector(vehicles[v].visible_targets);

		vehicles[v].visible_targets = vehicles[v].aim(vehicles[v].visible_targets);

		cout << "Targeted: " << vehicles[v].targeted << " Visible: ";
		displayVector(vehicles[v].visible_targets);

		//visible_targets is a vector of the id's of targets visible to that vehicle
		vehicles[v].visible_targets = visible_targets(vehicles[v].x, vehicles[v].y, vehicles[v].targeted, targets);
		cout << "Targeted: " << vehicles[v].targeted << " Visible: ";
		displayVector(vehicles[v].visible_targets);
// Re-aim
		vehicles[v].visible_targets = vehicles[v].aim(vehicles[v].visible_targets);
		vehicles[v].visible_targets = visible_targets(vehicles[v].x, vehicles[v].y, vehicles[v].targeted, targets);
		cout << "Targeted: " << vehicles[v].targeted << " Visible: ";
		displayVector(vehicles[v].visible_targets);
		cout << endl;
		totals[vehicles[v].targeted] +=1;
	}





/*
	for (int cc=0;cc<numTargets;cc++){
		cout << totals[cc]-targets[cc].size << "  ";
	}
	cout << endl;
*/


/*
	for (int c2=0;c2<numTargets;c2++){
		cout << totals[c2]-targets[c2].size << "  ";
	}
	cout << endl;
*/
	return 0;
}	
