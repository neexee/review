#pragma once
#include <string>

template<typename...Args>
std::string string_format(const std::string& format, Args...args);

#include "Impl/Utils.inl"
