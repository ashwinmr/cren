#include <iostream>
#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

// Function to parse command line arguments
bool parse_args(int argc, char** argv, po::variables_map& args){

  // Declare supported options
  po::options_description desc("Allowed options");

  // Add options
  desc.add_options()
    ("help", "Help message")
    ("directory,d",po::value<std::string>()->default_value("./"), "Directory")
    ("find,f",po::value<std::string>(), "Find pattern")
    ("rename,r",po::value<std::string>(),"Rename pattern")
    ("no-confirmation,n", "Do not provide confirmation")
  ;

  po::store(po::parse_command_line(argc,argv,desc),args);

  if(args.count("help")){
    std::cout << desc << std::endl;
    return false;
  }

  // Continue the program
  return true;
}

int main(int argc, char** argv){

  //  Parse arguments
  po::variables_map args;
  if(!parse_args(argc,argv,args)){
    return 0;
  }

  return 0;
}
