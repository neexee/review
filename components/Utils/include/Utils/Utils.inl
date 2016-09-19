#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

namespace utils {

template <typename... Args>
std::string string_format(const std::string& format, Args... args)
{
	size_t size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
	auto buf = std::make_unique<char[]>(size);
	snprintf(buf.get(), size, format.c_str(), args...);
	return std::string(buf.get(), buf.get() + size - 1);
}
}
