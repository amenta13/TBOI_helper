#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>

class ItemBrowserScreen : public QWidget {
    Q_OBJECT

public:
    explicit ItemBrowserScreen(QWidget* parent = nullptr);

private:
    QLineEdit* searchBox;
    QListWidget* listWidget;
    QLabel* detailsLabel;
    QPushButton* backButton;

    void populateList(const std::string& query);
};
