{$CALLING PASCAL}
Program h;
(*Uses f1, Crt in '/usr/local/lib/fpc/3.1.1/units/i386-linux/rtl-console/crt.ppu';*)
Uses f1, Crt;


var x, v: integer;
var str: string;
begin

  str := 'abc';

(*  x := max(5,6); *)
  x := 7;
  Writeln('hello free pascal, max: ', x, str);
end.
