#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <QProgressBar>
#include <QGraphicsScene>
#include <QImage>

class LSystem
{
public:      
    double  theta;
    double  startA;
    bool    bAbort;
    QString axiom;
    QString newf;
    QString word;

    LSystem();
    QString generate_word(QString axiom, QString newf, QString newx, QString newy, int level, QString newb);
    void Draw(QImage& resultImage);
    void DrawToScene(QGraphicsScene* scene, QProgressBar* progress, bool bWithDelay);
    void Abort();
};

#endif // LSYSTEM_H
