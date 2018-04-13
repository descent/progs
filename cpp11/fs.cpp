//#include <experimental/filesystem>
#include <filesystem>
#include <iostream>

//using namespace std::experimental::filesystem::v1;  

namespace fs = std::filesystem;




int main(int argc, char *argv[])
{
  //path list_path{"/home/"};

  //std::string mypath = "C:\\cpp_filesystem";
  std::string mypath = "/";

  for (auto & p : fs::directory_iterator(mypath))
    std::cout << p << std::endl;

  return 0;
}
