//----------------------------------------------------------------
// FMCompressedMatrix.h  : store 2D cross section in sparse format
//
//----------------------------------------------------------------

#pragma once

#include "MGXSUtils/FMGenerator/FMGenerator_global.h"

namespace FMGen
{
	class FMCompressedMatrix
	{
	private:
		vector<int>		ista;
		vector<int>		iend;
		int				max_ng;
		int				max_pl;
		vector<vector<REAL> >	data;

	public:

		FMCompressedMatrix()
		{
			clear();
		};
		~FMCompressedMatrix()
		{
			clear();
		};

		void clear()
		{
			ista.clear();
			iend.clear();
			max_ng = 0;
			max_pl = 0;
			for (int i = 0; i < (int)data.size(); i++)
				data[i].clear();
			data.clear();
		}
#if 0
		FMCompressedMatrix& operator = (const FMCompressedMatrix& _p)
		{
			clear();

			max_ng = _p.max_ng;
			max_pl = _p.max_pl;

			ista.resize(_p.ista.size());
			for (int i = 0; i < (int)_p.ista.size(); i++)
				ista[i] = _p.ista[i];

			iend.resize(_p.iend.size());
			for (int i = 0; i < (int)_p.iend.size(); i++)
				iend[i] = _p.iend[i];

			data.resize(_p.data.size());
			for (int i = 0; i < (int)_p.data.size(); i++)
			{
				data[i].resize(_p.data[i].size());
				for (int ii = 0; ii < (int)_p.data[i].size(); ii++)
					data[i][ii] = _p.data[i][ii];
			}

			return *this;
		}
#endif
		void set(vector<vector<vector<REAL> > >& _data)
		{
			max_ng = _data.size();
			max_pl = _data[0][0].size() - 1;
			ista.resize(max_ng);
			iend.resize(max_ng);
			data.resize(max_ng);
			for (int ig = 0; ig < max_ng; ig++)
			{
				//search start group
				ista[ig] = -1;
				for (int iig = 0; iig < max_ng; iig++)
				{
					REAL val = 0.0;
					for (int il = 0; il <= max_pl; il++)
						val += abs(_data[ig][iig][il]);
					if (val != 0.0)
					{
						ista[ig] = iig;
						break;
					}
				}

				//search end group
				iend[ig] = -1;
				for (int iig = max_ng - 1; iig >= 0; iig--)
				{
					REAL val = 0.0;
					for (int il = 0; il <= max_pl; il++)
						val += abs(_data[ig][iig][il]);
					if (val != 0.0)
					{
						iend[ig] = iig;
						break;
					}
				}

				//pack data
				vector<REAL> vec;
				if (ista[ig] != -1)
				{
					int len = iend[ig] - ista[ig] + 1;
					vec.resize(len * (max_pl + 1));
					for (int i = 0; i < len; i++)
						vec[i] = 0.0;
					for (int il = 0; il <= max_pl; il++)
					{
						for (int iig = ista[ig]; iig <= iend[ig]; iig++)
						{
							int loc = il * len + iig - ista[ig];
							vec[loc] = _data[ig][iig][il];
						}
					}
					data[ig] = vec;
				}
			}
		}
		REAL get(int ig, int iig, int il)
		{
			REAL val = 0.0;
			if (iig < ista[ig]) return 0.0;
			if (iig > iend[ig]) return 0.0;
			if (il > max_pl) return 0.0;

			int len = iend[ig] - ista[ig] + 1;
			int loc = il * len + iig - ista[ig];
			val = data[ig][loc];

			return val;
		}
		REAL* getPointer(int ig, int iig, int il)
		{
			if (iig < ista[ig]) return NULL;
			if (iig > iend[ig]) return NULL;
			if (il > max_pl) return NULL;

			int len = iend[ig] - ista[ig] + 1;
			int loc = il * len + iig - ista[ig];
			return &data[ig][loc];
		}
		void get(vector<vector<vector<REAL> > >& vec)
		{
			vec.resize(max_ng);
			for (int i = 0; i < max_ng; i++)
			{
				vec[i].resize(max_ng);
				for (int ii = 0; ii < max_ng; ii++)
				{
					vec[i][ii].resize(max_pl + 1);
					for (int il = 0; il <= max_pl; il++)
						vec[i][ii][il] = get(i, ii, il);
				}
			}
		}
		void multiply (int ig, int iig, int il, REAL fact)
		{
			if (iig < ista[ig]) return;
			if (iig > iend[ig]) return;
			if (il > max_pl) return;

			int len = iend[ig] - ista[ig] + 1;
			int loc = il * len + iig - ista[ig];
			data[ig][loc] *= fact;
		}
		bool isZero2dXS()
		{
			REAL sum = 0.0;
			for (int i = 0; i < max_ng; i++)
				for (int ii = 0; ii < max_ng; ii++)
					sum += get(i,ii,0);

			if (sum == 0.0)
				return true;
			else
				return false;
		}
		int getMaxPl()
		{
			return max_pl;
		}
		int getMaxNG()
		{
			return max_ng;
		}
	};
}
