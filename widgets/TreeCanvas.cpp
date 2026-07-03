#include "TreeCanvas.hpp"
#include <QPainter>

TreeCanvas::TreeCanvas(QWidget* parent)
    : QWidget(parent), rootNode(nullptr)
{
    setMinimumSize(2000, 2000); // Large canvas
}

void TreeCanvas::setRoot(TreeNode* root) {
    rootNode = root;
    update();
}

void TreeCanvas::paintEvent(QPaintEvent*) {
    if (!rootNode) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawNode(painter, rootNode, 100, 100);
}

void TreeCanvas::drawNode(QPainter& painter, TreeNode* node, int x, int y) {
    // Draw node box
    QRect rect(x, y, 150, 40);
    painter.drawRect(rect);
    painter.drawText(rect, Qt::AlignCenter, QString::fromStdString(node->name));

    // Draw children
    int childX = x - (node->children.size() * 100);
    int childY = y + 120;

    for (TreeNode* child : node->children) {
        // Draw connecting line
        painter.drawLine(x + 75, y + 40, childX + 75, childY);

        // Draw child node
        drawNode(painter, child, childX, childY);

        childX += 200;
    }
}
