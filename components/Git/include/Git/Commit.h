#pragma once
#include <memory>
#include <string>
#include "Object.h"
#include "Repo.h"

namespace git {

class Commit
{
public:
	Commit(const ObjectId& id, const RepoPtr& repo);
	~Commit();

	Commit(const Commit&) = delete;
	Commit& operator=(const Commit&) = delete;

	git_commit* Pointer();
	/**
	 * Get the full message of a commit.
	 */
	std::string Message() const;

	/**
	 * Get the first paragraph of the message
	 *  with whitespace trimmed and squashed.
	 */
	std::string Summary() const;

	/**
	 * Get everything but the first paragraph of the message.
	 * Leading and trailing whitespaces are trimmed.
	 */
	std::string Body() const;
	ObjectId Id() const;

private:
	git_commit* commit_;
};

typedef std::shared_ptr<Commit> CommitPtr;

} // namespace git
