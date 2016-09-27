#include <iostream>
#include <QtQml>
#include <QtQuick/QQuickView>

#include <Review/Application.h>

namespace review {

Application::Application(int argc, char** argv)
: qapplication_(argc, argv)
{
	RegisterTypes();
	cli::Options options = ParseOptions(argc, argv);
	review_ = std::make_unique<review::Review>(options);
}

int Application::Run()
{
	Init();
	ShowMainWindow();
	return qapplication_.exec();
}

void Application::Init()
{
	file_tree_.SetPaths(review_->Diff()->Paths());
	engine_.rootContext()->setContextProperty("cppReview", review_.get());
	engine_.rootContext()->setContextProperty("fileTreeModel", &file_tree_);
	engine_.load(QUrl("qrc:/qml/main.qml"));
}

void Application::ShowMainWindow()
{
	QObject* top_level = engine_.rootObjects().value(0);
	QQuickWindow* window = qobject_cast<QQuickWindow*>(top_level);
	window->show();
}

void Application::RegisterTypes()
{
	qmlRegisterType<review::Review>("review", 1, 0, "Review");
	qmlRegisterType<review::DiffLine>("diffline", 1, 0, "DiffLine");
}

cli::Options Application::ParseOptions(int argc, char** argv)
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

} // namespace review
