#!/bin/sh
#http://tex.stackexchange.com/questions/1551/use-latex-to-produce-epub

latexml --inputencoding=utf-8 --dest=$1.xml $1.tex 
latexmlpost -dest=$1.html $1.xml 
ebook-convert $1.html $1.epub --language en --no-default-epub-cover


