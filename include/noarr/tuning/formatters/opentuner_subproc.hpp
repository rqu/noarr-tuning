#ifndef NOARR_TUNING_OPENTUNER_SUBPROC_HPP
#define NOARR_TUNING_OPENTUNER_SUBPROC_HPP

#include <iostream>
#include <stdexcept>
#include <string_view>
#include <string>
#include <memory>

#include <snaketongs.hpp>

#include "../builders.hpp"
#include "../formatter.hpp"
#include "../macros.hpp"

#include "common.hpp"

namespace noarr::tuning {

namespace py = snaketongs;

template<class T>
concept IsMeasureCommand = requires(T t, py::process proc, py::object obj) {
	{t(proc, std::move(obj), std::move(obj))} -> std::same_as<py::object>;
};

template<IsMeasureCommand MeasureCommand>
class opentuner_subproc {
public:
	opentuner_subproc(std::vector<std::string> &&compile_command, std::vector<std::string> &&run_command, std::vector<std::string> &&opentuner_args, const MeasureCommand &measure_command)
		: compile_command_(std::move(compile_command))
		, run_command_(std::move(run_command))
		, opentuner_args_(std::move(opentuner_args))
		, measure_command_(measure_command)
	{
		compile_command_.push_back("-D" "NOARR_PASS_BY_DEFINE");
	}

	void header() {
		procptr = std::make_unique<py::process>();
		opentuner = (*procptr)["opentuner.*"];
	}

	void footer() {
		using py::kw;
		auto &proc = *procptr;

		auto ApplicationTuner = proc.type("ApplicationTuner", proc.make_tuple(opentuner.get("MeasurementInterface")), proc.dict(
			kw("save_final_config") = [](auto self, auto configuration) {
				self.call("manipulator").call("save_to_file", configuration.get("data"), "mmm_final_config.json");
			},

			kw("manipulator") = [&proc, this](auto) {
				auto manipulator = opentuner.call("ConfigurationManipulator");
				for(const auto &param : param_desc)
					manipulator.call("add_parameter", param);
				return manipulator;
			},

			kw("run") = [&proc, this](auto self, auto desired_result, auto input, auto limit) {
				auto Result = opentuner.get("Result");

				auto config = desired_result.get("configuration").get("data");

				auto compile_cmd = proc.list();
				for(const auto &arg : compile_command_)
					compile_cmd.call("append", arg);
				for(const auto &config_to_cmdline_arg : config_to_cmdline_args)
					compile_cmd += config_to_cmdline_arg(config);

				auto compile_result = self.call("call_program", compile_cmd);

#if defined(NOARR_TUNING_VERBOSE) && NOARR_TUNING_VERBOSE >= 1
				std::cerr << "Compile time: " << compile_result["time"] << std::endl;
				std::cerr << "Compile returncode: " << compile_result["returncode"] << std::endl;
#endif

				if(compile_result["returncode"] != 0)
					return Result(kw("state")="ERROR", kw("time")=proc["math.inf"]);

#if defined(NOARR_TUNING_VERBOSE) && NOARR_TUNING_VERBOSE >= 2
				std::cerr << "Compile stderr: " << compile_result["stderr"] << std::endl;
#endif

				auto run_cmd = proc.list();
				for(const auto &arg : run_command_)
					run_cmd.call("append", arg);

				auto run_result = self.call("call_program", run_cmd);

#if defined(NOARR_TUNING_VERBOSE) && NOARR_TUNING_VERBOSE >= 1
				std::cerr << "Run time: " << run_result["time"] << std::endl;
				std::cerr << "Run returncode: " << run_result["returncode"] << std::endl;
#endif

				if(run_result["returncode"] != 0)
					return Result(kw("state")="ERROR", kw("time")=proc["math.inf"]);

				return measure_command_(proc, std::move(Result), std::move(run_result));
			}
		));

		auto args = proc.list();
		for(const auto &arg : opentuner_args_)
			args.call("append", arg);

		auto argparser = opentuner.call("default_argparser");
		ApplicationTuner.call("main", argparser.call("parse_args", args));

		proc.terminate();
	}

	void format(std::string &&name, const category_parameter &par) {
		auto &proc = *procptr;

		param_desc.push_back(opentuner.call("SwitchParameter", name, par.num_));

		config_to_cmdline_args.emplace_back([&proc, name = std::move(name)](auto &config) {
			return proc.make_tuple("-D" "NOARR_TUNING_PARAMETER_VALUE_" + name + "=" + config[name].str());
		});
	}

	void format(std::string &&name, const permutation_parameter &par) {
		auto &proc = *procptr;

		param_desc.push_back(opentuner.call("PermutationParameter", name, proc.range(par.num_)));

		config_to_cmdline_args.emplace_back([&proc, name = std::move(name)](auto &config) {
			return proc.make_tuple("-D" "NOARR_TUNING_PARAMETER_VALUE_" + name + "=" + proc.str.call("join", ",", proc.map(proc.str, config[name])));
		});
	}

	template<class Start, class End, class Step>
	void format(std::string &&name, const range_parameter<Start, End, Step> &par) {
		auto &proc = *procptr;

		if (par.step_ != 1)
			throw std::runtime_error("OpenTuner does not support step in range parameters");

		param_desc.push_back(opentuner.call("IntegerParameter", name, par.min_, par.max_));

		config_to_cmdline_args.emplace_back([&proc, name = std::move(name)](auto &config) {
			return proc.make_tuple("-D" "NOARR_TUNING_PARAMETER_VALUE_" + name + "=" + config[name].str());
		});
	}

private:
	std::vector<std::string> compile_command_;
	std::vector<std::string> run_command_;
	std::vector<std::string> opentuner_args_;
	MeasureCommand measure_command_;

	std::unique_ptr<py::process> procptr {nullptr};
	py::object opentuner {nullptr};
	std::vector<py::object> param_desc;
	std::vector<std::function<py::object(const py::object &config)>> config_to_cmdline_args;
};

static_assert(IsTunerFormatter<opentuner_subproc<decltype([](auto &, auto Result, auto) { return Result(); })>>);

} // namespace noarr::tuning

#endif // NOARR_TUNING_OPENTUNER_SUBPROC_HPP
