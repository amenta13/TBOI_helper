#include "SpindownScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include "src/SpinDown.hpp"
#include "src/ItemDB.hpp"

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

    // Result image
    auto *imageLabel = new QLabel(this);
    imageLabel->setFixedSize(96, 96);
    imageLabel->setAlignment(Qt::AlignCenter);
    QPixmap placeHolder("src/images/questionmark.png");
    imageLabel->setPixmap(
        placeHolder.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation)
    );


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
    layout->addWidget(imageLabel);
    layout->addSpacing(20);
    layout->addWidget(btnBack);

    layout->setAlignment(Qt::AlignTop);

    // Logic connection
    connect(btnCalculate, &QPushButton::clicked, this, [inputBox, resultLabel, imageLabel, placeHolder]() {
        std::string name = inputBox->text().toStdString();

        if (name.empty()) {
            resultLabel->setText("Result: No item entered");
            imageLabel->setPixmap(
                placeHolder.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation)
            );
            return;
        }

        std::string result = SpinDown::byName(name);
        resultLabel->setText(QString::fromStdString(titlecase(result)));

        const Item* nextItem = ItemDatabase::instance().getByName(result);


        if (!nextItem) {
            imageLabel->setPixmap(
                placeHolder.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation)
            );
            return;
        }

        QPixmap pix(QString::fromStdString(nextItem->imagePath));

        if (!pix.isNull()) {
            imageLabel->setPixmap(
                pix.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation)
            );
        } else {
            imageLabel->setPixmap(
                placeHolder.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation)
            );
        }

    });


    // Navigation
    connect(btnBack, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(0);   // back to HomeScreen
    });
}
