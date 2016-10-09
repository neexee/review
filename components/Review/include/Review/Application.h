#pragma once
#include <memory>

#include <QApplication>
#include <QQmlApplicationEngine>

#include <Cli/Options.h>
#include <Review/FileTreeModel.h>
#include <Review/Review.h>

namespace review {

class Application
{
public:
	Application(int argc, char** argv);
	int Run();

	review::Review* Review(); // Only for testing
	void Init();

private:
	cli::Options ParseOptions(int argc, char** argv);
	void RegisterTypes();
	void ShowMainWindow();

	std::unique_ptr<review::Review> review_;
	review::FileTreeModel file_tree_;
	QApplication qapplication_;
	QQmlApplicationEngine engine_;
};

} // namespace review
