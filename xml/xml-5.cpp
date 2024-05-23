#include <iostream>
#include <unistd.h>

#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

int do_shorten;
int print_newline; // 1: 不管有沒有 <br> 都印出 \n, 0: 不印 \n
int br_tag_cnt;
int use_img;
int to_next_sibling;

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
  //to_next_sibling = 0;
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
              #if 0
              std::cout << "a tag" << std::endl;
              #endif
              const char* href = element->Attribute("href");
              if (href) 
              {
                //std::cout << "a tag Link Href: " << href << std::endl;

                const char* content = element->GetText();
                if (content) 
                {
                  std::cout << "Link Text: " << content << std::endl;
                  //std::cout << content;
                  //std::cout << content << std::endl;
                }
                else
                {
                  std::cout << "Link Text: empty" << std::endl;
                }

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

                to_next_sibling = 1;

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
                 else if (std::string(tagName) == "li") 
                 {
                   //cout << "li" << endl;
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

                std::cout << "node Content: ";
                //std::cout << content << std::endl;
                cout << trim(content);
                if (print_newline)
                  cout << endl;
            }
        }
    }
#endif
    // 遞迴處理子節點
  //for (tinyxml2::XMLNode* child = node->FirstChild(); child; ((child != 0) ? child = child->NextSibling() : {} )) 
  tinyxml2::XMLNode* child = node->FirstChild();
  while(child)
  {
  #if 1
    if (to_next_sibling == 1 && child)
    {
      child = child->NextSibling();
    }

    if (child)
    #endif
      printNodeAndTag(child);

    if (child)
      child = child->NextSibling();
    to_next_sibling = 0;
  }
}

void traversingXML(tinyxml2::XMLNode *node)
{
    if(node == nullptr)
        return;
    
    if(node->ToDeclaration()) {
        auto declaration = dynamic_cast<XMLDeclaration*>(node);
        cout << "XML declare，value=" << declaration->Value() << endl;
    }
    if(node->ToElement()) {
        auto element = dynamic_cast<XMLElement*>(node);
        #if 0
        cout << "XML element，name=" << element->Name() << ", value=" << element->Value() << endl;
        #endif
        const char* tagName = element->Value();
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
          br_tag_cnt = 0;

        if (std::string(tagName) == "a") 
        {
          #if 0
          cout << "a tag" << endl;
          XMLNode* text_n = node->NextSibling();
          if(text_n && text_n->ToText()) 
          {
            auto text = dynamic_cast<XMLText*>(text_n);
            cout << "aa a tag text：" << text->Value() << endl;
          }

          if(text_n && text_n->ToElement()) 
          {
            auto element = dynamic_cast<XMLElement*>(text_n);
            cout << "aa XML element，name=" << element->Name() << ", value=" << element->Value() << endl;
          }
          #endif

          XMLNode* ch = node->FirstChild();
          #if 1
          while (ch)
          {
            if(ch->ToElement()) 
            {
              XMLNode* tmp_ch;
              auto element = dynamic_cast<XMLElement*>(ch);
              //cout << "XML 55 element，name=" << element->Name() << ", value=" << element->Value() << endl;
              ch = ch->NextSibling();
              //ch = ch->FirstChild();
              #if 0
              tmp_ch = ch->FirstChild();
              if (tmp_ch)
                ch = tmp_ch;
              else
              {

                ch = ch->NextSibling();
                printf("xx ch: %p\n", ch);
              }
              #endif
            }
            else if(ch->ToText()) 
                 {
                   auto text = dynamic_cast<XMLText*>(ch);
                   //cout << "XML 22 text：" << text->Value() << endl;
                   //cout << text->Value() << endl;
                   cout << trim(text->Value() );
                   node = ch;
                   break;
                 }
            
            //printf("111 ch: %p\n", ch);
          }
          #endif
          const char* href = element->Attribute("href");
          if (href) 
          {
            //cout << href << endl;
            cout << trim(href);
          }
        }
        else
        {
        // for debug
          #if 0
          const XMLAttribute* attribute = element->FirstAttribute();
          while (attribute != nullptr) 
          {
            cout << "\tattribute " << attribute->Name() << "=" << attribute->Value() << endl;
            attribute = attribute->Next();
          }
          #endif
        }
        goto next_node;
    }
    if(node->ToText()) 
    {
      br_tag_cnt = 0;
      auto text = dynamic_cast<XMLText*>(node);
      //cout << "XML text：" << text->Value() << endl;
      //cout << text->Value() << endl;
      cout << trim(text->Value());
    }
    if(node->ToComment()) {
        auto comment = dynamic_cast<XMLComment*>(node);
        cout << "XML 注释：" << comment->Value() << endl;
    }
    if(node->ToUnknown()) {
        auto unknown = dynamic_cast<XMLUnknown*>(node);
        cout << "XML 未知：" << unknown->Value() << endl;
    }
    if(node->ToDocument()) {
        auto document = dynamic_cast<XMLDocument*>(node);
        cout << "XML 文档：" << document->ErrorName() << endl;
    }
    
    if(node->NoChildren()) {
        return;
    }
    
next_node:
    XMLNode* child = node->FirstChild();
    while(child != nullptr) {
        traversingXML(child);
        //cout << "22" << endl;
        child = child->NextSibling();
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
            traversingXML(root);

            //printNodeAndTag(root);
        }
    } else {
        std::cerr << "Failed to load HTML file." << std::endl;
    }

    return 0;
}
