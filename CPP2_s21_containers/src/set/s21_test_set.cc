#include <gtest/gtest.h>

#include "s21_set.h"

TEST(set, ConstructorDefault) {
  s21::set<int> my_set;
  std::set<int> set;
  EXPECT_EQ(my_set.empty(), set.empty());
}

TEST(set, ConstructorInitializer) {
  s21::set<int> my_set = {1, 2, 3, 4};
  std::set<int> set = {1, 2, 3, 4};
  EXPECT_EQ(my_set.size(), set.size());
  auto my_it = my_set.begin();
  auto it = set.begin();
  for (; my_it != my_set.end(); ++my_it, ++it) {
    EXPECT_TRUE(*it == *my_it);
  }
}

TEST(set, ConstructorCopy) {
  s21::set<int> my_set = {1, 2, 3, 4};
  s21::set<int> my_set1 = my_set;
  std::set<int> set = {1, 2, 3, 4};
  std::set<int> set1 = set;
  set = set1;
  EXPECT_EQ(my_set1.size(), set1.size());
  auto my_it = my_set1.begin();
  auto it = set1.begin();
  for (; my_it != my_set1.end(); ++my_it, ++it) {
    EXPECT_TRUE(*it == *my_it);
  }
}

TEST(set, ConstructorMove) {
  s21::set<int> my_set = {1, 2, 3, 4};
  s21::set<int> my_set1 = std::move(my_set);
  std::set<int> set = {1, 2, 3, 4};
  std::set<int> set1 = std::move(set);
  EXPECT_EQ(my_set1.size(), set1.size());
  auto my_it = my_set1.begin();
  auto it = set1.begin();
  for (; my_it != my_set1.end(); ++my_it, ++it) {
    EXPECT_TRUE(*it == *my_it);
  }
}

TEST(set, OperatorEq) {
  s21::set<int> my_set = {1, 2, 3, 4};
  s21::set<int> my_set1;
  my_set1 = my_set;
  std::set<int> set = {1, 2, 3, 4};
  std::set<int> set1;
  set1 = set;
  EXPECT_EQ(my_set1.size(), set1.size());
  auto my_it = my_set1.begin();
  auto it = set1.begin();
  for (; my_it != my_set1.end(); ++my_it, ++it) {
    EXPECT_TRUE(*it == *my_it);
  }
}

TEST(set, IteratorBegin) {
  s21::set<int> my_set = {1, 2, 3, 4};
  std::set<int> set = {1, 2, 3, 4};
  auto my_it = my_set.begin();
  auto it = set.begin();
  EXPECT_TRUE(*it == *my_it);
}

TEST(set, IteratorPlus) {
  s21::set<int> my_set = {1, 2, 3, 4};
  std::set<int> set = {1, 2, 3, 4};
  auto my_it = my_set.begin();
  auto it = set.begin();
  my_it++;
  it++;
  EXPECT_TRUE(*it == *my_it);
}

TEST(set, IteratorMinus) {
  s21::set<int> my_set = {1, 2, 3, 4};
  std::set<int> set = {1, 2, 3, 4};
  auto my_it = my_set.begin();
  auto it = set.begin();
  my_it++;
  my_it--;
  it++;
  it--;
  EXPECT_TRUE(*it == *my_it);
}

TEST(set, IteratorEq) {
  s21::set<int> my_set = {1, 2, 3, 4};
  std::set<int> set = {1, 2, 3, 4};
  auto my_it = my_set.begin();
  auto it = set.begin();
  EXPECT_EQ(my_it == my_set.begin(), it == set.begin());
}

TEST(set, FunctionEmpty) {
  s21::set<int> my_set;
  std::set<int> set;
  EXPECT_TRUE(my_set.empty() == set.empty());
}

TEST(set, FunctionSize) {
  s21::set<int> my_set = {1};
  std::set<int> set = {1};
  EXPECT_TRUE(my_set.size() == set.size());
}

TEST(set, FunctionClear) {
  s21::set<int> my_set = {1};
  std::set<int> set = {1};
  my_set.clear();
  set.clear();
  EXPECT_TRUE(my_set.size() == set.size());
}

TEST(set, FunctionInsert) {
  s21::set<int> my_set = {1};
  std::set<int> set = {1};
  auto my_it = my_set.insert(2);
  auto it = set.insert(2);
  EXPECT_EQ(*my_set.find(2), *set.find(2));
  EXPECT_TRUE(my_it.second == it.second);
}

TEST(set, FunctionErase) {
  s21::set<int> my_set = {1, 2};
  std::set<int> set = {1, 2};
  auto my_it = my_set.begin();
  auto it = set.begin();
  my_set.erase(my_it);
  set.erase(it);
  EXPECT_TRUE(my_set.size() == set.size());
}

TEST(set, FunctionSwap) {
  s21::set<int> my_set = {1, 2};
  s21::set<int> my_set1 = {1};
  std::set<int> set = {1, 2};
  std::set<int> set1 = {1};
  my_set.swap(my_set1);
  set.swap(set1);
  EXPECT_TRUE(my_set.size() == set.size());
  EXPECT_TRUE(my_set1.size() == set1.size());
}

TEST(set, FunctionMerge) {
  s21::set<int> my_set = {1, 2};
  s21::set<int> my_set1 = {3};
  std::set<int> set = {1, 2};
  std::set<int> set1 = {3};
  my_set.merge(my_set1);
  set.merge(set1);
  auto my_it = my_set.begin();
  auto it = set.begin();
  for (; my_it != my_set.end(); ++my_it, ++it) {
    EXPECT_TRUE(*it == *my_it);
  }
}

TEST(set, FunctionFind) {
  s21::set<int> my_set = {1, 2};
  std::set<int> set = {1, 2};
  auto my_it = my_set.find(1);
  auto it = set.find(1);
  EXPECT_TRUE(*my_it == *it);
}

TEST(set, avl_tree_test_1) {
  s21::set<int> my_set = {1,    2,  3,  4,  5,  6,   8,   9,     400, 401,
                          4040, 45, 35, 67, 98, 100, 101, 10003, 165};
  auto x = my_set.begin();
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;

  while (x != my_set.begin()) {
    EXPECT_TRUE(my_set.contains(*x));
    --x;
  }
}

TEST(set, plusAndStarOperators) {
  s21::set<int> s21ms;
  auto x = s21ms.begin();
  ++x;
  EXPECT_TRUE(*x == 0);
}

TEST(set, erase_test_1) {
  s21::set<int> s21ms = {2,   3,   14, 18,  22,  23,  35,  41,
                         423, 300, 64, 400, 325, 534, 470, 860};
  std::set<int> ms = {2,   3,   14, 18,  22,  23,  35,  41,
                      423, 300, 64, 400, 325, 534, 470, 860};

  EXPECT_EQ(s21ms.size(), ms.size());

  s21ms.insert(0);
  s21ms.insert(2);
  s21ms.insert(34);
  s21ms.insert(42);

  ms.insert(0);
  ms.insert(2);
  ms.insert(34);
  ms.insert(42);

  auto s21x = s21ms.begin();
  auto s21x2 = s21ms.begin();
  ++s21x;

  ++s21x2;
  ++s21x2;
  ++s21x2;
  ++s21x2;
  ++s21x2;

  s21ms.erase(s21x);
  s21ms.erase(s21x2);

  ms.erase(2);
  ms.erase(22);

  EXPECT_EQ(s21ms.size(), ms.size());
}
