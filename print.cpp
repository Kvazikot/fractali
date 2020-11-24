#include "fractals.h"
extern fractals* pdlg2;
char mu_printftmp[10000];
void prn(const char* fmt,...)
{
    va_list ap;

    va_start(ap, fmt);
    #ifdef WIN32
    _vsnprintf(mu_printftmp, 60000, fmt, ap);
    #else
    vsnprintf(mu_printftmp, 60000, fmt, ap);
    #endif
    va_end(ap);
    
	if(pdlg2!=0)
        pdlg2->print(mu_printftmp);

	

}
