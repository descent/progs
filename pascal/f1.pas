(*ref: https://www.tutorialspoint.com/pascal/pascal_functions.htm*)
(*ref: http://wiki.freepascal.org/Unit *)
unit f1;

interface
function max(num1, num2: integer): integer;
function min(num1, num2: integer): integer;

implementation

function max(num1, num2: integer): integer;
var
   (* local variable declaration *)
   result: integer;

begin
   if (num1 > num2) then
      result := num1
   
   else
      result := num2;
   max := result;
end;

function min(num1, num2: integer): integer;
var
   (* local variable declaration *)
   result: integer;

begin
   if (num1 < num2) then
      result := num1
   
   else
      result := num2;
   min := result;
end;

end.
