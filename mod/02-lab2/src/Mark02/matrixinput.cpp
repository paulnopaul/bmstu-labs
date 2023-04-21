#include "matrixinput.h"

#include <QList>
#include <iostream>

using namespace std;

MatrixInput::MatrixInput(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout();
    this->setLayout(layout);
    int newSize = 2;

    size = 0;

    size = newSize;
    matrix = QVector<QVector<QDoubleSpinBox *>>(newSize, QVector<QDoubleSpinBox *>(newSize));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            auto b = new QDoubleSpinBox();
            matrix[i][j] = b;
            layout->addWidget(b, i, j);
        }
    }
    // updateSize(2);
}

void MatrixInput::updateSize(int newSize) {
    cout << "updateSize called" << endl;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->layout->removeWidget(matrix[i][j]);
        }
    }
}
