#include <iostream>
#include "tinyxml2.h"

using namespace std;

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
            if (std::string(tagName) == "a") 
            {
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
                  std::cout << href << std::endl;
                }

                string cmd = string("./shorten.sh ") + href_str;
#if 1
                cout << cmd << endl;
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
                   const char* src = element->Attribute("src");
                   if (src)
                   {
                     cout << "src: " << src << endl;
                   }
                 }
                 else
                 {
              //std::cout << "xx Node: " << tagName;
              if (content) 
              {
                //std::cout << ", Content: " << content;
                //std::cout << content;
              }
              std::cout << std::endl;
                 }
            #endif
        }
    }
#if 1
    else
    {
        if (node->ToText()) {
            const char* content = node->ToText()->Value();
            if (content) {
                //std::cout << "node Content: " << endl;
                std::cout << content << std::endl;
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
