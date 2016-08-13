#pragma once
#include <string>
#include <vector>
#include "Common.h"
#include "DiffDelta.h"
#include "Object.h"
#include "Repo.h"
#include "Tree.h"

namespace git {

struct DiffOptions
{
	DiffOptions();
	git_diff_options diffopts;
	git_diff_find_options findopts;
};

typedef std::vector<DiffDelta> DeltaVector;
class Diff
{
public:
	Diff(const RepoPtr& repo, const Treeish& treeish1,
		 const Treeish& treeish, const DiffOptions& options);
	Diff(const RepoPtr& repo, const TreePtr& first, const TreePtr& second,
		 const DiffOptions& diffopts);

	Diff(const Diff&) = delete;
	Diff& operator=(const Diff&) = delete;

	DeltaVector Deltas() const;
	TreePtr NewTree() const;
	TreePtr OldTree() const;
	git_diff** GetPointerToDiff();

	~Diff();

private:
	void Init();
	int OnFile(const git_diff_delta *delta, float progress, void *payload);
	int OnHunk(const git_diff_delta *delta, const git_diff_hunk *hunk, void *payload);
	int OnLine(const git_diff_delta *delta, const git_diff_hunk *hunk,
		const git_diff_line *line, void *payload);
	int OnBinary(const git_diff_delta *delta, const git_diff_binary *binary,
								void *payload);

	git_diff* diff_;
	RepoPtr repo_;
	DiffOptions options_;
	DeltaVector deltas_;
	TreePtr new_tree_;
	TreePtr old_tree_;
};

typedef std::shared_ptr<Diff> DiffPtr;

} // namespace git
