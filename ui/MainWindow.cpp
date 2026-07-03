#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "screens/Home/HomeScreen.h"
#include "screens/Spindown/SpindownScreen.h"
#include "screens/ItemBrowser/ItemBrowserScreen.h"
#include "screens/CharacterInfo/CharacterInfoScreen.h"
#include "screens/GameplayTree/GameplayTreeScreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stack = new QStackedWidget(this);

    // Add screen to pages
    stack->addWidget(new HomeScreen(stack));
    stack->addWidget(new SpindownScreen(stack));
    stack->addWidget(new ItemBrowserScreen(stack));
    stack->addWidget(new CharacterInfoScreen(stack));
    stack->addWidget(new GameplayTreeScreen(stack));

    setCentralWidget(stack);
    setWindowTitle("Isaac Tools");
    this->showFullScreen();
}