#ifndef MATRIXINPUT_H
#define MATRIXINPUT_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QVector>


class MatrixInput : public QWidget
{
    Q_OBJECT
        public:
                 explicit MatrixInput(QWidget *parent = nullptr);
            void updateSize(int newSize);
signals:
             private:
    QGridLayout *layout;
                 QVector<QVector<QDoubleSpinBox *>> matrix;
    int size;
};

#endif // MATRIXINPUT_H
