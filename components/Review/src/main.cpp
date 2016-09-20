#include <iostream>
#include <QtCore/QString>
#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtWidgets/QApplication>

#include <Review/Commit.h>
#include <Review/DiffDelta.h>
#include <Review/DiffLine.h>
#include <Review/DiffModel.h>
#include <Review/DiffView.h>
#include <Review/FileTreeModel.h>
#include <Review/Review.h>

void PrintUsage();
void RegisterTypes();
void InitEngine(QQmlApplicationEngine& engine,
    review::Review& review,
    review::FileTreeModel& file_tree_model);
void ShowMainWindow(QQmlApplicationEngine& engine);

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		PrintUsage();
		return -1;
	}

	auto repo_path = std::string(argv[1]);
	auto from_commitish = std::string(argv[2]);
	auto to_commitish = std::string(argv[3]);

	review::Review review{from_commitish, to_commitish, repo_path};
	review::FileTreeModel file_tree_model;

	QApplication app(argc, argv);
	QQmlApplicationEngine engine;

	InitEngine(engine, review, file_tree_model);

	ShowMainWindow(engine);

	return app.exec();
}

void InitEngine(QQmlApplicationEngine& engine,
    review::Review& review,
    review::FileTreeModel& file_tree_model)
{
	RegisterTypes();
	file_tree_model.SetPaths(review.Diff()->Paths());

	engine.rootContext()->setContextProperty("review", &review);
	engine.rootContext()->setContextProperty("fileTreeModel", &file_tree_model);
	engine.load(QUrl("qrc:/qml/main.qml"));
}

void ShowMainWindow(QQmlApplicationEngine& engine)
{
	QObject* top_level = engine.rootObjects().value(0);
	QQuickWindow* window = qobject_cast<QQuickWindow*>(top_level);
	window->show();
}

void RegisterTypes()
{
	qmlRegisterType<review::DiffView>("diffview", 1, 0, "DiffView");
	qmlRegisterType<review::Review>("review", 1, 0, "Review");
	qmlRegisterType<review::FileTreeModel>("filetreemodel", 1, 0, "FileTreeModel");
	qmlRegisterType<review::DiffModel>();
	qmlRegisterType<review::DiffDelta>();
	qmlRegisterType<review::DiffLine>("diffline", 1, 0, "DiffLine");
}

void PrintUsage()
{
	std::cerr << "Usage: review commit commit repo_path" << std::endl;
}
