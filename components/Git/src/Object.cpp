#include <Git/Object.h>

namespace git {

Object::Object::Object()
: object_(nullptr)
{
}

Object::~Object()
{
	git_object_free(object_);
}

git_object** Object::Pointer()
{
	return &object_;
}

ObjectId Object::Id() const
{
	return ObjectId(*git_object_id(object_));
}

//////////////////////////////////////////////////////////////////////////////
ObjectId::ObjectId()
{
}

ObjectId::ObjectId(git_oid oid)
: oid_(oid)
{
}

git_oid ObjectId::Oid() const
{
	return oid_;
}

std::string ObjectId::ShortHex() const
{
	const size_t short_commit_length = 7;
	auto full_string = Hex();
	full_string.resize(short_commit_length);
	return full_string;
}

std::string ObjectId::Hex() const
{
	const size_t bufsize = GIT_OID_HEXSZ + 1;

	char buffer[bufsize];
	git_oid_tostr(buffer, bufsize, &oid_);

	return std::string(buffer);
}

} // namespace git
