#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <gtest/gtest.h>
#include <QMainWindow>
#include <QGridLayout>
#include <QtCharts/QtCharts>
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    qreal parabola(qreal a, qreal b, qreal c, qreal x);
public Q_SLOTS:
    void drawMyFuncion();
    
private:
    QChart *m_chart;

    QChartView *m_chartView;
    QGridLayout *interface;
    QGridLayout *mainLayout;

    QLineEdit *a_val, *b_val, *c_val;




    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
