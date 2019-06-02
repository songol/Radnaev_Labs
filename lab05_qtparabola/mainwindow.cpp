#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QLabel>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainLayout = new QGridLayout(ui->centralWidget);
    interface = new QGridLayout();
    QPushButton *plot_button =  new QPushButton("Calculate");
    connect(plot_button, &QPushButton::clicked, this, &MainWindow::drawMyFuncion);
    interface->addWidget(plot_button, 1, 0);
    a_val = new QLineEdit();
    b_val = new QLineEdit();
    c_val = new QLineEdit();
    QRegExp rx("\\[.]\\d{0,10}");
    a_val->setValidator(new QRegExpValidator(rx,this));
    b_val->setValidator(new QDoubleValidator(-100.0, 100.0, 2));
    c_val->setValidator(new QDoubleValidator(-100.0, 100.0, 2));
    a_val->setText("0.0");
    b_val->setText("0.0");
    c_val->setText("0.0");
    QFormLayout *input_layout = new QFormLayout();
    input_layout->addRow("A:", a_val);
    input_layout->addRow("B:", b_val);
    input_layout->addRow("C:", c_val);
    interface->addLayout(input_layout, 0, 0);
    mainLayout->addLayout(interface, 0, 0);
    //emit drawMyFuncion();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::drawMyFuncion() {
    m_chart = new QChart();
    qreal xmin = -1;
    qreal xmax = 1;
    qreal dx = 0.1;
    QLineSeries *series = new QLineSeries();
    for (qreal x = xmin; x < xmax; x += dx) {
        series->append(x, parabola(x));
    }
    series->setName("Parabola");
    m_chart->addSeries(series);
    m_chart->setTitle("Plot");

    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("X");
    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Y");
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setMinimumSize(640, 480);

    mainLayout->addWidget(m_chartView, 0, 1, 3, 1);

}

qreal MainWindow::parabola(qreal x){
    qreal a;
    qreal b;
    qreal c;
    if (a_val->text().isEmpty()){
        a = 0;
        a_val->setText("0.0");
    } else {
        a = a_val->text().toDouble();
    }
    if (b_val->text().isEmpty()){
        b= 0;
        b_val->setText("0.0");
    } else {
        b = b_val->text().toDouble();
    }
    if (c_val->text().isEmpty()){
        c = 0;
        c_val->setText("0.0");
    } else {
        c = c_val->text().toDouble();
    }

    return  a * x * x + b * x + c;
}
