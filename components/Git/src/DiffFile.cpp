#include <Git/DiffFile.h>

namespace git {

DiffFile::DiffFile()
{
}

DiffFile::DiffFile(const git_diff_file& diff_file)
: diff_file_(diff_file)
{
}

std::string DiffFile::Path() const
{
	return diff_file_.path;
}

ObjectId DiffFile::Id() const
{
	return ObjectId(diff_file_.id);
}

bool DiffFile::Exists() const
{
	return diff_file_.flags == GIT_DIFF_FLAG_EXISTS;
}

} // namespace git
