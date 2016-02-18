#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

#define myabs(a) ((a)>(0)?(a):(-a))

int main2()
{
	
						
	FILE *fp = fopen("iub_export_filtered.csv", "r");

	FILE *fpWrite = fopen("routeData.csv", "w");

	/*FILE *fpWrite = fopen("stopData.txt", "w");
	for (int i = 0; i < nGeoCodes; ++i)
	{
		fprintf(fpWrite, "INSERT INTO STOP_NAMES VALUES (%d,\'%s\',%.6lf,%.6lf);\n", geocodes[i].id, geocodes[i].name, geocodes[i].latitude, geocodes[i].longitude);
	}
	

	return 0;*/

	if (fp == NULL)
	{
		printf("Failed to open file\n");
		return 0;
	}

	char line[100];
	int count = 0, passed = 0;
	int i;
	const char s[2] = ",";
	char *token;
	int busID, stopID;
	char timestamp[50];
	int lastStopID[1000];
	char lastTime[1000][50];
	int totalRow = 22987143;

	for(i = 0; i < 1000; ++i)
		lastStopID[i] = 0;

	fprintf(fpWrite, "BUS_ID,FROM_STOP,TO_STOP,ACTUAL_TIMEOUT,ACTUAL_TIMEIN\n");

	while (fscanf(fp, " %[^\n]", line) != EOF)
	{

		token = strtok(line, s);
		sscanf(token, "%d", &busID);

		token = strtok(NULL, s);		
		sscanf(token, "%d", &stopID);
		
		token = strtok(NULL, s);
		strcpy(timestamp, token);
		timestamp[strlen(timestamp)-3] = 0;
		
		if (lastStopID[busID] == 0)
		{
			lastStopID[busID] = stopID;
			strcpy(lastTime[busID], timestamp);
		}
		else if (lastStopID[busID] == stopID)
		{
			strcpy(lastTime[busID], timestamp);			
		}
		else
		{
			fprintf(fpWrite, "\"%d\",\"%d\",\"%d\",\"%s\",\"%s\"\n", busID, lastStopID[busID], stopID, lastTime[busID], timestamp);
			//fprintf(fpWrite, "INSERT INTO ACTUAL_SCHEDULE VALUES (%d,%d,%d,\'%s\',\'%s\');\n", busID, lastStopID[busID], stopID, lastTime[busID], timestamp);
			lastStopID[busID] = stopID;
			strcpy(lastTime[busID], timestamp);
		}
		
		
					
		 

		++count;
		if (count % 10000 == 0)
		{
			printf ("%.2lf%%, count=%d, passed=%d\n", count*100.00/totalRow, count, passed);
			//printf ("%.2lf%%\n", count*100.00/totalRow);
			//printf ("Lat: %lf, Long: %lf, line: %s\n", latitude, longitude, linecopy);	
			//break;
		}
	}

	return 0;
}