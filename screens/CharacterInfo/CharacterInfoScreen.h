#pragma once
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

class CharacterInfoScreen : public QWidget {
    Q_OBJECT

public:
    explicit CharacterInfoScreen(QWidget* parent = nullptr);

private:
    QComboBox* characterBox;
    QLabel* infoLabel;
    QPushButton* backButton;

    void updateInfo(const QString& character);
};
