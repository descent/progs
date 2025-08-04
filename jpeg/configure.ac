#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(jpeglib_test, 0.0.1, descent@gmail.com)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([jpeg.cpp])
AC_PROG_LIBTOOL
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_CONFIG_FILES([Makefile])

# Checks for libraries.
#AC_CHECK_LIB([vga],main,,[echo "not find svgalib vgagl.";exit 1],)
#AC_CHECK_LIB([vgagl],main,,[echo "not find svgalib vga .";exit 1],[-lvga])

AC_LANG_PUSH([C++])
ORG_LIBS="LIBS"
AC_SUBST([CONFIG_SVGALIB_LIB],["-lvga -lvgagl"])
AC_MSG_CHECKING([we need to link svgalib lib])
LIBS="$CONFIG_SVGALIB_LIB $LIBS"
AC_LINK_IFELSE(
[AC_LANG_PROGRAM(
  [[
    #include <vga.h>
    #include <vgagl.h>
  ]],
  [[
    vga_init();
    int mode=G320x200x256;
    vga_setmode(mode);
    gl_setcontextvga(mode);
    vga_setmode(TEXT);
  ]]
)],
[CONFIG_SVGALIB_LIB="-lvga -lvgagl"; AC_MSG_RESULT(yes);],
[AC_MSG_RESULT(no), CONFIG_SVGALIB_LIB="" ; exit;]
)

LIBS=$ORG_LIBS

#check jpeg lib
AC_SUBST([CONFIG_JPEG_LIB],["-ljpeg"])
AC_MSG_CHECKING([we need to link jpeg lib])

LIBS="$CONFIG_JPEG_LIB $LIB"

AC_LINK_IFELSE(
[AC_LANG_PROGRAM(
  [[
    #include <cstdio> // this shoule before jpeg header file
    #include <cstdlib> // this shoule before jpeg header file
    #include <jpeglib.h>
    #include <jerror.h>

  ]],
  [[
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error (&jerr);

  ]]
)],
[CONFIG_JPEG_LIB="-ljpeg"; AC_MSG_RESULT(yes);],
[AC_MSG_RESULT(no), CONFIG_JPEG_LIB=""; echo "no"; exit;]
)

LIBS=$ORG_LIBS

AC_LANG_POP([C++])

LIBS="$CONFIG_JPEG_LIB $CONFIG_SVGALIB_LIB"

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_OUTPUT
