/*
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

int main()
{
	FILE *fp1 = fopen("Spring_Scheduled.csv", "r");
	FILE *fp2 = fopen("FinalFallSpringRoutes.csv", "r");
	FILE *fpWrite = fopen("joinSpringRouteScheduled.csv", "w");

	
	map<string, int> routeMap;
	string line;
	char cline[100];
	int count = 0;


	while (fscanf(fp2, " %[^\n]", cline) != EOF)
	{
		line = string(cline);
		istringstream iss(line);
		int routeID;
		string s;

		getline(iss, s, ',');
		istringstream iss2(s);
		iss2 >> routeID;

		getline(iss, s, ',');

		routeMap[s] = routeID;
	}

	count = 0;

	int fromStop, toStop, transitTime;
	string scheduledID, timeOut, timeIn;		

	fprintf(fpWrite, "RouteID,FromStop,ToStop,TimeOut,TimeIn,TransitTime\n");

	while (fscanf(fp1, " %[^\n]", cline) != EOF)
	{
		line = string(cline);
		++count;
		if (count == 1)
			continue;
		if (count % 1000 == 0)
		{
			cout << count << endl;
			//cout << id << fromStop << toStop << timeTaken << busID << routeID << timeStamp << endl;
			//break;
		}

		istringstream iss(line);
		string s;

		getline(iss, scheduledID, ',');				

		getline(iss, s, ',');
		istringstream iss2(s);
		iss2 >> fromStop;		

		getline(iss, s, ',');
		istringstream iss3(s);
		iss3 >> toStop;	

		getline(iss, timeOut, ',');

		getline(iss, timeIn, ',');

		getline(iss, s);
		istringstream iss4(s);
		iss4 >> transitTime;


		if (routeMap.find(scheduledID) != routeMap.end())
			fprintf(fpWrite, "%d,%d,%d,%s,%s,%d\n", routeMap[scheduledID], fromStop,
				toStop, timeOut.c_str(), timeIn.c_str(), transitTime);
			
		

	}
	
	return 0;
}*/