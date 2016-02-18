
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <map>

using namespace std;

int main()
{
	FILE *fp = fopen("difference_Spring_E_Route_M-R.csv", "r");

	string line;
	char cline[100];
	int count = 0;

	int stopID, routeID, delay;	

	map<int, pair<int, int > > record;

	fscanf(fp, " %[^\n]", cline) ;

	while (fscanf(fp, " %[^\n]", cline) != EOF)
	{
		line = string(cline);
		istringstream iss(line);

		string s;

		getline(iss, s, ',');
		istringstream iss2(s);
		iss2 >> routeID;


		getline(iss, s, ',');
		istringstream iss3(s);
		iss3 >> stopID;		

		getline(iss, s, ','); // actual time, ignore

		getline(iss, s, ','); // schedule time, ignore

		getline(iss, s, ',');
		istringstream iss4(s);
		iss4 >> delay;		
		
		if (record.find(stopID) == record.end())
		{
			record[stopID] = make_pair(delay, 1);
		}
		else
		{
			record[stopID] = make_pair(record[stopID].first+delay, record[stopID].second+1);
		}

	}

	for (map<int, pair<int, int> > ::iterator it = record.begin(); it != record.end(); ++it)
	{
		cout << (*it).first << ":" << (*it).second.first << " " << (*it).second.second
			<< " " << ((*it).second.first / (*it).second.second )<< endl;
	}

	
	
	return 0;
}