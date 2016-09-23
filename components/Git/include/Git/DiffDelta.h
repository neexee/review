#pragma once
#include <string>
#include <vector>
#include <git2.h>
#include "DiffFile.h"
#include "DiffLine.h"

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
	DeltaStatus ToDeltaStatus(int status);

	DeltaStatus status_;
	DiffFile old_file_;
	DiffFile new_file_;
	std::vector<DiffLine> lines_;
};

} // namespace git
