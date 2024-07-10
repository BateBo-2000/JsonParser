#pragma once
#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
using std::string;
class Utility {
public:
    static std::string prettifyJson(const std::string& jsonString);
    static bool matchingPattern(const string& str, const string& value, bool startsWith = false);
};

#endif // !UTILITY_HPP



