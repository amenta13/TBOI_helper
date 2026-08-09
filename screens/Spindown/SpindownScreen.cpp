#include "SpindownScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QListWidget>
#include <QSpinBox>
#include <QScrollArea>
#include <QCheckBox>
#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QCompleter>
#include "src/SpinDown.hpp"
#include "src/ItemDB.hpp"

// Model that stores item names and applies your standardize() logic
class ItemFilterModel : public QStringListModel {
public:
    using QStringListModel::QStringListModel;

    bool matches(int row, const QString& pattern) const {
        QString item = data(index(row, 0), Qt::DisplayRole).toString();

        std::string normalizedItem = standardize(item.toStdString());
        std::string normalizedPattern = standardize(pattern.toStdString());

        return normalizedItem.find(normalizedPattern) != std::string::npos;
    }
};

// Proxy model that filters rows using ItemFilterModel::matches()
class ItemProxyModel : public QSortFilterProxyModel {
public:
    ItemProxyModel(QObject* parent = nullptr) : QSortFilterProxyModel(parent) {}

    bool filterAcceptsRow(int row, const QModelIndex&) const override {
        auto model = static_cast<ItemFilterModel*>(sourceModel());
        return model->matches(row, filterRegularExpression().pattern());
    }
};

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

    // Autocomplete Setup
    QStringList itemNames;
    for (const auto& name : ItemDatabase::instance().getAllItemNames()) {
        itemNames << QString::fromStdString(name);
    }

    auto* model = new ItemFilterModel(itemNames, this);
    auto* proxy = new ItemProxyModel(this);
    proxy->setSourceModel(model);

    // QCompleter using normalized matching but real names for display
    QCompleter* completer = new QCompleter(proxy, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);

    inputBox->setCompleter(completer);


    inputBox->setPlaceholderText("Enter item name...");
    inputRow->addWidget(inputLabel);
    inputRow->addWidget(inputBox);

    // Challenge and Daily Toggles
    auto *toggleRow = new QHBoxLayout();
    auto *challengeToggle = new QCheckBox("Challenge Mode", this);
    auto *dailyToggle = new QCheckBox("Daily Run Mode", this);
    toggleRow->addWidget(challengeToggle);
    toggleRow->addWidget(dailyToggle);

    // Count row (how many spindowns)
    auto *countRow = new QHBoxLayout();
    auto *countLabel = new QLabel("Show next N items:", this);
    auto *countBox = new QSpinBox(this);
    countBox->setRange(1, 20);
    countBox->setValue(1);

    countRow->addWidget(countLabel);
    countRow->addWidget(countBox);

    // Result label
    auto *resultLabel = new QLabel("Result: ", this);
    resultLabel->setStyleSheet("font-size: 18px;");

    // Scrollable results area
    auto *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    auto *scrollWidget = new QWidget(scrollArea);
    auto *resultsLayout = new QVBoxLayout(scrollWidget);
    scrollWidget->setLayout(resultsLayout);

    scrollArea->setWidget(scrollWidget);

    // Buttons
    auto *btnCalculate = new QPushButton("Calculate Next ID", this);
    auto *btnBack = new QPushButton("Back to Home", this);

    btnCalculate->setMinimumHeight(35);
    btnBack->setMinimumHeight(35);

    // Add widgets to layout
    layout->addWidget(title);
    layout->addSpacing(15);
    layout->addLayout(inputRow);
    layout->addLayout(countRow);
    layout->addLayout(toggleRow);
    layout->addWidget(btnCalculate);
    layout->addSpacing(10);
    layout->addWidget(scrollArea);
    layout->addSpacing(20);
    layout->addWidget(btnBack);

    layout->setAlignment(Qt::AlignTop);

    QPixmap placeHolder("src/images/questionmark.png");

    // Logic connection
    connect(btnCalculate, &QPushButton::clicked, this, [inputBox, countBox, resultsLayout, placeHolder, challengeToggle, dailyToggle]() {

        // Clear previous results
        while (QLayoutItem* item = resultsLayout->takeAt(0)) {
            if (item->widget()) delete item->widget();
            delete item;
        }

        bool challengeMode = challengeToggle->isChecked();
        bool dailyMode = dailyToggle->isChecked();

        std::string name = inputBox->text().toStdString();
        if (name.empty()) {
            QLabel* msg = new QLabel("Result: No item entered");
            resultsLayout->addWidget(msg);
            return;
        }

        // Lookup starting item
        const Item* startItem = ItemDatabase::instance().getByName(name);
        if (!startItem) {
            QLabel* msg = new QLabel("Item not found");
            resultsLayout->addWidget(msg);
            return;
        } else if (startItem->id == 1) {
            QLabel* msg = new QLabel("The Sad Onion Will Disapear");
            resultsLayout->addWidget(msg);
            return;
        } else if (startItem->id == 668) {
            QLabel* msg = new QLabel("Dad's Note Is Not Affected By The Spindown Dice");
            resultsLayout->addWidget(msg);
            return;
        }

        int count = countBox->value();
        const Item* current = startItem;

        for (int i = 0; i < count; i++) {

            const Item* nextItem = nullptr;

            while (true) {
                int nextId = SpinDown::spinDownById(current->id);
                nextItem = ItemDatabase::instance().getById(nextId);

                while (!nextItem) {
                    nextId--;
                    if (nextId > 0)
                        nextItem = ItemDatabase::instance().getById(nextId);
                    else
                        break;
                }

                if (challengeMode && nextItem->bannedInChallenge) {
                    current = nextItem;
                    continue;
                }

                if (dailyMode && nextItem->bannedInDaily) {
                    current = nextItem;
                    continue;
                }

                break;
            }

            if (!nextItem) break;

            // Build row
            QWidget* row = new QWidget;
            QHBoxLayout* rowLayout = new QHBoxLayout(row);

            QLabel* imgLabel = new QLabel;
            imgLabel->setFixedSize(96, 96);
            imgLabel->setAlignment(Qt::AlignCenter);

            QPixmap pix(QString::fromStdString(nextItem->imagePath));
            if (!pix.isNull()) {
                imgLabel->setPixmap(
                    pix.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation)
                );
            } else {
                imgLabel->setPixmap(
                    placeHolder.scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation)
                );
            }

            QLabel* nameLabel = new QLabel(QString::fromStdString(nextItem->name));
            nameLabel->setStyleSheet("font-size: 18px;");

            // For "The Sad Onion" add "The Sad Onion Will Disappear"
            // For "Dad's Note" add "Dad's Note Is Not Affected By The Spindown Dice"

            rowLayout->addWidget(imgLabel);
            rowLayout->addWidget(nameLabel);

            resultsLayout->addWidget(row);

            current = nextItem;
        }

    });

    // Navigation
    connect(btnBack, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(0);   // back to HomeScreen
    });
}