#ifndef FT2_H
#define FT2_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <stdint.h>

#include <string>
using namespace std;


#define FAIL -1
#define OK 0

class Ft2
{
  public:
    Ft2(const string fontpath);
    ~Ft2();
    int init_ft2(const string fontpath);
    int get_slot(FT_GlyphSlot &slot, uint32_t char_code, int font_size=10);
  private:
    FT_Library library;
    FT_Face face;
    FT_Error error;
};

Ft2 *get_ft2(const char *fp);

#endif
