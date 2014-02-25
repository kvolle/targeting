#include <iostream>
#include <fstream>

using namespace std;

//int main(int argc, char *argv[]){
int main(){

int numTargets = 2;
int numVehicles = 2;
int sizeArray[2] = {2,3};
ofstream myfile;
myfile.open ("targeting.pomdpx", ios::out );

myfile << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
myfile << "   <pomdpx version=\"1.0\" id=\"relaxedVersion\"\n";
myfile << "      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n";
myfile << "      xsi:noNamespaceSchemaLocation=\"pomdpx.xsd\">\n";
myfile << "         <Description>Relaxed version of distributed asset allocation problem\n";
myfile << "         </Description>\n";
myfile << "         <Discount>0.95</Discount>\n";
myfile << "         <Variable>\n";
myfile << "              <StateVar vnamePrev=\"robot_0\" vnameCurr=\"robot_1\"\n";
myfile << "                fullyObs=\"true\">\n";
myfile << "                  <NumValues> "<< numTargets << "</NumValues>\n";
for (int i=0;i<numTargets;i++){
	myfile << "              <StateVar vnamePrev=\"target"<< i <<"_0\" vnameCurr=\"target"<<i<< "_1\"\n";
	myfile << "                fullyObs=\"true\">\n";
    myfile << "                  <NumValues>"<<numVehicles<<"</NumValues>\n";
	myfile << "              </StateVar>\n";
}
//TODO fix the observations
//myfile << "              <ObsVar vname=\"obs sensor\">\n";
//myfile << "                  <ValueEnum>ogood obad</ValueEnum>\n";
//myfile << "              </ObsVar>\n";
myfile << "              <ActionVar vname=\"action_robot\">\n";
myfile << "                  <ValueEnum>";
for (int j=0;j<numTargets;j++){
	myfile << " switchTo_" <<j;
}
myfile << "</ValueEnum>\n";
myfile << "              </ActionVar>\n";
myfile << "              <RewardVar vname =\"reward robot\" />\n";
myfile << "          </Variable>\n";
myfile << "      <StateTransitionFunction>\n";
myfile << "          <CondProb>\n";
myfile << "              <Var>robot_1</Var>\n";
myfile << "              <Parent>action_robot robot_0</Parent>\n";
myfile << "              <Parameter type=\"TBL\">\n";
for (int act=0;act<numTargets;act++){
	myfile << "                  <Entry>\n";
	myfile << "                      <Instance>switchTo_" << act <<" * s" << act << " </Instance>\n";
	myfile << "                      <ProbTable>1.0</ProbTable>\n";
	myfile << "                  </Entry>\n";
	myfile << "                  <Entry>\n";
	myfile << "                      <Instance>stay s"<< act << " S" << act << " </Instance>\n";
	myfile << "                      <ProbTable>1.0</Probtable>\n";
	myfile << "                  </Entry>\n";
}
myfile << "           </Parameter>\n";
myfile << "       </CondProb>\n";
for (int tar=0;tar<numTargets;tar++){
	myfile << "          <CondProb>\n";
	myfile << "              <Var>target"<<tar<<"_1</Var>\n";
	myfile << "              <Parent>action_robot robot_0 target"<<tar<<"_0</Parent>\n";
	myfile << "              <Parameter type=\"TBL\">\n";
	for (int veh=0;veh<numVehicles;veh++){
		myfile << "                  <Entry>\n";
		myfile << "                      <Instance>switchTo_" << tar <<" * s"<<veh <<" s" << veh+1 << " </Instance>\n";
		myfile << "                      <ProbTable>1.0</ProbTable>\n";
		myfile << "                  </Entry>\n";
		myfile << "                  <Entry>\n";
		myfile << "                      <Instance>stay * s"<< veh << " s" << veh << " </Instance>\n";
		myfile << "                      <ProbTable>1.0</ProbTable>\n";
		myfile << "                  </Entry>\n";
	}

	for (int tar2=0;tar2<numTargets;tar2++){
		for (int veh2=1;veh2<numVehicles;veh2++){
			if (tar2 != tar){
				myfile << "                  <Entry>\n";
				myfile << "                      <Instance>switchTo_" << tar <<" s"<< tar2 <<" s"<<veh2 <<" s" << veh2-1 << " </Instance>\n";
				myfile << "                      <ProbTable>1.0</ProbTable>\n";
				myfile << "                  </Entry>\n";
				myfile << "                  <Entry>\n";
				myfile << "                      <Instance>stay s" << tar2 << " s" << veh2 << " s" << veh2 <<" </Instance>\n";
				myfile << "                      <ProbTable>1.0</ProbTable>\n";
				myfile << "                  </Entry>\n";
			}
		}
	}
	myfile << "              </Parameter>\n";
	myfile << "          </CondProb>\n";
}
myfile << "      </StateTransitionFunction>\n";
//myfile << "      <ObsFunction>\n";
	//TODO Write Observation Function
//myfile << "      </ObsFunction>\n";
myfile << "      <RewardFunction>\n";
myfile << "        <Func>\n";
myfile << "            <Var> reward robot </Var>\n";
myfile << "            <Parent>action_robot robot_0";
for (int t=0;t<numTargets;t++){
	myfile << " target" << t << "_0";
}
myfile << " </Parent>\n";
myfile << "            <Parameter type=\"TBL\">\n";

for (int t=0;t<numTargets;t++){
	for (int r=0;r<numTargets;r++){
		if (r != t){
			for (int c=0;c<numVehicles;c++){
				myfile << "                  <Entry>\n";
				myfile << "                      <Instance>switchTo"<<t<<" s"<<r;
				for (int k=0;k<t-1;k++){
					myfile << " *";
				}
				myfile << " s"<<c;
				for (int kk=t;kk<numTargets;kk++){
					myfile << " *";
				}
				myfile << " </Instance>\n";
				myfile << "                      <ValueTable> "<< sizeArray[c]-c << "</ValueTable>\n";
				myfile << "                  </Entry>\n";
			}
		}
	}
}

myfile << "            </Parameter>\n";
myfile << "        </Func>\n";
myfile << "      </RewardFunction>\n";
myfile << "</pomdpx>";


myfile.close();
return 0;
}
