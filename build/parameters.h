#pragma once
#include <string>
#include <vector>

using Parameter = std::string;
using Parameters = std::vector<Parameter>;

Parameters toActualCompilerParameters(const Parameters clang_parameters);
