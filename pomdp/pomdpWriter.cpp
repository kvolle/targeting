#include <iostream>
#include <fstream>

using namespace std;

//int main(int argc, char *argv[]){
int main(){

int numTargets = 4;
int numVehicles = 5;
int sizeArray[10] = {1,2,3,2};
ofstream myfile;
myfile.open ("../appl-0.95/targeting.pomdpx", ios::out );

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
myfile << "              </StateVar>\n";
for (int t=0;t<numTargets;t++){
	myfile << "              <StateVar vnamePrev=\"target"<< t <<"_0\" vnameCurr=\"target"<<t<< "_1\"\n";
	myfile << "                fullyObs=\"true\">\n";
    myfile << "                  <NumValues>"<<numVehicles+1<<"</NumValues>\n";
	myfile << "              </StateVar>\n";
}

myfile << "              <ActionVar vname=\"action_robot\">\n";
myfile << "                  <ValueEnum> stay";
for (int j=0;j<numTargets;j++){
	myfile << " switchTo_" <<j;
}
myfile << "</ValueEnum>\n";
myfile << "              </ActionVar>\n";
//myfile << "              <ObsVar vname =\"obs sensor\"/>\n";
myfile << "              <RewardVar vname =\"reward robot\" />\n";
myfile << "      </Variable>\n";
myfile << "      <InitialStateBelief>\n";
myfile << "           <CondProb>\n";
myfile << "               <Var>robot_0</Var>\n";
myfile << "               <Parent>null</Parent>\n";
myfile << "               <Parameter type = \"TBL\">\n";
myfile << "                   <Entry>\n";
myfile << "                       <Instance>-</Instance>\n";
myfile << "                       <ProbTable>uniform</ProbTable>\n";
myfile << "                   </Entry>\n";
myfile << "               </Parameter>\n";
myfile << "           </CondProb>\n";
for (int isb=0;isb<numTargets;isb++){
	myfile << "           <CondProb>\n";
	myfile << "               <Var>target"<<isb<<"_0 </Var>\n";
	myfile << "               <Parent>null</Parent>\n";
	myfile << "               <Parameter type = \"TBL\">\n";
	myfile << "                   <Entry>\n";
	myfile << "                       <Instance>-</Instance>\n";
	myfile << "                       <ProbTable>uniform</ProbTable>\n";
	myfile << "                   </Entry>\n";
	myfile << "               </Parameter>\n";
	myfile << "           </CondProb>\n";
}
myfile << "      </InitialStateBelief>\n";
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
	myfile << "                      <Instance>stay s"<< act << " s" << act << " </Instance>\n";
	myfile << "                      <ProbTable>1.0</ProbTable>\n";
	myfile << "                  </Entry>\n";
}

myfile << "           </Parameter>\n";
myfile << "       </CondProb>\n";

for (int i=0;i<numTargets;i++){//target of interest
	myfile << "          <CondProb>\n";
	myfile << "              <Var>target"<<i<<"_1</Var>\n";
	myfile << "              <Parent>action_robot robot_0 target"<<i<<"_0</Parent>\n";
	myfile << "              <Parameter type=\"TBL\">\n";
	for (int j=0;j<numTargets;j++){//robot_0 value
		for (int k=0;k<numVehicles+1;k++){//value of target_i_0
			myfile << "                  <Entry>\n";
			myfile << "                      <Instance>stay s"<<j<<" s"<<k<<" s"<< k <<"</Instance>\n";
			myfile << "                      <ProbTable>1.0</ProbTable>\n";
			myfile << "                  </Entry>\n";
			for (int l=0;l<numTargets;l++){//actions
				if (l==j){
					myfile << "                  <Entry>\n";
					myfile << "                      <Instance>switchTo_"<< l <<" s" << j << " s" << k << " s" << k << "</Instance>\n";
					myfile << "                      <ProbTable>0.0</ProbTable>\n";
					myfile << "                  </Entry>\n";
				}

				else if (l==i){
					if (k<numVehicles){
						myfile << "                  <Entry>\n";
						myfile << "                      <Instance>switchTo_"<< l << " s" << j << " s" << k << " s" << k+1 << "</Instance>\n";
						myfile << "                      <ProbTable>1.0</ProbTable>\n";
						myfile << "                  </Entry>\n";
					}
					else {
						myfile << "                  <Entry>\n";
						myfile << "                      <Instance>switchTo_"<< l << " s" << j << " s" << k << " s" << k << "</Instance>\n";
						myfile << "                      <ProbTable>0</ProbTable>\n";
						myfile << "                  </Entry>\n";
					}
				}
				else if (i==j){
					if (k>0){
						myfile << "                  <Entry>\n";
						myfile << "                      <Instance>switchTo_"<< l << " s" << j << " s" << k << " s" << k-1 << "</Instance>\n";
						myfile << "                      <ProbTable>1.0</ProbTable>\n";
						myfile << "                  </Entry>\n";
					}
					else {
						myfile << "                  <Entry>\n";
						myfile << "                      <Instance>switchTo_"<< l << " s" << j << " s" << k << " s" << k << "</Instance>\n";
						myfile << "                      <ProbTable>0</ProbTable>\n";
						myfile << "                  </Entry>\n";
					}
				}
				else{
					myfile << "                  <Entry>\n";
					myfile << "                      <Instance>switchTo_"<< l << " s" << j << " s" << k << " s" << k << "</Instance>\n";
					myfile << "                      <ProbTable>1.0</ProbTable>\n";
					myfile << "                  </Entry>\n";
				}
			}
		}
	}
	myfile << "              </Parameter>\n";
	myfile << "          </CondProb>\n";
}
myfile << "      </StateTransitionFunction>\n";

myfile << "      <RewardFunction>\n";
myfile << "        <Func>\n";
myfile << "            <Var> reward robot </Var>\n";
myfile << "            <Parent>action_robot robot_0";
for (int t=0;t<numTargets;t++){
	myfile << " target" << t << "_0";
}
myfile << " </Parent>\n";
myfile << "            <Parameter type=\"TBL\">\n";
myfile << "                  <Entry>\n";
myfile << "                      <Instance> stay * ";
for (int tt=0;tt<numTargets;tt++){myfile << "* ";}
myfile << "</Instance>\n                      <ValueTable>0</ValueTable>\n";
myfile << "                  </Entry>\n";
for (int A=0;A<numTargets;A++){
	for (int V=0;V<numVehicles;V++){
		myfile << "                  <Entry>\n";
		myfile << "                      <Instance>switchTo_"<<A<<" * ";
		for (int a=0;a<A;a++){
			myfile << "* ";
		}
		myfile << "s" << V;
		for (int aa=A+1;aa<numTargets;aa++){
			myfile << " *";
		}
		myfile <<"</Instance>\n";
		myfile <<"                      <ValueTable>"<<sizeArray[A]-V-1<<"</ValueTable>\n";
		myfile <<"                    </Entry>\n";
	}
}

myfile << "            </Parameter>\n";
myfile << "        </Func>\n";
myfile << "      </RewardFunction>\n";
myfile << "</pomdpx>";


myfile.close();
return 0;
}
