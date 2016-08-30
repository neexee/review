#pragma once
#include <string>
#include <vector>

namespace utils {

template<typename...Args>
std::string string_format(const std::string& format, Args...args);

std::vector<std::string> SplitPath(const std::string& path);
} // namespace utils

#include "Utils.inl"
