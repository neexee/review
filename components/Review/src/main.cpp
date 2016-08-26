#include <QtCore/QString>
#include <QtQml>
#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>

#include "ReviewHandler.h"

void PrintUsage();
void SetupMainWindow(QObject *top_level, char *argv[]);

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		PrintUsage();
		return -1;
	}

	QApplication app(argc, argv);

	qmlRegisterType<ReviewHandler>("review.handler", 1, 0, "ReviewHandler");
	QQmlApplicationEngine engine(QUrl("qrc:/qml/main.qml"));

	QObject* top_level = engine.rootObjects().value(0);
	SetupMainWindow(top_level, argv);

	return app.exec();
}

void SetupMainWindow(QObject* top_level, char* argv[])
{
	QQuickWindow* window = qobject_cast<QQuickWindow*>(top_level);
	window->show();

	ReviewHandler* review_handler = top_level->findChild<ReviewHandler*>("reviewHandler");

	auto repo_path = std::string(argv[1]);
	auto from_commitish = std::string(argv[2]);
	auto to_commitish = std::string(argv[3]);

	review_handler->Init(repo_path, from_commitish, to_commitish);
}

void PrintUsage()
{
	std::cerr << "Usage: review commit commit repo_path" << std::endl;
}
