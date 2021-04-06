#include <algorithm>
#include <cstdio>
#include <string>
using namespace std;

char Buffer[100001];

struct BigBinary {
    string Digit;

    explicit BigBinary(const string& input) {
        Digit = input;
        reverse(Digit.begin(), Digit.end());
        while (Digit.back() == '0') Digit.pop_back();
        if (Digit.size() == 0) Digit.push_back('0');
    }

    explicit BigBinary(int input) {
        while (input != 0) {
            Digit.push_back(input % 2 + '0');
            input /= 2;
        }
        if (Digit.size() == 0) Digit.push_back('0');
    }

    string ToString() const {
        string answer(Digit);
        reverse(answer.begin(), answer.end());
        return answer;
    }

    void operator+=(const BigBinary& that) {
        if (that.Digit.size() > Digit.size()) Digit.resize(that.Digit.size(), '0');
        int carry = 0;
        for (int i = 0; i < Digit.size(); ++i) {
            int thatDigit = i < that.Digit.size() ? that.Digit[i] : '0';
            carry += (Digit[i] - '0') + (thatDigit - '0');
            Digit[i] = carry % 2 + '0';
            carry /= 2;
        }
        if (carry != 0) Digit.push_back(carry + '0');
    }

    void operator-=(const BigBinary& that) {
        int carry = 0;
        for (int i = 0; i < Digit.size(); ++i) {
            int thatDigit = i < that.Digit.size() ? that.Digit[i] : '0';
            carry += Digit[i] - thatDigit;
            Digit[i] = (carry + 2) % 2 + '0';
            carry = (carry - (carry + 2) % 2) / 2;
        }
        while (2 <= Digit.size() && Digit.back() == '0') Digit.pop_back();
    }

    int PopCount() const {
        int answer = 0;
        for (int i = 0; i < Digit.size(); ++i) {
            if (Digit[i] != '0') ++answer;
        }
        return answer;
    }
};

struct Solution {
    int N;
    string A, B;

    BigBinary Flips(BigBinary x) {
        x += x;
        x -= BigBinary(x.PopCount());
        return x;
    }

    BigBinary Flips(const string& a, const string& b) {
        BigBinary fB = Flips(BigBinary(b));
        BigBinary fA = Flips(BigBinary(a));
        fB -= fA;
        return fB;
    }

    void Solve() {
        scanf("%d", &N);
        scanf("%s", Buffer);
        A = Buffer;
        scanf("%s", Buffer);
        B = Buffer;
        BigBinary answer("");
        if (B < A) {
            answer = Flips(A, '1' + B);
            answer -= BigBinary("1");
        } else {
            answer = Flips(A, B);
        }
        printf("%s\n", answer.ToString().c_str());
    }
};

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) Solution().Solve();
    return 0;
}
