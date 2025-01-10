#include <gtest/gtest.h>

#include <array>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

void s21ExeptFunction() { s21::array<int, 4> s21arr = {1, 2, 3, 4, 5}; }

TEST(ArrayCtor, defaultCtor) {
  s21::array<int, 4> arr;
  std::array<int, 4> arr1;
  EXPECT_TRUE(arr.max_size() == arr1.max_size());
}

TEST(ArrayCtor, initial_listCtor) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  std::array<int, 4> arr1 = {1, 2, 3, 4};

  for (size_t i = 0; i < 4; i++) {
    EXPECT_EQ(arr[i], arr1[i]);
  }
}

TEST(ArrayCtor, copyCtor) {
  s21::array<int, 4> s21arr = {1, 2, 3, 4};
  s21::array<int, 4> s21arr1(s21arr);

  std::array<int, 4> arr = {1, 2, 3, 4};
  std::array<int, 4> arr1(arr);

  EXPECT_EQ(s21arr1.size(), arr1.size());

  for (size_t i = 0; i < 4; i++) {
    EXPECT_EQ(s21arr1[i], arr1[i]);
  }
}

TEST(ArrayCtor, moveCtor) {
  s21::array<int, 4> s21arr = {1, 2, 3, 4};
  s21::array<int, 4> s21arr1(std::move(s21arr));

  std::array<int, 4> arr = {1, 2, 3, 4};
  std::array<int, 4> arr1(std::move(arr));

  EXPECT_EQ(s21arr.at(2), s21arr1.at(2));
  EXPECT_EQ(s21arr.size(), s21arr1.size());
  EXPECT_EQ(arr.at(3), arr1.at(3));
  EXPECT_EQ(arr.size(), arr1.size());

  EXPECT_EQ(s21arr1.size(), arr1.size());

  for (size_t i = 0; i < 4; i++) {
    EXPECT_EQ(s21arr1[i], arr1[i]);
  }
}

TEST(ArrayOperators, equating_1) {
  s21::array<int, 4> s21arr = {1, 2, 3, 4};
  s21::array<int, 4> s21arr1;
  s21arr1 = s21arr;
  EXPECT_EQ(s21arr.size(), s21arr1.size());
  for (size_t i = 0; i < 4; i++) {
    EXPECT_EQ(s21arr[i], s21arr1[i]);
  }

  std::array<int, 4> arr = {1, 2, 3, 4};
  std::array<int, 4> arr1;
  arr = arr1;
  EXPECT_EQ(arr.size(), arr1.size());
  for (size_t i = 0; i < 4; i++) {
    EXPECT_EQ(arr[i], arr1[i]);
  }
}

TEST(ArrayOperators, equating_2) {
  s21::array<int, 4> s21arr = {1, 2, 3, 4};
  s21::array<int, 4> s21arr1;
  s21arr1 = std::move(s21arr);
  EXPECT_EQ(s21arr.size(), s21arr1.size());
  for (size_t i = 0; i < 4; i++) {
    EXPECT_EQ(s21arr[i], s21arr1[i]);
  }

  std::array<int, 4> arr = {1, 2, 3, 4};
  std::array<int, 4> arr1;
  arr = std::move(arr1);
  EXPECT_EQ(arr.size(), arr1.size());
  for (size_t i = 0; i < 4; i++) {
    EXPECT_EQ(arr[i], arr1[i]);
  }
}

TEST(ArrayOperators, pos) {
  s21::array<int, 4> s21arr = {1, 2, 3, 4};
  s21::array<int, 4> s21arr1(s21arr);
  EXPECT_EQ(s21arr[3], s21arr1[3]);

  std::array<int, 4> arr = {1, 2, 3, 4};
  std::array<int, 4> arr1(arr);
  EXPECT_EQ(arr[3], arr1[3]);
}

TEST(ArrayMethods, atExeption) {
  s21::array<int, 4> s21arr = {1, 2, 3, 4};
  EXPECT_THROW(s21arr.at(10), std::out_of_range);

  std::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST(ArrayMethods, at) {
  s21::array<int, 4> s21arr = {1, 2, 3, 4};
  std::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(s21arr.at(3), arr[3]);
  EXPECT_EQ(s21arr[2], arr.at(2));
}

TEST(ArrayMethods, frontAndBack) {
  s21::array<int, 4> s21arr = {1, 2, 3, 4};
  std::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(s21arr.front(), arr.front());
  EXPECT_EQ(s21arr.back(), arr.back());
}

TEST(ArrayMethods, emptyFalse) {
  s21::array<int, 4> s21arr = {1, 2, 3, 4};
  std::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_FALSE(s21arr.empty());
  EXPECT_FALSE(arr.empty());
}

TEST(ArrayMethods, emptyTrue) {
  s21::array<int, 0> s21arr;
  std::array<int, 0> arr;
  EXPECT_TRUE(s21arr.empty());
  EXPECT_TRUE(arr.empty());
}

TEST(ArrayMethods, size_1) {
  s21::array<int, 4> s21arr;
  std::array<int, 4> arr;
  EXPECT_EQ(s21arr.size(), arr.size());
}

TEST(ArrayMethods, size_2) {
  s21::array<int, 0> s21arr;
  std::array<int, 0> arr;
  EXPECT_EQ(s21arr.size(), arr.size());
}

TEST(ArrayMethods, max_sizeExeption) {
  EXPECT_THROW(s21ExeptFunction(), std::invalid_argument);
}

TEST(ArrayMethods, max_size) {
  s21::array<int, 4> s21arr = {1, 2};
  std::array<int, 4> arr = {3, 4};
  EXPECT_EQ(s21arr.max_size(), arr.max_size());
}

TEST(ArrayMethods, swap) {
  s21::array<int, 4> s21arr = {1, 2, 3, 4};
  s21::array<int, 4> s21arr1 = {4, 3, 2, 1};

  std::array<int, 4> arr = {1, 2, 3, 4};
  std::array<int, 4> arr1 = {4, 3, 2, 1};
  s21arr.swap(s21arr1);
  arr.swap(arr1);

  for (size_t i = 0; i < 4; i++) {
    EXPECT_EQ(s21arr[i], arr[i]);
  }

  for (size_t i = 0; i < 4; i++) {
    EXPECT_EQ(s21arr1[i], arr1[i]);
  }
}

TEST(ArrayMethods, fill) {
  s21::array<int, 10> s21arr;
  int a = 10;
  s21arr.fill(a);
  std::array<int, 10> arr;
  arr.fill(a);

  for (size_t i = 0; i < s21arr.size(); i++) {
    EXPECT_EQ(s21arr[i], arr[i]);
  }
}

TEST(ArrayIterators, dataAndBeginAndEnd) {
  s21::array<char, 5> s21arr = {'a', 'b', 'c', 'd', 'e'};
  std::array<char, 5> arr = {'a', 'b', 'c', 'd', 'e'};
  EXPECT_TRUE(*s21arr.data() == *arr.data());
  EXPECT_TRUE(*s21arr.begin() == *arr.begin());
  EXPECT_TRUE(*(s21arr.end() - 1) == *(arr.end() - 1));
}