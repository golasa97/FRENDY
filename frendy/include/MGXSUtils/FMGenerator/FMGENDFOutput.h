//----------------------------------------------------------------
// FMGENDFOutput.h  : output to GENDF format
//
//----------------------------------------------------------------

#pragma once

#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include "MGXSUtils/FMGenerator/FMDataContainer.h"
#include <fstream>

namespace FMGen
{
	class FMGENDFOutput
	{
	private:
		FMDataContainer* dc;
		stringstream			of;
		string					file_name;
		string					zaid;
		int						za;
		REAL					aw;
		REAL					temp;
		int						endf_id;
		vector<int>				xs1d_infdil;
		vector<int>				xs1d_shield;
		vector<int>				xs2d_infdil;
		vector<int>				xs2d_shield;
		map<int, int>			xs2d_plorder;

	public:

		FMGENDFOutput(FMDataContainer* _dc)
		{
			dc = _dc;
		};
		FMGENDFOutput()
		{
		};
		~FMGENDFOutput()
		{
		};

		void openFile(string _zaid, string add_name_ = "")
		{
			zaid = _zaid;
			file_name = "FMGENDFFile_" + add_name_ + zaid + ".txt";
			of.str("");
			of.clear();
		}
		void closeFile()
		{
			dc->output_list_data.insert(make_pair(file_name, of.str()));
			of.str("");
			of.clear();
		}
		void output();
		void outputMF1();
		void outputMF3();
		void outputMF5();
		void outputMF6();
		void outputToFile(string data, int _endf_id, int mf, int mt, int& line_no)
		{
			of << setw(66) << left << data;
			of << right;
			of << setw(4) << _endf_id;
			of << setw(2) << mf;
			of << setw(3) << mt;
			int wk = line_no;
			if (wk > 99999) wk = 99999;
			of << setw(5) << line_no;
			of << endl;
			line_no++;
		}
		void outputToFile(vector<string>& data, int _endf_id, int mf, int mt, int& line_no)
		{
			for (int i = 0; i < static_cast<int>(data.size()); i++)
			{
				of << setw(11) << right << data[i];
				if ((i + 1) % 6 == 0)
				{
					of << right;
					of << setw(4) << _endf_id;
					of << setw(2) << mf;
					of << setw(3) << mt;
					int wk = line_no;
					if (wk > 99999) wk = 99999;
					of << setw(5) << line_no;
					of << endl;
					line_no++;
				}
			}
			if (data.size() % 6 != 0)
			{
				int wk = 6 - data.size() % 6;
				for (int i = 0; i < wk; i++)
					of << setw(11) << right << " ";
				of << right;
				of << setw(4) << endf_id;
				of << setw(2) << mf;
				of << setw(3) << mt;
				wk = line_no;
				if (wk > 99999) wk = 99999;
				of << setw(5) << line_no;
				of << endl;
				line_no++;
			}
			data.clear();
		}
		void setDataString(string wk, vector<string>& data)
		{
			int ista = 0;
			for (;;)
			{
				string buf = wk.substr(ista,11);
				data.push_back(buf);
				ista += 11;
				if (ista >= static_cast<int>(wk.length())) break;
			}
		}
		void setDataREAL(REAL wk, vector<string>& data)
		{
			int digit;
			REAL val;
			const REAL MIN_FLOAT = 1.00000e-38;
			const REAL MAX_FLOAT = 9.99999e+38;

			if (wk == 0.0)
			{
				digit = 0;
				val = 0.0;
			}
			else
			{
				if (log(abs(wk)) < log(MIN_FLOAT)) wk = wk / abs(wk) * MIN_FLOAT;
				if (log(abs(wk)) > log(MAX_FLOAT)) wk = wk / abs(wk) * MAX_FLOAT;
				digit = (int) log10(abs(wk));
				val = wk / pow(10.0, digit);
				if ((int)abs(val) >= 10)
				{
					digit++;
					val = wk / pow(10.0, digit);
				}
				if ((int)abs(val) < 1)
				{
					digit--;
					val = wk / pow(10.0, digit);
				}
			}

			int prec;
			for (;;)
			{
				stringstream test;
				prec = 6;
				if (abs(digit) > 9)
					prec = 5;
				test << fixed << setprecision(prec) << val;
				REAL testval = abs(my_stod(test.str()));
				if (testval >= 10.0-1.0e-8)
				{
					digit++;
					val = wk / pow(10.0, digit);
				}
				else
					break;
			}

			stringstream ss;
			ss << fixed << setprecision(prec) << val;
			if (digit < 0)
				ss << "-";
			else
				ss << "+";
			ss << abs(digit);

			data.push_back(ss.str());
		}
		void setDataInt(int wk, vector<string>& data)
		{
			string buf = my_to_string(wk);
			if (buf.length() > 11)
			{
				cout << " Error in FMGENDFOutput::setDataInt " << endl;
				cout << buf << endl;
				exit(0);
			}
			data.push_back(buf);
		}
		bool is1dShieldXS(int mt)
		{
			vector<int>::iterator it;
			it = std::find(xs1d_shield.begin(), xs1d_shield.end(), mt);
			if (it == xs1d_shield.end()) return false;
			return true;
		}
		bool is2dShieldXS(int mt)
		{
			vector<int>::iterator it;
			it = std::find(xs2d_shield.begin(), xs2d_shield.end(), mt);
			if (it == xs2d_shield.end()) return false;
			return true;
		}
		void getNG2IG2LO(int mt, vector<int>& ng2, vector<int>& ig2lo)
		{
			int max_ng = dc->mg_max_num_energy;
			ng2.resize(max_ng);
			ig2lo.resize(max_ng);

			int num_bg = dc->xs_mg_2d_matrix[zaid][mt].size();
			int is = 0;
			int ie = max_ng - 1;
			for (int ig = 0; ig < max_ng; ig++)
			{
				REAL sum = 0.0;
				for (int igg = 0; igg < max_ng; igg++)
				{
					for (int ib = 0; ib < num_bg; ib++)
						sum += abs(dc->xs_mg_2d_matrix[zaid][mt][ib].get(ig,igg,0));
				}
				if (sum == 0.0)
				{
					ig2lo[ig] = 1;
					ng2[ig] = 2;
				}
				else
				{
					for (int igg = max_ng - 1; igg >= 0; igg--)
					{
						REAL val = 0.0;
						for (int ib = 0; ib < num_bg; ib++)
							val += abs(dc->xs_mg_2d_matrix[zaid][mt][ib].get(ig,igg,0));
						if (val != 0.0)
						{
							ie = igg;
							break;
						}
					}
					for (int igg = 0; igg < max_ng; igg++)
					{
						REAL val = 0.0;
						for (int ib = 0; ib < num_bg; ib++)
							val += abs(dc->xs_mg_2d_matrix[zaid][mt][ib].get(ig,igg,0));
						if (val != 0.0)
						{
							is = igg;
							break;
						}
					}
					ig2lo[ig] = max_ng - ie;
					ng2[ig] = ie - is + 2;
				}
			}
		}
	};
}
