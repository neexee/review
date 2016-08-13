#include "../Signature.h"
namespace git {

GitTime::GitTime()
{
}

GitTime::GitTime(const git_time& time)
: seconds_since_epoch_(time.time)
, minutes_offset_(time.offset)
{
}

//////////////////////////////////////////////////////////////////////////////

GitSignature::GitSignature()
{
}

GitSignature::GitSignature(const git_signature* signature)
: author_name_(signature->name)
, author_email_(signature->email)
, time_(signature->when)
{
}

std::string GitSignature::Name() const
{
	return author_name_;
}

std::string GitSignature::Email() const
{
	return author_email_;
}

GitTime GitSignature::Time() const
{
	return time_;
}

} // namespace git
