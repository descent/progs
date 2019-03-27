#include "ft2.h"
#include "draw.h"
#include "graphic.h"
#include "wstring2utf8.h"

#include <vector>
#include <fstream>
#include <locale>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include <signal.h>

extern const char *c_fg;
extern const char *c_bg;
extern char graphic_mode;
char aa = '0'; // anti-alias
int font_size=10;

int screen_width;
int screen_height;

void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    printf("Caught segfault at address %p\n", si->si_addr);
    exit(0);
}

void usage(const char *fp)
{
  printf("%s -p font_path -s font_size -t render_string -f fb -b bg -g 0 -a 0 -m [opened file] -x x -y y -d step_y\n", fp);
}

int main(int argc, char *argv[])
{
  const char *disp_str = "a中文bあい";
  string fontpath="./fireflysung.ttf";
  int pen_x = 0;
  int pen_y = 16;

  struct sigaction sa;

  // memset(&sa, 0, sizeof(sigaction));
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction = segfault_sigaction;
  sa.sa_flags   = SA_SIGINFO;

  sigaction(SIGSEGV, &sa, NULL);

#ifdef SVGALIB
  Graphic graphic;
#endif
  string textline;
  int opt;
  int x=0, y=100, step_x=16, step_y = 16;
  while ((opt = getopt(argc, argv, "d:m:x:y:t:a:s:b:f:p:g:h?")) != -1)
  {
    switch (opt)
    {
      case 't':
      {
        //str = QString::fromUtf8(optarg);
        disp_str = optarg;
        break;
      }
      case 'm':
      {
        ifstream infile(optarg, ios::in);
        if (!infile)
        {
          printf("cannot open file:%s\n", optarg);
          return -1;
        }
        string line;
        while(getline(infile, line, '\n'))
        {
          textline += (line + '\n');
          //str += QString::fromUtf8(textline.c_str(), textline.length());
        }
        disp_str = textline.c_str();
        break;
      }
      case 's':
      {
        font_size = strtol(optarg, 0, 10);
        break;
      }
      case 'x':
      {
        x = strtol(optarg, 0, 10);
        break;
      }
      case 'y':
      {
        step_y = y = strtol(optarg, 0, 10);
        break;
      }
      case 'd':
      {
        step_y = strtol(optarg, 0, 10);
        break;
      }
      case 'p':
      {
        fontpath = optarg;
        break;
      }
      case 'f':
      {
        c_fg = optarg;
        break;
      }
      case 'b':
      {
        c_bg = optarg;
        break;
      }
      case 'a':
      {
        aa = optarg[0];
        break;
      }

      case 'g':
      {
        graphic_mode = optarg[0];
        break;
      }
      case 'h':
      {
        usage(argv[0]);
        return 0;
      }
    }
  }
  //Ft2 ft2("./unifont.pcf.gz");
  Ft2 ft2(fontpath);

  FT_GlyphSlot slot;

  std::wstring utf32_str = utf8_to_wstring("A中B");

  system("clear");

  int w = 0;
  for (int i=0 ; i < utf32_str.size() ; ++i)
  {
    ft2.get_slot(slot, utf32_str[i], font_size);
    my_draw_bitmap_mono(&slot->bitmap, w, 200);
    w += slot->bitmap.width;
  }


#if 0
  ft2.get_slot(slot, utf32_str[0], font_size);
  my_draw_bitmap_mono(&slot->bitmap, 100, 600);

  int w = slot->bitmap.width;

  ft2.get_slot(slot, utf32_str[1]);
  my_draw_bitmap_mono(&slot->bitmap, w, 0);
  w += slot->bitmap.width;

  ft2.get_slot(slot, utf32_str[2], font_size);
  my_draw_bitmap_mono(&slot->bitmap, w, 500);
  w += slot->bitmap.width;
#endif

#if 0
  for (int i=0 ; i < 25 ; ++i)
  {

  ft2.get_slot(slot, utf32_str[0]);
  my_draw_bitmap_mono(&slot->bitmap, 0, pen_y*i);

  w = slot->bitmap.width;

  ft2.get_slot(slot, utf32_str[1]);
  my_draw_bitmap_mono(&slot->bitmap, w, pen_y*i);
  w += slot->bitmap.width;

  ft2.get_slot(slot, utf32_str[2]);
  my_draw_bitmap_mono(&slot->bitmap, w, pen_y*i);
  w += slot->bitmap.width;
  }
#endif
  return 0;
}
