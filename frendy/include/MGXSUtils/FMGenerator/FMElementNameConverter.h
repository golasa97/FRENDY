//--------------------------------------------------------------------------
// FMElementNameConverter.h : convert atomic numer to element name 
//
//--------------------------------------------------------------------------

#pragma once

#include "MGXSUtils/FMGenerator/FMGenerator_global.h"
#include "MGXSUtils/FMGenerator/FMZlib.h"

namespace FMGen
{
	class FMElementNameConverter
	{
	private:


	public:
		FMElementNameConverter() {};
		~FMElementNameConverter() {};
		string getName(int z)
		{
			//const int line = 118;
			const string element_name[] = {
				"H",
				"He",
				"Li",
				"Be",
				"B",
				"C",
				"N",
				"O",
				"F",
				"Ne",
				"Na",
				"Mg",
				"Al",
				"Si",
				"P",
				"S",
				"Cl",
				"Ar",
				"K",
				"Ca",
				"Sc",
				"Ti",
				"V",
				"Cr",
				"Mn",
				"Fe",
				"Co",
				"Ni",
				"Cu",
				"Zn",
				"Ga",
				"Ge",
				"As",
				"Se",
				"Br",
				"Kr",
				"Rb",
				"Sr",
				"Y",
				"Zr",
				"Nb",
				"Mo",
				"Tc",
				"Ru",
				"Rh",
				"Pd",
				"Ag",
				"Cd",
				"In",
				"Sn",
				"Sb",
				"Te",
				"I",
				"Xe",
				"Cs",
				"Ba",
				"La",
				"Ce",
				"Pr",
				"Nd",
				"Pm",
				"Sm",
				"Eu",
				"Gd",
				"Tb",
				"Dy",
				"Ho",
				"Er",
				"Tm",
				"Yb",
				"Lu",
				"Hf",
				"Ta",
				"W",
				"Re",
				"Os",
				"Ir",
				"Pt",
				"Au",
				"Hg",
				"Tl",
				"Pb",
				"Bi",
				"Po",
				"At",
				"Rn",
				"Fr",
				"Ra",
				"Ac",
				"Th",
				"Pa",
				"U",
				"Np",
				"Pu",
				"Am",
				"Cm",
				"Bk",
				"Cf",
				"Es",
				"Fm",
				"Md",
				"No",
				"Lr",
				"Rf",
				"Db",
				"Sg",
				"Bh",
				"Hs",
				"Mt",
				"Ds",
				"Rg",
				"Cn",
				"Nh",
				"Fl",
				"Mc",
				"Lv",
				"Ts",
				"Og"
			};

			if (z < 1 || z > 118) return "";

			return element_name[z - 1];
		}
	};
}
