#ifndef FRACTALS_H
#define FRACTALS_H
#include <QImage>
#include <QThread>
#include <QTimerEvent>
#include <QMainWindow>
#include "lsystem.h"
#include "ui_fractals.h"

class QResizeEvent;

struct Complex
{
	double i;
	double j;
	double mod() {return i * i + j * j; }
//	double mod() {return sqrt(i * i + j * j); }
};

class fractals : public QMainWindow
{
	Q_OBJECT

public:
	Ui::fractalsClass ui;
    LSystem lsystem;
    QImage im1;
    QImage im2;
	QImage resultImage;
    QGraphicsScene scene;
    QImage image;
	int myProgress;
    fractals(QWidget *parent = 0);
	~fractals();
	bool CheckIdx(int i, int j);
	void print(char* str);




private:


public slots:	
	void updatePixmap(const QImage &);
    void updateCellular();

private slots:
	void on_abortBut_clicked();
	void on_drawButton_clicked();
	void timerEvent(QTimerEvent*);
	void DrawJulia(int npix, int npiy, int kcolor, double pmin, double qmin, double xmin, double ymin, double xmax, double ymax);
	void resizeEvent ( QResizeEvent * event );
	void clear();
	
    void on_drawButton_2_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_setMaximumRes_clicked();
    void on_zoomInB_clicked();
    void on_zoomOutB_clicked();
    void on_clearButton_clicked();
    void on_abortBut_2_clicked();
    void on_drawButton_3_clicked();
    void on_clearButton_2_clicked();
    void on_pushButton_clicked();
    void on_drawGridCB_clicked();
    void on_pushButton_2_clicked();
    void on_fastDrawCB_clicked();
    void on_reinitWorld_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_reinitWorld_pressed();
};


class RenderThread : public QThread
{
	Q_OBJECT

public:
	fractals* pdlg;
	QImage resultImage;
	void DrawKamTorus(double square, double ax);
	void DrawAbstract(int r, int cmax,int npix, int npiy);
	bool CheckIdx(int i, int j);
    RenderThread(fractals* p);
	void run();

signals:
	void renderedImage(const QImage &image);

  
};



#endif // FRACTALS_H
