#include "config.h"

#include <fstream>
#include <iostream>
#include <string>

/**
 * Checks that the proper directory setup is present
 *   dotfiles/
 *   private/
 */
bool check() {
  return true;
}

// TODO(jsvana): use <experimental/filesystem>
const std::string private_path(const std::string& config) {
  return "private/" + config;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <file_to_dootify>" << std::endl;
    return 1;
  }

  if (!check()) {
    std::cerr << "Incorrect dotfiles setup, see error output for problems" << std::endl;
    return 1;
  }

  Config c(argv[1]);
  c.write();

  return 0;
}
