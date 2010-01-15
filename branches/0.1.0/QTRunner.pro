# -------------------------------------------------
# Project created by QtCreator 2010-01-12T10:21:02
# -------------------------------------------------
QT += xml \
    xmlpatterns \
    network
TARGET = QTRunner
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    testsuite.cpp \
    test.cpp \
    googletest.cpp \
    qtestlibtest.cpp \
    testtypeselectiondialog.cpp \
    addtestdialog.cpp \
    testfactory.cpp \
    updatedialog.cpp
HEADERS += mainwindow.h \
    testsuite.h \
    test.h \
    googletest.h \
    qtestlibtest.h \
    testtypeselectiondialog.h \
    addtestdialog.h \
    testfactory.h \
    testtypes.h \
    version.h \
    updatedialog.h
FORMS += mainwindow.ui \
    testtypeselectiondialog.ui \
    addtestdialog.ui \
    updatedialog.ui
OTHER_FILES += LicenseTemplate.txt
RC_FILE = QTRunner.rc
TRANSLATIONS = 
RESOURCES += QTRunner.qrc
