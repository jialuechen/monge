

#pragma once

#include "otsolver_2dgrid.h"
#include "inputparser.h"

// helps managing common CLIoptions
struct CLI_OTSolverOptions
{
  monge::SolverOptions solver_opt;
  int verbose_level;

  CLI_OTSolverOptions()
  {
    set_default();
  }

  // initializes the options to their default values
  void set_default()
  {
    verbose_level = 1;
  }

  static void print_help()
  {
    std::cout << "solver options :" << std::endl;
    std::cout << " * -beta <beta_opt>           ; possible value: cj, 0 (default: cj)" << std::endl;
    std::cout << " * -itr <max_iteration>" << std::endl;
    std::cout << " * -th  <residual threshold>" << std::endl;
    std::cout << " * -ratio <max_target_ratio>" << std::endl;
    std::cout << " * -v <verbose_level>         ; integer in [0,10], default is 1" << std::endl;
  }

  bool load(const InputParser& args)
  {
    set_default();

    std::vector<std::string> value;

    if(args.getCmdOption("-beta",value))
    {
      if(value[0]=="zero" || value[0]=="0")
        solver_opt.beta = monge::BetaOpt::Zero;
      else if(value[0]=="cj")
        solver_opt.beta = monge::BetaOpt::ConjugateJacobian;
      else
      {
        std::cerr << "!! Invalid beta option: " << value[0]  << ", fallback to \"Auto\" \n";
      }
    }

    if(args.getCmdOption("-itr", value))
      solver_opt.max_iter = std::stoi(value[0]);

    if(args.getCmdOption("-th", value))
      solver_opt.threshold = std::stod(value[0]);

    if(args.getCmdOption("-ratio", value))
      solver_opt.max_ratio = std::stod(value[0]);

    if(args.getCmdOption("-v",value))
      verbose_level = std::stoi(value[0]);

    return true;
  }
};



