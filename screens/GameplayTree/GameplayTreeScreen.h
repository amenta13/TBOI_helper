#pragma once
#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include "widgets/TreeCanvas.hpp"

class GameplayTreeScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameplayTreeScreen(QWidget* parent = nullptr);

private:
    QScrollArea* scrollArea;
    TreeCanvas* canvas;
    QPushButton* backButton;

    TreeNode* buildSampleTree();
};
