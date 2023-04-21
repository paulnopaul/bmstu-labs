#ifndef MARKOVCHART_H
#define MARKOVCHART_H

#include <QWidget>
#include <QGridLayout>
#include <QTCharts/QChartView>
#include <QTCharts/QLineSeries>
#include <QTCharts/QChart>

class MarkovChart : public QWidget
{
    Q_OBJECT
        public:
                 explicit MarkovChart(QWidget *parent = nullptr);
        signals:
        private:
     QtCharts::QChartView *chartView;
            QtCharts::QChart *chart;
            QtCharts::QLineSeries *series;
            QGridLayout *layout;
};

#endif // MARKOVCHART_H
