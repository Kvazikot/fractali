#include <QDebug>
#include <QApplication>
#define _USE_MATH_DEFINES
#include <math.h>
#include "fractals.h"
#include "livewidget.h"

double myatan(double x)
{
    double res,sign;
    res = x;
    sign = -1;
    for(int i=3; i < 27; i+=2)
    {
        res+= sign * (pow(x,i)/i);
        sign*=-1;
    }
    return res;
}

double calculate_pi()
{
    double pi1 = 0;

    for(int k=0; k < 20; k++)
    {
       pi1+= ( (double)1. / pow((double)16,k)  * ( (double)4. /((double)8.*k+1) - (double)2./((double)8.*k+(double)4.) - (double)1./((double)8.*k+(double)5.) - (double)1./((double)8.*k+(double)6.)) );
       qDebug("%1.20f", pi1);
    }

    double pi2 = 4*(4 * atan((double)1./5.)-atan((double)1./239.));
    qDebug("pi1 %1.20f", pi1);
    qDebug("M_PI %1.20f", M_PI);
    qDebug("pi1 - M_PI = %1.20f", pi1 - M_PI);
    qDebug("pi2 - M_PI = %1.20f", pi2 - M_PI);
    qDebug("myatan((double)1./5.)  - atan((double)1./5.) = %1.20f )", myatan((double)1./5.)- atan((double)1./5.) );

    return pi1;
}

int main(int argc, char *argv[])
{
    qApp->addLibraryPath("./plugins");
	QApplication a(argc, argv);    
    fractals w;
    w.show();

    //qDebug() << calculate_pi();
	return a.exec();
}
