#include <Git/Signature.h>

namespace git {
namespace signature {

Date::Date()
{
}

Date::Date(const git_time& time)
: seconds_since_epoch_(time.time)
, minutes_offset_(time.offset)
{
}

//////////////////////////////////////////////////////////////////////////////

Signature::Signature()
{
}

Signature::Signature(const git_signature* signature)
: author_name_(signature->name)
, author_email_(signature->email)
, time_(signature->when)
{
}

std::string Signature::Name() const
{
	return author_name_;
}

std::string Signature::Email() const
{
	return author_email_;
}

Date Signature::Time() const
{
	return time_;
}

} // namespace signature
} // namespace git
