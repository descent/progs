#include <iostream>
#include <unistd.h>

#include "tinyxml2.h"

using namespace std;

int do_shorten;
int print_newline; // 1: 不管有沒有 <br> 都印出 \n, 0: 不印 \n
int br_tag_cnt;
int use_img;

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) // 如果字符串全是空白字符
        return "";

    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

int shorten(const string &href_str)
{
  string cmd = string("./shorten.sh ") + href_str;
  if (do_shorten == 0)
  {
    cout << cmd;
   //if (print_newline)
    cout << endl;
  }
  else
  {
    system(cmd.c_str());
    //cout << "run shorten.sh delay 1s" << endl;
    sleep(1);
  }
  return 0;
}

void printNodeAndTag(tinyxml2::XMLNode* node) 
{
    tinyxml2::XMLElement* element = node->ToElement();
    if (element) {
        const char* tagName = element->Value();
        const char* content = element->GetText();
        #if 0
        if (tagName)
          std::cout << "Node: " << tagName << endl;
        #endif

        //if (std::string(tagName) != "body") 
        {
#if 1
            if (std::string(tagName) == "br") 
            {
              if (br_tag_cnt == 0 || br_tag_cnt == 1)
              {
                //std::cout << "br tag" << std::endl;
                std::cout << std::endl;
                ++br_tag_cnt;
              }
            }
            else
            if (std::string(tagName) == "a") 
            {
              br_tag_cnt = 0;
              //std::cout << "a tag" << std::endl;
              const char* href = element->Attribute("href");
              if (href) 
              {
                //std::cout << "a tag Link Href: " << href << std::endl;
                string href_str{href};
                size_t pos = href_str.find("picasaweb");
                if (pos != std::string::npos) 
                {
                // found
                  use_img = 1;
                  
                }
                else
                {
                  use_img = 0;

                pos = href_str.find("img");
                if (pos != std::string::npos) 
                {
                // found
                }
                else
                {
                  std::cout << href;
                  if (print_newline)
                    cout << endl;
                }

               shorten(href_str);

                const char* content = element->GetText();
                if (content) 
                {
                  //std::cout << "Link Text: " << content << std::endl;
                  //std::cout << content << std::endl;
                }
                else
                {
                  //std::cout << "Link Text: empty" << std::endl;
                }

                } // end else

              }
            }
            else if (std::string(tagName) == "img") 
                 {
                 #if 1
                   if (use_img)
                   {
                     br_tag_cnt = 0;
                     const char* src = element->Attribute("src");
                     if (src)
                     {
                       //cout << "src: " << src << endl;
                       shorten(src);
                     }
                   }
                 #endif
                 }
                 else
                 {
                   br_tag_cnt = 0;
              //std::cout << "xx Node: " << tagName;
              if (content) 
              {
                //std::cout << ", Content: " << content;
                //std::cout << content;
              }
              #if 0
                   if (std::string(tagName) == "br") 
                     std::cout << std::endl;
              #endif
                 }
            #endif
        }
    }
#if 1
    else
    {
                   br_tag_cnt = 0;
        if (node->ToText()) {
            const char* content = node->ToText()->Value();
            if (content) {

                //std::cout << "node Content: " << endl;
                //std::cout << content << std::endl;
                cout << trim(content);
                if (print_newline)
                  cout << endl;
            }
        }
    }
#endif
    // 遞迴處理子節點
    for (tinyxml2::XMLNode* child = node->FirstChild(); child; child = child->NextSibling()) {
        printNodeAndTag(child);
    }
}

void usage(const char *cmd)
{
  printf("%s -f fn -s 0/1 -n 0/1\n", cmd);
  printf("-s 0 don't do shorten url\n");
  printf("-s 1 do shorten url\n");
  printf("-n 0 don't printf newline\n");
  printf("-n 1 force printf newline\n");
}

int main(int argc, char *argv[])
{
  char *fn=0;
  int opt;

  while ((opt = getopt(argc, argv, "f:s:n:h?")) != -1) 
  {
    switch (opt) 
    {
      case 'f':
      {
        fn = optarg;
        break;
      }
      case 's':
      {
        do_shorten = strtol(optarg, 0, 0);
        printf("do_shorten: %d\n", do_shorten);
        break;
      }
      case 'n':
      {
        print_newline = strtol(optarg, 0, 0);
        printf("print_newline: %d\n", print_newline);
        break;
      }
    }
  }

    //doc.LoadFile("example.html");
    if (fn == 0)
    {
      usage(argv[0]);
      return 0;
    }

    tinyxml2::XMLDocument doc;
    doc.LoadFile(fn);

    if (doc.ErrorID() == tinyxml2::XML_SUCCESS) {
        //tinyxml2::XMLElement* root = doc.FirstChildElement("body");
        tinyxml2::XMLElement* root = doc.FirstChildElement();
        if (root) {
            printNodeAndTag(root);
        }
    } else {
        std::cerr << "Failed to load HTML file." << std::endl;
    }

    return 0;
}
