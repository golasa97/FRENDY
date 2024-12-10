//----------------------------------------------------------------
// FMMatxsOutput.h  : output to matxs format
//
//----------------------------------------------------------------

#pragma once

#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include "MGXSUtils/FMGenerator/FMDataContainer.h"
#include <fstream>

namespace FMGen
{
	class FMMatxsOutput
	{
	private:
	public:
		FMDataContainer* dc;
		stringstream			of;
		string					file_name;
		string					zaid;
		int						za;
		string					hmatn;
		int						ntype;
		int						nsubm;
		vector<int>				xs1d_infdil;
		vector<int>				xs1d_shield;
		vector<int>				xs2d_infdil;
		vector<int>				xs2d_shield;
		map<int, int>			xs2d_plorder;
		vector<int>				xs_thermal;
		const int				MAXW = 5000;
		vector<int>				matxs_block_num;

		FMMatxsOutput(FMDataContainer* _dc)
		{
			dc = _dc;
		};
		~FMMatxsOutput()
		{
		};

		void openFile(string _zaid, string add_name_ = "")
		{
			zaid = _zaid;
			file_name = "FMMatxsFile_" + add_name_ + zaid + ".txt";
			of.str("");
			of.clear();
		}
		void closeFile()
		{
			dc->output_list_data.insert(make_pair(file_name, of.str()));
			of.str("");
			of.clear();
		}
		void compressVectorData(vector<REAL>& vec, int& sta, int& end);
		void compressMatrixData(int pl_order, vector<vector<vector<REAL> > >& matrix, vector<int>& jband, vector<int>& ijj, vector<vector<REAL> >& cmp_vec);
		void calcBlockNumber();
		void outputHeader();
		void outputMaterialControl();
		void outputVectorMatrix();
		void outputVectorData(bool thermal, int ib, bool output, int& block_num);
		void outputMatrixData(bool thermal, int ib, bool output, int& block_num);
		void output4d7d9d10d(int name, vector<REAL>& vec);
	};
}
