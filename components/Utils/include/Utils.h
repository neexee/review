#pragma once
#include <string>
namespace utils {

template<typename...Args>
std::string string_format(const std::string& format, Args...args);

} // namespace utils

#include "Utils.inl"
