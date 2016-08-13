#pragma once
#include <string>
#include <memory>
#include "Common.h"

namespace git {

class Oid
{
public:
	Oid();
	explicit Oid(git_oid oid);
	git_oid OidC() const;
	std::string ToString() const;
private:
	git_oid oid_;
};

class Object
{
public:
	Object();
	~Object();

	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;

	git_object** GetPointerToObject();
	Oid GetOid() const;
private:
	git_object* object;
};

typedef std::shared_ptr<Object> ObjectPtr;

} // namespace git
