#pragma once
#include <string>
#include <vector>

using Parameter = std::string;
using Parameters = std::vector<Parameter>;

enum e_CompilerId {
	eCompilerId_Undefined
	, eCompilerId_clang
	, eCompilerId_bcc32
	, eCompilerId_bcc32c
	, eCompilerId_bcc64
	, eCompilerId_Unknown
};

Parameters fromClangtoBcc32cCompilerParameters(const Parameters& parameters);

template <e_CompilerId source_compiler_id>
struct fromCompilerParameters {
	static Parameters to(e_CompilerId target_compiler_id, const Parameters parameters) {
		Parameters result;

		std::cout << "\n[[CLANG-BCC]]:Parameter Transformation";
		std::cout << "\n\t<IN Parameter List (vaules between [...]>";
		std::for_each(std::begin(parameters), std::end(parameters), [](const Parameter& p) {std::cout << "\n\t[" << p << "]"; });

		if (source_compiler_id == target_compiler_id) {
			result = parameters;
		}
		else switch (target_compiler_id) {
		case eCompilerId_bcc32c:
			result = fromClangtoBcc32cCompilerParameters(parameters);
			break;
		default:
			throw std::runtime_error(std::string("No parameter transform available"));
			break;
		}

		std::cout << "\n\t<OUT Parameter List (vaules between [...]>";
		std::for_each(std::begin(result), std::end(result), [](const Parameter& p) {std::cout << "\n\t[" << p << "]"; });

		return result;
	 }
};
