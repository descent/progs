#include <iostream>
#include <unistd.h>

#include "tinyxml2.h"

using namespace std;

int br_tag_cnt;

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) // 如果字符串全是空白字符
        return "";

    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
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
                size_t pos = href_str.find("img");
                if (pos != std::string::npos) 
                {
                // found
                }
                else
                {
                  std::cout << href;// << std::endl;
                }

                string cmd = string("./shorten.sh ") + href_str;
#if 1
                cout << cmd;// << endl;
#else
                system(cmd.c_str());
                cout << "run shorten.sh delay 1s" << endl;
                sleep(1);
#endif
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
              }
            }
            else if (std::string(tagName) == "img") 
                 {
                 #if 0
                   br_tag_cnt = 0;
                   const char* src = element->Attribute("src");
                   if (src)
                   {
                     cout << "src: " << src << endl;
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
                std::cout << trim(content);
            }
        }
    }
#endif
    // 遞迴處理子節點
    for (tinyxml2::XMLNode* child = node->FirstChild(); child; child = child->NextSibling()) {
        printNodeAndTag(child);
    }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << argv[0] << " " << "filename" << endl;
    return 0;
  }
    tinyxml2::XMLDocument doc;
    //doc.LoadFile("example.html");
    doc.LoadFile(argv[1]);

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
