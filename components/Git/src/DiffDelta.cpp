#include <map>
#include <git2.h>
#include <Git/DiffDelta.h>

namespace git {

namespace {

// clang-format off
const std::map<int, DeltaStatus> status_map =
{
	{ GIT_DELTA_UNMODIFIED, DeltaStatus::Unmodified },
	{ GIT_DELTA_ADDED,      DeltaStatus::Added      },
	{ GIT_DELTA_DELETED,    DeltaStatus::Deleted    },
	{ GIT_DELTA_MODIFIED,   DeltaStatus::Modified   },
	{ GIT_DELTA_RENAMED,    DeltaStatus::Renamed    },
	{ GIT_DELTA_COPIED,     DeltaStatus::Copied     },
	{ GIT_DELTA_IGNORED,    DeltaStatus::Ignored    },
	{ GIT_DELTA_UNTRACKED,  DeltaStatus::Untracked  },
	{ GIT_DELTA_TYPECHANGE, DeltaStatus::Typechange },
	{ GIT_DELTA_UNREADABLE, DeltaStatus::Unreadable },
	{ GIT_DELTA_CONFLICTED, DeltaStatus::Conflicted }
};
// clang-format off

} // namespace

DiffDelta::DiffDelta()
{
}

DiffDelta::DiffDelta(const git_diff_delta* delta)
: status_(ToDeltaStatus(delta->status))
, old_file_(delta->old_file)
, new_file_(delta->new_file)
, lines_()
{
}

DeltaStatus DiffDelta::Status() const
{
	return status_;
}

DiffFile DiffDelta::OldFile() const
{
	return old_file_;
}

DiffFile DiffDelta::NewFile() const
{
	return new_file_;
}

void DiffDelta::AddLine(const DiffLine &line)
{
	lines_.push_back(line);
}

std::vector<DiffLine> DiffDelta::Lines() const
{
	return lines_;
}

DeltaStatus DiffDelta::ToDeltaStatus(int status)
{
	return status_map.at(status);
}

} // namespace git
