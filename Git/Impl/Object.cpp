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

} // namespace git
