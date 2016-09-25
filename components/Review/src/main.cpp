#include <iostream>
#include <QtCore/QString>
#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtWidgets/QApplication>

#include <Cli/Options.h>
#include <Review/Commit.h>
#include <Review/DiffDelta.h>
#include <Review/DiffLine.h>
#include <Review/DiffModel.h>
#include <Review/FileTreeModel.h>
#include <Review/Review.h>

cli::Options HandleOptions(int argc, char** argv);
void RegisterTypes();
void InitEngine(QQmlApplicationEngine& engine,
	review::Review& review,
	review::FileTreeModel& file_tree_model);
void ShowMainWindow(QQmlApplicationEngine& engine);

int main(int argc, char* argv[])
{
	cli::Options options = HandleOptions(argc, argv);
	review::Review review{options};
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

	engine.rootContext()->setContextProperty("cppReview", &review);
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
	qmlRegisterType<review::Review>("review", 1, 0, "Review");
	qmlRegisterType<review::DiffLine>("diffline", 1, 0, "DiffLine");
}

cli::Options HandleOptions(int argc, char** argv)
{
	try
	{
		return cli::Options(argc, argv);
	}
	catch (cli::OptionParseError& err)
	{
		std::cerr << err.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}
