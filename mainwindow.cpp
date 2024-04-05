#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->calculateButton, &QPushButton::clicked, this, &MainWindow::calculate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate() {
    // Generowanie 10 losowych liczb
    QVector<int> numbers;
    for(int i = 0; i < 10; ++i) {
        numbers.push_back(QRandomGenerator::global()->bounded(1, 101));
    }

    // Obliczanie średniej
    double mean = std::accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();

    // Obliczanie wartości wg wzoru
    double result = 0.0;
    for(int i = 0; i < numbers.size(); ++i) {
        result += std::pow(numbers[i] - mean, 2);
        if(i < numbers.size() - 1) {
            result += std::pow(numbers[i + 1] - mean, 2);
        }
    }
    result = std::sqrt(result);

    QMessageBox::information(this, "Wynik", QString("Średnia: %1\nWynik po przepuszczeniu przez wzór: %2").arg(mean).arg(result));
}
