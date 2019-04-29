#pragma once
class Sensor
{
public:
	Sensor();
	~Sensor();
	Sensor(char *m_gas_number, char *m_gas_name, char *m_time, char *m_concentration, char *m_sensor_number);
public:
	char gas_number[4];
	char gas_name[50];
	char time[50];
	char concentration[50];
	char sensor_number[4];
};

