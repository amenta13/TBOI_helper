#pragma once
#include <QMainWindow>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stack;
    QWidget *createHomeScreen();
};
