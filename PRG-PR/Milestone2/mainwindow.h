#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addPoint(double x,double y);
    void clearData();
    void clearData2();
    void plot();
    void middlePoint(double n,double m,int number_cities);
    double middlePoint_x();
    double middlePoint_y();
    void new_coordinates();
    double delta_n(int j,int c);
    double v_i_a(int i,int j,int z);
    double T_von_n(int n);
    double K_von_n(int n);

private slots:
    void on_btn_random_clicked();

    void on_btn_clear_clicked();
    void clickedGraph(QMouseEvent *event);

    void on_btn_start_clicked();

private:
    int iters;
    Ui::MainWindow *ui;
    QVector<double>qv_x,qv_y;
    QVector<double>qv_n,qv_m;
    QVector<double>new_n,new_m;
    QVector<int>clicks_counter;
};

#endif // MAINWINDOW_H
