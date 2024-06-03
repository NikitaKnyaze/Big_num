
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class big_integer
{
public:
   std::vector<int> word;
   big_integer() {};
   big_integer(std::string number)
   {
      size_t size = number.size();
      for (int i = 0; i < size; ++i) {
         int n = (number[i] - '0');
         word.push_back(n);
      }
   }

   big_integer(big_integer&& other) noexcept : word(std::move(other.word)) {};

   big_integer& operator=(big_integer&& other) noexcept
   {
      word = std::move(other.word);
      return *this;
   }

   big_integer operator+(big_integer& other)
   {
      big_integer result;
      size_t size_first = this->word.size(), size_second = other.word.size();
      if (size_first < size_second)
         std::swap(this->word, other.word);
      int sum = 0;

      for (int i = 0; i < size_first; ++i)
      {
         if (i < size_first) { sum += this->word[size_first - i - 1]; }
         if (i < size_second) { sum += other.word[size_second - i - 1]; }

         result.word.push_back(sum % 10);
         sum /= 10;
      }

      std::reverse(result.word.begin(), result.word.end());

      return result;
   }

   big_integer operator*(int num) const
   {
      big_integer result;
      int some = 0;
      size_t size = word.size();
      for (size_t i = 0; (i < size) || some; ++i) {
         int mult = some + (i < size ? word[size-i-1] * num : 0);
         result.word.push_back(mult % 10);
         some = mult / 10;
      }
      std::reverse(result.word.begin(), result.word.end());
      return result;
   }

};

std::ostream& operator<<(std::ostream & o_obj, const big_integer & some_res)
{
   for (auto c : some_res.word)
      o_obj << c;

   return o_obj;
};

int main()
{
   auto number1 = big_integer("114575");
   auto number2 = big_integer("78524");
  
   auto result = number1 + number2;
   std::cout << result; // 193099

   auto result1 = number1 * 78524;
   std::cout <<std::endl<< result1;

   return 0;
}