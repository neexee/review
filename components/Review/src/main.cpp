#include <QtCore/QString>
#include <QtQml>
#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>

#include "ReviewHandler.h"
#include "FileTreeModel.h"

void PrintUsage();
void SetupMainWindow(QObject *top_level, const git::AnnotatedDiff&);
git::AnnotatedDiff GetDiff(char* argv[]);
std::vector<std::string> DiffFilePaths(const git::AnnotatedDiff& diff);

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		PrintUsage();
		return -1;
	}

	QApplication app(argc, argv);

	qmlRegisterType<review::ReviewHandler>("review.handler", 1, 0, "ReviewHandler");
	QQmlApplicationEngine engine;

	auto diff = GetDiff(argv);

	review::FileTreeModel model(DiffFilePaths(diff));
	engine.rootContext()->setContextProperty("fileTreeModel",&model);

	engine.load(QUrl("qrc:/qml/main.qml"));

	QObject* top_level = engine.rootObjects().value(0);
	SetupMainWindow(top_level, diff);

	return app.exec();
}

git::AnnotatedDiff GetDiff(char* argv[])
{
	auto repo_path = std::string(argv[1]);
	auto from_commitish = std::string(argv[2]);
	auto to_commitish = std::string(argv[3]);

	auto repo = std::make_shared<git::Repo>(repo_path);
	auto diff = std::make_shared<git::Diff>(repo, from_commitish,
											to_commitish, git::DiffOptions());

	return git::AnnotatedDiff(diff, repo);
}
void SetupMainWindow(QObject* top_level, const git::AnnotatedDiff& diff)
{
	QQuickWindow* window = qobject_cast<QQuickWindow*>(top_level);
	window->show();

	auto review_handler = top_level->findChild<review::ReviewHandler*>("reviewHandler");

	review_handler->Init(diff);
}

std::vector<std::string> DiffFilePaths(const git::AnnotatedDiff& diff)
{
	std::vector<std::string> file_paths;
	auto deltas = diff.Deltas();
	std::transform(deltas.begin(), deltas.end(), std::back_inserter(file_paths),
				   [](auto& delta){ return delta.NewFile().Path(); });
	return file_paths;
}

void PrintUsage()
{
	std::cerr << "Usage: review commit commit repo_path" << std::endl;
}
