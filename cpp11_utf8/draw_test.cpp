#include "ft2.h"
#include "draw.h"
#include "graphic.h"
#include "wstring2utf8.h"

#include <iostream>

using namespace std;

#include <signal.h>

void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    printf("Caught segfault at address %p\n", si->si_addr);
    exit(0);
}

int main(int argc, char *argv[])
{

  struct sigaction sa;

  // memset(&sa, 0, sizeof(sigaction));
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction = segfault_sigaction;
  sa.sa_flags   = SA_SIGINFO;

  sigaction(SIGSEGV, &sa, NULL);

#ifdef SVGALIB
  Graphic graphic;
#endif
  Ft2 ft2("./unifont.pcf.gz");

  FT_GlyphSlot slot;

  std::wstring utf32_str = utf8_to_wstring("A中");

  ft2.get_slot(slot, utf32_str[1]);
  my_draw_bitmap_mono(&slot->bitmap, 0, 0);

  return 0;
}
