#include "stdafx.h"
#include "Gas.h"


Gas::Gas()
{
	strcpy_s(gas_number, sizeof(gas_number), "101");
	strcpy_s(gas_name, sizeof(gas_name), "So2");
	strcpy_s(time, sizeof(time), "12:15");
	strcpy_s(sensor_number, sizeof(sensor_number), "1");
}


Gas::~Gas()
{
}

Gas::Gas(char *m_gas_number, char *m_gas_name, char *m_time, char *m_concentration, char *m_sensor_number)
{
	strcpy_s(gas_number, sizeof(gas_number), m_gas_number);
	strcpy_s(gas_name, sizeof(gas_name), m_gas_name);
	strcpy_s(time, sizeof(time), m_time);
	strcpy_s(concentration, sizeof(concentration), m_concentration);
	strcpy_s(sensor_number, sizeof(sensor_number), m_sensor_number);
}
