#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>
#include <time.h>
#include <iostream>
#include <numeric>
#include  <cmath>
#include<algorithm>
#include<QMessageBox>

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

void MainWindow::new_coordinates()
{
    qDebug() << "qvn" << qv_n.size();
    for(int a=0;a<qv_n.size();a++){
        new_n.append(qv_n[a]+delta_n(a, 1));
        new_m.append(qv_m[a]+delta_n(a, 2)) ;
    }
    clearData2();
    qDebug()<<new_n;
    ui->plot->graph(1)->setData(new_n,new_m);
    ui->plot->graph(0)->setData(qv_x,qv_y);
    ui->plot->replot();
    ui->plot->update();
    qv_n = new_n;
    qv_m = new_m;

}

double MainWindow::delta_n(int a, int z)
{
    QVector<double> vec_c=(z>1)?qv_y:qv_x;
    QVector<double> vec_r=(z>1)?qv_m:qv_n;
    double alfa=1;double beta=1;
    double summe=0;
    for (int i=0;i<vec_c.size();i++){
        qDebug() << "csize" << vec_c.size() << i;
        qDebug() << "rsize" << vec_r.size() << a;
        summe +=v_i_a(i,a,z)*((vec_c[i]-vec_r[a]));
        qDebug() << "Summme" << summe;
    }
    qDebug() << "BREAK";
    //qDebug() << "ra-1" << vec_r[(((a-1)%vec_r.size())+vec_r.size())%vec_r.size()];
    //qDebug() << "ra" << vec_r[a];
    //qDebug() << "ra+1" << vec_r[(((a+1)%vec_r.size())+vec_r.size())%vec_r.size()];
    qDebug() << K_von_n(a);
    double delta=alfa*summe+beta*K_von_n(a)*(vec_r[(((a-1)%vec_r.size())+vec_r.size())%vec_r.size()]
            +vec_r[a]-2*vec_r[(((a+1)%vec_r.size())+vec_r.size())%vec_r.size()]);
    qDebug() << "Delta" << delta;
    return delta;
}

double MainWindow::v_i_a(int i,int a,int z)
{
    QVector<double> vec_c=(z>1)?qv_y:qv_x;
    QVector<double> vec_r=(z>1)?qv_m:qv_n;
    double summ=0;
    for (int k=0;k<qv_n.size();k++){
        summ+=exp((-1)*(pow(abs(vec_c[i]-vec_r[k]), 2))/T_von_n(a));

    }
    double v_i_a=(exp((-1)*(pow(abs(vec_c[i]-vec_r[a]),2))/T_von_n(a)))/summ;
    qDebug() << "via " << v_i_a;
    return v_i_a;

}

double MainWindow::T_von_n(int n)
{
    double T=2*pow(K_von_n(n),2);
    return T;
}

double MainWindow::K_von_n(int n)
{
    double K_null=0.2;
    double a=pow(0.99,floor(n/50))*K_null;
    double b=0.01;
    double K=(a>b)?a:b;
    return K;
}

void MainWindow::on_btn_random_clicked()
{
    clearData2();
    srand(time(nullptr));
    int random_cities=ui->number_cities->value();
    for (int i=0;i<random_cities;i++){
        addPoint(((double)rand() / RAND_MAX) * 5,((double)rand() / RAND_MAX) * 5);//add points randomly
        clicks_counter.append(1);
    }
    middlePoint(middlePoint_x(),middlePoint_y(),clicks_counter.count());
    plot();

}

void MainWindow::on_btn_clear_clicked()
{
    clearData();
    clearData2();
    plot();
}

void MainWindow::clickedGraph(QMouseEvent *event)
{
    clearData2();
    QPoint point = event ->pos();
    clicks_counter.append(1);
    addPoint(ui->plot->xAxis->pixelToCoord(point.x()),ui->plot->yAxis->pixelToCoord(point.y()));
    middlePoint(middlePoint_x(),middlePoint_y(),clicks_counter.count());
    plot();
}


void MainWindow::on_btn_start_clicked()
{
   new_coordinates();
}
