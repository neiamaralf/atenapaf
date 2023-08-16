#ifndef __STRING_H_
#define __STRING_H_

#include <string>
#include <iostream>



	class Palavra
	{
		std::string realStr;

	public:
#ifdef _WIN32
        //TODO something less dirty-hackish.
        static const size_t npos = static_cast<std::string::size_type>(-1);
#else
		static const size_t npos = std::string::npos;
#endif

		~Palavra() {}

		Palavra() {}

		Palavra(const Palavra & other) : realStr(other.realStr) {}

		Palavra(const std::string & other) : realStr(other) {}

		Palavra(const char other[]) : realStr(other) {}

		Palavra(const char * s, size_t n) : realStr(s, n) {}

		// Needed for stuff like Palavra str= "char * string constant"
		const Palavra & operator=(const char * s)
		{
			realStr = s;
			return *this;
		}

		const Palavra & operator=(const std::string & rhs)
		{
			realStr = rhs;
			return *this;
		}
		
		const Palavra & operator=(const int & rhs){
			static char s[32];
			sprintf(s,"%d",rhs);
			realStr=s;
			return *this;
		}
		
		const Palavra & operator=(const double & rhs){
			static char s[32];
			sprintf(s,"%.3f",rhs);
			realStr=s;
			return *this;
		}

		const Palavra & operator=(const Palavra & rhs)
		{
			realStr = rhs.realStr;
			return *this;
		}

		// Conversion to st::string. Comes in play for stuff like std::string str= SQLString_var;
		operator const std::string &() const
		{
			return realStr;
		}

		/** For access std::string methods. Not sure we need it. Makes it look like some smart ptr.
			possibly operator* - will look even more like smart ptr */
		std::string * operator ->()
		{
			return & realStr;
		}

		int compare(const Palavra& str) const
		{
			return realStr.compare(str.realStr);
		}

		int compare(const char * s) const
		{
			return realStr.compare(s);
		}

		int compare(size_t pos1, size_t n1, const char * s) const
		{
			return realStr.compare(pos1, n1, s);
		}

		const std::string & asStdString() const
		{
			return realStr;
		}

		const char * c_str() const
		{
			return realStr.c_str();
		}

		size_t length() const
		{
			return realStr.length();
		}

		Palavra & append(const std::string & str)
		{
			realStr.append(str);
			return *this;
		}

		Palavra & append(const char * s)
		{
			realStr.append(s);
			return *this;
		}

		Palavra & append(int i)
		{
			static char s[32];
			sprintf(s,"%d",i);
			realStr.append(s);
			return *this;
		}

		Palavra & append(double d)
		{
			static char s[32];
			sprintf(s,"%g",d);
			realStr.append(s);
			return *this;
		}

		const char& operator[](size_t pos) const
		{
			return realStr[pos];
		}

		size_t find(char c, size_t pos = 0) const
		{
			return realStr.find(c, pos);
		}

		size_t find(const Palavra & s, size_t pos = 0) const
		{
			return realStr.find(s.realStr, pos);
		}

		Palavra substr(size_t pos = 0, size_t n = npos) const
		{
			return realStr.substr(pos, n);
		}

		const Palavra& replace(size_t pos1, size_t n1, const Palavra & s)
		{
			realStr.replace(pos1, n1, s.realStr);
			return *this;
		}

		size_t find_first_of(char c, size_t pos = 0) const
		{
			return realStr.find_first_of(c, pos);
		}

		size_t find_last_of(char c, size_t pos = npos) const
		{
			return realStr.find_last_of(c, pos);
		}

		const Palavra & operator+=(const Palavra & op2)
		{
			realStr += op2.realStr;
			return *this;
		}
};


/*
  Operators that can and have to be not a member.
*/
inline const Palavra operator+(const Palavra & op1, const Palavra & op2)
{
	return Palavra(op1.asStdString() + op2.asStdString());
}

inline bool operator ==(const Palavra & op1, const Palavra & op2)
{
	return (op1.asStdString() == op2.asStdString());
}

inline bool operator !=(const Palavra & op1, const Palavra & op2)
{
	return (op1.asStdString() != op2.asStdString());
}

inline bool operator <(const Palavra & op1, const Palavra & op2)
{
	return op1.asStdString() < op2.asStdString();
}





namespace std
{
	// operator << for Palavra output
	inline ostream & operator << (ostream & os, const Palavra & str )
	{
		return os << str.asStdString();
	}
}
#endif
