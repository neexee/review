#pragma once
#include "Common.h"

namespace git
{

class Object
{
public:
	Object();
	~Object();
	git_object** GetPointerToObject();
private:
	git_object* object;
};

} // namespace git
