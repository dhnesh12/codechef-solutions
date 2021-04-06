-- Helpers

function Main(task)
  local tests_qtd = tonumber( io.read() )

  for i=1, tests_qtd do
    if i ~= tests_qtd then
      print(task())
    else
      -- To not print a new line on last test
      io.write(task())
    end
  end
end

function Split(s, delimiter)
  local result = {};
  for match in (s..delimiter):gmatch("(.-)"..delimiter) do
      table.insert(result,tonumber( match ));
  end
  return result;
end

-- Main task

function Puppy_and_gcd()

  function gcd(n,d)
    -- Calculates the greatest common divisor between 2 given numbers
    if d==0 then
      return n
    else
      return gcd(d, n % d)
    end
  end

  local entries = Split(io.read(), " ")
  local range_limit = entries[1]
  local expected_gcd = entries[2]

  local counter = 0

  for i=expected_gcd, range_limit, expected_gcd do
    for j=i ,range_limit, expected_gcd do
      if gcd(i,j) == expected_gcd then
        counter = counter +1
      end
      end
  end

  return counter

end

Main(Puppy_and_gcd)
