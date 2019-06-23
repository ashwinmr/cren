#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <regex>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

// Function to parse command line arguments
bool parse_args(int argc, char** argv, po::variables_map& args) {

    // Declare supported options
    po::options_description desc("A program to rename files. Allowed options");
    desc.add_options()
        ("help,h", "Help message")
        ("find,f", po::value<std::string>()->required(), "Find pattern")
        ("ignore_case,i", po::bool_switch()->default_value(false), "Ignore case")
        ("rename,r", po::value<std::string>()->required(), "Rename pattern")
        ("directory,d", po::value<std::string>()->default_value("./"), "Directory")
        ("no-confirmation,n", "Do not provide confirmation")
        ;

    // Make options positional
    po::positional_options_description desc_p;
    desc_p.add("find", 1);
    desc_p.add("rename", 1);

    // Store options
    po::store(po::command_line_parser(argc, argv).
        options(desc).positional(desc_p).run(), args);

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

int main(int argc, char** argv) {

  //  Parse arguments
  po::variables_map args;
  if(!parse_args(argc,argv,args)){
    return 0;
  }

  // Get directory
  std::string dir = args["directory"].as<std::string>();

  // Get find pattern
  std::string find_pat = args["find"].as<std::string>();

  // Get rename pattern
  std::string ren_pat = args["rename"].as<std::string>();

  // Set icase flag
  std::regex::flag_type icase;
  if(args["ignore_case"].as<bool>()){
    icase = std::regex::icase;
  }
  else{
    icase = static_cast<std::regex::flag_type>(0);
  }

  // Create vector of old and new file names
  std::vector<std::pair<std::string,std::string>> results;

  // Create regex object
  std::regex ro(find_pat, icase);

  for(fs::directory_entry& de : fs::directory_iterator(dir)){
    std::string file_str = de.path().filename().string();
    if(std::regex_search(file_str,ro)){
      results.push_back(std::pair<std::string,std::string>(file_str,ren_pat));
    }
  }

  std::cout << "Results: " << std::endl;
  for(auto& result : results){
    std::cout << result.first << "\t" << result.second << std::endl;
  }

  return 0;
}
