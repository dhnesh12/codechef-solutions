#include <algorithm>
#include <iostream>
#include <vector>

auto constexpr max = 100000;

auto sieve()
{
	auto primes = std::vector<int>{ 2 };
	auto not_prime = std::vector<char>(max);
	for (auto p = 3ll; max > p; p += 2)
		if (!not_prime[p])
		{
			primes.emplace_back(p);
			for (auto i = p * p; max > i; i += p) not_prime[i] = true;
		}
	return primes;
}

auto prime_factors(std::vector<int> const &primes, long long y)
{
	auto result = std::vector<int>{};
	for (auto p : primes)
	{
		if (y % p == 0)
		{
			result.emplace_back(p);
			while (y % p == 0) y /= p;
		}
		if (1 == y)
			break;
	}
	if (y != 1)
		result.emplace_back(y);
	return result;
}

auto lssb(int const bits)
{
	return bits & (-bits);
}

auto inclusion_exclusion(std::vector<int> const &factors, long long const x) -> long long
{
	auto result = x;
	for (auto bits = 1; bits < (1 << factors.size()); ++bits)
	{
		auto sign = 1;
		auto product = 1ll;
		for (auto tmp0 = bits; tmp0; tmp0 ^= lssb(tmp0))
		{
			sign = -sign;
			auto position = 0;
			for (auto tmp1 = lssb(tmp0); tmp1 > 1; tmp1 >>= 1)
				++position;
			product *= factors[position];
		}
		auto const count = x / product;
		result += count * sign;
	}
	return result;
}

int main()
{
	auto const primes = sieve();
	int t;
	std::cin >> t;
	for (auto tt = 0; t > tt; ++tt)
	{
		long long y, x1, x2;
		std::cin >> y >> x1 >> x2;
		auto const factors = prime_factors(primes, std::abs(y));
		if (0 > x1 && 0 < x2)
			std::cout << (inclusion_exclusion(factors, std::abs(x1)) +
				inclusion_exclusion(factors, std::abs(x2))) << std::endl;
		else
		{
			if (std::abs(x2) < std::abs(x1))
				std::swap(x1, x2);
			std::cout << (inclusion_exclusion(factors, std::abs(x2)) -
				inclusion_exclusion(factors, std::max(0ll, std::abs(x1) - 1))) << std::endl;
		}
	}
}