#include <QString>
#include <QVector>
#include <QDebug>

#include <unistd.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include <iostream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

#include "graphic.h"

const char *c_fg = "*";
const char *c_bg = "|";
char graphic_mode = '0';
char aa = '0'; // anti-alias
int font_size=10;

int screen_width;
int screen_height;

void print_raw_data(FT_Bitmap *bitmap)
{
  unsigned char *tmp = bitmap->buffer;
  for (int i=0 ; i < bitmap->rows ; i++)
  {
    unsigned char c = *tmp;
    
    for (int j=0 ; j < bitmap->pitch ; j++)
    {
      printf("%x, ", c); 
      ++tmp;
      c = *tmp;
    }
    printf("\n");
  }
}

void my_draw_bitmap_256(FT_Bitmap *bitmap,int pen_x,int pen_y)
{
  cout << "bitmap rows : " << bitmap->rows << endl;
  cout << "bitmap width : " << bitmap->width << endl;
  cout << "bitmap pitch : " << bitmap->pitch << endl;
  if (bitmap->pixel_mode==ft_pixel_mode_mono)
    cout << "bitmap pixel mode : mono" << endl;
   if (bitmap->pixel_mode==ft_pixel_mode_grays)
   {
    cout << "bitmap pixel mode : grays" << endl;
    cout << "bitmap grays level : " << bitmap->num_grays << endl;
   }
  if (graphic_mode == '0')
  {
    cout << "anti-alias mode only support graphic mode" << endl;
    return;
  }

  int startx = pen_x;
  int starty = pen_y;
  int cx=0, cy=0;
  unsigned char *tmp = bitmap->buffer;
  for (int i=0 ; i < bitmap->rows ; i++)
  {
    unsigned char c = *tmp;
    
    for (int j=0 ; j < bitmap->pitch ; j++)
    {
      //gl_setpixel(startx+cx, starty+cy, c);
      if (c==0)
        gl_setpixelrgb(startx+cx, starty+cy, 0, 120, 0);
      else
        gl_setpixelrgb(startx+cx, starty+cy, c, 0, 0);
      printf("%x, ", c); 
      ++tmp;
      c = *tmp;
      ++cx;
    }
    cx=0;
    ++cy;
  }
}

void my_draw_bitmap_mono(FT_Bitmap *bitmap,int pen_x,int pen_y)
{
  cout << "bitmap rows : " << bitmap->rows << endl;
  cout << "bitmap width : " << bitmap->width << endl;
  cout << "bitmap pitch : " << bitmap->pitch << endl;
  if (bitmap->pixel_mode==ft_pixel_mode_mono)
    cout << "bitmap pixel mode : mono" << endl;
   if (bitmap->pixel_mode==ft_pixel_mode_grays)
   {
    cout << "bitmap pixel mode : grays" << endl;
    cout << "bitmap grays level : " << bitmap->num_grays << endl;
   }

  int startx = pen_x;
  int starty = pen_y;
  int cx=0, cy=0;

  unsigned char *tmp = bitmap->buffer;
  for (int i=0 ; i < bitmap->rows ; i++)
  {
    unsigned char c = *tmp;
    
    int font_w = 0;
    for (int j=0 ; j < bitmap->pitch ; j++)
    {
      #if 0
      printf("%x, ", ch); 
      ++tmp;
      ch = *tmp;
      #endif



      for (int i=7 ; i>=0 ; --i)
      {
        if (font_w < bitmap->width)
        {

        if (((c >> i) & 0x1) == 1)
        {
          if (graphic_mode == '0')
            printf(c_fg);
          else
            gl_setpixel(startx+cx, starty+cy, vga_white());
        }
        else
        {
          if (graphic_mode == '0')
            printf(c_bg);
          else
            gl_setpixelrgb(startx+cx, starty+cy, 180, 0, 0);
        }

        }
        //++cur_x;
        ++cx;
        ++font_w;
      }
      ++tmp;
      c = *tmp;

    }
    cx=0;
    ++cy;
    printf("\n");

    #if 0
    for (int j=0 ; j < bitmap->width ; j++)
    {
      for (int k=7 ; k >= 0 ; --k)
      {
      }
    }
    ++tmp;
    #endif
  }
}

void usage(const char *fp)
{
  printf("%s -p font_path -s font_size -t render_string -f fb -b bg -g 0 -a 0 -m [opened file] -x x -y y\n", fp);
}

int main(int argc, char *argv[])
{
  QString str = QString::fromUtf8("a中文bあい"); 
  string fontpath="./fireflysung.ttf";

  int opt;
  int x=0, y=100, step_x=16, step_y = 16;
  while ((opt = getopt(argc, argv, "m:x:y:t:a:s:b:f:p:g:h?")) != -1)
  {
    switch (opt)
    {
      case 't':
      {
        str = QString::fromUtf8(optarg);
        break;
      }
      case 'm':
      {
        FILE *fs = fopen(optarg, "r");
        if (fs == NULL)
        {
          printf("cannot open file:%s\n", optarg);
          return -1;
        }
        str = "";
        while(1)
        {
          const int LEN = 256;
          char buf[LEN];
          int read_len = fread(buf, 1, LEN, fs);
          if (read_len == 0)
          {
            break;
          }
          str += QString::fromUtf8(buf, read_len);
        }
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
        y = strtol(optarg, 0, 10);
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

  //FT_Vector vector;
  //TGlyph glyphs[MAX_GLYPHS];
  //PGlyph glyph=glyphs;
  FT_Library library;
  FT_Face face;
  FT_Error error;

  error=FT_Init_FreeType(&library);
  if (error!=0)
  {
    cout << "FT_Init_FreeType(&library) error!!" << endl;
    return -1;
  }

  error=FT_New_Face(library,fontpath.c_str(),0,&face); // 從字型載入 face
  if (error==FT_Err_Unknown_File_Format)
  {
    cout << "Don't support this font file" << endl;
    return -1;
  }
  else if (error)
       {
         cout << "The font file cann't be opened!" << endl;
         return -1;
       }
  cout << "face information : " << endl;
  cout << "face number is : " << face->num_faces << endl;
  cout << "face glyphs number is : " << face->num_glyphs << endl;
  cout << "face's sytle name is : " << face->style_name << endl;
  cout << "units per EM : " << face->units_per_EM << endl;
  cout << "num_fixed_sizes : " << face->num_fixed_sizes << endl;
  cout << "flags : " << face->face_flags << endl;
  if (face->charmap==NULL)
   cout << "No charmap is selected" << endl;
  cout << "charmap numbers is : " << face->num_charmaps << endl;
  error=FT_Select_Charmap(face,ft_encoding_unicode);
  if (error)
  {
    cout << "FT_Select_CharMap(face,ft_encoding_unicode) error"  << endl;
    return -1;
  }

  FT_UInt gindex;

  QVector<uint> utf32_str = str.toUcs4();
  //qDebug() << utf32_str.size();

  if (graphic_mode == '1')
  {
    static Graphic graphic;
    screen_width = graphic.width();
    screen_height = graphic.height();
  }

  //int x=0, y=14;
  for (int i=0 ; i < utf32_str.size() ; ++i)
  {
    cout << "utf-32: " << utf32_str[i] << endl;

    switch (utf32_str[i])
    {
      //case 0xd:
      //case 0xa:
      case '\n':
      {
        x = 0;
        y += step_y;
        continue;
        break;
      }
    }

    gindex = FT_Get_Char_Index(face, utf32_str[i]);
    if (gindex==0)
    {
      cout << "glyph index not found" << endl;
      continue;
    }

    if (face->face_flags & FT_FACE_FLAG_SCALABLE)
    {
      #if 1
      error = FT_Set_Pixel_Sizes(face, font_size, font_size);
      if (error)
      {
        cout << "FT_Set_Pixel_Sizes error" << endl;
        return -1;
      }
      #else
      // only scale font can set font size.
      error=FT_Set_Char_Size(face, 0, font_size*64,360,360);
      if (error)
      {
        cout << "FT_Set_Pixel_Sizes error" << endl;
        return -1;
      }
      #endif
    }

  FT_Int load_flags=FT_LOAD_DEFAULT;
  error = FT_Load_Glyph(face, gindex,load_flags);
  if (error!=0)
  {
   cout << "FT_Load_Glyph(face,glyph_index,load_flags) is fail " << endl;
   cout << "The error number is : " << error << endl;
   return -1;
  }
  if (face->glyph->format!=ft_glyph_format_bitmap)
  {
   cout << "run FT_Render_Glyph" << endl;
   //error=FT_Render_Glyph(face->glyph,ft_render_mode_normal);
   if (aa == '1')
     error=FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
   else
     error=FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);
   if (error)
   {
    cout << "FT_Render_Glyph error " << endl;
    return -1;
   }
  }

    FT_GlyphSlot slot=face->glyph;
    cout << "slot->bitmap_left: " << slot->bitmap_left << endl;
    cout << "slot->bitmap_top: " << slot->bitmap_top << endl;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "draw x: " << x + slot->bitmap_left << endl;
    cout << "draw y: " << y - slot->bitmap_top << endl;

    // ref: fbterm-1.7/src/font.cpp Font::Glyph *Font::getGlyph(u32 unicode)
    int left = face->glyph->metrics.horiBearingX >> 6;
    int top = (face->size->metrics.descender >> 6) - (face->glyph->metrics.horiBearingY >> 6);
    cout << "left: " << left << endl;
    cout << "top: " << top << endl;

    //my_draw_bitmap_mono(&slot->bitmap,slot->bitmap_left,slot->bitmap_top);
    if (aa=='1')
    {
      if (x + slot->bitmap_left >= screen_width)
      {
        x = 0;
        y += step_y;
      }
      my_draw_bitmap_256(&slot->bitmap, x + slot->bitmap_left, y - slot->bitmap_top);
    }
    else
    {
      if (x + slot->bitmap_left >= screen_width)
      {
        x = 0;
        y += step_y;
      }
      my_draw_bitmap_mono(&slot->bitmap, x + slot->bitmap_left, y - slot->bitmap_top);
    }
    print_raw_data(&slot->bitmap);
    #if 1
    x += slot->advance.x >> 6;
    y += slot->advance.y >> 6;
    #else
    x += slot->advance.x;
    y += slot->advance.y;
    #endif
  }

  FT_Done_FreeType(library);
  return 0;
}
