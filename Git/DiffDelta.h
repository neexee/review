#pragma once
#include <string>
#include <vector>
#include <git2.h>
#include "DiffLine.h"
#include "Object.h"

namespace git {

enum class DeltaStatus
{
	Unmodified,
	Added,
	Deleted,
	Modified,
	Renamed,
	Copied,
	Ignored,
	Untracked,
	Typechange,
	Unreadable,
	Conflicted
};

DeltaStatus ToDeltaStatus(int status);

//////////////////////////////////////////////////////////////////////////////

class DiffFile
{
public:
	DiffFile();
	explicit DiffFile(const git_diff_file& diff_file);

	std::string Path() const;
	ObjectId GetOid() const;

private:
	std::string path_;
	ObjectId oid_;
};

class DiffDelta
{
public:
	DiffDelta();
	explicit DiffDelta(const git_diff_delta* delta);

	DeltaStatus Status() const;
	DiffFile OldFile() const;
	DiffFile NewFile() const;
	std::vector<DiffLine> Lines() const;

	void AddLine(const DiffLine& line);

private:
	DeltaStatus status_;
	DiffFile old_file_;
	DiffFile new_file_;
	std::vector<DiffLine> lines_;
};

} // namespace git
