#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "funcs.hpp"

namespace po = boost::program_options;

// Function to parse command line arguments
bool parse_args(int argc, char** argv, po::variables_map& args) {

  // Declare supported options
  po::options_description desc("A program to rename files. Allowed options");
  desc.add_options()
    ("help,h", "Help message")
    ("find,f", po::value<std::string>()->required(), "Find pattern")
    ("ignore_case,i", po::bool_switch()->default_value(false), "Ignore case")
    ("rename,r", po::value<std::string>()->required(), "Rename pattern")
    ("directory,d", po::value<std::string>(), "Directory")
    ("no_confirm,y", po::bool_switch()->default_value(false), "Don't ask for confirmation")
    ;

  // Make options positional
  po::positional_options_description desc_p;
  desc_p.add("find", 1);
  desc_p.add("rename", 1);

  // Store options
  po::store(po::command_line_parser(argc, argv).options(desc).positional(desc_p).run(), args);

  // Handle help before checking for errors
  if (args.count("help") || (argc < 2)) {
      std::cout << desc << std::endl;
      return false;
  }

  // Check inputs for errors
  po::notify(args);

  // Continue the program
  return true;
}
