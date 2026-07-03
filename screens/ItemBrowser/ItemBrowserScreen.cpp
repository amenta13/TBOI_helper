#include "ItemBrowserScreen.h"
#include "src/ItemDB.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>

ItemBrowserScreen::ItemBrowserScreen(QWidget* parent)
    : QWidget(parent)
{
    auto* stack = qobject_cast<QStackedWidget*>(parent);

    searchBox = new QLineEdit(this);
    searchBox->setPlaceholderText("Search items...");

    listWidget = new QListWidget(this);
    detailsLabel = new QLabel("Select an item to see details", this);
    backButton = new QPushButton("Back", this);

    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(searchBox);
    layout->addWidget(listWidget);
    layout->addWidget(detailsLabel);
    layout->addWidget(backButton);

    setLayout(layout);

    // Logic: update list as you type
    connect(searchBox, &QLineEdit::textChanged, this, [this](const QString& text) {
        populateList(text.toStdString());
    });

    // Logic: show details when clicked
    connect(listWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
        std::string name = item->text().toStdString();
        const Item* it = ItemDatabase::instance().getByName(standardize(name));
        detailsLabel->setText(
            QString("ID: %1\nQuality: %2")
            .arg(it->id)
            .arg(it->quality)
        );
    });

    // Navigation
    connect(backButton, &QPushButton::clicked, this, [stack]() {
        stack->setCurrentIndex(0);
    });

    // Initial load
    populateList("");
}

void ItemBrowserScreen::populateList(const std::string& query) {
    listWidget->clear();

    auto results = ItemDatabase::instance().searchByPrefix(query);

    for (const Item* item : results) {
        listWidget->addItem(QString::fromStdString(titlecase(item->name)));
    }
}
