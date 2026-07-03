#include "HomeScreen.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QApplication>

HomeScreen::HomeScreen(QWidget *parent)
    : QWidget(parent)
{
    auto *stack = qobject_cast<QStackedWidget*>(parent);

    auto *layout = new QVBoxLayout(this);

    auto *title = new QLabel("Isaac Tools", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 28px; font-weight: bold;");

    auto *btnSpindown = new QPushButton("Spindown Dice Tool", this);
    auto *btnItems = new QPushButton("Item Browser", this);
    auto *btnTree = new QPushButton("Gameplay Tree", this);
    auto *btnChars = new QPushButton("Character Info", this);

    auto *btnExit = new QPushButton("Exit", this);

    btnSpindown->setMinimumHeight(40);
    btnItems->setMinimumHeight(40);
    btnTree->setMinimumHeight(40);
    btnChars->setMinimumHeight(40);

    layout->addWidget(title);
    layout->addSpacing(20);
    layout->addWidget(btnSpindown);
    layout->addWidget(btnItems);
    layout->addWidget(btnTree);
    layout->addWidget(btnChars);

    layout->addSpacing(20);
    layout->addWidget(btnExit);

    layout->setAlignment(Qt::AlignTop);

    // Navigation (will work once screens exist)
    connect(btnSpindown, &QPushButton::clicked, [stack](){ stack->setCurrentIndex(1); });
    connect(btnItems, &QPushButton::clicked, [stack](){ stack->setCurrentIndex(2); });
    connect(btnTree, &QPushButton::clicked, [stack](){ stack->setCurrentIndex(3); });
    connect(btnChars, &QPushButton::clicked, [stack](){ stack->setCurrentIndex(4); });

    // Exit button
    connect(btnExit, &QPushButton::clicked, []() {
        QApplication::quit();
    });
}
