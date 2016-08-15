#pragma once
#include <string>
#include <memory>
#include "Common.h"

namespace git {

class ObjectId
{
public:
	ObjectId();
	explicit ObjectId(git_oid oid);

	git_oid Oid() const;
	std::string ShortHex() const;
	std::string Hex() const;

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

	git_object** Pointer();
	ObjectId Id() const;

private:
	git_object* object_;
};

typedef std::shared_ptr<Object> ObjectPtr;

} // namespace git
