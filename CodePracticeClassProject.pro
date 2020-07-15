#-------------------------------------------------
#
# Project created by QtCreator 2020-07-13T17:22:30
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodePracticeClassProject
TEMPLATE = app


SOURCES += main.cpp\
    delbook.cpp \
        mainwindow.cpp \
    logindlg.cpp \
    managerdlg.cpp \
    newbook.cpp \
    registerdlg.cpp \
    changepwddlg.cpp \
    studentlistdlg.cpp \
    booklistdlg.cpp \
    modifybook.cpp

HEADERS  += mainwindow.h \
    delbook.h \
    logindlg.h \
    managerdlg.h \
    newbook.h \
    registerdlg.h \
    changepwddlg.h \
    studentlistdlg.h \
    booklistdlg.h \
    modifybook.h

FORMS    += mainwindow.ui \
    delbook.ui \
    logindlg.ui \
    managerdlg.ui \
    newbook.ui \
    registerdlg.ui \
    changepwddlg.ui \
    studentlistdlg.ui \
    booklistdlg.ui \
    modifybook.ui
