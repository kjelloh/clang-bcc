#pragma once
#include <string>
#include <vector>

using Parameter = std::string;
using Parameters = std::vector<Parameter>;

Parameters toBccParameters(const Parameters clang_parameters);
