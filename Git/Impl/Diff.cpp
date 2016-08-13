#include <memory>
#include "Utils/Utils.h"
#include "Utils/Callback.h"
#include "../Diff.h"
#include "../Tree.h"

namespace git {

DiffOptions::DiffOptions()
: diffopts(GIT_DIFF_OPTIONS_INIT)
, findopts(GIT_DIFF_FIND_OPTIONS_INIT)
{
}


Diff::Diff(const RepoPtr& repo, const Treeish& first,
	 const Treeish& second, const DiffOptions& diffopts)
: Diff(repo, std::make_shared<Tree>(repo, first),
	std::make_shared<Tree>(repo, second), diffopts)
{
}

Diff::Diff(const RepoPtr& repo, const TreePtr& old_tree,
	 const TreePtr& new_tree, const DiffOptions& options)
: diff_(nullptr)
, repo_(repo)
, options_(options)
, deltas_()
, new_tree_(new_tree)
, old_tree_(old_tree)
{
	check_lg2(git_diff_tree_to_tree(&diff_, repo->GetRepository(),
									old_tree->GetTree(), new_tree->GetTree(), &options.diffopts),
			  "diff trees", nullptr);
	Init();
}

DeltaVector Diff::Deltas() const
{
	return deltas_;
}

TreePtr Diff::NewTree() const
{
	return new_tree_;
}

TreePtr Diff::OldTree() const
{
	return old_tree_;
}

git_diff** Diff::GetPointerToDiff()
{
	return &diff_;
}

Diff::~Diff()
{
	git_diff_free(diff_);
}

void Diff::Init()
{
	git_diff_foreach(
		diff_,
		callback::MakeCallback(&Diff::OnFile, this),
		callback::MakeCallback(&Diff::OnBinary, this),
		callback::MakeCallback(&Diff::OnHunk, this),
		callback::MakeCallback(&Diff::OnLine, this),
		nullptr);
}

int Diff::OnFile(const git_diff_delta* delta, float /*progress*/,
	void* /*payload*/)
{
	deltas_.emplace_back(delta);
	return 0;
}

int Diff::OnHunk(const git_diff_delta* /*delta*/, const git_diff_hunk* /*hunk*/,
	void* /*payload*/)
{
	return 0;
}

int Diff::OnLine(const git_diff_delta* /*delta*/, const git_diff_hunk* /*hunk*/,
	const git_diff_line *line, void* /*payload*/)
{
	auto& current_delta = deltas_.back();
	current_delta.AddLine(DiffLine(line));
	return 0;
}

int Diff::OnBinary(const git_diff_delta* /*delta*/, const git_diff_binary* /*binary*/,
							void* /*payload*/)
{
	return 0;
}

} // namespace git
