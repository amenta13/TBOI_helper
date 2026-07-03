#include "SpindownScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include "src/SpinDown.hpp"

SpindownScreen::SpindownScreen(QWidget *parent)
    : QWidget(parent)
{
    auto *stack = qobject_cast<QStackedWidget*>(parent);

    auto *layout = new QVBoxLayout(this);

    // Title
    auto *title = new QLabel("Spindown Dice Tool", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold;");

    // Input row
    auto *inputRow = new QHBoxLayout();
    auto *inputLabel = new QLabel("Item Name:", this);
    auto *inputBox = new QLineEdit(this);
    inputBox->setPlaceholderText("Enter item name...");

    inputRow->addWidget(inputLabel);
    inputRow->addWidget(inputBox);

    // Result label
    auto *resultLabel = new QLabel("Result: ", this);
    resultLabel->setStyleSheet("font-size: 18px;");

    // Buttons
    auto *btnCalculate = new QPushButton("Calculate Next ID", this);
    auto *btnBack = new QPushButton("Back to Home", this);

    btnCalculate->setMinimumHeight(35);
    btnBack->setMinimumHeight(35);

    // Add widgets to layout
    layout->addWidget(title);
    layout->addSpacing(15);
    layout->addLayout(inputRow);
    layout->addWidget(btnCalculate);
    layout->addSpacing(10);
    layout->addWidget(resultLabel);
    layout->addSpacing(20);
    layout->addWidget(btnBack);

    layout->setAlignment(Qt::AlignTop);

    // Logic connection
    connect(btnCalculate, &QPushButton::clicked, this, [inputBox, resultLabel]() {
        std::string name = inputBox->text().toStdString();

        if (name.empty()) {
            resultLabel->setText("Result: No item entered");
            return;
        }

        std::string result = SpinDown::byName(name);
        resultLabel->setText(QString::fromStdString(result));
    });


    // Navigation
    connect(btnBack, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(0);   // back to HomeScreen
    });
}
