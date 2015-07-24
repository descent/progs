#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <string>
using namespace std;

#define FAIL -1
#define OK 0

class Ft2
{
  public:
    ~Ft2();
    int init_ft2(const string fontpath);
    int get_slot(uint32_t char_code, int font_size, FT_GlyphSlot &slot);
  private:
    FT_Library library;
    FT_Face face;
    FT_Error error;
};

