#pragma once

#include <experimental/filesystem>
#include <string>

namespace fs = std::experimental::filesystem;

class Config {
 private:
  const std::string PUBLIC_PREFIX = "public/";
  const std::string PRIVATE_PREFIX = "private/";

  const std::string path_;

  const fs::path get_output_path();

  bool write_private(const std::string& private_path, std::ofstream& out_f);

 public:
  explicit Config(const std::string& path) : path_(path) {}

  bool write();
};
