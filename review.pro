QT       += core gui

QMAKE_CXXFLAGS += -std=c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = review
TEMPLATE = app


SOURCES += Git/Impl/Common.cpp \
		   Git/Impl/Diff.cpp \
		   Git/Impl/Object.cpp \
		   Git/Impl/Repo.cpp \
		   Git/Impl/Tree.cpp \
		   Review/Impl/CliMain.cpp

HEADERS  += Git/Common.h \
			Git/Diff.h \
			Git/Object.h \
			Git/Repo.h \
			Git/Tree.h \
			Utils/Utils.h \
			Utils/Impl/Utils.inl

FORMS    += \
    UI/MainWindow.ui

unix: LIBS += -lgit2
