#include <QApplication>
#include <QGraphicsScene>
#include <QPainter>
#include <QString>
#include <QDebug>
#include <stack>
#define _USE_MATH_DEFINES
#include <math.h>
#include "lsystem.h"

LSystem::LSystem()
{
    bAbort = false;
    theta = M_PI / 3;
    startA = 0;
    axiom = "F++F++F";
    newf = "F-F++F-F";
    generate_word(axiom, newf,"","", 2,"");
    qDebug() << word;
}


void LSystem::Draw(QImage& resultImage)
{
    QPainter  painter(&resultImage);
    double x0, y0, a;
    double x, y;
    std::stack<double> stack;
    QString W = word;
    qDebug() << word;
    int n = word.length();
    resultImage.fill(Qt::white);
    x0 = resultImage.width()/2;
    y0 = resultImage.height()/2;
    a = startA;
    for( int i=0; i < n; i++ )
    {
        if( W[i] == '+') a = a + theta;
        if( W[i] == '-') a = a - theta;
        if((  W[i] == 'F' ) )
        {
            x = x0 + 10 * cos(a);
            y = y0 + 10 * sin(a);
            painter.drawLine(x0,y0,x,y);
            x0 = x; y0 = y;
        }
        if( W[i] == 'b' )
        {
            x = x0 + 10 * cos(a);
            y = y0 + 10 * sin(a);
            x0 = x; y0 = y;
        }
        if( W[i] == ']' )
        {
            x0 = stack.top();
            stack.pop();
            y0 = stack.top();
            stack.pop();
            a = stack.top();
            stack.pop();
        }
        if( W[i] == '[' )
        {
            stack.push(a);
            stack.push(y0);
            stack.push(x0);
        }

    }

}


void LSystem::DrawToScene(QGraphicsScene* scene, QProgressBar* progress, bool bWithDelay)
{
    double x0, y0, a;
    double x, y;
    std::stack<double> stack;
    QString W = word;
    qDebug() << word;
    int n = word.length();
    scene->setBackgroundBrush(Qt::white);
    x0 = scene->width()/2;
    y0 = scene->height()/2;
    a = startA;
    for( int i=0; i < n; i++ )
    {
        if( bWithDelay )
        {
            progress->setValue(i * 100 / n);
            QApplication::processEvents();
        }
        if( bAbort )
        {
            bAbort = false;
            return;
        }
        if( W[i] == '+') a = a + theta;
        if( W[i] == '-') a = a - theta;
        if((  W[i] == 'F' ) )
        {
            x = x0 + 10 * cos(a);
            y = y0 + 10 * sin(a);
            scene->addLine(x0,y0,x,y);
            x0 = x; y0 = y;
        }
        if( W[i] == 'b' )
        {
            x = x0 + 10 * cos(a);
            y = y0 + 10 * sin(a);
            x0 = x; y0 = y;
        }
        if( W[i] == ']' )
        {
            x0 = stack.top();
            stack.pop();
            y0 = stack.top();
            stack.pop();
            a = stack.top();
            stack.pop();
        }
        if( W[i] == '[' )
        {
            stack.push(a);
            stack.push(y0);
            stack.push(x0);
        }

    }

}

QString LSystem::generate_word(QString axiom, QString newf, QString newx, QString newy, int level, QString newb="")
{

    QString W = axiom;

    while (level > 0)
    {
        QString T;
        for( int i=0;  i < W.length(); i++ )
        {
            if( W[i] == '+' ) T = T + "+";
            if( W[i] == '-' ) T = T + "-";
            if( W[i] == '[' ) T = T + "[";
            if( W[i] == ']' ) T = T + "]";
            if( W[i] == 'F' ) T = T + newf;
            if( W[i] == 'b' ) T = T + newb;
            if( W[i] == 'X' ) T = T + newx;
            if( W[i] == 'Y' ) T = T + newy;
        }
        W = T;
        level--;
    }
    word = W;
    return W;
}


void LSystem::Abort()
{
    bAbort = true;
}
