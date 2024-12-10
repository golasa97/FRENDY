//--------------------------------------------------------------------------
// FMEffectiveTemperature.h : effective temperature for short collision time approx. 
//
//--------------------------------------------------------------------------

#pragma once

#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include "MGXSUtils/FMGenerator/FMZlib.h"

namespace FMGen
{
	class FMEffectiveTemperature
	{
	private:


	public:
		FMEffectiveTemperature() {};
		~FMEffectiveTemperature() {};
		REAL getEffectiveTemperature(string sab_type, REAL tin)
		{
			if (sab_type == "")
			{
				return tin;
			}

			vector<REAL> temp, temp_eff;
			temp.clear(); temp_eff.clear();

			string table_name = "NJOY2016";
			getTableNJOY2016(sab_type, temp, temp_eff);

			if (temp.size() == 0)
			{
				table_name = "ENDF/B-8.0";
				getTableENDF80(sab_type, temp, temp_eff);
			}

			if (temp.size() == 0)
			{
				table_name = "JENDL5-alpha4";
				getTableJENDL5(sab_type, temp, temp_eff);
			}

			//if s(a,b) name is not found, effective temperature = temperature
			REAL eff_temperature = 0.0;
			if (temp.size() == 0)
			{
				cout << " effective temperature table is not found in setEffectiveTemperature " << endl;
				cout << " input temperature is used for effective temperature " << endl;
				eff_temperature = tin;
			}
			else
			{
				int ind = getInterval(temp, tin);
				eff_temperature = endfInterpolator2Point(2, temp[ind], temp[ind + 1], temp_eff[ind], temp_eff[ind + 1], tin, eExtraporationConst);
			}

			cout << fixed << setprecision(3);
			cout << " Effective tempearture for this material " << endl;
			cout << " s(a,b) type                          : " << sab_type << endl;
			cout << " effective temperature table          : " << table_name << endl;
			cout << " temperature in ace file           [K]: " << setw(10) << tin << endl;
			cout << " effective temperature             [K]: " << setw(10) << eff_temperature << endl;
			cout << endl;

			return eff_temperature;

		}
		void getTableNJOY2016(string sab_type, vector<REAL>& temp, vector<REAL>& temp_eff)
		{

			//effective temperature ... taken from NJOY2016 thermr
			if (compareString(sab_type, "hh2o"))
			{
				int num = 8;
				REAL val[] =
				{ 296.0e0,1396.8e0,
					350.0e0,1411.6e0,
					400.0e0,1427.4e0,
					450.0e0,1444.9e0,
					500.0e0,1464.1e0,
					600.0e0,1506.8e0,
					800.0e0,1605.8e0,
					1000.e0,1719.8e0 };

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "dd2o"))
			{
				int num = 8;
				REAL val[] =
				{ 296.0e0,940.91e0,
					350.0e0,961.62e0,
					400.0e0,982.93e0,
					450.0e0,1006.1e0,
					500.0e0,1030.9e0,
					600.0e0,1085.1e0,
					800.0e0,1209.0e0,
					1000.e0,1350.0e0 };

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}

			}

			if (compareString(sab_type, "be"))
			{
				int num = 8;
				REAL val[] =
				{
					296.0e0,405.64e0,
					400.0e0,484.22e0,
					500.0e0,568.53e0,
					600.0e0,657.66e0,
					700.0e0,749.69e0,
					800.0e0,843.63e0,
					1000.0e0,1035.e0,
					1220.0e0,1229.3e0 };

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "graph"))
			{
				int num = 10;
				REAL val[] =
				{ 296.0e0,713.39e0,
					400.0e0,754.68e0,
					500.0e0,806.67e0,
					600.0e0,868.38e0,
					700.0e0,937.64e0,
					800.0e0,1012.7e0,
					1000.e0,1174.9e0,
					1200.e0,1348.2e0,
					1600.e0,1712.9e0,
					2000.e0,2091.0e0 };

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}

			}

			if (compareString(sab_type, "benz"))
			{
				int num = 8;
				REAL val[] =	//not benzine, benzene
				{ 296.0e0,1165.9e0,
					350.0e0,1177.8e0,
					400.0e0,1191.4e0,
					450.0e0,1207.7e0,
					500.0e0,1226.0e0,
					600.0e0,1268.7e0,
					800.0e0,1373.4e0,
					1000.e0,1497.7e0 };

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "zrzrh"))
			{
				int num = 8;
				REAL val[] =
				{ 296.0e0,317.27e0,
					400.0e0,416.29e0,
					500.0e0,513.22e0,
					600.0e0,611.12e0,
					700.0e0,709.60e0,
					800.0e0,808.43e0,
					1000.e0,1006.8e0,
					1200.e0,1205.7e0 };

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "hzrh"))
			{
				int num = 8;
				REAL val[] =
				{ 296.0e0,806.79e0,
					400.0e0,829.98e0,
					500.0e0,868.44e0,
					600.0e0,920.08e0,
					700.0e0,981.82e0,
					800.0e0,1051.1e0,
					1000.e0,1205.4e0,
					1200.e0,1373.4e0 };

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "bebeo") || compareString(sab_type, "obeo"))
			{
				int num = 7;
				REAL val[] =
				{ 296.0e0,596.4e0,
					400.0e0,643.9e0,
					500.0e0,704.6e0,
					600.0e0,775.3e0,
					800.0e0,935.4e0,
					1000.e0,1109.8e0,
					1200.e0,1292.3e0 };

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "poly"))
			{
				int num = 2;
				REAL val[] =
				{ 296.0e0,1222.0e0,
					350.0e0,1239.0e0 };

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

		}
		void getTableENDF80(string sab_type, vector<REAL>& temp, vector<REAL>& temp_eff)
		{

			//effective temperature
			if (compareString(sab_type, "al"))
			{
				int num = 6;
				REAL val[] =
				{ 
				  20.000000,  149.16900,
				  80.000000,  159.16250,
				  293.60000,  320.55920,
				  400.00000,  420.00560,
				  600.00000,  613.43410,
				  800.00000,  810.10150
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "fe"))
			{
				int num = 6;
				REAL val[] =
				{ 
				  20.000000,  157.33060,
				  80.000000,  165.76660,
				  293.60000,  322.96780,
				  400.00000,  421.79700,
				  600.00000,  614.63880,
				  800.00000,  811.00780
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "bebeo"))
			{
				int num = 6;
				REAL val[] =
				{
				  293.60000,  533.20830,
				  400.00000,  590.86470,
				  500.00000,  658.85340,
				  600.00000,  735.47260,
				  700.00000,  817.82250,
				  800.00000,  904.10190,
				  1000.0000,  1084.2640,
				  1200.0000,  1270.6780
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "be"))
			{
				int num = 8;
				REAL val[] =
				{
				  296.00000,  433.38170,
				  400.00000,  506.39290,
				  500.00000,  586.94720,
				  600.00000,  673.33050,
				  700.00000,  763.32080,
				  800.00000,  855.67550,
				  1000.0000,  1044.7990,
				  1200.0000,  1237.4510
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "benz"))
			{
				int num = 8;
				REAL val[] =
				{
				  296.00000,  1165.9000,
				  350.00000,  1177.8000,
				  400.00000,  1191.4000,
				  450.00000,  1207.7000,
				  500.00000,  1226.0000,
				  600.00000,  1268.7000,
				  800.00000,  1373.4000,
				  1000.0000,  1497.7000
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "csic"))
			{
				int num = 8;
				REAL val[] =
				{
				  300.00000,  553.26270,
				  400.00000,  604.73190,
				  500.00000,  670.29860,
				  600.00000,  745.15140,
				  700.00000,  826.18280,
				  800.00000,  911.44960,
				  1000.0000,  1090.1690,
				  1200.0000,  1275.6090
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "graph"))
			{
				//B8.0 crystalline-graphite (without porus)
				int num = 10;
				REAL val[] =
				{
				  296.00000,  706.22430,
				  400.00000,  748.87620,
				  500.00000,  801.92710,
				  600.00000,  864.43430,
				  700.00000,  934.27780,
				  800.00000,  1009.7460,
				  1000.0000,  1172.6710,
				  1200.0000,  1346.2710,
				  1600.0000,  1711.5790,
				  2000.0000,  2089.9870
				};
#if 0
				//B8.0 reactor graphite with porus of 10%
				REAL val[] =
				{
				  296.00000,  690.54110,
				  400.00000,  738.32950,
				  500.00000,  794.85270,
				  600.00000,  859.69770,
				  700.00000,  931.09430,
				  800.00000,  1007.6000,
				  1000.0000,  1171.7080,
				  1200.0000,  1345.8830,
				  1600.0000,  1711.6440,
				  2000.0000,  2090.1860
				};
				//B8.0 reactor graphite with porus of 30%
				REAL val[] =
				{
				  296.00000,  573.82570,
				  400.00000,  631.83190,
				  500.00000,  698.18280,
				  600.00000,  772.13010,
				  700.00000,  851.62200,
				  800.00000,  935.19030,
				  1000.0000,  1110.7150,
				  1200.0000,  1293.5050,
				  1600.0000,  1671.1030,
				  2000.0000,  2057.2570
				};

#endif

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "dd2o"))
			{
				int num = 17;
				REAL val[] =
				{
				  283.60000,  861.76370,
				  293.60000,  865.55660,
				  300.00000,  867.51380,
				  323.60000,  875.22140,
				  350.00000,  886.96120,
				  373.60000,  894.08480,
				  400.00000,  906.40340,
				  423.60000,  919.03220,
				  450.00000,  931.72000,
				  473.60000,  944.30550,
				  500.00000,  956.68490,
				  523.60000,  968.50500,
				  550.00000,  983.69620,
				  573.60000,  996.95990,
				  600.00000,  1011.2200,
				  623.60000,  1024.5230,
				  650.00000,  1040.0470
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "c5o2h8"))
			{
				int num = 1;
				REAL val[] =
				{
					300.00000,  1243.4860
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "poly"))
			{
				int num = 11;
				REAL val[] =
				{
				  77.000000,  1184.5400,
				  196.00000,  1191.8090,
				  233.00000,  1195.3600,
				  293.60000,  1203.0520,
				  300.00000,  1204.0230,
				  303.00000,  1204.4890,
				  313.00000,  1206.0950,
				  323.00000,  1207.7840,
				  333.00000,  1209.5580,
				  343.00000,  1211.4160,
				  350.00000,  1212.7690
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "hh2o"))
			{
				int num = 18;
				REAL val[] =
				{
				  283.60000,  1192.4530,
				  293.60000,  1194.3340,
				  300.00000,  1195.5380,
				  323.60000,  1200.5060,
				  350.00000,  1207.0750,
				  373.60000,  1212.9850,
				  400.00000,  1220.6190,
				  423.60000,  1228.2420,
				  450.00000,  1237.2870,
				  473.60000,  1246.3430,
				  500.00000,  1257.2890,
				  523.60000,  1266.9850,
				  550.00000,  1278.8430,
				  573.60000,  1289.0880,
				  600.00000,  1301.0140,
				  623.60000,  1312.7560,
				  650.00000,  1325.6090,
				  800.00000,  1412.8820
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "hice"))
			{
				int num = 9;
				REAL val[] =
				{
				  115.00000,  1221.2860,
				  188.15000,  1225.9410,
				  208.15000,  1228.1310,
				  228.15000,  1230.7860,
				  233.15000,  1231.5240,
				  248.15000,  1233.9150,
				  253.15000,  1234.7710,
				  268.15000,  1237.5140,
				  273.15000,  1238.4860
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "hyh2"))
			{
				int num = 10;
				REAL val[] =
				{
				  293.60000,  732.82610,
				  400.00000,  762.64920,
				  500.00000,  807.79070,
				  600.00000,  865.69450,
				  700.00000,  932.91650,
				  800.00000,  1006.9100,
				  1000.0000,  1168.5980,
				  1200.0000,  1341.9480,
				  1400.0000,  1522.4370,
				  1600.0000,  1707.5740
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "hzrh"))
			{
				int num = 8;
				REAL val[] =
				{
				  296.00000,  806.73400,
				  400.00000,  829.91540,
				  500.00000,  868.38040,
				  600.00000,  920.03620,
				  700.00000,  981.78440,
				  800.00000,  1051.0940,
				  1000.0000,  1205.4020,
				  1200.0000,  1373.3240
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "lch4"))
			{
				int num = 1;
				REAL val[] =
				{
				  100.00000,  927.70670
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "nun"))
			{
				int num = 8;
				REAL val[] =
				{
				  296.00000,  382.70990,
				  400.00000,  465.89200,
				  500.00000,  553.35030,
				  600.00000,  644.75470,
				  700.00000,  738.51660,
				  800.00000,  833.79110,
				  1000.0000,  1027.1170,
				  1200.0000,  1222.6360
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "obeo"))
			{
				int num = 8;
				REAL val[] =
				{
				  293.60000,  466.02040,
				  400.00000,  535.05300,
				  500.00000,  611.42790,
				  600.00000,  694.52970,
				  700.00000,  781.93710,
				  800.00000,  872.23080,
				  1000.0000,  1058.3040,
				  1200.0000,  1248.8280
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "od2o"))
			{
				int num = 17;
				REAL val[] =
				{
				  283.60000,  445.65010,
				  293.60000,  454.53810,
				  300.00000,  459.60290,
				  323.60000,  478.46550,
				  350.00000,  500.93820,
				  373.60000,  517.81730,
				  400.00000,  539.98730,
				  423.60000,  561.01230,
				  450.00000,  582.56130,
				  473.60000,  602.89350,
				  500.00000,  624.23730,
				  523.60000,  643.76980,
				  550.00000,  666.74780,
				  573.60000,  686.90570,
				  600.00000,  709.31010,
				  623.60000,  729.58300,
				  650.00000,  752.54270
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "oice"))
			{
				int num = 9;
				REAL val[] =
				{
				  115.00000,  270.17890,
				  188.15000,  322.59370,
				  208.15000,  338.51210,
				  228.15000,  354.84750,
				  233.15000,  358.98640,
				  248.15000,  371.51830,
				  253.15000,  375.73080,
				  268.15000,  388.46330,
				  273.15000,  392.73660
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "ouo2"))
			{
				int num = 8;
				REAL val[] =
				{
				  296.00000,  381.74800,
				  400.00000,  465.59240,
				  500.00000,  553.28430,
				  600.00000,  644.78580,
				  700.00000,  738.59010,
				  800.00000,  833.88300,
				  1000.0000,  1027.2180,
				  1200.0000,  1222.7320
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "dortho"))
			{
				int num = 1;
				REAL val[] =
				{
				  19.000000,  34.542160
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "hortho"))
			{
				int num = 1;
				REAL val[] =
				{
				  20.000000,  39.696180
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "dpara"))
			{
				int num = 1;
				REAL val[] =
				{
				  19.000000,  34.542160
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "hpara"))
			{
				int num = 1;
				REAL val[] =
				{
				  20.000000,  39.696180
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "sch4"))
			{
				int num = 1;
				REAL val[] =
				{
				  22.000000,  910.07610
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "sisic"))
			{
				int num = 8;
				REAL val[] =
				{
				  300.00000,  421.38920,
				  400.00000,  495.68930,
				  500.00000,  578.53220,
				  600.00000,  666.41070,
				  700.00000,  757.44640,
				  800.00000,  850.57130,
				  1000.0000,  1040.7520,
				  1200.0000,  1234.0960
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "uun"))
			{
				int num = 8;
				REAL val[] =
				{
				  296.00000,  306.09700,
				  400.00000,  407.53070,
				  500.00000,  506.04590,
				  600.00000,  605.04810,
				  700.00000,  704.33210,
				  800.00000,  803.79350,
				  1000.0000,  1003.0380,
				  1200.0000,  1202.5330
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "uuo2"))
			{
				int num = 8;
				REAL val[] =
				{
				  296.00000,  307.42890,
				  400.00000,  408.56740,
				  500.00000,  506.89560,
				  600.00000,  605.76590,
				  700.00000,  704.95260,
				  800.00000,  804.33950,
				  1000.0000,  1003.4770,
				  1200.0000,  1202.9000
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "yyh2"))
			{
				int num = 10;
				REAL val[] =
				{
				  293.60000,  309.19520,
				  400.00000,  411.71520,
				  500.00000,  509.48350,
				  600.00000,  607.95920,
				  700.00000,  706.85330,
				  800.00000,  806.01510,
				  1000.0000,  1004.8300,
				  1200.0000,  1204.0340,
				  1400.0000,  1403.4620,
				  1600.0000,  1603.0320
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "zrzrh"))
			{
				int num = 8;
				REAL val[] =
				{
				  296.00000,  317.41630,
				  400.00000,  416.33250,
				  500.00000,  513.28260,
				  600.00000,  611.18160,
				  700.00000,  709.64790,
				  800.00000,  808.48020,
				  1000.0000,  1006.8220,
				  1200.0000,  1205.7030
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "sio2alpha"))
			{
				int num = 5;
				REAL val[] =
				{
				  293.60000,  508.33900,
				  350.00000,  540.94980,
				  400.00000,  573.26900,
				  500.00000,  645.33060,
				  800.00000,  896.28320
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "sio2beta"))
			{
				int num = 2;
				REAL val[] =
				{
				  1000.0000,  1080.1420,
				  1100.0000,  1173.1980
				};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}


		}

		void getTableJENDL5(string sab_type, vector<REAL>& temp, vector<REAL>& temp_eff)
		{

			//effective temperature
			if (compareString(sab_type, "hh2o"))
			{
				int num = 56;
				REAL val[] =
				{ 270.00000,  1189.4610,
				  280.00000,  1192.5560,
				  290.00000,  1193.0690,
				  293.60000,  1192.3960,
				  296.00000,  1194.5320,
				  300.00000,  1196.1290,
				  310.00000,  1197.7600,
				  320.00000,  1200.6880,
				  330.00000,  1203.9340,
				  340.00000,  1205.6450,
				  350.00000,  1208.6880,
				  360.00000,  1212.2050,
				  370.00000,  1215.2540,
				  380.00000,  1218.3070,
				  390.00000,  1221.7680,
				  400.00000,  1226.0500,
				  410.00000,  1229.8540,
				  420.00000,  1233.1560,
				  430.00000,  1237.8590,
				  440.00000,  1241.4580,
				  450.00000,  1245.7150,
				  460.00000,  1251.6870,
				  470.00000,  1255.3720,
				  480.00000,  1258.9070,
				  490.00000,  1265.2560,
				  500.00000,  1268.0700,
				  510.00000,  1272.7410,
				  520.00000,  1276.9720,
				  530.00000,  1282.9050,
				  540.00000,  1288.0780,
				  550.00000,  1292.7780,
				  560.00000,  1297.0980,
				  570.00000,  1303.6810,
				  580.00000,  1309.2250,
				  590.00000,  1314.3280,
				  600.00000,  1318.9370,
				  610.00000,  1323.7430,
				  620.00000,  1328.8260,
				  630.00000,  1336.2610,
				  640.00000,  1340.8740,
				  650.00000,  1345.4560,
				  660.00000,  1351.6180,
				  670.00000,  1359.7150,
				  680.00000,  1365.5100,
				  690.00000,  1372.3270,
				  700.00000,  1376.0700,
				  710.00000,  1384.7650,
				  720.00000,  1389.8930,
				  730.00000,  1396.9720,
				  740.00000,  1402.1940,
				  750.00000,  1407.6310,
				  760.00000,  1413.3840,
				  770.00000,  1420.8750,
				  780.00000,  1427.9080,
				  790.00000,  1434.1980,
				  800.00000,  1440.5330	};

				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}
			}

			if (compareString(sab_type, "oh2o"))
			{
				int num = 56;
				REAL val[] =
				{ 270.00000,  413.57560,
				  280.00000,  421.91210,
				  290.00000,  429.42170,
				  293.60000,  432.00900,
				  296.00000,  434.31600,
				  300.00000,  437.84730,
				  310.00000,  445.94140,
				  320.00000,  454.26020,
				  330.00000,  462.52110,
				  340.00000,  470.78370,
				  350.00000,  479.25560,
				  360.00000,  487.69960,
				  370.00000,  496.22460,
				  380.00000,  505.17500,
				  390.00000,  513.55440,
				  400.00000,  522.61500,
				  410.00000,  531.24770,
				  420.00000,  539.81520,
				  430.00000,  548.70840,
				  440.00000,  557.44330,
				  450.00000,  566.20590,
				  460.00000,  575.41800,
				  470.00000,  584.17720,
				  480.00000,  593.05990,
				  490.00000,  602.28260,
				  500.00000,  610.72110,
				  510.00000,  619.72660,
				  520.00000,  628.59840,
				  530.00000,  637.75210,
				  540.00000,  646.79350,
				  550.00000,  655.81750,
				  560.00000,  664.99960,
				  570.00000,  674.37770,
				  580.00000,  683.40570,
				  590.00000,  692.60930,
				  600.00000,  701.44260,
				  610.00000,  710.48490,
				  620.00000,  719.69170,
				  630.00000,  729.50850,
				  640.00000,  738.11020,
				  650.00000,  746.92270,
				  660.00000,  755.93680,
				  670.00000,  765.24220,
				  680.00000,  774.00220,
				  690.00000,  783.14370,
				  700.00000,  791.83020,
				  710.00000,  801.43810,
				  720.00000,  810.43870,
				  730.00000,  820.03800,
				  740.00000,  829.28900,
				  750.00000,  838.50720,
				  760.00000,  847.88210,
				  770.00000,  857.12530,
				  780.00000,  867.13780,
				  790.00000,  876.78310,
				  800.00000,  885.90460 };
				for (int i = 0; i < num; i++)
				{
					temp.push_back(val[2 * i]);
					temp_eff.push_back(val[2 * i + 1]);
				}

			}
		}

	};
}

