#pragma once
#include <string>
#include "Common.h"

namespace git {
namespace signature {

class Date
{
public:
	Date();
	Date(const git_time& time);
	int64_t seconds_since_epoch_;
	int minutes_offset_;
};

class Signature
{
public:
	Signature();
	explicit Signature(const git_signature* signature);

	std::string Name() const;
	std::string Email() const;
	Date Time() const;

private:
	std::string author_name_;
	std::string author_email_;
	Date time_;
};

} // namespace signature
} // namespace git
