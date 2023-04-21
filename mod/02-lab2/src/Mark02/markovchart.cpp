#include "markovchart.h"

using namespace QtCharts;

MarkovChart::MarkovChart(QWidget *parent) : QWidget(parent)
{
    series = new QLineSeries();
    for (double i = 0; i < 100; ++i) {
        series->append(i, i*i);
    }
    chart = new QChart();
    chart->addSeries(series);
    chartView = new QChartView(chart);
    layout = new QGridLayout();
    layout->addWidget(chartView);
    this->setLayout(layout);
}
