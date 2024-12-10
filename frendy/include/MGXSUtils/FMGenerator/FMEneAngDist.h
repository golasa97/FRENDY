//--------------------------------------------------------------------------
// FMEneAngDist.h : data to describe energy and angular distribution 
//
//--------------------------------------------------------------------------

#pragma once
#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include "MGXSUtils/FMGenerator/FMZlib.h"

namespace FMGen
{
	class FMEneAngDist
	{
		vector<int>				ene_index;

	public:
		int						max_ng;
		int						max_pl;
		vector<REAL>			ene_boundary;
		vector<REAL>			pdf;			//[max_ng]
		vector<vector<REAL> >	pl_coef;		//[max_ng][max_pl+1]

		FMEneAngDist()
		{
			clear();
		};
		~FMEneAngDist()
		{
		};

		void clear()
		{
			max_ng = 0;
			max_pl = 0;
			ene_boundary.clear();
			pdf.clear();
			for (int i = 0; i < static_cast<int>(pdf.size()); i++)
				pl_coef[i].clear();
			pl_coef.clear();
		};
		void resize(int ne)
		{
			max_ng = ne;
			ene_boundary.resize(max_ng + 1);
			for (int i = 0; i < max_ng + 1; i++)
				ene_boundary[i] = 0.0;

			pdf.resize(max_ng);
			for (int i = 0; i < max_ng; i++)
				pdf[i] = 0.0;
		};
		void add(REAL w, FMEneAngDist& ead)
		{
			for (int ie = 0; ie < max_ng; ie++)
			{
				pdf[ie] += ead.pdf[ie] * w;
				for (int il = 0; il <= max_pl; il++)
					pl_coef[ie][il] += ead.pl_coef[ie][il] * w;
			}
		}
		void resizePlCoef(int _max_pl)
		{
			max_pl = _max_pl;
			pl_coef.resize(max_ng);
			for (int i = 0; i < max_ng; i++)
			{
				pl_coef[i].resize(max_pl + 1);
				for (int j = 0; j <= max_pl; j++)
					pl_coef[i][j] = 0.0;
			}
		};
		void setZero()
		{
			for (int i = 0; i < max_ng; i++)
				pdf[i] = 0.0;
			for (int i = 0; i < max_ng; i++)
			{
				for (int j = 0; j <= max_pl; j++)
					pl_coef[i][j] = 0.0;
			}
		};
		int getEnergyGroup(REAL e)
		{
			int ibe = -1;
#if 0
			for (int i = 0; i < max_ng; i++)
			{
				if (e <= ene_boundary[i] && e >= ene_boundary[i + 1])
				{
					ibe = i;
					break;
				}
			}
#else
			int offset = -1;
			for (int i = 0; i < (int)ene_index.size() - 1; i++)
			{
				int i0 = ene_index[i];
				int i1 = ene_index[i+1];
				if (e <= ene_boundary[i0] && e >= ene_boundary[i1])
				{
					offset = i;
					break;
				}
			}
			if (offset < 0)
			{
				cout << " energy is out of range in  FMEneAngDist " << endl;
				cout << " lower energy " << ene_boundary.back() << endl;
				cout << " upper energy " << ene_boundary[0] << endl;
				cout << " current energy " << e << endl;
				exit(0);
			}
			for (int i = ene_index[offset]; i < ene_index[offset+1]; i++)
			{
				if (e <= ene_boundary[i] && e >= ene_boundary[i+1])
				{
					ibe = i;
					break;
				}
			}
#endif
			if (ibe < 0)
			{
				cout << " energy is out of range in  FMEneAngDist " << endl;
				cout << " lower energy " << ene_boundary.back() << endl;
				cout << " upper energy " << ene_boundary[0] << endl;
				cout << " current energy " << e << endl;
				exit(0);
			}

			return ibe;
		};
		void setEnergyBoundary(vector<REAL>& _ene_boundary)
		{
			for (int i = 0; i < max_ng + 1; i++)
				ene_boundary[i] = _ene_boundary[i];

			ene_index.clear();
			int wk = (int)sqrt(max_ng);
			if (wk < 1) wk = 1;
			ene_index.resize(wk + 1);
			for (int i = 0; i < wk; i++)
				ene_index[i] = i * wk;
			ene_index[wk] = max_ng;
		}
		void normalize()
		{
			REAL sum = 0.0;
			for (int i = 0; i < max_ng; i++)
				sum += pdf[i];
			if (sum != 0.0)
			{
				for (int i = 0; i < max_ng; i++)
				{
					pdf[i] /= sum;
					for (int j = 0; j <= max_pl; j++)
						pl_coef[i][j] /= sum;
				}
			}
		}
		REAL getPdfSum()
		{
			REAL sum = 0.0;
			for (int i = 0; i < max_ng; i++)
				sum += pdf[i];
			return sum;
		}
		void dumpPdfPerEnergy()
		{
			for (int i = 0; i < max_ng; i++)
			{
				cout << setw(5) << i;
				cout << setw(15) << setprecision(4) << pdf[i] / (ene_boundary[i] - ene_boundary[i + 1]) << endl;
			}
		}
		void dumpPdf()
		{
			for (int i = 0; i < max_ng; i++)
			{
				cout << setw(5) << i;
				cout << setw(15) << setprecision(4) << pdf[i] << endl;
			}
		}
		void dumpPlCoef()
		{
			for (int il = 0; il <= max_pl; il++)
			{
				cout << " il = " << il << endl;
				for (int i = 0; i < max_ng; i++)
				{
					cout << setw(5) << i;
					cout << setw(15) << setprecision(4) << scientific << ene_boundary[i];
					cout << setw(15) << setprecision(4) << scientific << ene_boundary[i + 1];
					cout << setw(15) << setprecision(4) << scientific << pl_coef[i][il] << endl;
				}
			}
		}
	};
}
