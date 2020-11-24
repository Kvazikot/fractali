#include <QApplication>
#include <time.h>
#include <algorithm>
#include <QDebug>
#include <QPainter>
#include <cmath>
#include "fit_rects.h"

GeneCurveFitter::GeneCurveFitter(float P[4])
{
    a = 3;
    b = 4;
    c = 3;
    //double U = (double)rand()/RAND_MAX;
    //qDebug() << 10*U;
    m = 4;
    n = 4;
    s1 = a * b;
    s2 = c * b;
    s3 = m * (a + c);
    s4 = n * (a + c);
    double sum = s1+s2+s3+s4;
    tSum = 72;

    //вектор отношений площадей
    w.resize(4);
    tw.resize(4);
    w[0] = 45./100.;
    w[1] = 5./100.;
    w[2] = 10./100.;
    w[3] = 40./100.;

    tw[0] = P[0];
    tw[1] = P[1];
    tw[2] = P[2];
    tw[3] = P[3];


    Solve();
}

double GetSumKoeff(double c[5])
{
    return 1./c[0] + 1./c[1] + 1./c[2] + 1./c[3] + 1./c[4];
}

void setin_population(int i,double a, double b, double c, double m, double n, double Population[][5])
{
    Population[i][0] = a;
    Population[i][1] = b;
    Population[i][2] = c;
    Population[i][3] = m;
    Population[i][4] = n;
}

void setin_population2(int i,double c[5], double Population[][5])
{
    Population[i][0] = c[0];
    Population[i][1] = c[1];
    Population[i][2] = c[2];
    Population[i][3] = c[3];
    Population[i][4] = c[4];
}


void get_from_population(int i, double Population[][5], double c[5])
{
    c[0] = Population[i][0];
    c[1] = Population[i][1];
    c[2] = Population[i][2];
    c[3] = Population[i][3];
    c[4] = Population[i][4];
}

void GeneCurveFitter::crossover(double p1[5], double p2[5], double c[5])
{
   int board = rand()%4;
   bool orr = rand()%101 < 50;

   switch (board) {
   case 0:
       if( orr )
         { c[0] = p1[0]; c[1] = p2[1]; c[2] = p2[2]; c[3] = p2[3]; c[4] = p2[4]; }
       else
         { c[0] = p2[0]; c[1] = p1[1]; c[2] = p1[2]; c[3] = p1[3]; c[4] = p1[4]; }
       break;
   case 1:
       if( orr )
          { c[0] = p1[0]; c[1] = p1[1]; c[2] = p2[2]; c[3] = p2[3]; c[4] = p2[4]; }
       else
          { c[0] = p2[0]; c[1] = p2[1]; c[2] = p1[2]; c[3] = p1[3]; c[4] = p1[4]; }
       break;
   case 2:
       if( orr )
          { c[0] = p1[0]; c[1] = p1[1]; c[2] = p1[2]; c[3] = p2[3]; c[4] = p2[4]; }
       else
          { c[0] = p2[0]; c[1] = p2[1]; c[2] = p2[2]; c[3] = p1[3]; c[4] = p1[4]; }
       break;
   case 3:
       if( orr )
          { c[0] = p1[0]; c[1] = p1[1]; c[2] = p1[2]; c[3] = p1[3]; c[4] = p2[4]; }
       else
          { c[0] = p2[0]; c[1] = p2[1]; c[2] = p2[2]; c[3] = p2[3]; c[4] = p1[4]; }
       break;
   }
   //мутации
   int max = tSum+1;
   for(int i=0; i<5; i++)
     if (rand() % 101 < 5) c[i] = rand() % max ;
}

double equation(double c[5])
{
    //Rs[i] = a * b + c * b + m * (a+c) + n * (a + c);
    return c[0] * c[1] + c[2]*c[1] + c[3] * (c[0]+c[2]) + c[4] * (c[0]+c[2]);
}

double getVectorDiff(std::vector<double>& w, std::vector<double>& tw)
{
    double diff=0;
    for(int i=0; i < w.size(); i++)
    {
        diff+=fabs((w[i] - tw[i])*(w[i] - tw[i]));
    }
    return diff;
}

// средняя приспособленность fitness потомков
double GeneCurveFitter::get_fitness(double Population[][5])
{
    double fitness=0;
    double c[5];
    double MultInv=0;
    for(int i=0; i < MAX_POPULATION; i++)
    {
        get_from_population(i, Population, c);
        s1 = c[0] * c[1];
        s2 = c[2] * c[1];
        s3 = c[3] * (c[0] + c[2]);
        s4 = c[4] * (c[0] + c[2]);
        double sum = s1+s2+s3+s4;
        if(sum==0) continue;
        w[0] = s1/sum;
        w[1] = s2/sum;
        w[2] = s3/sum;
        w[3] = s4/sum;
        sort(w.begin(), w.end());
        sort(tw.begin(), tw.end());
        fitnesss[i] = getVectorDiff(w,tw);//fabs(tSum - equation(c));
        //if(fitnesss[i]==0) return 0;
        MultInv+= 1/fitnesss[i];
        fitness+=fitnesss[i];
    }
    double last = 0;
    for(int i=0; i < MAX_POPULATION; i++)
      likehood[i] = last = last + ((1/(fitnesss[i]) / MultInv) * 100);
    fitness = fitness/MAX_POPULATION;
    return fitness;
}

int GeneCurveFitter::get_index(double val) {
    double last = 0;
    for(int i=0;i<MAX_POPULATION;i++) {
        if (last <= val && val <= likehood[i]) return i;
        else last = likehood[i];
    }
    return 5;
}

void PrintPopulation(double Population[][5])
{
    QString s="Population={\n";
    for(int i=0; i < MAX_POPULATION; i++)
    {
        for(int j=0; j < 5; j++)
            s+=QString::number(Population[i][j])+" ";
        s+="\n";
        s="";
    }
}

bool genes_equal(double p1[5], double p2[5])
{
    for(int i=0; i < 5; i++)
        if(p1[i]!=p2[i]) return false;
    return true;
}

bool compare_by_square(QRectF& rc1, QRectF& rc2)
{
    return (rc1.width() * rc1.height()) < (rc2.width() * rc2.height());
}

//a * b + c * b + m * (a+c) + n * (a + c) = tSum;
void GeneCurveFitter::Solve()
{
    // коэф лежат на отрезке [0..72]
    srand((unsigned)time(NULL));

    //генерируем первую популяцию

    for(int i=0; i < MAX_POPULATION; i++)
    {
        int max = tSum+1;
        a = rand()%max;
        b = rand()%max;
        c = rand()%max;
        m = rand()%max;
        n = rand()%max;
        setin_population(i,a,b,c,m,n,Population);
    }
    PrintPopulation(Population);

    double fitness=20;
    double next_fitness=20;
    int generation=0;
    while(fitness > 0.0001)
    {
        generation++;
        //расстояние до tSum = коэфф. выживаемости
        double c[5];

        fitness = get_fitness(Population);
        if( fitness != fitness  )
          QApplication::processEvents();

        qDebug("gen %d fitness %f ", generation, fitness);

        // выбираем 5 пар родителей у них будет по одному ребенку
        double p1[5];
        double p2[5];

        for(int i=0; i < MAX_POPULATION; i++)
        {
            int i1=0,i2=0,iterations=0;

            while(i1 == i2 || genes_equal(p1, p2) )
            {
                i1 = get_index((double)(rand() % 101));
                i2 = get_index((double)(rand() % 101));
                get_from_population(i1, Population, p1);
                get_from_population(i2, Population, p2);
                if (++iterations > 25) break;
            }
            crossover(p1,p2,c);
            /*
            qDebug("crossover p1=%f,%f,%f,%f,%f p2=%f,%f,%f,%f,%f c=%f,%f,%f,%f,%f",
                   p1[0],p1[1],p1[2],p1[3],p1[4],
                    p2[0],p2[1],p2[2],p2[3],p2[4],
                    c[0],c[1],c[2],c[3],c[4]);
                    */
            setin_population2(i, c, NextPopulation);
        }

        //копирование популяции
        for(int i=0; i < MAX_POPULATION; i++)
        {
            for(int j=0; j < 5; j++)
            {
                Population[i][j] = NextPopulation[i][j];
            }
        }

        PrintPopulation(Population);

    }
    qDebug() << "all done!";

    double* min_fitness = std::min_element(&fitnesss[0], &fitnesss[MAX_POPULATION]);
    int index = (int)(min_fitness - &fitnesss[0]);
    a = Population[index][0];
    b = Population[index][1];
    c = Population[index][2];
    m = Population[index][3];
    n = Population[index][4];

    float sizex = b+m+n;
    float sizey = a+c;
    QRectF rc1(0,0,b/sizex,a/sizey);
    QRectF rc2(b/sizex,0,m/sizex,(a+c)/sizey);
    QRectF rc3((b+m)/sizex,0,n/sizex,(a+c)/sizey);
    QRectF rc4(0,a/sizey,b/sizex,c/sizey);
    scaled_squares.push_back(rc4);
    scaled_squares.push_back(rc1);
    scaled_squares.push_back(rc3);
    scaled_squares.push_back(rc2);
    //sort(scaled_squares.begin(), scaled_squares.end(),compare_by_square);

}

void GeneCurveFitter::DrawInitalRefinment(QPainter* painter, int w, int h)
{
    painter->save();
    painter->translate(w/4,h/4);
   // painter->scale(10,10);
    QRect rc1(0,0,b,a);
    painter->drawRect(rc1);
    QRect rc2(b,0,m,a+c);
    painter->drawRect(rc2);
    QRect rc3(b+m,0,n,a+c);
    painter->drawRect(rc3);
    QRect rc4(0,a,b,c);
    painter->drawRect(rc4);
    painter->restore();

    QString s;
    s = s.sprintf("Squares: w1=%0.4f w2=%0.4f w3=%0.4f w4=%0.4f",this->w[0],this->w[1],this->w[2],this->w[3]);
    //painter->scale(,1);
    painter->drawText(QPointF(0,h-60),s);

    s = s.sprintf("Target: tw1=%0.4f tw2=%0.4f tw3=%0.4f tw4=%0.4f ",tw[0],tw[1],tw[2],tw[3]);
    painter->drawText(QPointF(0,h-40),s);

    s = s.sprintf("Coef: a=%0.4f b=%0.4f m=%0.4f n=%0.4f c=%0.4f",a,b,m,n,c);
    //painter->scale(,1);
    painter->drawText(QPointF(0,h-20),s);

}


