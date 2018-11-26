#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>
#include <time.h>
#include <iostream>
#include <numeric>
#include  <cmath>
#include<QMessageBox>
#define PI 3.14159265

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc));
    ui->plot->graph(0)->setPen(QPen(Qt::blue));
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);//No line connecting points
    ui->plot->addGraph(ui->plot->xAxis, ui->plot->yAxis);
    ui->plot->graph(1)->setLineStyle(QCPGraph::lsNone);//No line connecting points
    ui->plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
    ui->plot->graph(1)->setPen(QPen(Qt::red));
    connect(ui->plot,SIGNAL(mousePress(QMouseEvent *)),SLOT(clickedGraph(QMouseEvent *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);
}
void MainWindow::clearData()
{
    qv_x.clear();
    qv_y.clear();
    clicks_counter.clear();
}
void MainWindow::clearData2()
{
    qv_n.clear();
    qv_m.clear();
}

void MainWindow::plot()
{
    ui->plot->graph(0)->setData(qv_x,qv_y);
    ui->plot->graph(1)->setData(qv_n,qv_m);
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::middlePoint(double n, double m,int number)
{
    double circle_points=floor(2.5*number);
    for (double i=0;i<circle_points;i++){
        double xDegrees = 360/circle_points*(i+1);
        double x = xDegrees*3.14159/180;
        qv_n.append(0.5*cos(x)+n);
        qv_m.append(0.5*sin(x)+m);
    }
    qDebug()<<n<<m;
    qDebug()<<qv_n<<qv_m;
}

double MainWindow::middlePoint_x()
{
    double sum_x=0;

    for (int i=0;i<qv_x.count();i++){
        sum_x+=qv_x[i];
    }
    double middle_x;
    return middle_x=sum_x/qv_x.count();
}
double MainWindow::middlePoint_y()
{
    double sum_y=0;

    for (int i=0;i<qv_y.count();i++){
        sum_y+=qv_y[i];
    }
    double middle_y;
    return middle_y=sum_y/qv_y.count();
}

void MainWindow::on_btn_random_clicked()
{
    srand(time(nullptr));
    int random_cities=ui->number_cities->value();
    for (int i=0;i<random_cities;i++){
        addPoint(((double)rand() / RAND_MAX) * 5,((double)rand() / RAND_MAX) * 5);//add points randomly
        clicks_counter.append(1);
    }
    middlePoint(middlePoint_x(),middlePoint_y(),clicks_counter.count());
    plot();
    clearData2();
}

void MainWindow::on_btn_clear_clicked()
{
    clearData();
    clearData2();
    plot();
}

void MainWindow::clickedGraph(QMouseEvent *event)
{
    QPoint point = event ->pos();
    clicks_counter.append(1);
    addPoint(ui->plot->xAxis->pixelToCoord(point.x()),ui->plot->yAxis->pixelToCoord(point.y()));
    middlePoint(middlePoint_x(),middlePoint_y(),clicks_counter.count());
    plot();
    qDebug()<<qv_n<<qv_m;
    clearData2();
}


void MainWindow::on_btn_start_clicked()
{
   QMessageBox::critical(this,"FehlerMeldung","Noch nicht implementiert");
}
