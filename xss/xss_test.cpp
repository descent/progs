#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "cgicc/HTTPContentHeader.h"

using namespace std;
using namespace cgicc;

void encode(std::string& data) 
{
  // https://stackoverflow.com/questions/5665231/most-efficient-way-to-escape-xml-html-in-c-string
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        switch(data[pos]) {
            case '&':  buffer.append("&amp;");       break;
            case '\"': buffer.append("&quot;");      break;
            case '\'': buffer.append("&apos;");      break;
            case '<':  buffer.append("&lt;");        break;
            case '>':  buffer.append("&gt;");        break;
            default:   buffer.append(&data[pos], 1); break;
        }
    }
    data.swap(buffer);
}

int main(int argc, char *argv[])
{
  //printf("Content-type: text/plain\n\n");
  //printf("cgi test\n");

  try 
  {
    Cgicc cgi;

    // Send HTTP header
    //cout << HTTPHTMLHeader() << endl;
    cout << HTTPContentHeader("text/html; charset=utf-8") << endl;
    cout << "Set-Cookie:count=2;\n";
    cout << "Set-Cookie:user=test_name;\n";
    cout << "Set-Cookie:password=test_password;\n\n";

    // Set up the HTML document
    //cout << html() << << head(title("Cgicc example")) << endl;
    //cout << body() << endl;

    // Print out the submitted element
    form_iterator name = cgi.getElement("name");
    if(name != cgi.getElements().end()) 
    {
      //cout << "Your name: " << **name << endl;
      string s{name->getValue()};
      encode(s);
      cout << "Your name: " << s << endl;
    }

    // Close the HTML document
    //cout << body() << html();
   }
   catch(exception& e) 
   {
      // handle any errors - omitted for brevity
   }
  return 0;
}
