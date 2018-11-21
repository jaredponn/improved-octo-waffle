#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iostream>

namespace iow
{

// splits the string by a delimter. If there are empty strings between
// delimiters, wit will not append that to the token vector
static inline std::vector<std::string>
splitStringBy(const std::string &str, const std::string delimiter)
{
	std::string s = str;
	std::vector<std::string> tokens;
	std::string token;

	size_t pos = s.find(delimiter);

	while (pos != std::string::npos) {
		pos = s.find(delimiter);
		token = s.substr(0, pos);
		if (token != "") {
			tokens.push_back(token);
		}
		s.erase(0, pos + delimiter.length());
	}

	return tokens;
}

static inline bool isNumber(const std::string &str)
{
	return !str.empty()
	       && str.end() == std::find_if(str.begin(), str.end(), [](char c) {
			  return !std::isdigit(c);
		  });
}

}; // namespace iow
