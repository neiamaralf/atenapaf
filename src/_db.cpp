#include "vilavilela.h"

	wxString _DbRow::getstr(int icol){
		wxString str;icol--;
		if(icol<0||icol>=ncols)return wxEmptyString;
		cols[icol].getstr(&str);
		return str;
	}

	char* _DbRow::getcstr(int icol){
		static char str[256];*str=0;
		icol--;
		if(icol<0||icol>=ncols)return str;
		cols[icol].getcstr(str);
		return str;
	}