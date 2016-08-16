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
		   Review/Impl/CliMain.cpp \
		   Git/Impl/AnnotatedDiff.cpp \
		   Git/Impl/DiffLine.cpp \
		   Git/Impl/DiffDelta.cpp \
		   CLI/Impl/DiffFormat.cpp \
		   Git/Impl/Blame.cpp \
		   Git/Impl/Signature.cpp \
		   Git/Impl/AnnotatedDiffLine.cpp \
		   Git/Impl/BlameHunk.cpp \
		   Git/Impl/DiffOptions.cpp \
		   Git/Impl/Common.inl \
		   Git/Impl/Commit.cpp

HEADERS  += Git/Common.h \
			Git/Diff.h \
			Git/Object.h \
			Git/Repo.h \
			Git/Tree.h \
			Utils/Utils.h \
			Utils/Impl/Utils.inl \
			Git/AnnotatedDiff.h \
			Utils/Callback.h \
			Git/DiffLine.h \
			Git/DiffDelta.h \
			CLI/DiffFormat.h \
			Git/Blame.h \
			Git/Signature.h \
			Git/AnnotatedDiffLine.h \
			Git/BlameHunk.h \
			Git/DiffOptions.h \
			Git/Commit.h

FORMS    += \
	UI/MainWindow.ui

unix: LIBS += -lgit2
