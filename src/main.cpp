#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <regex>
#include <iomanip>
#include "funcs.hpp"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main(int argc, char** argv) {

  //  Parse arguments
  po::variables_map args;
  try{
    if(!parse_args(argc,argv,args)){
      return 0;
    }
  }
  catch( po::error& e){
    std::cout << "Error: " << e.what() << std::endl;
    return 0;
  }

  // Store inputs
  std::string find_pat = args["find"].as<std::string>(); // Find pattern
  std::string ren_pat = args["rename"].as<std::string>(); // Rename pattern
  if(ren_pat.empty()){
    std::cout << "Error: Invalid rename pattern" << std::endl;
    return 0;
  }

  // Set directory
  fs::path dir;
  if(args.count("directory")){
    dir = fs::path(args["directory"].as<std::string>());
    if(!fs::is_directory(dir)){
      std::cout << "Error: Invalid directory specified" << std::endl;
      return 0;
    }
  }
  else{
    dir = fs::current_path();
  }

  // Set icase flag
  std::regex::flag_type icase;
  if(args["ignore_case"].as<bool>()){
    icase = std::regex::icase;
  }
  else{
    icase = static_cast<std::regex::flag_type>(0);
  }

  // Create vector of old and new paths
  std::vector<std::pair<fs::path,fs::path>> results;

  // Create regex object
  std::regex ro(find_pat, icase); // Regex object

  // Create rename list from files in directory
  for(fs::directory_entry& de : fs::directory_iterator(dir)){
    std::string old_str = de.path().filename().string();
    std::smatch sm; // String match object

    // Check for matching file
    if(std::regex_match(old_str,sm,ro)){

      // Create rename string by using patterns
      std::string new_str = std::regex_replace(old_str, ro, ren_pat, std::regex_constants::format_no_copy | std::regex_constants::format_first_only );

      // Store results
      results.push_back(std::pair<fs::path,fs::path>(de.path(),fs::path(dir).append(new_str)));
    }
  }

  // Display results
  std::cout << std::left; // Left justify
  std::cout << "\nThe following files will be renamed:\n";
  for(auto& result : results){
    std::cout << std::setw(30) << result.first.filename().string() << std::setw(30) << result.second.filename().string() << std::endl;
  }

  // Ask for confirmation before renaming
  bool perform = true;
  if(args["confirm"].as<bool>()){
    std::string resp;
    do{
      std::cout << "\nContinue? [y/n]\n";
      std::cin >> resp;
    }
    while( !std::cin.fail() && resp!="y" && resp!="n" );
    if(resp == "n"){
      perform = false;
    }
  }

  // Perform rename
  if(perform){
    std::cout << "\nRenaming...\n\n";
    for(auto& result: results){
      try{
        // Display rename action
        std::cout << result.first.filename().string() << " -> " << result.second.filename().string() << std::endl;
        fs::rename(result.first,result.second);
      }
      catch( fs::filesystem_error& e ){
        std::cout << "Error: " << e.what() << std::endl << std::endl;
      }
    }
  }

  return 0;
}
