#include <iostream>
#include "Git/Diff.h"

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

	const char* repo_path = argv[1];
	const char* from = argv[2];
	const char* to = argv[3];
	auto diff = git::MakeDiff(git::DiffOptions(from, to, repo_path));
	git::PrintDiff(diff, git::PrintOptions{GIT_DIFF_FORMAT_PATCH, -1});
	return 0;
}
