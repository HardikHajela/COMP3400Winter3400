//Code by Hardik Hajela(Raj)/105070182

#include <iostream>
#include <string>
#include <filesystem>
#include <iomanip>
#include <regex>

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{

  using namespace std;

  // cout << argv[0];
  if (argc != 2 && argc != 3)
  {
    cerr << "Usage: " << argv[0] << " <path> [<regex>]\n";
    return 1;
  }

  char const *re = ".*";
  if (argc == 3)
  {
    re = argv[2];
  }
  regex compiled_re(re);
  cout << argv[1];
  fs::path const base = argv[1];

  for (auto const &entry : fs::recursive_directory_iterator(base, fs::directory_options::skip_permission_denied))
  {

    smatch m;
    if (regex_match(entry.path().filename().native(), m, compiled_re))
    {
      string const nativeCurrentFilePath = entry.path().lexically_relative(base).native();
      // your previous range for body should be inside this if statement
      auto const quotedStr = quoted(nativeCurrentFilePath);

      if (fs::is_symlink(entry))
      {
        cout << "LINK:" << quotedStr << "\n";
      }
      else if (fs::is_regular_file(entry))
      {
        cout << "FILE:" << fs::file_size(entry) << " " << quotedStr << "\n";
      }
      else if (fs::is_directory(entry))
      {
        cout << "DIR: " << quotedStr << "\n";
      }
      else
      {
        cout << "OTHER: " << quotedStr << "\n";
      }
    }
  }

  //Output : https://cdn.discordapp.com/attachments/1069423325153087559/1069423344857907260/image.png
  return 1;
}