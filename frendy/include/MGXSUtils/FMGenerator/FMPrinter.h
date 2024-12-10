//-----------------------------------------------------
// FMPrinter.h : Format output data to output
//        
//-----------------------------------------------------

#pragma once

#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include <fstream>
#include <sstream>

namespace FMGen
{
	inline void print1stHeader(string str)
	{
		cout << " " << endl;
		cout << " " << endl;
		cout << " ====================================================================================================== " << endl;
		cout << "  " << str << endl;
		cout << " ====================================================================================================== " << endl;
	}
	inline void print2ndHeader(string str)
	{
		cout << " < " << str << " >" << endl;
	}
	inline void printError(string str, int flag = true)
	{
		cout << " " << endl;
		cout << " " << endl;
		cout << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << endl;
		cout << "  Error occured during execution " << endl;
		cout << "  " << str << endl;
		cout << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << endl;
		if (flag)	exit(999);
	}
	inline void printError(vector<string> str_vec, int flag = true)
	{
		cout << " " << endl;
		cout << " " << endl;
		cout << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << endl;
		cout << "  Error occured during execution " << endl;
		for (int i = 0; i < static_cast<int>(str_vec.size()); i++)
			cout << "  " << str_vec[i] << endl;
		cout << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << endl;
		if (flag)	exit(999);
	}
}
