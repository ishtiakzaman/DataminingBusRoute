#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

#define myabs(a) ((a)>(0)?(a):(-a))

typedef struct
{
	int id;
	char name[100];
	double latitude;
	double longitude;
} geo;

int main1()
{
	int nGeoCodes = 52;
	geo geocodes[] = {  { 67, "Stadium (A)", 39.180308, -86.527963 },
						{ 35, "Assembly Hall()", 39.179001, -86.521805 },
						{ 39, "Alumni Center", 39.179033, -86.521693 },
						{ 38, "Briscoe", 39.178289, -86.518900 },
						{ 34, "Briscoe()", 39.178259, -86.518823 },
						{ 37, "McNutt", 39.176169, -86.518910 },
						{ 30, "Foster", 39.175574, -86.518973 },
						{ 41, "Kelley School", 39.172928, -86.518969 },
						{ 36, "Kelley School()", 39.172441, -86.518902 },
						{ 1, "Wells Library", 39.171558, -86.516562 },
						{ 4, "Neals Marshall", 39.168015, -86.516158 },
						{ 6, "3rd and Jordan", 39.164290, -86.516958 },
						{ 8, "Jordan Hall", 39.164267, -86.521633 },
						{ 10, "Maurer School of Law", 39.164334, -86.526585 },
						{ 11, "Kirkwood & Indiana", 39.166500, -86.526910 },
						{ 12, "IMU", 39.168477, -86.523894 },
						{ 13, "10th & Woodlawn", 39.171431, -86.523475 },
						{ 14, "Psychology", 39.171567, -86.520956 },

						{ 78, "Audotorium(X)", 39.168657, -86.518632 },
						{ 64, "IMU(X)", 39.168487, -86.521573 },
						{ 118, "7th & Woodlawn", 39.168750, -86.523517 },
						{ 76, "Stadium(X)", 39.180175, -86.527885 },

						{ 62, "Evermann Redbud", 39.177981, -86.507072 },
						{ 47, "Evermann", 39.177704, -86.508163 },
						{ 48, "Bicknell", 39.176756, -86.509115 },
						{ 61, "Bicknell()", 39.176706, -86.509085 },
						{ 60, "Hepburn Apartment", 39.175928, -86.509885 },
						{ 107, "Nutt Apartment()", 39.175805, -86.509944 },
						{ 50, "Campus View", 39.173747, -86.509863 },
						{ 59, "Campus View ()", 39.173308, -86.509594 },
						{ 58, "Eigenmann", 39.170912, -86.509438 },
						{ 51, "Union & 10th", 39.170561, -86.509507 },
						{ 52, "Union & 7th", 39.168319, -86.509484 },
						{ 57, "7th & Union", 39.168045, -86.510560 },
						{ 45, "Willkie", 39.166080, -86.510960 },
						{ 46, "Forest", 39.164287, -86.512845 },


						{ 99, "Fisher Court", 39.183987, -86.516888 },					
						{ 25, "ZBT", 39.183554, -86.514620 },
						{ 23, "ZBT()", 39.183589, -86.514561 },
						{ 26, "Balfour", 39.182420, -86.512664 },
						{ 22, "Balfour()", 39.182364, -86.512468 },
						{ 27, "Kappa Sigma", 39.180747, -86.511096 },
						{ 21, "Chi Omega ()", 39.181007, -86.511142 },
						{ 20, "Phi Kappa Sigma ()", 39.179562, -86.510905 },
						{ 28, "Jordan & 17th", 39.179105, -86.510985 },
						{ 29, "Lingelbach", 39.177223, -86.512545 },
						{ 75, "Lingelbach ()", 39.177107, -86.512518 },
						{ 31, "Kappa Delta", 39.174578, -86.514765 },
						{ 16, "SRSC()", 39.174412, -86.514862 },
						{ 33, "10th & Jordan", 39.171689, -86.515690 },
						{ 88, "10th and Jordan()", 39.171398, -86.515636 },
						{ 87, "Jordan Garage", 39.167387, -86.515912 }

					};
						
	FILE *fp = fopen("iub_export.csv", "r");

	FILE *fpWrite = fopen("iub_export_filtered.csv", "w");

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
	double margin = 0.000150;
	const char s[2] = ",";
	char *token;
	double latitude, longitude;
	int busid;
	int lastBusID = -1, lastStopID = -1;
	double lastLat = 0.0, lastLong = 0.0;
	int totalRow = 135970255;

	while (fscanf(fp, " %[^\n]", line) != EOF)
	{

		token = strtok(line, s);
		sscanf(token, "%d", &busid);

		token = strtok(NULL, s);		
		sscanf(token, "%lf", &latitude);
		
		token = strtok(NULL, s);
		sscanf(token, "%lf", &longitude);

		token = strtok(NULL, s); // unknown 4th column
		token = strtok(NULL, s); // unknown 5th column

		token = strtok(NULL, s);

		for (i = 0; i < nGeoCodes; ++i)
		{
			
			if (myabs(latitude - geocodes[i].latitude) < margin && myabs(longitude - geocodes[i].longitude) < margin)
			{
					
				passed++;
					
				lastBusID = busid;
				lastStopID = geocodes[i].id;

				fprintf(fpWrite, "%d,%d,%s\n", lastBusID, lastStopID, token);
				break;
					
			}

			
		}
		 

		++count;
		if (count % 100000 == 0)
		{
			printf ("%.2lf%%, count=%d, passed=%d\n", count*100.00/totalRow, count, passed);
			//printf ("%.2lf%%\n", count*100.00/totalRow);
			//printf ("Lat: %lf, Long: %lf, line: %s\n", latitude, longitude, linecopy);	
			//break;
		}
	}

	return 0;
}