#pragma once
#include <string>
#include <memory>
#include "Common.h"

namespace git {

class GitTime
{
public:
	GitTime();
	GitTime(const git_time& time);
	int64_t seconds_since_epoch_;
	int minutes_offset_;
};

class GitSignature
{
public:
	GitSignature();
	explicit GitSignature(const git_signature* signature);

	std::string Name() const;
	std::string Email() const;
	GitTime Time() const;

private:
	std::string author_name_;
	std::string author_email_;
	GitTime time_;
};

} // namespace git
