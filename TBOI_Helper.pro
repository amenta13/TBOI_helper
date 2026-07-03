QT += widgets
CONFIG += c++17 gui
TEMPLATE = app

SOURCES += \
    main.cpp \
    ui/MainWindow.cpp \
    src/ItemDB.cpp \
    src/SpinDown.cpp \
    screens/Home/HomeScreen.cpp \
    screens/Spindown/SpindownScreen.cpp \
    screens/ItemBrowser/ItemBrowserScreen.cpp \
    screens/GameplayTree/GameplayTreeScreen.cpp \
    screens/CharacterInfo/CharacterInfoScreen.cpp \
    widgets/TreeCanvas.cpp \
    widgets/TreeNode.cpp

HEADERS += \
    ui/MainWindow.h \
    src/ItemDB.hpp \
    src/SpinDown.hpp \
    screens/Home/HomeScreen.h \
    screens/Spindown/SpindownScreen.h \
    screens/ItemBrowser/ItemBrowserScreen.h \
    screens/GameplayTree/GameplayTreeScreen.h \
    screens/CharacterInfo/CharacterInfoScreen.h \
    widgets/TreeCanvas.hpp \
    widgets/TreeNode.hpp

INCLUDEPATH += 
    src
