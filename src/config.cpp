#include "config.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

const fs::path Config::get_output_path() {
  // TODO(jsvana): make this line not suck
  fs::path suffix = "." + path_.substr(PUBLIC_PREFIX.length());
  fs::path home = std::getenv("HOME");
  // TODO(jsvana): support directories in paths (like .ssh/config)
  return home / suffix;
}

bool Config::write_private(const std::string& private_path, std::ofstream& out_f) {
  std::ifstream private_cfg(private_path);

  if (!private_cfg.is_open()) {
    std::cerr << "Unable to open private config file \"" << private_path << "\"" << std::endl;
    return 1;
  }

  std::string cfg_line;
  while(std::getline(private_cfg, cfg_line)) {
    out_f << cfg_line << std::endl;
  }
  private_cfg.close();

  return true;
}

bool Config::write() {
  std::ifstream config_f(path_);

  if (!config_f.is_open()) {
    std::cerr << "Unable to open config file \"" << path_ << "\"" << std::endl;
    return 1;
  }

  auto output_path = get_output_path();
  std::cout << "Writing to " << output_path << std::endl;
  std::ofstream out_f(output_path);

  if (!out_f.is_open()) {
    std::cerr << "Unable to open destination config file \"" << output_path << "\"" << std::endl;
    return 1;
  }

  std::string line;
  unsigned int line_num = 1;
  while (std::getline(config_f, line)) {
    if (line.find(".include") == 0) {
      auto space = line.find(' ');
      if (space == std::string::npos) {
        std::cerr << "Malformed config (line " << line_num << "): .include requires an argument" << std::endl;
        return 1;
      }

      if (line.find(' ', space + 1) != std::string::npos) {
        std::cerr << "Malformed config (line " << line_num << "): .include takes only one argument" << std::endl;
        return 1;
      }

      write_private(PRIVATE_PREFIX + line.substr(space + 1), out_f);
    } else {
      out_f << line << std::endl;
    }
    line_num++;
  }
  config_f.close();

  return true;
}
