QT += widgets
requires(qtConfig(filedialog))

HEADERS       = mainwindow.h \
                linkedlist.h \
    node.h
SOURCES       = main.cpp \
                mainwindow.cpp \
    linkedlist.cpp \
    node.cpp \
    asupprimer.cpp
#! [0]
RESOURCES     = application.qrc
#! [0]

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
INSTALLS += target
