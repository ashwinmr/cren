#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <regex>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

// Function to parse command line arguments
bool parse_args(int argc, char** argv, po::variables_map& args){

  // Declare supported options
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "Help message")
    ("find,f",po::value<std::string>()->required(), "Find pattern")
    ("rename,r",po::value<std::string>(),"Rename pattern")
    ("directory,d",po::value<std::string>()->default_value("./"), "Directory")
    ("no-confirmation,n", "Do not provide confirmation")
  ;

  // Make options positional
  po::positional_options_description desc_p;
  desc_p.add("find",1);
  desc_p.add("rename",1);

  // Store options
  po::store(po::command_line_parser(argc,argv).
            options(desc).positional(desc_p).run(), args);
  po::notify(args);

  // Handle help
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

  std::string dir = args["directory"].as<std::string>();

  std::string find_pat = args["find"].as<std::string>();

  std::regex ro(find_pat);

  for(fs::directory_entry& de : fs::directory_iterator(dir)){
    std::string path_str = de.path().string();
    if(std::regex_search(path_str,ro)){
      std::cout << path_str << std::endl;
    }
  }


  return 0;
}
