#include <boost/program_options.hpp>

namespace po = boost::program_options;

// Function to parse command line arguments
bool parse_args(int, char**, po::variables_map&);
