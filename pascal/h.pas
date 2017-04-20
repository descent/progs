Program h;
(*Uses f1, Crt in '/usr/local/lib/fpc/3.1.1/units/i386-linux/rtl-console/crt.ppu';*)
Uses f1, Crt;

  var x, v: integer;
begin

  x := max(5,6);
  v := min(5,6);
  Writeln('hello free pascal, max: ', x);
  Writeln('hello free pascal, min: ', v);
end.
