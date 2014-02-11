#include "../include/target.h"
#include "../include/vehicle.h"
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>

const int numTargets = 4;
const int numVehicles = 7;
const int threshold = 72; 
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
	int totals[numTargets];
	for (int c=0;c<numTargets;c++){
		totals[c] = 0;
	}

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
		//if (vehicles[v].visible_targets.size()>0 && vehicles[v].visible_targets.size()<numVehicles+1)
			cout << v << ":  ";
			for (int fuck=0;fuck<vehicles[v].visible_targets.size();fuck++){
				cout << vehicles[v].visible_targets[fuck] << " ";
			}
			cout << endl;
			vehicles[v].visible_targets = vehicles[v].aim(vehicles[v].visible_targets);
			cout << v << ":  ";
			for (int fuck2=0;fuck2<vehicles[v].visible_targets.size();fuck2++){
				cout << vehicles[v].visible_targets[fuck2] << " ";
			}
			cout << endl;
			totals[vehicles[v].targeted] +=1;
	}
	for (int cc=0;cc<numTargets;cc++){
		cout << totals[cc]-targets[cc].size << "  ";
	}
cout << endl;
	srand((unsigned)time(NULL));
for(int 



redo=0;redo<1;redo++){
	for (int r=0;r<numVehicles;r++){
		if (totals[vehicles[r].targeted]-targets[vehicles[r].targeted].size > 0){
cout << (int)50*(totals[vehicles[r].targeted]-targets[vehicles[r].targeted].size )/targets[vehicles[r].targeted].size << endl;
				vehicles[r].visible_targets = vehicles[r].aim(vehicles[r].visible_targets);
			
		}
		cout << r << ":  ";
		for (int fuck2=0;fuck2<vehicles[r].visible_targets.size();fuck2++){
			cout << vehicles[r].visible_targets[fuck2] << " ";
		}
		cout << endl;
	}
}

	for (int c2=0;c2<numTargets;c2++){
		cout << totals[c2]-targets[c2].size << "  ";
	}

	return 0;
}	
