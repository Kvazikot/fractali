#ifndef FIT_RECTS_H
#define FIT_RECTS_H

#include <QPainter>
#include <vector>

#define MAX_POPULATION 25


class RectsFitter
{
public:
    double a,b,c,m,n;    // коэффициенты
    double s1,s2,s3,s4;
    int  MAX_VALUE;
    float minX, minY, maxX, maxY;
    std::vector<QRectF>  scaled_squares;
    std::vector<double> w;        // текущий вектор
    std::vector<double> tw;       //целевой вектор
    std::vector<int>  index2index;
    double Population[MAX_POPULATION][5];
    double NextPopulation[MAX_POPULATION][5];

    double likehood[MAX_POPULATION];
    double fitnesss[MAX_POPULATION];
    QMap<QString,int> pair_map;
    RectsFitter(float P[4]);
    void Solve();
    double get_fitness(double Population[][5]);
    int   get_index(double val);
    void  crossover(double p1[5], double p2[5], double c[5]);
    void DrawInitalRefinment(QPainter* painter, int w, int h);

};

#endif // FIT_RECTS_H
