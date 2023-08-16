#include "vilavilela.h"
#include "wx/dc.h"



#define DEL 200
#define FNC3 201
#define FNC2 202
#define Shift_B 203
#define Shift_A 203
#define Code_C 204
#define Code_B 205
#define FNC4B 205
#define FNC4 206
#define Code_A 206
#define FNC1 207
#define Start_A 208
#define Start_B 209
#define Start_C 210
#define Stop 211

unsigned int returnbarcodemask ( int codetype,unsigned char c,unsigned char c2=0,bool left=true,bool gcode=false ) {
	if ( codetype==CODE_3_9 ) {
		switch ( c ) {
		case ' ':
			return 0x9AD;
		case '$':
			return 0x925;
		case '%':
			return 0xA49;
		case '*':
			return 0x96D;
		case '+':
			return 0x949;
		case '-':
			return 0x95B;
		case '.':
			return 0xCAD;
		case '/':
			return 0x929;
		case '0':
			return 0xA6D;
		case '1':
			return 0xD2B;
		case '2':
			return 0xB2B;
		case '3':
			return 0xD95;
		case '4':
			return 0xA6B;
		case '5':
			return 0xD35;
		case '6':
			return 0xB35;
		case '7':
			return 0xA5B;
		case '8':
			return 0xD2D;
		case '9':
			return 0xB2D;
		case 'A':
			return 0xD4B;
		case 'B':
			return 0xB4B;
		case 'C':
			return 0xDA5;
		case 'D':
			return 0xACB;
		case 'E':
			return 0xD65;
		case 'F':
			return 0xB65;
		case 'G':
			return 0xA9B;
		case 'H':
			return 0xD4D;
		case 'I':
			return 0xB4D;
		case 'J':
			return 0xACD;
		case 'K':
			return 0xD53;
		case 'L':
			return 0xB53;
		case 'M':
			return 0xDA9;
		case 'N':
			return 0xAD3;
		case 'O':
			return 0xD69;
		case 'P':
			return 0xB69;
		case 'Q':
			return 0xAB3;
		case 'R':
			return 0xD59;
		case 'S':
			return 0xB59;
		case 'T':
			return 0xAD9;
		case 'U':
			return 0xCAB;
		case 'V':
			return 0x9AB;
		case 'W':
			return 0xCD5;
		case 'X':
			return 0x96B;
		case 'Y':
			return 0xCB5;
		case 'Z':
			return 0x9B5;
		}
	} else if ( codetype==CODE_128_A ) {
		switch ( c ) {
		case ' ':
			return 0x6cc;
		case '!':
			return 0x66c;
		case '"':
			return 0x666;
		case '#':
			return 0x498;
		case '$':
			return 0x48c;
		case '%':
			return 0x44c;
		case '&':
			return 0x4c8;
		case '`':
			return 0x4c4;
		case '(':
			return 0x464;
		case ')':
			return 0x648;
		case '*':
			return 0x644;
		case '+':
			return 0x624;
		case ',':
			return 0x59c;
		case '-':
			return 0x4dc;
		case '.':
			return 0x4ce;
		case '/':
			return 0x5cc;
		case '0':
			return 0x4ec;
		case '1':
			return 0x4e6;
		case '2':
			return 0x672;
		case '3':
			return 0x65c;
		case '4':
			return 0x64e;
		case '5':
			return 0x6e4;
		case '6':
			return 0x674;
		case '7':
			return 0x76e;
		case '8':
			return 0x74c;
		case '9':
			return 0x72c;
		case ':':
			return 0x726;
		case ';':
			return 0x764;
		case '<':
			return 0x734;
		case '=':
			return 0x732;
		case '>':
			return 0x6d8;
		case '?':
			return 0x6c6;
		case '@':
			return 0x636;
		case 'A':
			return 0x518;
		case 'B':
			return 0x458;
		case 'C':
			return 0x446;
		case 'D':
			return 0x588;
		case 'E':
			return 0x468;
		case 'F':
			return 0x462;
		case 'G':
			return 0x688;
		case 'H':
			return 0x628;
		case 'I':
			return 0x622;
		case 'J':
			return 0x5b8;
		case 'K':
			return 0x58e;
		case 'L':
			return 0x46e;
		case 'M':
			return 0x5d8;
		case 'N':
			return 0x5c6;
		case 'O':
			return 0x476;
		case 'P':
			return 0x776;
		case 'Q':
			return 0x68e;
		case 'R':
			return 0x62e;
		case 'S':
			return 0x6e8;
		case 'T':
			return 0x6e2;
		case 'U':
			return 0x6ee;
		case 'V':
			return 0x758;
		case 'W':
			return 0x746;
		case 'X':
			return 0x716;
		case 'Y':
			return 0x768;
		case 'Z':
			return 0x762;
		case '[':
			return 0x71a;
		case '\\':
			return 0x77a;
		case ']':
			return 0x642;
		case '^':
			return 0x78a;
		case '_':
			return 0x530;
		case 0:
			return 0x50c;
		case 1:
			return 0x4b0;
		case 2:
			return 0x486;
		case 3:
			return 0x42c;
		case 4:
			return 0x426;
		case 5:
			return 0x590;
		case 6:
			return 0x584;
		case 7:
			return 0x4d0;
		case 8:
			return 0x4c2;
		case 9:
			return 0x434;
		case 10:
			return 0x432;
		case 11:
			return 0x612;
		case 12:
			return 0x650;
		case 13:
			return 0x7ba;
		case 14:
			return 0x614;
		case 15:
			return 0x47a;
		case 16:
			return 0x53c;
		case 17:
			return 0x4bc;
		case 18:
			return 0x49e;
		case 19:
			return 0x5e4;
		case 20:
			return 0x4f4;
		case 21:
			return 0x4f2;
		case 22:
			return 0x7a4;
		case 23:
			return 0x794;
		case 24:
			return 0x792;
		case 25:
			return 0x6de;
		case 26:
			return 0x6f6;
		case 27:
			return 0x7b6;
		case 28:
			return 0x578;
		case 29:
			return 0x51e;
		case 30:
			return 0x45e;
		case 31:
			return 0x5e8;
		case FNC3:
			return 0x5e2;
		case FNC2:
			return 0x7a8;
		case Shift_B:
			return 0x7a2;
		case Code_C:
			return 0x5de;
		case Code_B:
			return 0x5ee;
		case FNC4:
			return 0x75e;
		case FNC1:
			return 0x7ae;
		case Start_A:
			return 0x684;
		case Start_B:
			return 0x690;
		case Start_C:
			return 0x69c;
		case Stop:
			return 0x18EB;
		}
	} else if ( codetype==CODE_128_B ) {
		switch ( c ) {
		case ' ':
			return 0x6cc;
		case '!':
			return 0x66c;
		case '"':
			return 0x666;
		case '#':
			return 0x498;
		case '$':
			return 0x48c;
		case '%':
			return 0x44c;
		case '&':
			return 0x4c8;
		case '\'':
			return 0x4c4;
		case '(':
			return 0x464;
		case ')':
			return 0x648;
		case '*':
			return 0x644;
		case '+':
			return 0x624;
		case ',':
			return 0x59c;
		case '-':
			return 0x4dc;
		case '.':
			return 0x4ce;
		case '/':
			return 0x5cc;
		case '0':
			return 0x4ec;
		case '1':
			return 0x4e6;
		case '2':
			return 0x672;
		case '3':
			return 0x65c;
		case '4':
			return 0x64e;
		case '5':
			return 0x6e4;
		case '6':
			return 0x674;
		case '7':
			return 0x76e;
		case '8':
			return 0x74c;
		case '9':
			return 0x72c;
		case ':':
			return 0x726;
		case ';':
			return 0x764;
		case '<':
			return 0x734;
		case '=':
			return 0x732;
		case '>':
			return 0x6d8;
		case '?':
			return 0x6c6;
		case '@':
			return 0x636;
		case 'A':
			return 0x518;
		case 'B':
			return 0x458;
		case 'C':
			return 0x446;
		case 'D':
			return 0x588;
		case 'E':
			return 0x468;
		case 'F':
			return 0x462;
		case 'G':
			return 0x688;
		case 'H':
			return 0x628;
		case 'I':
			return 0x622;
		case 'J':
			return 0x5b8;
		case 'K':
			return 0x58e;
		case 'L':
			return 0x46e;
		case 'M':
			return 0x5d8;
		case 'N':
			return 0x5c6;
		case 'O':
			return 0x476;
		case 'P':
			return 0x776;
		case 'Q':
			return 0x68e;
		case 'R':
			return 0x62e;
		case 'S':
			return 0x6e8;
		case 'T':
			return 0x6e2;
		case 'U':
			return 0x6ee;
		case 'V':
			return 0x758;
		case 'W':
			return 0x746;
		case 'X':
			return 0x716;
		case 'Y':
			return 0x768;
		case 'Z':
			return 0x762;
		case '[':
			return 0x71a;
		case '\\':
			return 0x77a;
		case ']':
			return 0x642;
		case '^':
			return 0x78a;
		case '_':
			return 0x530;
		case '`':
			return 0x50c;
		case 'a':
			return 0x4b0;
		case 'b':
			return 0x486;
		case 'c':
			return 0x42c;
		case 'd':
			return 0x426;
		case 'e':
			return 0x590;
		case 'f':
			return 0x584;
		case 'g':
			return 0x4d0;
		case 'h':
			return 0x4c2;
		case 'i':
			return 0x434;
		case 'j':
			return 0x432;
		case 'k':
			return 0x612;
		case 'l':
			return 0x650;
		case 'm':
			return 0x7ba;
		case 'n':
			return 0x614;
		case 'o':
			return 0x47a;
		case 'p':
			return 0x53c;
		case 'q':
			return 0x4bc;
		case 'r':
			return 0x49e;
		case 's':
			return 0x5e4;
		case 't':
			return 0x4f4;
		case 'u':
			return 0x4f2;
		case 'v':
			return 0x7a4;
		case 'w':
			return 0x794;
		case 'x':
			return 0x792;
		case 'y':
			return 0x6de;
		case 'z':
			return 0x6f6;
		case '{':
			return 0x7b6;
		case '|':
			return 0x578;
		case '}':
			return 0x51e;
		case '~':
			return 0x45e;
		case DEL:
			return 0x5e8;
		case FNC3:
			return 0x5e2;
		case FNC2:
			return 0x7a8;
		case Shift_A:
			return 0x7a2;
		case Code_C:
			return 0x5de;
		case FNC4B:
			return 0x5ee;
		case Code_A:
			return 0x75e;
		case FNC1:
			return 0x7ae;
		case Start_A:
			return 0x684;
		case Start_B:
			return 0x690;
		case Start_C:
			return 0x69c;
		case Stop:
			return 0x18EB;
		}
	} else if ( codetype==CODE_128_C ) {
		switch ( c ) {
		case '0':
			switch ( c2 ) {
			case '0':
				return 0x6cc;
			case '1':
				return 0x66c;
			case '2':
				return 0x666;
			case '3':
				return 0x498;
			case '4':
				return 0x48c;
			case '5':
				return 0x44c;
			case '6':
				return 0x4c8;
			case '7':
				return 0x4c4;
			case '8':
				return 0x464;
			case '9':
				return 0x648;
			}
		case '1':
			switch ( c2 ) {
			case '0':
				return 0x644;
			case '1':
				return 0x624;
			case '2':
				return 0x59c;
			case '3':
				return 0x4dc;
			case '4':
				return 0x4ce;
			case '5':
				return 0x5cc;
			case '6':
				return 0x4ec;
			case '7':
				return 0x4e6;
			case '8':
				return 0x672;
			case '9':
				return 0x65c;
			}
		case '2':
			switch ( c2 ) {
			case '0':
				return 0x64e;
			case '1':
				return 0x6e4;
			case '2':
				return 0x674;
			case '3':
				return 0x76e;
			case '4':
				return 0x74c;
			case '5':
				return 0x72c;
			case '6':
				return 0x726;
			case '7':
				return 0x764;
			case '8':
				return 0x734;
			case '9':
				return 0x732;
			}
		case '3':
			switch ( c2 ) {
			case '0':
				return 0x6d8;
			case '1':
				return 0x6c6;
			case '2':
				return 0x636;
			case '3':
				return 0x518;
			case '4':
				return 0x458;
			case '5':
				return 0x446;
			case '6':
				return 0x588;
			case '7':
				return 0x468;
			case '8':
				return 0x462;
			case '9':
				return 0x688;
			}
		case '4':
			switch ( c2 ) {
			case '0':
				return 0x628;
			case '1':
				return 0x622;
			case '2':
				return 0x5b8;
			case '3':
				return 0x58e;
			case '4':
				return 0x46e;
			case '5':
				return 0x5d8;
			case '6':
				return 0x5c6;
			case '7':
				return 0x476;
			case '8':
				return 0x776;
			case '9':
				return 0x68e;
			}
		case '5':
			switch ( c2 ) {
			case '0':
				return 0x62e;
			case '1':
				return 0x6e8;
			case '2':
				return 0x6e2;
			case '3':
				return 0x6ee;
			case '4':
				return 0x758;
			case '5':
				return 0x746;
			case '6':
				return 0x716;
			case '7':
				return 0x768;
			case '8':
				return 0x762;
			case '9':
				return 0x71a;
			}
		case '6':
			switch ( c2 ) {
			case '0':
				return 0x77a;
			case '1':
				return 0x642;
			case '2':
				return 0x78a;
			case '3':
				return 0x530;
			case '4':
				return 0x50c;
			case '5':
				return 0x4b0;
			case '6':
				return 0x486;
			case '7':
				return 0x42c;
			case '8':
				return 0x426;
			case '9':
				return 0x590;
			}
		case '7':
			switch ( c2 ) {
			case '0':
				return 0x584;
			case '1':
				return 0x4d0;
			case '2':
				return 0x4c2;
			case '3':
				return 0x434;
			case '4':
				return 0x432;
			case '5':
				return 0x612;
			case '6':
				return 0x650;
			case '7':
				return 0x7ba;
			case '8':
				return 0x614;
			case '9':
				return 0x47a;
			}
		case '8':
			switch ( c2 ) {
			case '0':
				return 0x53c;
			case '1':
				return 0x4bc;
			case '2':
				return 0x49e;
			case '3':
				return 0x5e4;
			case '4':
				return 0x4f4;
			case '5':
				return 0x4f2;
			case '6':
				return 0x7a4;
			case '7':
				return 0x794;
			case '8':
				return 0x792;
			case '9':
				return 0x6de;
			}
		case '9':
			switch ( c2 ) {
			case '0':
				return 0x6f6;
			case '1':
				return 0x7b6;
			case '2':
				return 0x578;
			case '3':
				return 0x51e;
			case '4':
				return 0x45e;
			case '5':
				return 0x5e8;
			case '6':
				return 0x5e2;
			case '7':
				return 0x7a8;
			case '8':
				return 0x7a2;
			case '9':
				return 0x5de;
			}
		case Code_B:
			return 0x5ee;
		case Code_A:
			return 0x75e;
		case FNC1:
			return 0x7ae;
		case Start_A:
			return 0x684;
		case Start_B:
			return 0x690;
		case Start_C:
			return 0x69c;
		case Stop:
			return 0x18EB;
		}
	} else if ( codetype==CODE_UPC_A || codetype==CODE_EAN_13|| codetype==CODE_EAN_8) {
		unsigned int ret;
		switch ( c ) {
		case '0':
			ret=0xd;
			break;
		case '1':
			ret=0x19;
			break;
		case '2':
			ret=0x13;
			break;
		case '3':
			ret=0x3D;
			break;
		case '4':
			ret=0x23;
			break;
		case '5':
			ret=0x31;
			break;
		case '6':
			ret=0x2F;
			break;
		case '7':
			ret=0x3B;
			break;
		case '8':
			ret=0x37;
			break;
		case '9':
			ret=0xB;
			break;
		case 0x0a:
			return 0x0a;
		case 0x5:
			return 0x5;
			break;
		}
		if ( !left ){
			ret= ( ~ret ) &0x7f;
			
		}
		else if ( gcode){
			ret= ( ~ret ) &0x7f;
				unsigned int tret=ret;
				ret=0;
				for(int i=0;i<7;i++)
					ret|=(((tret&(1<<(6-i)))>>(6-i))<<i)&(1<<i);
			}
		return ret;
	}
	return 0;
}

int returnvalcode128C ( unsigned char c,unsigned char c2 ) {
	char ret[3]="";
	ret[0]=c;
	ret[1]=c2;
	return atoi ( ret );
}

void printbarcodechar ( wxDC *dc,int codetype,double ppmmX,double ppmmY,double x0,double y0,double yf,double largbarra,
																								unsigned char c,unsigned char c2=0,bool left=true,bool gcode=false  ) {
#define _X(_x) (int)ceil((_x)*ppmmX)
#define _Y(_y) (int)ceil((_y)*ppmmY)
	int nchar,x;
	double xx;
	unsigned int bc;
	switch ( codetype ) {
	case CODE_3_9:
		nchar=12;
		break;
	case CODE_128_A:
	case CODE_128_B:
	case CODE_128_C:
		if ( c==Stop )
			nchar=13;
		else
			nchar=11;
		break;
	case CODE_UPC_A:case CODE_EAN_13:case CODE_EAN_8:
		if ( c==0x5 ) nchar=3;
		else if ( c==0xa ) nchar=5;
		else		nchar=7;
		break;
	}
	bc=returnbarcodemask ( codetype,c,c2,left ,gcode);
	int cx,cy0=_Y ( y0 ),cyf=_Y ( yf );
	for ( x=nchar-1,xx=0;x>=0;x--,xx+=largbarra ) {
		if ( bc& ( 0x01<<x ) ) {
			cx=_X ( x0+xx );
			dc->DrawLine ( cx, cy0, cx, cyf );
		}
	}
}

bool isgcode(char key,int i){
	switch(key){
		case '0':return false;
		case '1':	return(i==2||i==4||i==5);	
		case '2':	return(i==2||i==3||i==5);		
		case '3':	return(i==2||i==3||i==4);		
		case '4':	return(i==1||i==4||i==5);		
		case '5':	return(i==1||i==2||i==5);		
		case '6':	return(i==1||i==2||i==3);		
		case '7':	return(i==1||i==3||i==5);		
		case '8':	return(i==1||i==3||i==4);		
		case '9':	return(i==1||i==2||i==4);	
		default: break;
	}
	return false;
}

void printbarcodechar ( wxDC *dc,int codetype,double ppmmX,double ppmmY,double x0,double y0,double yf,double largbarra,const char *str ,const char *toptext ) {
	double delx,dx;
	wxString txt;
	wxSize sztxt;
	int cxtxt,orgx0=x0;

	switch ( codetype ) {
	case CODE_3_9: {
			int strlengh=strlen ( str );
			dx=largbarra/ ( 25.0+strlengh*13.0 );
			wxPen penl=wxPen ( *wxBLACK,_X ( dx ),wxSOLID );
			penl.SetCap ( wxCAP_BUTT );
			dc->SetPen ( penl );
			delx=dx*13;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,'*' );
			x0+=delx;
			for ( unsigned int i=0;i<strlen ( str );i++ ) {
				printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,str[i] );
				x0+=delx;
			}
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,'*' );
		}
		txt=wxString::FromAscii(str );
		sztxt=dc->GetTextExtent ( txt );
		cxtxt=_X ( orgx0 ) + ( _X ( largbarra )-sztxt.GetWidth() ) *0.5;
		dc->SetPen ( *wxWHITE_PEN );
		dc->DrawRectangle ( cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5,sztxt.GetWidth(),sztxt.GetHeight() );
		dc->DrawText ( txt,cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5 );
		break;
	case CODE_UPC_A: {
			char strupc[13]="00000000000",*ptrc=strupc+11-strlen ( str );
			sprintf ( ptrc,"%s",str );
			dx=largbarra/ ( 95.0 );
			wxPen penl=wxPen ( *wxBLACK,_X ( dx ),wxSOLID );
			penl.SetCap ( wxCAP_BUTT );
			dc->SetPen ( penl );
			delx=dx*7;
			int checksum=0;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,0x5 );
			x0+=3*dx;
			for ( int i=0;i<11;i++ ) {
				if ( ( ( i+1 ) %2 ) ==0 ) checksum+=returnvalcode128C ( strupc[i],0 );
				else checksum+=returnvalcode128C ( strupc[i],0 ) *3;
				printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,strupc[i],0,i<=5 );
				x0+=delx;
				if ( i==5 ) {
					printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,0xa );
					x0+=5.0*dx;
				}
			}
			checksum=checksum%10;
			if ( checksum!=0 )
				checksum=10-checksum;
			checksum+=48;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,checksum,0,false );
			x0+=delx;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,0x5 );
			txt=wxString::FromAscii(strupc );
			sztxt=dc->GetTextExtent ( txt );
			cxtxt=_X ( orgx0 ) + ( _X ( largbarra )-sztxt.GetWidth() ) *0.5;
			dc->SetPen ( *wxWHITE_PEN );
			dc->DrawRectangle ( cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5,sztxt.GetWidth(),sztxt.GetHeight() );
			dc->DrawText ( txt,cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5 );
		}
		break;
	case CODE_EAN_13: {
			char strupc[13]="000000000000", *ptrc=strupc+12-strlen(str);
			sprintf ( ptrc,"%s",str );
			dx=largbarra/ ( 95.0 );
			wxPen penl=wxPen ( *wxBLACK,_X ( dx ),wxSOLID );
			penl.SetCap ( wxCAP_BUTT );
			dc->SetPen ( penl );
			delx=dx*7;
			int checksum=0;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,0x5 );
			x0+=3*dx;
			for ( int i=0;i<12;i++ ) {
				
				if ( ( ( i+1 ) %2 ) ==0 ) checksum+=returnvalcode128C ( strupc[i],0 );
				else checksum+=returnvalcode128C ( strupc[i],0 ) *3;
				if(i>0){
				printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,strupc[i],0,i<=6,isgcode(strupc[0], i-1) );
				x0+=delx;}
				if ( i==6 ) {
					printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,0xa );
					x0+=5.0*dx;
				}
			}
			checksum=checksum%10;
			if ( checksum!=0 )
				checksum=10-checksum;
			checksum+=48;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,checksum,0,false );
			
			x0+=delx;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,0x5 );
			txt.Printf( _( "%c-%s-%d" ),strupc[0],strupc+1, checksum-48);
			sztxt=dc->GetTextExtent ( txt );
			cxtxt=_X ( orgx0 ) + ( _X ( largbarra )-sztxt.GetWidth() ) *0.5;
			dc->SetPen ( *wxWHITE_PEN );
			dc->DrawRectangle ( cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5,sztxt.GetWidth(),sztxt.GetHeight() );
			dc->DrawText ( txt,cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5 );
		}
		break;
	case CODE_EAN_8: {
			char strupc[13]="0000000", *ptrc=strupc+7-strlen(str);
			sprintf ( ptrc,"%s",str );
			dx=largbarra/ ( 67.0 );
			wxPen penl=wxPen ( *wxBLACK,_X ( dx ),wxSOLID );
			penl.SetCap ( wxCAP_BUTT );
			dc->SetPen ( penl );
			delx=dx*7;
			int checksum=0;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,0x5 );
			x0+=3*dx;
			for ( int i=0;i<7;i++ ) {
				
				if ( ( ( i+1 ) %2 ) ==0 ) checksum+=returnvalcode128C ( strupc[i],0 );
				else checksum+=returnvalcode128C ( strupc[i],0 ) *3;
				
				printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,strupc[i],0,i<=3,isgcode(strupc[0], i-1) );
				x0+=delx;
				if ( i==3 ) {
					printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,0xa );
					x0+=5.0*dx;
				}
			}
			checksum=checksum%10;
			if ( checksum!=0 )
				checksum=10-checksum;
			checksum+=48;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,checksum,0,false );
			
			x0+=delx;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,0x5 );
			txt.Printf ( _( "%s-%d" ),strupc,checksum-48);
			sztxt=dc->GetTextExtent ( txt );
			cxtxt=_X ( orgx0 ) + ( _X ( largbarra )-sztxt.GetWidth() ) *0.5;
			dc->SetPen ( *wxWHITE_PEN );
			dc->DrawRectangle ( cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5,sztxt.GetWidth(),sztxt.GetHeight() );
			dc->DrawText ( txt,cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5 );
		}
		break;
	case CODE_128_A: {
			int strlengh=strlen ( str );
			dx=largbarra/ ( 35.0+strlengh*11.0 );
			wxPen penl=wxPen ( *wxBLACK,_X ( dx ),wxSOLID );
			penl.SetCap ( wxCAP_BUTT );
			dc->SetPen ( penl );
			delx=dx*11;
			int checksum=Start_A-105;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,Start_A );
			x0+=delx;
			for (unsigned int i=0;i<strlen ( str );i++ ) {
				checksum+= ( ( ( int ) ( str[i]-32 ) ) &0xff ) * ( i+1 );
				printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,str[i] );
				x0+=delx;
			}
			checksum=checksum%103;
			checksum=checksum<95?checksum+=32:checksum+=105;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,checksum );
			x0+=delx;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,Stop );
			txt=wxString::FromAscii(str );
			sztxt=dc->GetTextExtent ( txt );
			cxtxt=_X ( orgx0 ) + ( _X ( largbarra )-sztxt.GetWidth() ) *0.5;
			dc->SetPen ( *wxWHITE_PEN );
			dc->DrawRectangle ( cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5,sztxt.GetWidth(),sztxt.GetHeight() );
			dc->DrawText ( txt,cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5 );
		}
		break;
	case CODE_128_B: {
			int strlengh=strlen ( str );
			dx=largbarra/ ( 35.0+strlengh*11.0 );
			wxPen penl=wxPen ( *wxBLACK,_X ( dx ),wxSOLID );
			penl.SetCap ( wxCAP_BUTT );
			dc->SetPen ( penl );
			delx=dx*11;
			int checksum=Start_B-105;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,Start_B );
			x0+=delx;
			for (unsigned int i=0;i<strlen ( str );i++ ) {
				checksum+= ( ( ( int ) ( str[i]-32 ) ) &0xff ) * ( i+1 );
				printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,str[i] );
				x0+=delx;
			}
			checksum=checksum%103;
			checksum=checksum<95?checksum+=32:checksum+=105;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,checksum );
			x0+=delx;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,Stop );
			txt=wxString::FromAscii(str );
			sztxt=dc->GetTextExtent ( txt );
			cxtxt=_X ( orgx0 ) + ( _X ( largbarra )-sztxt.GetWidth() ) *0.5;
			dc->SetPen ( *wxWHITE_PEN );
			dc->DrawRectangle ( cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5,sztxt.GetWidth(),sztxt.GetHeight() );
			dc->DrawText ( txt,cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5 );
		}
		break;
	case CODE_128_C: {
			int checksum=Start_C-105;

			int strlenght=strlen ( str );
			char *buf=new char[strlenght+2];
			if ( ( strlenght%2 ) !=0 ) {
				sprintf ( buf,"0%s",str );
			} else strcpy ( buf,str );
			strlenght=strlen ( buf );
			dx=largbarra/ ( 35.0+strlenght*0.5*11.0 );
			wxPen penl=wxPen ( *wxBLACK,_X ( dx ),wxSOLID );
			penl.SetCap ( wxCAP_BUTT );
			dc->SetPen ( penl );
			delx=dx*11;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,Start_C );
			x0+=delx;
			for ( int i=0;i<strlenght;i+=2 ) {
				checksum+= ( ( ( int ) ( returnvalcode128C ( buf[i],buf[i+1] ) ) ) &0xff ) * ( i/2+1 );
				printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,buf[i],buf[i+1] );
				x0+=delx;
			}
			checksum=checksum%103;
			checksum=checksum<95?checksum+=32:checksum+=105;
			printbarcodechar ( dc,CODE_128_B,ppmmX,ppmmY,x0,y0,yf,dx,checksum );
			x0+=delx;
			printbarcodechar ( dc,codetype,ppmmX,ppmmY,x0,y0,yf,dx,Stop );
			delete []buf;
			txt=wxString::FromAscii(str );
			sztxt=dc->GetTextExtent ( txt );
			cxtxt=_X ( orgx0 ) + ( _X ( largbarra )-sztxt.GetWidth() ) *0.5;
			dc->SetPen ( *wxWHITE_PEN );
			dc->DrawRectangle ( cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5,sztxt.GetWidth(),sztxt.GetHeight() );
			dc->DrawText ( txt,cxtxt,_Y ( yf )-sztxt.GetHeight() *0.5 );
		}
		break;
	}
	txt=wxString::FromUTF8 (toptext );
	sztxt=dc->GetTextExtent ( txt );
	cxtxt=_X ( orgx0 ) + ( _X ( largbarra )-sztxt.GetWidth() ) *0.5;
	dc->SetPen ( *wxWHITE_PEN );
	dc->DrawRectangle ( cxtxt,_Y ( y0 )-sztxt.GetHeight() *0.5,sztxt.GetWidth(),sztxt.GetHeight() );
	dc->DrawText ( txt,cxtxt,_Y ( y0 )-sztxt.GetHeight() *0.5 );
}

bool PrintBarCode::performPageSetup ( const bool showPageSetupDialog ) {
	// don't show page setup dialog, use default values
	wxPrintData printdata;
	printdata.SetPrintMode ( wxPRINT_MODE_PRINTER );
	//printdata.SetOrientation( m_orient );
	printdata.SetNoCopies ( 1 );
	printdata.SetPaperId ( m_paper_type );

	m_page_setup = wxPageSetupDialogData ( printdata );
	m_page_setup.SetMarginTopLeft ( wxPoint ( m_margin_left,  m_margin_top ) );
	m_page_setup.SetMarginBottomRight ( wxPoint ( m_margin_right, m_margin_bottom ) );

	if ( showPageSetupDialog ) {
		wxPageSetupDialog dialog ( NULL, &m_page_setup );
		if ( dialog.ShowModal() == wxID_OK ) {

			m_page_setup = dialog.GetPageSetupData();
			m_orient = m_page_setup.GetPrintData().GetOrientation();
			m_paper_type = m_page_setup.GetPrintData().GetPaperId();

			wxPoint marginTopLeft = m_page_setup.GetMarginTopLeft();
			wxPoint marginBottomRight = m_page_setup.GetMarginBottomRight();
			m_margin_left   = marginTopLeft.x;
			m_margin_right  = marginBottomRight.x;
			m_margin_top    = marginTopLeft.y;
			m_margin_bottom = marginBottomRight.y;
		} 
		else {
			return false;
		}
	}
	return true;
}

PrintBarCode::PrintBarCode ( const wxChar *title,int tipoimp )  :wxPrintout ( title ) {
	m_page_amount = 1;m_numpages=30;
	bcopts = new dlgPrintBarCode ( vilavielaframe );
	m_orient = wxPORTRAIT;
	m_paper_type = wxPAPER_LETTER;
	m_margin_left   = 0;
	m_margin_right  = 0;
	m_margin_top    = 0;
	m_margin_bottom = 0;
	tipoimpressao=tipoimp;
}

void PrintBarCode::DrawPage ( wxDC *dc ) {
	int w, h,ppiScreenX, ppiScreenY,ppiPrinterX, ppiPrinterY,pageWidth, pageHeight,pageWidthmm, pageHeightmm;
	double ppmmX,ppmmY;
	dc->SetBackgroundMode ( wxSOLID );
	dc->GetSize ( &w, &h );
	dc->SetDeviceOrigin ( ( long ) 0, ( long ) 0 );
	GetPPIScreen ( &ppiScreenX, &ppiScreenY );
	GetPPIPrinter ( &ppiPrinterX, &ppiPrinterY );
	GetPageSizePixels ( &pageWidth, &pageHeight );
	GetPageSizeMM ( &pageWidthmm, &pageHeightmm );
	if ( IsPreview() ) {
		float scaleX = ( float ) ( ( float ) ppiPrinterX/ ( float ) ppiScreenX );
		float scaleY = ( float ) ( ( float ) ppiPrinterY/ ( float ) ppiScreenY );
		double zoom=1;
#ifndef WIN32
		zoom=this->GetPreview()->GetZoom() /100.0;
#endif
		ppmmX=ppiPrinterX*zoom/ ( scaleX*25.4 );
		ppmmY=ppiPrinterY*zoom/ ( scaleY*25.4 );
	} else {
		ppmmX=ppiPrinterX/ ( 25.4 );
		ppmmY=ppiPrinterY/ ( 25.4 );
	}
	if(!bcopts)return;
	
	EtiquetaInfo *ei=bcopts->lstetiquetainfo.etiquetapadrao;if(!ei)return;
	char teste[32]="10802";//"590123412345";
	_DbResult *glbres=vilavielaframe->glb_res[TABLE_produtos];
	strcpy(teste,glbres->current->getcstr(4));
	strcat(teste,"-R$ ");
	strcat(teste,glbres->current->getcstr(6));
	double x0=ei->CB_MH,y0=ei->CB_MV,yf=y0+ei->CB_ACB,largbarra=ei->CB_LCB;
	wxRect pr;
	pr=GetLogicalPaperRect();
	pr=GetLogicalPageRect();
	int ltxt=_X ( ei->CB_AT ),htxt=_Y ( ei->CB_AT );
	wxSize sz( ltxt,htxt );
	wxFont font ( sz,wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, (wxFontWeight)wxLIGHT,false,_("arial"),wxFONTENCODING_DEFAULT );
	font.SetFaceName(_("Arial"));
	dc->SetFont ( font );
	wxSize txtext=dc->GetTextExtent(glbres->current->getstr(2));
	double lx=(double)txtext.GetX(),lb=_X (largbarra);
	double alpha= lb/lx ;
	
	if(alpha<1.0){
		ltxt=((int)floor(ltxt*alpha));
		htxt=((int)floor(htxt*alpha));
	}
	font.SetPixelSize(wxSize ( 2*ltxt,2*htxt ));
	dc->SetFont ( font );
	dc->SetBackgroundMode ( wxTRANSPARENT );
	dc->SetBrush ( *wxWHITE_BRUSH );

	dc->SetTextBackground ( wxColour ( 255,255,255 ) );
	dc->SetTextForeground ( wxColour ( 0,0,0 ) );
	double lx0,ly0=y0;
	if(tipoimpressao==IMPRIME_CODIGO_PRODUTO){
	for(int l=0;l<ei->CB_NEV;l++,ly0+=ei->CB_DL){
		lx0=x0;
		for(int col=0;col<ei->CB_NEH;col++){
			printbarcodechar ( dc,ei->CB_TIPO,ppmmX,ppmmY,lx0,ly0,ly0+ei->CB_ACB,ei->CB_LCB,teste,glbres->current->getcstr(2) );
			lx0+=ei->CB_DC;
		}
	}
	}
	else if(tipoimpressao==IMPRIME_PRODUTOS_KG){
		
		lx0=0.75*pageWidthmm;
		
		if (glbres->current=currprint) {
				do {
				dc->SetPen ( *wxBLACK_PEN);
					dc->DrawLine(_X(x0),_Y(ly0),_X(x0+pageWidthmm-ei->CB_MH),_Y(ly0));
			dc->DrawText ( wxString::Format(_("%d"),glbres->current-glbres->rows+1)+_(" - ")+glbres->current->getstr(2)+_(" - ")+glbres->current->getstr(3)+_(" - preço/kg=")+glbres->current->getstr(6),_X(x0),_Y(ly0) );
					strcpy(teste,glbres->current->getcstr(4));
					printbarcodechar ( dc,ei->CB_TIPO,ppmmX,ppmmY,lx0,ly0,ly0+ei->CB_ACB,ei->CB_LCB,teste,glbres->current->getcstr(2) );
					
					
					
					ly0+=ei->CB_DL;
					if((ly0+ei->CB_ACB)>pageHeightmm){
						break;
						
					}
		
					
				}
				while (glbres->next());
				glbres->next();
				currprint=glbres->current;
			}
			printf("dadosimp  pgh=%d\n",pageHeightmm);
	}
	
}

void PrintBarCode::OnPreparePrinting(){
		int w, h,ppiScreenX, ppiScreenY,ppiPrinterX, ppiPrinterY,pageWidth, pageHeight,pageWidthmm, pageHeightmm;
	double ppmmX,ppmmY;
	GetPPIScreen ( &ppiScreenX, &ppiScreenY );
	GetPPIPrinter ( &ppiPrinterX, &ppiPrinterY );
	GetPageSizePixels ( &pageWidth, &pageHeight );
	GetPageSizeMM ( &pageWidthmm, &pageHeightmm );
	ppmmX=ppiPrinterX/ ( 25.4 );
	ppmmY=ppiPrinterY/ ( 25.4 );
	if(!bcopts)return;
	
	EtiquetaInfo *ei=bcopts->lstetiquetainfo.etiquetapadrao;if(!ei)return;
glbres=vilavielaframe->glb_res[TABLE_produtos];
	double x0=ei->CB_MH,y0=ei->CB_MV,yf=y0+ei->CB_ACB,largbarra=ei->CB_LCB;
	wxRect pr;
	pr=GetLogicalPaperRect();
	pr=GetLogicalPageRect();
	double lx0,ly0=y0;
	m_numpages=1;
	if(tipoimpressao==IMPRIME_CODIGO_PRODUTO){
	 m_numpages=1;
	}
	else if(tipoimpressao==IMPRIME_PRODUTOS_KG){
		curgrav=glbres->current;
		if (glbres->first()) {
				do {					
					
					ly0+=ei->CB_DL;
					if((ly0+ei->CB_ACB)>pageHeightmm){
						ly0=y0;
						m_numpages++;						
					}
			
				}
				while (glbres->next());
			}
			printf("dadosprevios npg=%d pgh=%d\n",m_numpages,pageHeightmm);
			glbres->current=curgrav;
			
	}
}

 void PrintBarCode::OnBeginPrinting(){
		glbres=vilavielaframe->glb_res[TABLE_produtos];
		curgrav=glbres->current;
		glbres->first();
		currprint=glbres->current;
	}
	
	
void PrintBarCode::OnEndPrinting(){
	glbres->current=curgrav;
				}


bool PrintBarCode::OnBeginDocument ( int startPage, int endPage ) {wxPrintout::OnBeginDocument ( startPage, endPage );
	//if ( !wxPrintout::OnBeginDocument ( startPage, endPage ) )
	//	return false;
	return true;
}

void PrintBarCode::GetPageInfo ( int *minPage, int *maxPage, int *selPageFrom, int *selPageTo ) {
	*minPage = 1;
	*maxPage = m_numpages;
	*selPageFrom = 1;
	*selPageTo = m_numpages;printf("GetPageInfo m_numpages %d\n",m_numpages);
}

bool PrintBarCode::HasPage ( int pageNum ) {
	printf("HasPage pagina %d\n",pageNum);
	return ( pageNum >= 1 && pageNum<=m_numpages);
}

bool PrintBarCode::OnPrintPage ( int page ) {
 printf("imprimindo pagina %d\n",page);
	wxDC *dc = GetDC();
	if ( dc )	{
		DrawPage ( dc );
		return true;
	} else
		return false;
}
// kate: indent-mode cstyle; replace-tabs off; tab-width 1;
