//--------------------------------------------------------------------------
// FMCalcluationTime.h : Measure & show breakdown of calculation time 
//
//--------------------------------------------------------------------------

#pragma once
#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include <time.h>

namespace FMGen
{
	class FMCalculationTime
	{
	private:
		clock_t				start;
		map<string, clock_t>	total;
		map<string, clock_t>	lap;

	public:
		FMCalculationTime()
		{
			start = clock();
		}
		~FMCalculationTime()
		{
			total.clear();
			lap.clear();
		}
		REAL getElapsedTime()
		{
			clock_t now = clock();
			REAL elapsed = (REAL)(now - start) / CLOCKS_PER_SEC;
			return elapsed;
		}
		void startMeasure(string label)
		{
			lap[label] = clock();
		}
		void stopMeasure(string label)
		{
			clock_t difference = clock() - lap[label];
			total[label] += difference;
		}
		void editBreakdown(string& output)
		{
			output = "";

			stringstream of;
			of << fixed << setprecision(3);

			of << " =====  Breakdown of calculation time  ===" << endl << endl;
			of << "---------------------------------------------------------------------------------------------------------------------" << endl;
			of << "                                             Function              Calculation time(sec)  Fraction to total time(%)" << endl;
			of << "---------------------------------------------------------------------------------------------------------------------" << endl;
			map<string, clock_t>::iterator it;

			REAL tot = getElapsedTime();
			REAL sum = 0.0;

			for (it = total.begin(); it != total.end(); it++)
			{
				of << setw(61) << it->first.c_str();
				REAL time = (REAL)it->second / CLOCKS_PER_SEC;
				sum += time;
				of << setw(20) << time;
				of << setw(20) << time / tot * 100.0;
				of << endl;
			}
			string buf = "Miscellaneous";
			of << setw(61) << buf.c_str();
			REAL diff = tot - sum;
			if (diff < 0.0) diff = 0.0;
			of << setw(20) << diff;
			of << setw(20) << diff / tot * 100.0;
			of << endl;
			of << "---------------------------------------------------------------------------------------------------------------------" << endl;
			buf = "Total";
			of << setw(61) << buf.c_str();
			of << setw(20) << tot;
			of << setw(20) << tot / tot * 100.0;
			of << endl;
			of << "---------------------------------------------------------------------------------------------------------------------" << endl;
			output = of.str();
		}
	};
}
