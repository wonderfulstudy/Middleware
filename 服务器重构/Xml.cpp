#include "stdafx.h"
#include "Xml.h"


Xml::Xml()
{
	Version = "<?xml version=\"1.0\" encoding=\"UTF - 8\"?>";
}


Xml::~Xml()
{
}

Sensor Xml::XmlAnalysis(char * Data)
{
	Sensor	GoBack;
	int		j = 0, i = 0;
	int		count, start = 0;

	while (*(Data + j) != '\0')
	{
		j++;

		if (*(Data + j) == '>')
		{
			if (*(Data + j + 1) != '<')
			{
				i++;
				count = 0;
				start = 1;
			}
		}
		else if (*(Data + j) == '<')
		{
			start = 0;
		}
		else if (start == 1)
		{
			switch (i)
			{
			case 1:
				if (count < sizeof(GoBack.gas_number) - 1)
				{
					GoBack.gas_number[count] = *(Data + j);
					GoBack.gas_number[count + 1] = '\0';
					count++;
				}
				break;
			case 2:
				if (count < sizeof(GoBack.gas_name) - 1)
				{
					GoBack.gas_name[count] = *(Data + j);
					GoBack.gas_name[count + 1] = '\0';
					count++;
				}
				break;
			case 3:
				if (count < sizeof(GoBack.time) - 1)
				{
					GoBack.time[count] = *(Data + j);
					GoBack.time[count + 1] = '\0';
					count++;
				}
				break;
			case 4:
				if (count < sizeof(GoBack.concentration) - 1)
				{
					GoBack.concentration[count] = *(Data + j);
					GoBack.concentration[count + 1] = '\0';
					count++;
				}
				break;
			case 5:
				if (count < sizeof(GoBack.sensor_number) - 1)
				{
					GoBack.sensor_number[count] = *(Data + j);
					GoBack.sensor_number[count + 1] = '\0';
					count++;
				}
				break;
			default:
				break;
			}
		}
	}
	return GoBack;
}

void Xml::VersionAnalysis(char * Data)
{
	string buff(Data);
	unsigned int loc = buff.find(Version, 0);
	if (loc != string::npos)
		cout << "Found at!" << loc << endl;
	else
		cout << "Didn't find!" << endl;
}
