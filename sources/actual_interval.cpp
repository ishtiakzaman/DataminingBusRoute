#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main3()
{
	FILE *fp = fopen("intervaldata2014-2015.tsv", "r");
	FILE *fpWrite = fopen("actual_data.csv", "w");

	string line;
	char cline[100];
	int count = 0;
	int id, fromStop, toStop, timeTaken, busID, routeID;
	string hourToken, timeStamp;	
	vector< vector<int> > lastDwell(400, vector<int>(160, 0));
	vector< vector<string> > lastTime(400, vector<string>(160, ""));

	fprintf(fpWrite, "RouteID,From,To,TimeOut,TimeIn,DwellTime\n");				

	while (fscanf(fp, " %[^\n]", cline) != EOF)
	{
		line = string(cline);
		++count;
		if (count % 1000 == 0)
		{
			cout << count << endl;
			//cout << id << fromStop << toStop << timeTaken << busID << routeID << timeStamp << endl;
			//break;
		}


		istringstream iss(line);		
		iss >> id >> fromStop >> toStop >> timeTaken >> busID >> routeID >> timeStamp >> hourToken;
		timeStamp += " ";
		timeStamp += hourToken;

		if (fromStop != toStop)
		{
			fprintf(fpWrite, "%d,%d,%d,%s,%s,%d\n",
				routeID, fromStop, toStop, lastTime[routeID][fromStop].c_str(), timeStamp.c_str(),
					lastDwell[routeID][fromStop]);			
		}
		else
		{			
			lastDwell[routeID][toStop] = timeTaken;			
		}		
		lastTime[routeID][toStop] = timeStamp;		
	}
	
	return 0;
}