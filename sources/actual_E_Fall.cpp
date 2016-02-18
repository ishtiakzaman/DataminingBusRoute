/*
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

using namespace std;

#define myAbs(a)	((a)<0?-(a):(a))

bool isMajorStopID(int stopID)
{
	return (stopID == 47 || stopID == 51 || stopID == 45 || stopID == 6 || stopID == 12 || stopID == 1);
}

int convertToSecond(string time)
{
	 //time in hh:mm:ss format (24 hour)
	istringstream iss(time);
	int hh, mm, ss;
	string s;

	getline(iss, s, ':');
	istringstream iss2(s);
	iss2 >> hh;

	getline(iss, s, ':');
	istringstream iss3(s);
	iss3 >> mm;

	getline(iss, s);
	istringstream iss4(s);
	iss4 >> ss;

	return hh*3600+mm*60+ss;
}

int delay(string actualTime, string scheduledTime)
{
	// return delay (actualTime - scheduledTime) in seconds
	// actualTime YYYY-MM-DD HH:MM:SS
	// scheduledTime HH:MM:SS
	istringstream iss(actualTime);
	string datePart, timePart;
	iss >> datePart >> timePart;

	int t1, t2;
	t1 = convertToSecond(timePart);
	t2 = convertToSecond(scheduledTime);
	return t1 - t2;
}

int timeMatched(string time1, string time2)
{	
	// time1 and time2 are in HH:MM:SS format
	int t1, t2;
	t1 = convertToSecond(time1);
	t2 = convertToSecond(time2);

	if ( myAbs(t2-t1) < 15*60)
		return myAbs(t2-t1);
	return -1;
}

string findNearestTime(int stopID, string timeStamp, vector< pair<int,string> > *record)
{
	// timeStamp YYYY-MM-DD HH:MM:SS
	istringstream iss(timeStamp);
	string datePart, timePart;
	iss >> datePart >> timePart;
	string returnTime = ".";
	int initMatchCounter = 10;
	int matchCounter;
	int secDiff, minDiff = 9999999;
	matchCounter = initMatchCounter;
	for (int i = 0; i < record->size() && matchCounter >= 0; ++i)
	{
		if (matchCounter < initMatchCounter) --matchCounter;
		if (stopID == (*record)[i].first )
		{
			secDiff = timeMatched(timePart, (*record)[i].second);
			if (secDiff != -1 && secDiff < minDiff)
			{
				minDiff = secDiff;
				returnTime = (*record)[i].second;
				if (matchCounter == initMatchCounter) matchCounter--;			
			}
		}
	}
	return returnTime;
}

int main()
{
	FILE *fp1 = fopen("actual_data.csv", "r");
	FILE *fp2 = fopen("joinFallRouteScheduled.csv", "r");
	FILE *fpWrite = fopen("difference_Fall_E_Route_M-R.csv", "w");

	int fixedRouteID = 320;

	string line;
	char cline[100];
	int count = 0;

	int fromStop, toStop, routeID, dwellTime;
	string timeOut, timeIn;		
	string scheduledTime;

	vector< pair<int,string> > record;

	while (fscanf(fp2, " %[^\n]", cline) != EOF)
	{
		line = string(cline);
		istringstream iss(line);
		int routeID;
		string s;

		getline(iss, s, ',');
		istringstream iss2(s);
		iss2 >> routeID;

		if (routeID != fixedRouteID)
			continue;

		getline(iss, s, ',');
		istringstream iss3(s);
		iss3 >> fromStop;		

		getline(iss, s, ','); // toStop, ignore

		getline(iss, timeOut, ',');

		record.push_back(make_pair(fromStop, timeOut));

	}

	fprintf(fpWrite, "RouteID,StopID,ActualTime,ScheduledTime,Delay\n");

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

		getline(iss, s, ',');
		istringstream iss1(s);
		iss1 >> routeID;

		if (routeID != fixedRouteID)
			continue;

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
		iss4 >> dwellTime;		
	
		
		if (isMajorStopID(toStop))
		{
			scheduledTime = findNearestTime(toStop, timeIn, &record);
			if (scheduledTime != ".")
			{
				int delayInSecond = delay(timeIn, scheduledTime);
				fprintf(fpWrite, "%d,%d,%s,%s,%d\n", routeID, toStop,
					timeIn.c_str(), scheduledTime.c_str(), delayInSecond);
			}
		}

	}
	
	return 0;
}*/