#include "config.h"

#include <cstdlib>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::experimental::filesystem;

/**
 * Checks that the proper directory setup is present
 *   dotfiles/
 *   private/
 */
bool check() {
  fs::directory_iterator iter(fs::current_path());
  bool has_public = false, has_private = false;
  for (const auto& dirent : iter) {
    if (fs::is_directory(dirent)) {
      if (dirent.path().stem() == "public") {
        has_public = true;
      } else if (dirent.path().stem() == "private") {
        has_private = true;
      }
    }
  }

  if (!has_public) {
    std::cerr << "Your dotfiles directory doesn't contain a public directory." << std::endl
      << "To fix, run \"mkdir public\"." << std::endl;
  }
  if (!has_private) {
    std::cerr << "Your dotfiles directory doesn't contain a private directory." << std::endl
      << "To fix, run \"mkdir private\"." << std::endl;
  }
  return has_public && has_private;
}

int main(int argc, char** argv) {
  if (!check()) {
    std::cerr << "Incorrect dotfiles setup, see error output for problems" << std::endl;
    return 1;
  }

  // Run on specific file
  if (argc == 2) {
    Config c(argv[1]);
    if (c.write()) {
      return 0;
    } else {
      return 1;
    }
  }

  auto path = fs::current_path() / "public";
  std::cout << "Reading " << path << std::endl;
  fs::directory_iterator iter(path);
  // TODO(jsvana): fix sadness
  int current_path_len = std::string(fs::current_path()).length() + 1;
  for (const auto& dirent : iter) {
    auto rel = static_cast<std::string>(dirent.path()).substr(current_path_len);
    std::cout << "Processing " << rel << std::endl;
    Config c(rel);
    c.write();
  }

  return 0;
}
