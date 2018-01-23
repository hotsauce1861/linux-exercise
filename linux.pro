TEMPLATE = subdirs
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SUBDIRS += \
    input_test

DESTDIR = $$PWD/output
