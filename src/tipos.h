#ifndef tiposH
#define tiposH

typedef double NDOUBLE;
#define n_unicode_char wchar_t
#define n_unicode_char_l wchar_t
#define n_utf8_strlen(s) MultiByteToWideChar(CP_UTF8,0,s,-1,NULL,0)
#define n_swprintf swprintf
#define _tounicode(s) L##s
#define n_strlen strlen
#define n_utf8_char char
#define _towchar_t(s) s
#define n_atoi atoi
#define n_atof atof
#define n_strlwr _strlwr
#define n_strcpy strcpy
#define n_strcat strcat
#define n_strcmp strcmp
#define n_sprintf sprintf
#define n_fscanf fscanf

#define n_fopen fopen
#define n_getcwd _getcwd
#define n_chdir _chdir
#define n_wcsinc(__ptr) __ptr++ 
#define n_strtol strtol
#define NULL 0

#endif

