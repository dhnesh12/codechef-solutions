var t,n,m,k,i:longint;

begin
readln(t);

for i:=1 to t do
begin
readln(n,m,k);

if abs(n-m)<=k then
writeln(0)
else
writeln(abs(n-m)-k);
end;

end.