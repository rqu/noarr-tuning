#include <noarr/tuning/formatters/opentuner_subproc.hpp>

static constexpr auto main_cpp_file = __FILE__;

static constexpr auto measure_command = [](auto &proc, auto Result, auto run_result) {
	return Result(snaketongs::kw("time")=proc.int_(run_result["stderr"].call("split")[2]));
};

#define SPECIFIC_TUNING_BEGIN(...) NOARR_TUNE_BEGIN(noarr::tuning::opentuner_subproc( \
		{"g++", "-O2", "-g", "-std=c++20", "-o" "tmp.bin", "-I" "../../../include", "-I" "../build/_deps/noarr-src/include", "-I" "../build/_deps/snaketongs-src/include", main_cpp_file}, \
		{"./tmp.bin", "../matrices", "512"}, \
		{"--test-limit=20", "--no-dups"}, \
		measure_command))

#include "../program.hpp"
