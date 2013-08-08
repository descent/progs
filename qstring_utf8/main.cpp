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

#include <vga.h>
#include <vgagl.h>


#define BLACK			(0)
#define BLUE			(1)
#define GREEN			(2)
#define CYAN			(3)
#define RED			(4)
#define MAGENTA			(5)
#define BROWN			(6) // or YELLOW
#define GRAY		        (7)

#define LIGHTBLACK      	(8)
#define LIGHTBLUE       	(9)
#define LIGHTGREEN      	(10)
#define LIGHTCYAN       	(11)
#define LIGHTRED        	(12)
#define LIGHTMAGENTA    	(13)
#define LIGHTBROWN      	(14)

#ifdef VGALIB
#define LIGHTWHITE      	(vga_white())
#else
#define LIGHTWHITE      	(255)
#endif

void init_graph_mode()
{
  vga_init();
  int vga_mode=G640x480x256;
  vga_setmode(vga_mode);
  gl_setcontextvga(vga_mode);

  gl_setpalettecolor(BLUE, 0, 0, 63); // blue
  gl_setpalettecolor(BLACK, 0, 0, 0); // black
  gl_setpalettecolor(GREEN, 0, 63, 0);
  gl_setpalettecolor(RED, 63, 0, 0);
  gl_setpalettecolor(BROWN, 170/4, 85/4, 0);
  gl_setpalettecolor(MAGENTA, 170/4, 0, 170/4);
  gl_setpalettecolor(CYAN, 0, 170/4, 170/4);
  gl_setpalettecolor(GRAY, 48, 48, 48);

  gl_setpalettecolor(LIGHTBLACK, 85/4, 85/4, 85/4);
  gl_setpalettecolor(LIGHTBLUE, 85/4, 85/4, 255/4);
  gl_setpalettecolor(LIGHTGREEN, 85/4, 255/4, 85/4);
  gl_setpalettecolor(LIGHTCYAN, 85/4, 255/4, 255/4);
  gl_setpalettecolor(LIGHTRED, 25/45/4, 85/4, 85/4);
  gl_setpalettecolor(LIGHTMAGENTA, 255/4, 85/4, 255/4);
  gl_setpalettecolor(LIGHTBROWN, 255/4, 255/4, 85/4);
}

const char *c_fg = "*";
const char *c_bg = "|";

// draw 256 gray
void my_draw_bitmap(FT_Bitmap *bitmap,int pen_x,int pen_y)
{
}
#if 0
 vga_clear();
 unsigned char *tmp=Bitmap->buffer;
 for (int i=0 ; i < Bitmap->rows ; i++)
 {
  for (int j=0 ; j < Bitmap->width ; j++)
  {
   if (*tmp)
    gl_setpixelrgb(pen_x+j,pen_y+i,*tmp,*tmp,*tmp);
   tmp++;
  }
 }
 vga_getch();

 vga_setmode(TEXT);
#endif

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
    
    for (int j=0 ; j < bitmap->pitch ; j++)
    {
      #if 0
      printf("%x, ", ch); 
      ++tmp;
      ch = *tmp;
      #endif



      for (int i=7 ; i>=0 ; --i)
      {
        if (((c >> i) & 0x1) == 1)
          //printf(c_fg);
          gl_setpixel(startx+cx, starty+cy, GRAY);
        else
          gl_setpixelrgb(startx+cx, starty+cy, 0, 0, 0);
          //printf(c_bg);
        //++cur_x;
        ++cx;
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

int main(int argc, char *argv[])
{
  QString str = QString::fromUtf8("中文"); 
  string fontpath="./fireflysung.ttf";

  int opt;
  while ((opt = getopt(argc, argv, "s:b:f:p:h?")) != -1)
  {
    switch (opt)
    {
      case 's':
      {
        str = QString::fromUtf8(optarg);
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

  init_graph_mode();

  int x=0, y=0;
  for (int i=0 ; i < utf32_str.size() ; ++i)
  {
    qDebug() << "utf-32: " << utf32_str[i];

    gindex = FT_Get_Char_Index(face, utf32_str[i]);
    if (gindex==0)
    {
      cout << "glyph index not found" << endl;
      return 0;
    }

#if 1
     error=FT_Set_Char_Size(face,0,10*64,360,360);
     if (error)
     {
       cout << "FT_Set_Pixel_Sizes error" << endl;
       return -1;
     }
#endif


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
   //error=FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
   error=FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);
   if (error)
   {
    cout << "FT_Render_Glyph error " << endl;
    return -1;
   }
  }

    FT_GlyphSlot slot=face->glyph;
    //my_draw_bitmap_mono(&slot->bitmap,slot->bitmap_left,slot->bitmap_top);
    my_draw_bitmap_mono(&slot->bitmap, x, y);
    x+=40;
  }

  vga_getch();
  vga_setmode(TEXT);

  FT_Done_FreeType(library);
  return 0;
}
