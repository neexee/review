#include "../Object.h"

namespace git {

Object::Object::Object()
: object(nullptr)
{
}

Object::~Object()
{
	git_object_free(object);
}

git_object** Object::GetPointerToObject()
{
	return &object;
}

Oid Object::GetOid() const
{
	return Oid(*git_object_id(object));
}

//////////////////////////////////////////////////////////////////////////////
Oid::Oid()
{
}

Oid::Oid(git_oid oid)
: oid_(oid)
{
}

git_oid Oid::OidC() const
{
	return oid_;
}

std::string Oid::ToString() const
{
	const size_t bufsize = GIT_OID_HEXSZ + 1;

	char buffer[bufsize];
	git_oid_tostr(buffer, bufsize, &oid_);

	return std::string(buffer);
}

} // namespace git
