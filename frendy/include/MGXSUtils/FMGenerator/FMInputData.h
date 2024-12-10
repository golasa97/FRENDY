//----------------------------------------------------------------
// FMInputData.h  : processing of input data for multi-group xs
//
//----------------------------------------------------------------

#pragma once

#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include <fstream>
#include <sstream>

namespace FMGen
{
	class FMInputData
	{
	private:
		ifstream					fin;
		vector< vector<string> >	_data;
		int							pos;

		void readLine(vector<string>& buf_vec, string inp="")
		{
			buf_vec.clear();

			string buf, wk;

			if (inp.length() == 0)
				getline(fin, buf);
			else
				buf = inp;

			// delete comment
			int n = buf.find("//");
			if (n != static_cast<int>(string::npos))
			{
				int m = buf.size();
				buf.erase(n, m - n);
			}

			// replace "," by " "
			for (;;)
			{
				n = buf.find(",");
				if (n != static_cast<int>(string::npos))
					buf[n] = ' ';
				else
					break;
			}

			// replace tab by space
			for (;;)
			{
				n = buf.find('\t');
				if (n != static_cast<int>(string::npos))
					buf[n] = ' ';
				else
					break;
			}

			// replace carriage-return for DOS
			for (;;)
			{
				n = buf.find('\r');
				if (n != static_cast<int>(string::npos))
					buf[n] = ' ';
				else
					break;
			}

			// delete space at the end of line
			int bufsize = buf.size() - 1;
			for (int i = bufsize; i >= 0; i--)
			{
				if (buf[i] != ' ')
					break;
				else
					buf.erase(i, 1);
			}

			// split into token
			istringstream strin(buf);
			while (!strin.eof())
			{
				strin >> wk;
				if (wk.size() != 0)
					buf_vec.push_back(wk);
			}
		}


	public:
		FMInputData( )
		{
			this->clear();
		}

		~FMInputData()
		{
			fin.close();
		}
		void clear()
		{
			fin.clear();;
			pos = 0;
			_data.clear();
		}
		void readDataFromFile(string fname)
		{
			fin.open(fname.c_str());
			if (!fin)
			{
				cout << " Error while open input data " << endl;
				cout << " File name : " << fname << endl;
				exit(0);
			}

			vector<string> buf_vec;
			_data.clear();

			//readin input data
			while (!fin.eof())
			{
				readLine(buf_vec);
				if (buf_vec.size() != 0)
					_data.push_back(buf_vec);
			}
			fin.close();
		}

		void setDataFromMap(map<string, vector<string> >& _inp)
		{
			vector<string> buf_vec;

			map<string, vector<string> >::iterator it;
			for (it = _inp.begin(); it != _inp.end(); it++)
			{
				vector<string> wk;
				wk.push_back(it->first);
				_data.push_back(wk);
				wk.clear();

				for (int i = 0; i < static_cast<int>(it->second.size()); i++)
				{
					readLine(buf_vec, it->second[i]);
					_data.push_back(buf_vec);
				}
			}
			buf_vec.clear();
			buf_vec.push_back("end_mg");

			_data.push_back(buf_vec);
#if 1
			ofstream of;
			of.open("FMAlternateInputData.txt");
			for (int i = 0; i < static_cast<int>(_data.size()); i++)
			{
				for (int ii = 0; ii < static_cast<int>(_data[i].size()); ii++)
					of << _data[i][ii] << " ";
				of << endl;
			}
			of.close();
#endif
		}

		void rewind()
		{
			pos = 0;
		}

		void skip(int n)
		{
			pos += n;
		}

		void next()
		{
			pos++;
		}

		void prev()
		{
			pos--;
		}

		bool findBlock(string keyword, int sta = -1)
		{
			bool exist = false;
			if (sta < 0)
				sta = pos;
			else
				pos = sta;
			for (int i = sta; i < static_cast<int>(_data.size()); i++)
			{
				if (keyword == _data[i][0])
				{
					pos = i + 1;
					exist = true;
					break;
				}
			}
			return exist;
		}

		void getData(vector<string>& buf_vec)
		{
			if (pos >= static_cast<int>(_data.size()))
			{
				buf_vec.clear();
				return;
			}
			buf_vec = _data[pos];
			pos++;
		}
		bool isEndOfBlock(string key)
		{
			vector<string> list;
			list.push_back("ultra_fine_group");
			list.push_back("multi_group");
			list.push_back("default_spectrum");
			list.push_back("material");
			list.push_back("endf_id");
			list.push_back("ace_file");
			list.push_back("calc_cond");
			list.push_back("reso_upscat");
			list.push_back("thermal_cutoff");
			list.push_back("thermal_sab");
			list.push_back("bg_xs_set");
			list.push_back("edit_xs");
			list.push_back("max_pl");
			list.push_back("end_mg");
			list.push_back("potential_xs");
			list.push_back("file_add_name");

			for (int i = 0; i < static_cast<int>(list.size()); i++)
			{
				string s1 = list[i];
				string s2 = key;
				transform(s1.begin(), s1.end(), s1.begin(), (int(*)(int)) toupper);
				transform(s2.begin(), s2.end(), s2.begin(), (int(*)(int)) toupper);
				if (s1 == s2) return true;
			}

			return false;
		}

	};
}
