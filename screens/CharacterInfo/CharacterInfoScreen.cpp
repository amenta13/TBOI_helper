#include "CharacterInfoScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>

CharacterInfoScreen::CharacterInfoScreen(QWidget* parent)
    : QWidget(parent)
{
    auto* stack = qobject_cast<QStackedWidget*>(parent);

    characterBox = new QComboBox(this);
    infoLabel = new QLabel("Select a character", this);
    backButton = new QPushButton("Back", this);

    // Add characters (you can expand this later)
    characterBox->addItem("Isaac");
    characterBox->addItem("Magdalene");
    characterBox->addItem("Cain");
    characterBox->addItem("Judas");
    characterBox->addItem("???");
    characterBox->addItem("Eve");
    characterBox->addItem("Samson");
    characterBox->addItem("Azazel");
    characterBox->addItem("Lazarus");
    characterBox->addItem("Eden");
    characterBox->addItem("The Lost");

    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(characterBox);
    layout->addWidget(infoLabel);
    layout->addWidget(backButton);
    setLayout(layout);

    // Logic: update info when character changes
    connect(characterBox, &QComboBox::currentTextChanged, this, [this](const QString& name) {
        updateInfo(name);
    });

    // Navigation
    connect(backButton, &QPushButton::clicked, this, [stack]() {
        stack->setCurrentIndex(0);
    });
}

void CharacterInfoScreen::updateInfo(const QString& character) {
    // Placeholder data — you can expand later
    if (character == "Isaac") {
        infoLabel->setText("Starting Item: D6\nHealth: 3 Red Hearts");
    }
    else if (character == "Magdalene") {
        infoLabel->setText("Starting Item: Yum Heart\nHealth: 4 Red Hearts");
    }
    else if (character == "Cain") {
        infoLabel->setText("Starting Item: Paper Clip\nHealth: 2 Red Hearts");
    }
    else {
        infoLabel->setText("Info not added yet");
    }
}
