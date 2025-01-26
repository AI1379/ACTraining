#include <bits/stdc++.h>
using namespace std;
#define ll long long

template <size_t kSize> class FixedBigInt {
public:
  // static constexpr size_t kSize = 1024;

  void print() {
    for (size_t i = 0; i <= highestDigit(); ++i)
      cout << digits[i] << ' ';
    cout << endl;
  }

  std::string to_string() const {
    std::string result;
    result.reserve(kSize + 1);
    // TODO: Handle negative numbers
    size_t idx = highestDigit();
    if (isNegative) {
      result.push_back('-');
    }
    for (size_t i = idx; i > 0; --i) {
      result.push_back('0' + digits[i]);
    }
    result.push_back('0' + digits[0]);
    return result;
  }

  static FixedBigInt from_string(const std::string &str) {
    FixedBigInt result;
    size_t i = 0;
    if (str[i] == '-') {
      result.isNegative = true;
      ++i;
    }
    for (; i < str.size(); ++i) {
      result.digits[str.size() - i - 1] = str[i] - '0';
    }
    return result;
  }

  static int compare(const FixedBigInt &lhs, const FixedBigInt &rhs) {
    if (lhs.isNegative && !rhs.isNegative)
      return -1;
    if (!lhs.isNegative && rhs.isNegative)
      return 1;
    for (size_t i = kSize - 1; i > 0; --i) {
      if (lhs.digits[i] < rhs.digits[i])
        return -1;
      if (lhs.digits[i] > rhs.digits[i])
        return 1;
    }
    return 0;
  }

  friend auto operator==(const FixedBigInt &lhs, const FixedBigInt &rhs) {
    return compare(lhs, rhs) == 0;
  }
  friend auto operator<=>(const FixedBigInt &lhs, const FixedBigInt &rhs) {
    return compare(lhs, rhs) <=> 0;
  }

  static FixedBigInt negative(const FixedBigInt &lhs) {
    FixedBigInt result = lhs;
    result.isNegative = !result.isNegative;
    return result;
  }

  static FixedBigInt add(const FixedBigInt &lhs, const FixedBigInt &rhs) {
    if (rhs.isNegative)
      return subtract(lhs, negative(rhs));
    else if (lhs.isNegative)
      return subtract(rhs, negative(lhs));
    FixedBigInt result;
    int carry = 0;
    for (size_t i = 0; i < kSize; ++i) {
      result.digits[i] = lhs.digits[i] + rhs.digits[i] + carry;
      carry = result.digits[i] / 10;
      result.digits[i] %= 10;
    }
    if (lhs.isNegative && rhs.isNegative)
      result.isNegative = true;
    return result;
  }

  static FixedBigInt subtract(const FixedBigInt &lhs, const FixedBigInt &rhs) {
    FixedBigInt result;
    int carry = 0;
    for (size_t i = 0; i < kSize; ++i) {
      result.digits[i] = lhs.digits[i] - rhs.digits[i] - carry;
      if (result.digits[i] < 0) {
        result.digits[i] += 10;
        carry = 1;
      } else {
        carry = 0;
      }
    }
    return result;
  }

  static FixedBigInt multiply(const FixedBigInt &lhs, const FixedBigInt &rhs) {
    FixedBigInt result;
    for (size_t i = 0; i < kSize; ++i) {
      for (size_t j = 0; j < kSize; ++j) {
        if (i + j >= kSize)
          break;
        result.digits[i + j] += lhs.digits[i] * rhs.digits[j];
      }
    }
    int carry = 0;
    for (size_t i = 0; i < kSize; ++i) {
      result.digits[i] += carry;
      carry = result.digits[i] / 10;
      result.digits[i] %= 10;
    }
    result.isNegative = lhs.isNegative ^ rhs.isNegative;
    return result;
  }

  static pair<FixedBigInt, FixedBigInt> divide(const FixedBigInt &lhs,
                                               const FixedBigInt &rhs) {
    // TODO: the code given by copilot is NONE SENSE
    // FixedBigInt quotient;
    // FixedBigInt remainder = lhs;
    // for (size_t i = kSize - 1; i > 0; --i) {
    //   int count = 0;
    //   while (remainder >= rhs) {
    //     remainder = subtract(remainder, rhs);
    //     ++count;
    //   }
    //   quotient.digits[i] = count;
    // }
    // return {quotient, remainder};
  }

  friend FixedBigInt operator+(const FixedBigInt &lhs, const FixedBigInt &rhs) {
    return add(lhs, rhs);
  }

  FixedBigInt operator-() const { return negative(*this); }

  friend FixedBigInt operator-(const FixedBigInt &lhs, const FixedBigInt &rhs) {
    return subtract(lhs, rhs);
  }

  friend FixedBigInt operator*(const FixedBigInt &lhs, const FixedBigInt &rhs) {
    return multiply(lhs, rhs);
  }

  friend FixedBigInt operator/(const FixedBigInt &lhs, const FixedBigInt &rhs) {
    return divide(lhs, rhs).first;
  }

  friend FixedBigInt operator%(const FixedBigInt &lhs, const FixedBigInt &rhs) {
    return divide(lhs, rhs).second;
  }

  FixedBigInt &operator=(const std::string &str) {
    *this = from_string(str);
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const FixedBigInt &num) {
    os << num.to_string();
    return os;
  }

  friend std::istream &operator>>(std::istream &is, FixedBigInt &num) {
    std::string str;
    is >> str;
    num = from_string(str);
    return is;
  }

private:
  size_t highestDigit() const {
    for (size_t i = kSize - 1; i > 0; --i) {
      if (digits[i] != 0)
        return i;
    }
    return 0;
  }
  // num = sum digits[i] * 10^i
  array<int, kSize> digits = {};
  bool isNegative = false;
};

int main() {
  FixedBigInt<1024> a, b;
  cin >> a >> b;
  auto c = a * b;
  cout << c << endl;
  return 0;
}