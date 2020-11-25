#include <QMatrix3x3>
#include <QPainter>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QtMath>
#include <QGraphicsProxyWidget>
#include <QResizeEvent>
#include <QThread>
#include <QDebug>
#include <QTimer>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <array>
#include "fractals.h"
#include "print.h"
#include "fit_rects.h"
#include "lsystem.h"
#include "cellularautomatas.h"
#include "livewidget.h"

fractals* pdlg2;
RectsFitter*  fit_rects;
CellularAutomatas* cellular;
LiveWidget*        livewidget = 0;
bool	  DoAbort;
bool	  DoCellular;
QTimer    cellular_timer;


fractals::fractals(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    scene.addText("Hello, world!");
    scene.setSceneRect(0,0,ui.resWidth->value(), ui.resHeight->value());
    ui.graphicsView->setScene(&scene);
    //ui.graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    cellular = new CellularAutomatas(ui.xCells->value(),ui.yCells->value());
    DoCellular = 0;
    cellular_timer.setInterval(100);
    connect(&cellular_timer,SIGNAL(timeout()),this,SLOT(updateCellular()));


    pdlg2 = this;
    startTimer(10);
    ui.toolBox->setCurrentIndex(4);
    on_drawButton_clicked();

}



void fractals::DrawJulia(int npix, int npiy, int kcolor, double pmin, double qmin,  double xmin, double ymin, double xmax, double ymax)
{
    double dx,dy,x,y,x0,y0,r;
    int    k;
    Complex z;
    unsigned int n_black;
    prn("aa");
    kcolor = 250;

    r = 0;
    dx = (double)(xmax-xmin)/(npix-1);
    dy = (double)(ymax-ymin)/(npiy-1);
    //myProgress = 100;
    //return;
    uchar* p0 = resultImage.bits();
    prn("image size %dx%d", resultImage.width(), resultImage.height());
    //return;

    FILE* f = fopen("out.csv","w+");

    QColor fc;

    //for(int m=0; m < 100; m++)
    {
       // qmin =  (double)sin((double) 2 * M_PI * ((double)m / (double)npix)* 10);
        //Rosenbrock fn(plot);

        QApplication::processEvents();
        for(int i=0; i<npix-1; i++)
        {
            x0 = xmin + (double)i * dx;
            for(int j=0; j<npiy-1; j++)
            {
                y = ymin + (double)j * dy;
                x = x0;
                r = 0;
                k = 0;
                do
                {
                    //pmin = fn(x,y);
                    //qmin = fn(x,y);
                    z.i = (x+y) * (x-y) + pmin;
                    z.j = (x*y) + (x*y) + qmin;
                    r = z.mod();

                    k++;
                    if(r >= kcolor)
                    {
                        // некий узор
                        fc.setRed( fabs( 128 * (double)cos((double) 2 * M_PI * ((double)j*i / (double)npix)* 100)));
                        fc.setBlue( fabs( 128 * (double)cos((double) 2 * M_PI * ((double)j*i / (double)npix)* 100)));
                        fc.setGreen( fabs( 128 * (double)cos((double) 2 * M_PI * ((double)j*i / (double)npix)* 100)));
                        double col;

                        resultImage.setPixel(i,j,fc.value()); //модуляция синусом
                        //if(im1.width() == npix )
                        //    resultImage.setPixel(i,j,im1.pixel(i,j));

                        fprintf(f,"%d\n",k);
                        n_black++;
                    }
                    if(k == kcolor)
                    {

                        //QColor cc;
                        //cc.setRed((k-250) );
                        // для маскирования фоном
                        //fc.setRed( fabs( 128 * (double)cos((double) 2 * M_PI * ((double)j*i / (double)npix)* 100)));

                        //resultImage.setPixel(i,j,fc.value()); //замаскированное
                        if(im1.width() == npix )
                            resultImage.setPixel(i,j,im2.pixel(i,j));
                    }
                    x = z.i; //предыдущая итерация z(n+1) = z*z + c
                    y = z.j;
                }while( r <=kcolor  && k<=kcolor);

            }
        }
    }

    // вычислить отношение площади к площади черного
    // вероятность попадания в зону фрактала
    double p;
    p = (double)npix*npiy / (double)n_black;
    qDebug("p=%f pmin = %f qmin = %f n_black=%d npix=%d npiy=%d", p, pmin, qmin, n_black, npix, npiy);


    fclose(f);
    myProgress = 100;
}


void fractals::print(char* str)
{
    //ui.console->appendPlainText(str);
    //ui.console->moveCursor(QTextCursor::End);
	

}


RenderThread::RenderThread(fractals* p){ pdlg = p;}

int IPAR(const char* name)
{
	pdlg2->ui.toolBox->currentIndex();
	QWidget* page = pdlg2->ui.toolBox->currentWidget();
	QList<QSpinBox*> list = page->findChildren<QSpinBox *>();
	foreach(QSpinBox *w, list) 
	{
		if(w->objectName() == name)
			return w->value();
	}
	return 0;

}

double DPAR(const char* name)
{
	pdlg2->ui.toolBox->currentIndex();
	QWidget* page = pdlg2->ui.toolBox->currentWidget();
	QList<QDoubleSpinBox*> list = page->findChildren<QDoubleSpinBox *>();
	foreach(QDoubleSpinBox *w, list) 
	{
		if(w->objectName() == name)
			return w->value();
	}
	return 0;
}



void fractals::timerEvent(QTimerEvent*)
{
	ui.progressBar->setValue(myProgress);    
    statusBar()->showMessage("Количество линий: " + QString::number(scene.items().size()) );
    if(livewidget)
      ui.label_12->setText(QString("generation %1").arg(livewidget->n_frame));
}

fractals::~fractals()
{

}

void fractals::clear()
{
	//QPainter painter(&resultImage);
	//painter.fillRect(resultImage.rect(), Qt::white);		
    //painter.end();
}

void fractals::resizeEvent ( QResizeEvent * event )
{


}

void TorusPrint(QString s)
{
    pdlg2->ui.TorusMemo->appendPlainText(s);
}

void RenderThread::DrawKamTorus(double square, double ax)
{
    int a,b, nx,  ny, c, r0;
	double an,can,san,can1,san1,e,ay;
    double x,xa,x1,x2,x3,y,y1,y2,y3,rand1,rand2,rand3;
	a = 0; b = 0;
	nx = resultImage.width() / 2;
	ny = resultImage.height() / 2;
	ay = ax;
	c = 1;
	time_t t;
    unsigned u =(unsigned)time(&t);
    //u = 1458919558;
    //u = 1458919768-20000;
    srand(u);
	rand1 = qrand() % 20000;
    rand2 = qrand() % 20000;

	rand1 = 5.0e-5*rand1;
	rand2 = 5.0e-5*rand2;

    TorusPrint(QString().sprintf("rand1 %f  rand2 %f  srand %d",rand1,rand2,u));

    //rand1=0.619000;  rand2=0.467500;
    rand1=0.653250;  rand2=0.276150;

	an = 10.0 *(rand1-rand2);
	can = 0.99*cos(an);
	san = 0.99*sin(an);
    can1 = 1.01 * cos(an);
    san1 = 1.01 * sin(an);

	x3 = 0.01;
	y3 = 0.01;
	do
    {
        rand3 = (float)rand()/RAND_MAX;
        can1 = 1.01 * cos(an+rand3);


		xa = x3*x3 - y3;
        x2 = x3*can1 + xa*san1;
		y2 = x3*san1 - xa*can1;
		x3 = x2;
		x = x2;
		y = y2;
		a = 0;
		do
		{
            xa = x*x - y ;
			x1 = x*can + xa * san;
			y1 = x*san - xa * can;

            x = x1;
			y = y1;
			a++;
			//qDebug("%d ", (int)(ax*x+nx)-1) ;
			int XPix = (int)(ax*x+nx)-1;
			int YPix = (int)(ay*y+ny)-1;


			if ( ( XPix < resultImage.width() ) &&  ( YPix < resultImage.height()  )
				 && ( XPix > 0 ) &&  ( YPix > 0 ) )
				resultImage.setPixel(XPix,YPix,c);
			pdlg->myProgress = a;
        }while((fabs(x1)<=square) && (fabs(y1)<=square) && a<=100);
		e = e + 0.075;
		c = qrand() % 32767;
		b++;
	}while((fabs(x2) <=square) && (fabs(y2)<=square) && b<=10000);
	pdlg->myProgress = 100;
}

double abs_random(void)
{
	int random_integer, temp_integer;
	double random_double, temp_double;
	random_integer = rand();
	random_double = (double) random_integer / RAND_MAX;
	temp_integer = rand() % 32767;
	temp_double = (double) temp_integer /1000000000000L;
	random_double+=temp_double;
	return random_double;
}

bool RenderThread::CheckIdx(int xpix, int ypix)
{
	if ( ( xpix < resultImage.width() ) &&  ( ypix < resultImage.height()  )
				 && ( xpix >= 0 ) &&  ( ypix >= 0 ) )			
				 return true;
	else
		return false;
	
}

bool fractals::CheckIdx(int xpix, int ypix)
{
	if ( ( xpix < resultImage.width() ) &&  ( ypix < resultImage.height()  )
				 && ( xpix >= 0 ) &&  ( ypix >= 0 ) )			
				 return true;
	else
		return false;
	
}


void RenderThread::DrawAbstract(int r, int cmax, int npix, int npiy)
{
	int Raio[5000],Cx[5000],Cy[5000],color,iopt;	
	double Tcor, Cor[5000];
	int xpix,ypix,Cmax, i, index, dx,dy,Rmax;

	Cmax = (rand()% 2000) + cmax;
	Rmax = (rand()% r) + 1;
	pdlg->myProgress = 0;
	for(i=1; i < Cmax; i++)
	{
		Cx[i] = (int)npix*abs_random();
		Cy[i] = (int)npiy*abs_random();
		Raio[i] = (int)Rmax*abs_random();
		if(iopt == 1)
			Cor[i] = (double)(16.0*abs_random() + 15.0);
		else
			Cor[i] = (double)(256*abs_random() );
	}

	

	for(xpix=0; xpix < (npix-1); xpix++)
	{
		for(ypix=0; ypix < (npiy-1); ypix++)
		{
			index = 0;
			Tcor = 0;
			for(i=1; i < Cmax; i++)
			{
				dx = xpix - Cx[i];
				dy = ypix - Cy[i];
				if((int)(dx*dx+dy*dy) <= Raio[i]*Raio[i])
				{
					index++;
					Tcor = Tcor + Cor[i];
				}
			}
			if(index > 0)
				color = (int)(Tcor/index);
			else
				color = 0;
			pdlg->myProgress = qRound(100*((float)xpix * ypix /  npiy));
			if( CheckIdx(xpix,ypix) )
				resultImage.setPixel(xpix,ypix,color*16);	
		
		}
	}

	pdlg->myProgress = 100;
}

int randCol(float alpha)
{
	unsigned char r = qRound( 255 * (double)qrand() / RAND_MAX);
	unsigned char g = qRound( 255 * (double)qrand() / RAND_MAX);
	unsigned char b = qRound( 255 * (double)qrand() / RAND_MAX);
	return ((b<<16) + (g<<8) + r);

}

void fractals::updatePixmap(const QImage &resultImage)
{
    ui.graphicsView->scene()->clear();
    ui.graphicsView->scene()->addPixmap(QPixmap::fromImage(resultImage));
    //ui.label->setPixmap(QPixmap::fromImage(resultImage));
}


float random(float from, float to)
{
    return from + ((float)rand()/RAND_MAX) * to;
}

void branch(QPainter* painter, float len) {
//Start by picking a random angle for each branch.
  float theta = random(0,M_PI/3);
  painter->drawLine(0, 0, 0, -len);
  painter->translate(0, -len);
  len *= 0.66;
  if (len > 2) {
    painter->save();
    painter->rotate(theta * 180. / M_PI);
    branch(painter,len);
    painter->restore();
    painter->save();
    painter->rotate(-theta * 180. / M_PI);
    branch(painter,len);
    painter->restore();
  }
}

std::vector<std::vector<int>> seqs;
#include <random>
std::default_random_engine generator;
std::normal_distribution<float> distribution(0.5,0.2);



int PICK(float P[],int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({P[0]*1000, P[1]*1000,  P[2]*1000, P[3]*1000});
    return d(gen);
}

float c_pap[K_MAX][6] = {{0.0,0.0,0.0,0.3,0.4987,0.0070}, \
                 {0.1,0.4330,-0.1732,0.2500,0.4445,0.1559}, \
                 {0.1,-0.433,0.1732,0.2500,0.4478,0.0014}, \
                  {0.7,0.0,0.0,0.7,0.1496,0.2962}};

float c_list[K_MAX][6] = { {0,0,0,0,0,0}, \
                       {0,0,0,0,0,0}, \
                       {0.4,-0.3,0.06,0.6,0.3433,0}, \
                       {-0.8,-0.1867,0.1371,0.8,1.1,0.1} };

float c_cristal[K_MAX][6] = {{0.2550,0,0,0.2550,0.3726,0.6714},
                         {0.2550,0,0,0.2550,0.1146,0.2232},
                         {0.2550,0,0,0.2550,0.6306,0.2232},
                         {0.37,-0.6420,0.6420,0.3700,0.6356,-0.0061} };


void calc_weights(float C[][6], float P[],int kMax)
{
    float detA[4];
    float SUMdetA=0;
    for(int k=0; k<kMax; k++)
    {
        float a = C[k][0];
        float b = C[k][1];
        float c = C[k][2];
        float d = C[k][3];
        detA[k] = fabs(a * d - b * c);
        SUMdetA+=detA[k];
    }
    //веса
    for(int k=0; k<kMax; k++)
    {
        P[k] = detA[k]/SUMdetA;
        qDebug("p[%d]=%f",k,detA[k]/SUMdetA);

    }

}

int totalIterations = 0;

int monte_carlo_method(float P[],int n)
{
   float X, Y;

   bool hit = false;
   //while( !hit && --iterations > 0 )
   {
       X = (float)rand()/RAND_MAX;
       Y = (float)rand()/RAND_MAX;
       std::vector<QRectF>::iterator irc;
       int cnt=0;
       for(irc=fit_rects->scaled_squares.begin(); irc!=fit_rects->scaled_squares.end(); irc++, cnt++)
       {
           if( X >= (*irc).left() && X <= (*irc).right())
           {
            if( Y <=  (*irc).bottom() && Y >=  (*irc).top())
            {
                  hit = true;
                  return fit_rects->index2index[cnt];
            }
           }
       }
       qDebug("point (%f,%f) missed");
       return -1;


   }


}


void cif_algo(QPainter* painter, float C[][6], int kMax, int level, int w, int h)
{
    float P[4]={0,0,0,0.00};
    float x,y,x0,y0;
    float a,b,c,d;
    int kHist[4]={0,0,0,0};

    calc_weights(C,P,kMax);
    fit_rects = new RectsFitter(P);
    fit_rects->DrawInitalRefinment(painter, 200, 500);

    a = 0; b = 0;
    c = w; d = h;
    int k;
    x0 = 1.1; y0 = 1.1;
    for(int i=0; i < 100; i++ )
    {
        k = monte_carlo_method(P, kMax);
        if(k==-1) continue;
        x = (C[k][0] * x0 + C[k][1]*y0 + C[k][4]);
        y = (C[k][2] * x0 + C[k][3]*y0 + C[k][5]);
        x0 = x;
        y0 = y;
    }
    //qDebug("n1=%d P=%f",n1,(float)n1/1000);

    totalIterations = 0;
    int misses = 0;
    for(int i=0; i < level; i++)
    {
        k = monte_carlo_method(P, kMax); //PICK(P, kMax);
        if(k==-1)
        {
            misses++;
            continue;
        }
        totalIterations++;
        kHist[k]++;
        x = (C[k][0] * x0 + C[k][1]*y0 + C[k][4]);
        y = (C[k][2] * x0 + C[k][3]*y0 + C[k][5]);
        int xs = a * x + c * x;
        int ys = b * x + d * y;
        painter->drawPoint(QPoint(xs,ys));
        x0 = x;
        y0 = y;
    }
    for(int i=0; i<4; i++)
        qDebug("kHist[%d]=%f misses=%d",i,(float)kHist[i]/totalIterations, misses);
    qDebug("totalIterations=%d", totalIterations);

}

void form_permut(int N, int K, int nIterations, std::vector<std::vector<int>>& seqs)
{
    QString hash;
    std::vector<int> seq;
    static QHash<QString,QString>   seq_hashs;
    QMap<int,int> tab;

    N = K;

    seq.resize(N);
    int nSeq=0;

    while( --nIterations > 0 )
   {

        tab.clear();
        int k = 0;
        hash="";
        while(k!=K)
        {
            int i=rand()%K;
            if( tab.find(i)==tab.end())
            {
                seq[k] = i;
                tab[i] = i;
                hash+=QString::number(i);
                k++;
            }
        }

       if( seq_hashs.find( hash )==seq_hashs.end() )
       {
           seqs.push_back(seq);
           seq_hashs[hash] = hash;
           qDebug() << nSeq << " seq " << hash << "\n";
           nSeq++;
       }
    }
}


void RenderThread::run()
{

    //----test
    form_permut(4,4,10000,seqs);


    //----test
	int npage = pdlg->ui.toolBox->currentIndex();
	if( npage == 2) return;
    int w = pdlg->ui.graphicsView->sceneRect().width();
    int h = pdlg->ui.graphicsView->sceneRect().height();
    resultImage = QImage(w,h,QImage::Format_ARGB32_Premultiplied);
    resultImage.fill(Qt::white);
    QPainter painter(&resultImage);
	if( npage == 0)
		DrawKamTorus(DPAR("orbit"), DPAR("ax"));
	if( npage == 1)
		DrawAbstract(IPAR("r"),IPAR("cmax"),IPAR("npix"),IPAR("npiy"));
	//if( npage == 2)
	//	DrawJulia(640,480,100,-0.74,0.111);
    if( npage == 3 )
    {
        time_t t;
        srand(time(&t));
        painter.translate(resultImage.width()/2,resultImage.height());
        branch(&painter, 100);
    }
    if( npage == 4 )
    {
        float c[K_MAX][6] = { {0,0,0,0,0,0}, \
                               {0,0,0,0,0,0}, \
                               {0.4,-0.3,0.06,0.6,0.3433,0}, \
                               {-0.8,-0.1867,0.1371,0.8,1.1,0.1} };

        parse_matrix_edit(c);
        cif_algo(&painter, c, K_MAX, pdlg->ui.nPoints->value(), resultImage.width(), resultImage.height());
        //cif_algo(&painter, c_list, K_MAX, pdlg->ui.nPoints->value(), resultImage.width(), resultImage.height());
        //cif_algo(&painter, c_pap,4, pdlg->ui.nPoints->value(), resultImage.width(), resultImage.height());
    }
	emit renderedImage(resultImage);
}

void RenderThread::parse_matrix_edit(float c[K_MAX][6])
{
    QString text = pdlg->ui.matrixEdit->toPlainText();
    QStringList lines = text.split("\n");
    int n = lines.length();
    if(n > K_MAX) n = K_MAX;
    for(int i=0; i < n; i++)
    {
        QStringList line_parts = lines[i].split(" ", QString::SplitBehavior::SkipEmptyParts);
        if(line_parts.length() < 6) continue;
        for(int j=0; j < 6; j++)
          c[i][j] = line_parts[j].toFloat();
    }
}

void fractals::on_drawButton_clicked()
{
	if(ui.toolBox->currentIndex() == 2)
	{        
        int w = ui.xRes->value() ;//ui.graphicsView->sceneRect().width();
        int h = ui.yRes->value();//ui.graphicsView->sceneRect().height();
        resultImage = QImage(w,h,QImage::Format_RGB32);
        DrawJulia(w,h,100,DPAR("pmin"),DPAR("qmin"),DPAR("xmin"),DPAR("ymin"),DPAR("xmax"),DPAR("ymax"));
        //updatePixmap(resultImage);
        QGraphicsPixmapItem* item;
        item = ui.graphicsView->scene()->addPixmap(QPixmap::fromImage(resultImage));
        item->moveBy(ui.graphicsView->sceneRect().width()/2-w/2,ui.graphicsView->sceneRect().height()/2-h/2);

	}
	else{
		RenderThread* th = new RenderThread(this);
	    connect(th, SIGNAL(renderedImage(const QImage &)),
            this, SLOT(updatePixmap(const QImage &)));
        connect(th, &QThread::finished, th, &QObject::deleteLater);

		th->start();


/*        resultImage = QImage(ui.label->width(),ui.label->height(),QImage::Format_ARGB32_Premultiplied);
        resultImage.fill(Qt::white);
        QPainter painter(&resultImage);
        FitRects*  fr = new FitRects();
        fr->DrawInitalRefinment(&painter, resultImage.width(), resultImage.height());
        updatePixmap(resultImage);
*/

	}
	
}

void fractals::on_abortBut_clicked()
{
	DoAbort = true;
}

void fractals::on_drawButton_2_clicked()
{

    int w = ui.graphicsView->sceneRect().width();
    int h = ui.graphicsView->sceneRect().height();
    resultImage = QImage(w,h,QImage::Format_RGB32);
    lsystem.theta = qDegreesToRadians(ui.theta->value());
    lsystem.startA = qDegreesToRadians(ui.a->value());
    QString word = lsystem.generate_word(ui.axiom->toPlainText(), ui.newf->toPlainText(), ui.newx->toPlainText(), ui.newy->toPlainText(), ui.level->value(), ui.newb->toPlainText());
    ui.outputWord->setText(QString("<html><head/><body><p><span style=\" font-weight:600;\">%1</span></p></body></html>").arg(word));
    //lsystem.Draw(resultImage);
    lsystem.DrawToScene(ui.graphicsView->scene(), ui.progressBar_2, ui.delay->isChecked());
    //updatePixmap(resultImage);
}

void fractals::on_listWidget_itemClicked(QListWidgetItem *item)
{

    ui.axiom->setPlainText("");
    ui.newf->setPlainText("");
    ui.newx->setPlainText("");
    ui.newy->setPlainText("");
    ui.newb->setPlainText("");
    ui.level->setValue(4);
    ui.a->setValue(0);

    if (item->text() == "Снежинка Коха" )
    {
        ui.axiom->setPlainText("F++F++F");
        ui.newf->setPlainText("F-F++F-F");
        ui.level->setValue(2);
        ui.theta->setValue(60);

    }

    if (item->text() == "Дракон" )
    {
        ui.axiom->setPlainText("FX");
        ui.newf->setPlainText("F");
        ui.newx->setPlainText("X+YF+");
        ui.newy->setPlainText("-FX-Y");
        ui.level->setValue(12);
        ui.theta->setValue(90);
    }

    if (item->text() == "Мой фрактал 1" )
    {
        ui.axiom->setPlainText("FX");
        ui.newf->setPlainText("F");
        ui.newx->setPlainText("FY+");
        ui.newy->setPlainText("-FX+Y");
        ui.level->setValue(15);
        ui.theta->setValue(60);
    }

    if (item->text() == "Ковер Серпинского " )
    {
        ui.axiom->setPlainText("FXF--FF--FF");
        ui.newf->setPlainText("FF");
        ui.newx->setPlainText("--FXF++FXF++FXF--");
        ui.theta->setValue(60);
    }

    if (item->text() == "Кривая Гильберта" )
    {
        ui.axiom->setPlainText("X");
        ui.newf->setPlainText("F");
        ui.newx->setPlainText("-YF+XFX+FY-");
        ui.newy->setPlainText("+XF-YFY-FX+");
        ui.theta->setValue(90);
    }

    if (item->text() == "Кривая Госпера" )
    {
        ui.axiom->setPlainText("XF");
        ui.newf->setPlainText("F");
        ui.newx->setPlainText("X+YF++YF-FX--FXFX-YF+");
        ui.newy->setPlainText("-FX+YFYF++YF+FX--FX-Y");
        ui.theta->setValue(60);
    }

    if (item->text() == "Кривая Пеано" )
    {
        ui.axiom->setPlainText("F");
        ui.newf->setPlainText("F-F+F+F+F-F-F-F+F");
        ui.a->setValue(45);
        ui.theta->setValue(90);
    }

    if (item->text() == "Кривая Серпинского" )
    {
        ui.axiom->setPlainText("F+XF+F+XF");
        ui.newf->setPlainText("F");
        ui.newx->setPlainText("XF-F+F-XF+F+XF-F+F-X");
        ui.a->setValue(45);
        ui.theta->setValue(90);
    }


    if (item->text() == "Куст" )
    {
        ui.axiom->setPlainText("F");
        ui.newf->setPlainText("-F+F+[+F-F-]-[-F+F+F]");
        ui.theta->setValue(180./8.);
    }


    if (item->text() == "Мозайка" )
    {
        ui.axiom->setPlainText("F-F-F-F");
        ui.newf->setPlainText("F-b++FF-F-FF-Fb-FF+b-FF+F+FF+Fb+FFF");
        ui.newb->setPlainText("bbbbbb");
        ui.level->setValue(2);
        ui.theta->setValue(90);
    }

    if (item->text() == "Остров" )
    {
        ui.axiom->setPlainText("F+F+F+F");
        ui.newf->setPlainText("F+F-F-FFF+F+F-F");
        ui.theta->setValue(90);
    }

    if (item->text() == "Снежинка" )
    {
        ui.axiom->setPlainText("[F]+[F]+[F]+[F]+[F]+[F]");
        ui.newf->setPlainText("F[++F][-FF]FF[+F][-F]FF");
        ui.theta->setValue(60);
    }

    if (item->text() == "Сорняк" )
    {
        ui.axiom->setPlainText("F");
        ui.newf->setPlainText("F[+F]F[-F]F");
        ui.theta->setValue(180./7);
    }

    if (item->text() == "Цветок" )
    {
        ui.axiom->setPlainText("F[+F+F][-F-F][++F][--F]F");
        ui.newf->setPlainText("FF[++F[+F][F][-F][--F]");
        ui.a->setValue(90);
        ui.theta->setValue(180./16);
    }

    if (item->text() == "Цепочка" )
    {
        ui.axiom->setPlainText("F+F+F+F");
        ui.newf->setPlainText("F+b-F-FFF+F+b-F");
        ui.newb->setPlainText("bbb");
        ui.theta->setValue(90);
    }

    QString word = lsystem.generate_word(ui.axiom->toPlainText(), ui.newf->toPlainText(), ui.newx->toPlainText(), ui.newy->toPlainText(), ui.level->value(), ui.newb->toPlainText());
    int cnt=0;
    for(int i=0; i<word.length(); i++)
        if( word[i] == 'F' ) cnt++;

    statusBar()->showMessage("Количество линий: " + QString::number(cnt) );

}

void fractals::on_setMaximumRes_clicked()
{
    //scene.setSceneRect(0,0,ui.resWidth->value(),ui.resHeight->value());
    ui.graphicsView->setSceneRect(0,0,ui.resWidth->value(),ui.resHeight->value());
}

void fractals::on_zoomInB_clicked()
{
    ui.graphicsView->scale(1.1,1.1);
}

void fractals::on_zoomOutB_clicked()
{
    ui.graphicsView->scale(0.9,0.9);
}

void fractals::on_clearButton_clicked()
{
    ui.graphicsView->scene()->clear();
}

void fractals::on_abortBut_2_clicked()
{
    lsystem.Abort();
}

QGraphicsPixmapItem* item=0;

void fractals::on_drawButton_3_clicked()
{
    int w = ui.xRes_2->value() ;//ui.graphicsView->sceneRect().width();
    int h = ui.yRes_2->value();//ui.graphicsView->sceneRect().height();
    resultImage = QImage(w,h,QImage::Format_ARGB32);
    delete cellular;
    cellular = new CellularAutomatas(ui.xCells->value(),ui.yCells->value());
    //�������� ���� ����
    cellular->setDrawGrid(ui.drawGridCB->isChecked());
    cellular->setFastDraw(ui.fastDrawCB->isChecked());
    cellular->Draw(resultImage);
    item = ui.graphicsView->scene()->addPixmap(QPixmap::fromImage(resultImage));
    item->moveBy(ui.graphicsView->sceneRect().width()/2-w/2,ui.graphicsView->sceneRect().height()/2-h/2);

}

void fractals::on_clearButton_2_clicked()
{
    ui.graphicsView->scene()->clear();
}

void fractals::on_pushButton_clicked()
{
    ui.graphicsView->scene()->clear();
    cellular->NextFrame();
    int w = ui.xRes_2->value() ;//ui.graphicsView->sceneRect().width();
    int h = ui.yRes_2->value();//ui.graphicsView->sceneRect().height();
    if(resultImage.width()!=w || resultImage.height()!=h)
      resultImage = QImage(w,h,QImage::Format_ARGB32);
    //�������� ���� ����
    cellular->setFastDraw(ui.fastDrawCB->isChecked());
    cellular->Draw(resultImage);
    item = ui.graphicsView->scene()->addPixmap(QPixmap::fromImage(resultImage));
    item->moveBy(ui.graphicsView->sceneRect().width()/2-w/2,ui.graphicsView->sceneRect().height()/2-h/2);
    ui.label_10->setText(QString("Gen %1 Live %2 \nfrom %3").arg(cellular->n_generation).arg(cellular->n_live).arg(cellular->cellsX*cellular->cellsY));

}

void fractals::on_drawGridCB_clicked()
{
    cellular->setDrawGrid(ui.drawGridCB->isChecked());
}

void fractals::updateCellular()
{
    on_pushButton_clicked();
    QApplication::processEvents();
}

void fractals::on_pushButton_2_clicked()
{
    if(!DoCellular)
    {
        DoCellular = true;
        cellular_timer.start();
        ui.pushButton_2->setText("Stop");
    }
    else
    {
        DoCellular = false;
        cellular_timer.stop();
        ui.pushButton_2->setText("Play");
    }
}

void fractals::on_fastDrawCB_clicked()
{
    cellular->setFastDraw(ui.fastDrawCB->isChecked());
}

void fractals::on_reinitWorld_clicked()
{

    if(!livewidget)
     {
         livewidget = new LiveWidget(ui.graphicsView);
         livewidget->setGeometry(0,0,1024,768);
         livewidget->show();
     }
    else
        livewidget->initCelularWorld(ui.density->value());


}

void fractals::on_tabWidget_currentChanged(int index)
{

    if(index == 4)
    {
        if(!livewidget)
         {
             livewidget = new LiveWidget(ui.graphicsView);
             livewidget->setGeometry(0,0,1024,768);
             livewidget->show();
         }
    }
    else
    {
        delete livewidget;
        livewidget = 0;
    }

}

void fractals::on_reinitWorld_pressed()
{

}


void fractals::on_savedCIFsCombo_activated(const QString &arg1)
{
    ui.matrixEdit->clear();
    for(int k=0; k < K_MAX; k++)
    {
        QString s;
        for(int i=0; i < 6; i++)
        {
           char str [128];
           if(arg1 == "Crystal")
             sprintf(str, "%4.4f", c_cristal[k][i]);
           else if (arg1 == "Leaf")
             sprintf(str, "%4.4f", c_list[k][i]);
           else if (arg1 == "Pap")
               sprintf(str, "%4.4f", c_pap[k][i]);
           s+=QString(str) + "  ";
        }
        ui.matrixEdit->append(s);
    }
}

void fractals::on_randomMatrixButton_clicked()
{
    ui.matrixEdit->clear();
    for(int k=0; k < K_MAX; k++)
    {
        QString s;
        for(int i=0; i < 6; i++)
        {
           char str [128];
           sprintf(str, "%4.4f", (float)rand()/RAND_MAX);
           s+=QString(str) + "  ";
        }
        ui.matrixEdit->append(s);
    }
}

void fractals::on_addLineBut_clicked()
{
    float angle1 = qDegreesToRadians(ui.angle1SB->value());
    float angle2 = qDegreesToRadians(ui.angle2SB->value());
    float Tx = ((float)rand()/RAND_MAX);
    float Ty = ((float)rand()/RAND_MAX);

    char str [128];
    sprintf(str, "%4.4f %4.4f %4.4f %4.4f %4.4f %4.4f", cos(angle1), -sin(angle1), sin(angle2), cos(angle2), Tx, Ty );
    ui.matrixEdit->append(QString(str));

}

void fractals::on_pushButton_3_clicked()
{
    ui.angle1SB->setValue(60 * (float)rand()/RAND_MAX); //in degrees
    ui.angle2SB->setValue(60 * (float)rand()/RAND_MAX); //in degrees
    ui.TxSB->setValue((rand()/RAND_MAX));
    ui.TySB->setValue((rand()/RAND_MAX) );
}
