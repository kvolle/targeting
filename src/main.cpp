#include "../include/target.h"
#include "../include/vehicle.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

vector<int> visible_targets(int n, int threshold, int x, int y){
	vector<int> visible;
	stringstream ss;
	map<string,target> targetMap;

	for (int i=0;i<n;i++){
		ss.str("");
		ss<<i;
		string name = 't'+ ss.str();
		int xdiff = targetMap[name].x-x;
		int ydiff = targetMap[name].y-y;
	cout << name << ": " << xdiff << " " << ydiff << endl;
		if (xdiff*xdiff + ydiff*ydiff <threshold*threshold){
			visible.push_back(i);
		}
	}
	return visible;
}


int main() {

	int numTargets = 4;
	int numVehicles = 15;
	int threshold = 200;

	stringstream ss;
	map<string,target> targetMap;
	map<string,vehicle> vehicleMap;
	for (int i=0;i<numTargets;i++){
		ss.str("");
		ss << i;
		string name = 't' + ss.str();
		targetMap[name];
		targetMap[name].random_start(i);
		cout << name <<" " << targetMap[name].x << " " << targetMap[name].y << endl;
	}

	for (int j = 0;j<numVehicles;j++){
		ss.str("");
		ss << j;
		string name = 'v' +ss.str();
		vehicleMap[name];
		vehicleMap[name].random_start(j);
		//cout << name << " " << vehicleMap[name].x << " " << vehicleMap[name].y << endl;
	}
	vector <int> dump;
	string tmp = "v3";

	dump = visible_targets(numTargets,threshold,vehicleMap[tmp].x,vehicleMap[tmp].y);
	ss.str("");
	ss << dump[0];
	string tmp2 = 't' + ss.str();
	cout << "t: " << targetMap[tmp2].x << " " << targetMap[tmp2].y << endl;
	ss.str("");
	ss << dump[1];
	tmp2 = 't' + ss.str();
	cout << "t: " << targetMap[tmp2].x << " " << targetMap[tmp2].y << endl;
	ss.str("");
	ss << dump[2];
	tmp2 = 't' + ss.str();
	cout << "t: " << targetMap[tmp2].x << " " << targetMap[tmp2].y << endl;
	ss.str("");
	ss << dump[3];
	tmp2 = 't' + ss.str();
	cout << "t: " << targetMap[tmp2].x << " " << targetMap[tmp2].y << endl;

	return 0;
}	