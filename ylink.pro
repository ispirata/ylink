######################################################################
# Automatically generated by qmake (3.1) Thu Jul 11 12:27:36 2019
######################################################################

TEMPLATE = app
TARGET = ylink
INCLUDEPATH += .

QT += network qml
QT -= gui

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += cachedhttp.h \
           constants.h \
           datautils.h \
           http.h \
           httputils.h \
           jsfunctions.h \
           localcache.h \
           temporary.h \
           throttledhttp.h \
           videodefinition.h \
           yt3.h \
           ytvideo.h
SOURCES += cachedhttp.cpp \
           constants.cpp \
           datautils.cpp \
           http.cpp \
           httputils.cpp \
           jsfunctions.cpp \
           localcache.cpp \
           main.cpp \
           temporary.cpp \
           throttledhttp.cpp \
           videodefinition.cpp \
           yt3.cpp \
           ytvideo.cpp
