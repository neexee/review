#include <map>
#include <git2.h>
#include "../DiffDelta.h"

namespace git {

namespace {
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

DeltaStatus ToDeltaStatus(int status)
{
	return status_map.at(status);
}

//////////////////////////////////////////////////////////////////////////////

DiffFile::DiffFile()
{
}

DiffFile::DiffFile(const git_diff_file& diff_file)
: path_(diff_file.path)
, oid_(diff_file.id)
{
}

std::string DiffFile::Path() const
{
	return path_;
}

Oid DiffFile::GetOid() const
{
	return oid_;
}

} // namespace git
