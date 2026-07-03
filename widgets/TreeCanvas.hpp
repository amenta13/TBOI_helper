#pragma once
#include <QWidget>
#include "TreeNode.hpp"

class TreeCanvas : public QWidget {
    Q_OBJECT

public:
    explicit TreeCanvas(QWidget* parent = nullptr);

    void setRoot(TreeNode* root);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    TreeNode* rootNode;

    void drawNode(QPainter& painter, TreeNode* node, int x, int y);
};
