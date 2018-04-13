//#include <experimental/filesystem>
#include <filesystem>
#include <iostream>
#include <algorithm>

//using namespace std::experimental::filesystem::v1;  

namespace fs = std::filesystem;
using namespace std;

void demo_perms(fs::perms p)
{
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
              << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
              << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
              << '\n';
}

int main(int argc, char *argv[])
{
  //demo_perms(fs::status("/").permissions());

  std::string mypath = "/";

  if (argc >= 2)
  {
    mypath = argv[1];
  }
  //path list_path{"/home/"};

  //std::string mypath = "C:\\cpp_filesystem";
  std::cout << "list dir: " << mypath << endl;
  std::error_code ec;

  fs::directory_iterator dir_it = fs::directory_iterator(mypath, ec);
  fs::directory_iterator end_dir_it;
  //sort(dir_it, end_dir_it);

  // http://timothyqiu.com/archives/std-error-code-and-more/
  // http://en.cppreference.com/w/cpp/error/errno_macros
  if (ec.value() == EACCES) // Permission denied
  {
    // show Permission denied
  }

  cout << ec.message() << endl;
  cout << ec.value() << ", " << EACCES << endl;

  if (ec.value() == 0)
  {
    for (; dir_it != end_dir_it ; ++dir_it)
    {
      cout << *dir_it << endl;
    }
  }

#if 0
  try
  {
    std::error_code ec;

    fs::directory_iterator dir_it = fs::directory_iterator(mypath, ec);
    fs::directory_iterator end_dir_it;

    for (; dir_it != end_dir_it ; ++dir_it)
    {
      cout << *dir_it << endl;
    }
  }
  catch(std::filesystem::__cxx11::filesystem_error &fs_err)
  {
    cout << "error message: " << fs_err.what() << endl;
    cout << "error code: " << fs_err.code() << endl;
  }
#endif

#if 0
  auto b = begin(fs::directory_iterator(mypath));
  auto e = end(fs::directory_iterator(mypath));

#endif

#if 0
  try
  {
    //for (auto & p : fs::directory_iterator(mypath))
    for (auto & p : fs::recursive_directory_iterator(mypath))
    {
      cout << p;
      if (p.is_directory())
      {
        cout << "/";
      }
      cout << endl;
    }
  }
  catch(std::filesystem::__cxx11::filesystem_error &fs_err)
  {
    cout << "error" << endl;
  }
#endif
  return 0;
}
