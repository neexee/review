#pragma once
#include <string>
#include <git2.h>
#include "Object.h"

namespace git {

class DiffFile
{
public:
	DiffFile();
	explicit DiffFile(const git_diff_file& diff_file);

	std::string Path() const;
	ObjectId Id() const;
	bool Exists() const;

private:
	git_diff_file diff_file_;
	std::string path_;
	ObjectId oid_;
};

} // namespace git
