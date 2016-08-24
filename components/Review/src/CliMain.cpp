#include <iostream>
#include "Diff.h"
#include "AnnotatedDiff.h"
#include "Repo.h"
#include "DiffFormat.h"

void PrintUsage()
{
	std::cerr << "Usage: review commit commit repo_path" << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		PrintUsage();
		return -1;
	}

	auto repo_path = std::string(argv[1]);
	auto from = std::string(argv[2]);
	auto to = std::string(argv[3]);

	auto repo = std::make_shared<git::Repo>(repo_path);
	auto diff = std::make_shared<git::Diff>(repo, from, to, git::DiffOptions());

	namespace cd = cliutils::diff;
	cd::PrintOptions options{cd::Format::Patch, cd::Appearance::Colorized};
	git::AnnotatedDiff adiff(diff, repo);
	std::cout << ToString(adiff, options);
	return 0;
}
