#include "ft2.h"

#include "wstring2utf8.h"

#include <stdint.h>

#include <iostream>

using namespace std;

Ft2::~Ft2()
{
  FT_Done_FreeType(library);
}

int Ft2::init_ft2(const string fontpath)
{
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

  const char *disp_str = "a中文bあい";
  std::wstring utf32_str = utf8_to_wstring(disp_str);

#if 0
  for (int i=0 ; i < utf32_str.size() ; ++i)
  {
    cout << "utf-32: " << utf32_str[i] << endl;

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
     //error=FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
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

      //my_draw_bitmap_256(&slot->bitmap, x + slot->bitmap_left, y - slot->bitmap_top);
      //my_draw_bitmap_mono(&slot->bitmap, x + slot->bitmap_left, y - slot->bitmap_top);
    //print_raw_data(&slot->bitmap);
    #if 1
    x += slot->advance.x >> 6;
    y += slot->advance.y >> 6;
    #else
    x += slot->advance.x;
    y += slot->advance.y;
    #endif
  }
#endif

  return 0;
}

  //FT_GlyphSlot slot = face->glyph;
// char_code: usc-4
int Ft2::get_slot(uint32_t char_code, int font_size, FT_GlyphSlot &slot)
{
  int ret = OK;
  FT_UInt gindex = FT_Get_Char_Index(face, char_code);
  if (gindex==0)
  {
    cout << "glyph index not found" << endl;
    return FAIL;
  }

  if (face->face_flags & FT_FACE_FLAG_SCALABLE)
  {
    #if 1
    error = FT_Set_Pixel_Sizes(face, font_size, font_size);
    if (error)
    {
      cout << "FT_Set_Pixel_Sizes error" << endl;
      return FAIL;
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
    return FAIL;
  }
  if (face->glyph->format != ft_glyph_format_bitmap)
  {
   cout << "run FT_Render_Glyph" << endl;
   //error=FT_Render_Glyph(face->glyph,ft_render_mode_normal);
     //error=FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
     error=FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);
   if (error)
   {
    cout << "FT_Render_Glyph error " << endl;
    return FAIL;
   }
  }

  cout << "slot->bitmap_left: " << slot->bitmap_left << endl;
  cout << "slot->bitmap_top: " << slot->bitmap_top << endl;
#if 0
  cout << "x: " << x << endl;
  cout << "y: " << y << endl;
  cout << "draw x: " << x + slot->bitmap_left << endl;
  cout << "draw y: " << y - slot->bitmap_top << endl;
#endif

  // ref: fbterm-1.7/src/font.cpp Font::Glyph *Font::getGlyph(u32 unicode)
  int left = face->glyph->metrics.horiBearingX >> 6;
  int top = (face->size->metrics.descender >> 6) - (face->glyph->metrics.horiBearingY >> 6);
  cout << "left: " << left << endl;
  cout << "top: " << top << endl;
  //my_draw_bitmap_mono(&slot->bitmap, x + slot->bitmap_left, y - slot->bitmap_top);

  return ret;
}
