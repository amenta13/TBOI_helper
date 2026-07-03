#include "GameplayTreeScreen.h"
#include <QVBoxLayout>
#include <QStackedWidget>

GameplayTreeScreen::GameplayTreeScreen(QWidget* parent)
    : QWidget(parent)
{
    auto* stack = qobject_cast<QStackedWidget*>(parent);

    scrollArea = new QScrollArea(this);
    canvas = new TreeCanvas(this);
    backButton = new QPushButton("Back", this);

    scrollArea->setWidget(canvas);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(scrollArea);
    layout->addWidget(backButton);
    setLayout(layout);

    // Load a sample tree
    canvas->setRoot(buildSampleTree());

    connect(backButton, &QPushButton::clicked, this, [stack]() {
        stack->setCurrentIndex(0);
    });
}

TreeNode* GameplayTreeScreen::buildSampleTree() {
    TreeNode* root = new TreeNode{"Start"};

    TreeNode* a = new TreeNode{"Path A"};
    TreeNode* b = new TreeNode{"Path B"};
    TreeNode* c = new TreeNode{"Path C"};

    root->children = {a, b, c};

    a->children = { new TreeNode{"A1"}, new TreeNode{"A2"} };
    b->children = { new TreeNode{"B1"} };
    c->children = { new TreeNode{"C1"}, new TreeNode{"C2"}, new TreeNode{"C3"} };

    return root;
}
