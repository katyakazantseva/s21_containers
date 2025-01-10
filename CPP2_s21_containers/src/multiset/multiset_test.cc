#include <gtest/gtest.h>

#include <set>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

TEST(MultisetCtor, defaultCtor) {
  s21::multiset<int> s21ms;
  std::multiset<int> ms;

  EXPECT_TRUE(s21ms.empty());
  EXPECT_TRUE(ms.empty());
}

TEST(MultisetCtor, initial_listCtor) {
  s21::multiset<int> s21ms = {1, 2, 3, 4};
  std::multiset<int> ms = {1, 2, 3, 4};

  auto s21x = s21ms.begin();
  auto x = ms.begin();
  EXPECT_EQ(*s21x, *x);

  ++s21x;
  ++s21x;
  ++x;
  ++x;

  EXPECT_EQ(*s21x, *x);
}

TEST(MultisetCtor, copyCtor) {
  s21::multiset<double> s21ms = {1.23, 2.345345,   3.8,
                                 4.0,  4324.56656, 14324.54};
  s21::multiset<double> ms(s21ms);

  auto s21x = s21ms.begin();
  auto x = ms.begin();
  while (x != s21ms.end()) {
    EXPECT_EQ(*s21x, *x);
    ++s21x;
    ++x;
  }
}

TEST(MultisetCtor, moveCtor) {
  s21::multiset<double> s21ms = {1.23, 2.345345,   3.8,
                                 4.0,  4324.56656, 14324.54};
  s21::multiset<double> ms(std::move(s21ms));

  EXPECT_TRUE(s21ms.empty());

  auto x = ms.begin();
  ++x;
  ++x;
  ++x;

  EXPECT_EQ(*x, 4.0);
}

TEST(MultisetOperators, minusOperator) {
  s21::multiset<int> s21ms = {2,   3,   14, 18,  22,  23,  35,  41,
                              423, 300, 64, 400, 325, 534, 470, 860};
  auto x = s21ms.end();

  while (x != s21ms.begin()) {
    EXPECT_TRUE(s21ms.contains(*x));
    --x;
  }
}

TEST(MultisetOperators, plusAndStarOperators) {
  s21::multiset<int> s21ms;
  auto x = s21ms.begin();
  ++x;
  EXPECT_TRUE(*x == ZERO);
}

TEST(MultisetOperators, copyEqOperator_test_1) {
  s21::multiset<double> s21ms = {1.23, 2.345345,   3.8,
                                 4.0,  4324.56656, 14324.54};
  s21::multiset<double> ms = s21ms;

  auto s21x = s21ms.begin();
  auto x = ms.begin();
  while (s21x != s21ms.end()) {
    EXPECT_EQ(*s21x, *x);
    ++s21x;
    ++x;
  }
}

TEST(MultisetOperators, copyEqOperator_test_2) {
  s21::multiset<double> s21ms = {1.23, 2.345345,   3.8,
                                 4.0,  4324.56656, 14324.54};
  s21::multiset<double> ms;

  ms = s21ms;

  auto x = ms.begin();
  ++x;
  ++x;
  ++x;
  ++x;
  --x;

  auto a = s21ms.begin();
  ++a;
  ++a;
  ++a;
  ++a;
  --a;

  EXPECT_EQ(*x, *a);
}

TEST(MultisetOperators, moveEqOperator) {
  s21::multiset<double> s21ms = {1.23, 2.345345,   3.8,
                                 4.0,  4324.56656, 14324.54};
  s21::multiset<double> ms = std::move(s21ms);

  EXPECT_TRUE(s21ms.empty());

  auto x = ms.begin();
  ++x;
  ++x;
  ++x;

  EXPECT_EQ(*x, 4.0);
}

TEST(MultisetIterators, begin) {
  s21::multiset<int> s21ms = {1, 2, 3, 4, 4, 1};
  std::multiset<int> ms = {1, 2, 3, 4, 4, 1};

  EXPECT_EQ(*s21ms.begin(), *ms.begin());
}

TEST(MultisetMethods, emptyTrue) {
  s21::multiset<int> s21ms;
  EXPECT_TRUE(s21ms.empty());
}

TEST(MultisetMethods, emptyFalse) {
  s21::multiset<int> s21ms = {1, 2, 3, 4};
  EXPECT_FALSE(s21ms.empty());
  EXPECT_EQ(*s21ms.find(3), 3);
}

TEST(MultisetMethods, size) {
  s21::multiset<int> s21ms = {2,   3,   14, 18,  22,  23,  35,  41,
                              423, 300, 64, 400, 325, 534, 470, 860};
  std::multiset<int> ms = {2,   3,   14, 18,  22,  23,  35,  41,
                           423, 300, 64, 400, 325, 534, 470, 860};
  EXPECT_EQ(s21ms.size(), ms.size());
}

TEST(MultisetMethods, clear) {
  s21::multiset<char> s21ms = {'h', 'f', 'F', 'v', 'e', 'e', 'f', 'r', 't'};
  std::multiset<char> ms = {'h', 'f', 'F', 'v', 'e', 'e', 'f', 'r', 't'};
  s21ms.clear();
  ms.clear();
  EXPECT_TRUE(s21ms.empty() == ms.empty());
}

TEST(MultisetMethods, insert) {
  s21::multiset<int> s21ms = {2,   3,   14, 18,  22,  23,  35,  41,
                              423, 300, 64, 400, 325, 534, 470, 860};
  std::multiset<int> ms = {2,   3,   14, 18,  22,  23,  35,  41,
                           423, 300, 64, 400, 325, 534, 470, 860};

  EXPECT_EQ(s21ms.size(), ms.size());

  s21ms.insert(400);
  s21ms.insert(400);
  s21ms.insert(400);
  s21ms.insert(400);
  s21ms.insert(400);
  s21ms.insert(0);
  s21ms.insert(2);
  s21ms.insert(34);
  s21ms.insert(42);

  ms.insert(400);
  ms.insert(400);
  ms.insert(400);
  ms.insert(400);
  ms.insert(400);
  ms.insert(0);
  ms.insert(2);
  ms.insert(34);
  ms.insert(42);

  EXPECT_EQ(s21ms.count(400), ms.count(400));
  EXPECT_EQ(s21ms.count(2), ms.count(2));
  EXPECT_EQ(s21ms.count(42), ms.count(42));
  EXPECT_EQ(s21ms.count(325), ms.count(325));
  EXPECT_EQ(s21ms.count(324), ms.count(324));
  EXPECT_EQ(s21ms.size(), ms.size());
}

TEST(MultisetMethods, erase_test_1) {
  s21::multiset<int> s21ms = {2,   3,   14, 18,  22,  23,  35,  41,
                              423, 300, 64, 400, 325, 534, 470, 860};
  std::multiset<int> ms = {2,   3,   14, 18,  22,  23,  35,  41,
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

  EXPECT_EQ(s21ms.count(2), ms.count(2));
  EXPECT_EQ(s21ms.count(22), ms.count(22));

  EXPECT_EQ(s21ms.size(), ms.size());
}

TEST(MultisetMethods, erase_test_2) {
  s21::multiset<int> s21ms = {2,   3,   14, 18,  22,  23,  35,  41,
                              423, 300, 64, 400, 325, 534, 470, 860};
  std::multiset<int> ms = {2,   3,   14, 18,  22,  23,  35,  41,
                           423, 300, 64, 400, 325, 534, 470, 860};

  EXPECT_EQ(s21ms.size(), ms.size());

  size_t counter = 0;
  size_t size = ms.size();

  while (counter < size) {
    auto s21x = s21ms.begin();
    auto x = ms.begin();

    for (size_t i = 0; i < counter; i++) {
      ++x;
      ++s21x;
    }

    auto val = *x;

    s21ms.insert(*s21x);
    ms.insert(val);

    EXPECT_EQ(s21ms.count(val), ms.count(val));

    s21ms.erase(s21x);
    ms.erase(*x);

    EXPECT_EQ(s21ms.count(val), ms.count(val));

    EXPECT_EQ(s21ms.size(), ms.size());

    s21ms.insert(val);
    ms.insert(val);

    EXPECT_EQ(s21ms.size(), ms.size());

    counter++;
  }
}

TEST(MultisetMethods, erase_test_3) {
  s21::multiset<int> s21ms;
  s21ms.erase(0);
  auto x = s21ms.begin();
  EXPECT_TRUE(x == nullptr);
}

TEST(MultisetMethods, swap) {
  s21::multiset<std::string> s21ms_1 = {"afdsfsfs", "fdsfsfsf",
                                        "fsdjfihsofkmsk"};
  s21::multiset<std::string> s21ms_2 = {"fdsfsfdsd", "yatstdrastdy"};
  std::multiset<std::string> ms_1 = {"afdsfsfs", "fdsfsfsf", "fsdjfihsofkmsk"};
  std::multiset<std::string> ms_2 = {"fdsfsfdsd", "yatstdrastdy"};
  s21ms_1.swap(s21ms_2);
  ms_1.swap(ms_2);
  EXPECT_TRUE(s21ms_1.size() == ms_1.size());
  EXPECT_TRUE(s21ms_2.size() == ms_2.size());

  auto s21x = s21ms_1.begin();
  auto x = ms_1.begin();

  for (; s21x != s21ms_1.end(); ++s21x, ++x) {
    EXPECT_TRUE(*s21x == *x);
  }
}

TEST(MultisetMethods, merge) {
  s21::multiset<std::string> s21ms_1 = {"afdsfsfs", "fdsfsfsf",
                                        "fsdjfihsofkmsk"};
  s21::multiset<std::string> s21ms_2 = {"fdsfsfdsd", "yatstdrastdy"};
  std::multiset<std::string> ms_1 = {"afdsfsfs", "fdsfsfsf", "fsdjfihsofkmsk"};
  std::multiset<std::string> ms_2 = {"fdsfsfdsd", "yatstdrastdy"};
  s21ms_1.merge(s21ms_2);
  ms_1.merge(ms_2);
  auto s21x = s21ms_1.begin();
  auto x = ms_1.begin();

  for (; s21x != s21ms_1.end(); ++s21x, ++x) {
    EXPECT_TRUE(*s21x == *x);
  }
}

TEST(MultisetMethods, findSuccess) {
  s21::multiset<int> s21ms = {1, 2, 3, 4, 4, 1};
  std::multiset<int> ms = {1, 2, 3, 4, 4, 1};
  auto it21 = s21ms.find(3);
  auto it = ms.find(3);

  EXPECT_EQ(*it, *it21);
}

TEST(MultisetMethods, findFault) {
  s21::multiset<int> s21ms = {1, 2, 3, 4, 4, 1};
  auto it21 = s21ms.find(10);

  EXPECT_EQ(*it21, ZERO);
}

TEST(MultisetMethods, contains) {
  s21::multiset<int> s21ms = {2,   3,   14, 18,  22,  23,  35,  41,
                              423, 300, 64, 400, 325, 534, 470, 860};
  std::multiset<int> ms = {2,   3,   14, 18,  22,  23,  35,  41,
                           423, 300, 64, 400, 325, 534, 470, 860};

  EXPECT_TRUE(s21ms.contains(64));
  EXPECT_FALSE(s21ms.contains(10));
}

TEST(MultisetMethods, equal_range_test_1) {
  s21::multiset<int> s21ms = {2,   3,   14, 18,  22,  23,  35,  41,
                              423, 300, 64, 400, 325, 534, 470, 860};
  std::multiset<int> ms = {2,   3,   14, 18,  22,  23,  35,  41,
                           423, 300, 64, 400, 325, 534, 470, 860};

  size_t counter = 0;
  size_t size = ms.size();

  while (counter < size - UNIT) {
    auto s21x = s21ms.begin();
    auto x = ms.begin();

    for (size_t i = 0; i < counter; i++) {
      ++x;
      ++s21x;
    }

    auto s21res = s21ms.equal_range(*s21x);
    auto res = ms.equal_range(*x);

    EXPECT_TRUE(*s21res.first == *res.first);
    EXPECT_TRUE(*s21res.second == *res.second);

    counter++;
  }
}

TEST(MultisetMethods, equal_range_test_2) {
  s21::multiset<int> s21ms = {2, 3, 140};
  std::multiset<int> ms = {2, 3, 140};

  auto s21res = s21ms.equal_range(ZERO);
  auto res = ms.equal_range(ZERO);

  EXPECT_TRUE(*s21res.first == *res.first);
  EXPECT_TRUE(*s21res.second == *res.second);
}

TEST(MultisetMethods, lower_bound_test_1) {
  s21::multiset<int> s21ms = {2, 3, 140};
  std::multiset<int> ms = {2, 3, 140};

  auto s21res = s21ms.lower_bound(ZERO);
  auto res = ms.lower_bound(ZERO);

  EXPECT_TRUE(*s21res == *res);
}

TEST(MultisetMethods, lower_bound_test_2) {
  s21::multiset<int> s21ms = {2, 3, 140};
  std::multiset<int> ms = {2, 3, 140};

  auto s21res = s21ms.lower_bound(2);
  auto res = ms.lower_bound(2);

  EXPECT_TRUE(*s21res == *res);
}

TEST(MultisetMethods, lower_bound_test_3) {
  s21::multiset<int> s21ms = {2, 3, 140};
  std::multiset<int> ms = {2, 3, 140};

  auto s21res = s21ms.lower_bound(140);
  auto res = ms.lower_bound(140);

  EXPECT_TRUE(*s21res == *res);
}

TEST(MultisetMethods, lower_bound_test_4) {
  s21::multiset<int> s21ms = {2, 3, 140};

  EXPECT_THROW(s21ms.lower_bound(1000), std::out_of_range);
}

TEST(MultisetMethods, upper_bound_test_1) {
  s21::multiset<int> s21ms = {2, 3, 140};
  std::multiset<int> ms = {2, 3, 140};

  auto s21res = s21ms.upper_bound(ZERO);
  auto res = ms.upper_bound(ZERO);

  EXPECT_TRUE(*s21res == *res);
}

TEST(MultisetMethods, upper_bound_test_2) {
  s21::multiset<int> s21ms = {2, 3, 140};
  std::multiset<int> ms = {2, 3, 140};

  auto s21res = s21ms.upper_bound(3);
  auto res = ms.upper_bound(3);

  EXPECT_TRUE(*s21res == *res);
}

TEST(MultisetMethods, upper_bound_test_3) {
  s21::multiset<int> s21ms = {2, 3, 140};

  auto s21res = s21ms.upper_bound(3);

  EXPECT_TRUE(*s21res == 140);
}

TEST(MultisetMethods, upper_bound_test_4) {
  s21::multiset<int> s21ms = {2, 3, 140};

  EXPECT_THROW(s21ms.upper_bound(1000), std::out_of_range);
}

TEST(MultisetMethods, insert_many) {
  s21::multiset<int> s21ms = {2,   3,   14, 18,  22,  23,  35,  41,
                              423, 300, 64, 400, 325, 534, 470, 860};
  s21::vector<s21::multiset<int>::iterator> vec;

  vec = s21ms.insert_many(5, 8, 9, 1000, 1002);

  auto x = vec.begin();

  EXPECT_TRUE(*x == s21ms.find(5));

  ++x;
  ++x;
  ++x;
  ++x;

  EXPECT_TRUE(*x == s21ms.find(1002));
}
