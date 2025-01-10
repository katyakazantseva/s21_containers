#include <gtest/gtest.h>

#include "s21_vector.h"

TEST(vector, DefaultConstructor) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_TRUE(v.size() == 0);
}

TEST(vector, SizeConstructor1) {
  const size_t size = 5;
  s21::vector<int> v(size);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(vector, SizeConstructor2) {
  const size_t size = 0;
  s21::vector<int> v(size);
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), size);
}

TEST(vector, InitializerListConstructor1) {
  s21::vector<int> v = {};
  EXPECT_TRUE(v.empty());
  EXPECT_TRUE(v.size() == 0);
}

TEST(vector, InitializerListConstructor2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_FALSE(v.empty());
  EXPECT_TRUE(v.size() == 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[4], 5);
}

TEST(vector, CopyConstructor1) {
  s21::vector<int> v1;
  s21::vector<int> v2(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_TRUE(v2.size() == 0);
}

TEST(vector, CopyConstructor2) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(v1);
  EXPECT_TRUE(v2.size() == v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(vector, MoveConstructor1) {
  s21::vector<int> v1;
  s21::vector<int> v2(std::move(v1));
  EXPECT_TRUE(v2.empty());
  EXPECT_TRUE(v2.size() == 0);
}

TEST(vector, MoveConstructor2) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(std::move(v1));
  EXPECT_TRUE(v2.size() == 3);
  EXPECT_TRUE(v1.empty());
}

TEST(vector, Destructor1) {
  s21::vector<int>* v = new s21::vector<int>();
  delete v;
}

TEST(vector, Destructor2) {
  s21::vector<int>* v = new s21::vector<int>{1, 2, 3};
  delete v;
}

TEST(vector, OperatorEq1) {
  s21::vector<int> v1;
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_TRUE(v2.size() == 0);
}

TEST(vector, OperatorEq2) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_TRUE(v2.size() == 3);
  EXPECT_TRUE(v1.empty());
}

TEST(vector, OperatorEq3) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_TRUE(v2.size() == 0);
}

TEST(vector, OperatorEq4) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_TRUE(v2.size() == 3);
  EXPECT_TRUE(v1.empty());
}

TEST(vector, FunctionAt1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.at(4), 5);
}

TEST(vector, FunctionAt2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_THROW(v.at(5), std::out_of_range);
  EXPECT_THROW(v.at(10), std::out_of_range);
}

TEST(vector, OperatorBrakets1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

TEST(vector, OperatorBrakets2) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

TEST(vector, FunctionFront) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.front(), 1);
}

TEST(vector, FunctionBack) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.back(), 5);
}

TEST(vector, FunctionData1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  int* dataPtr = v.data();
  EXPECT_EQ(*dataPtr, 1);
  *dataPtr = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(vector, FunctionData2) {
  s21::vector<int> v;
  int* dataPtr = v.data();
  EXPECT_EQ(dataPtr, nullptr);
}

TEST(vector, IteratorBegin1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  *it = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(vector, IteratorBegin2) {
  s21::vector<int> v;
  auto it = v.begin();
  EXPECT_EQ(it, v.end());
}

TEST(vector, IteratorEnd1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.end();
  auto beginIt = v.begin();
  EXPECT_NE(it, beginIt);
}

TEST(vector, IteratorEnd2) {
  s21::vector<int> v;
  auto it = v.end();
  EXPECT_EQ(it, v.begin());
}

TEST(vector, IteratorCbegin1) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.cbegin();
  EXPECT_EQ(*it, 1);
}

TEST(vector, IteratorCbegin2) {
  const s21::vector<int> v;
  auto it = v.cbegin();
  EXPECT_EQ(it, v.cend());
}

TEST(vector, IteratorCend1) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.cend();
  auto beginIt = v.cbegin();
  EXPECT_EQ(it, beginIt + 5);
}

TEST(vector, IteratorCend2) {
  const s21::vector<int> v;
  auto it = v.cend();
  EXPECT_EQ(it, v.cbegin());
}

TEST(vector, FunctionEmpty1) {
  const s21::vector<int> v;
  EXPECT_TRUE(v.empty());
}

TEST(vector, FunctionEmpty2) {
  const s21::vector<int> v = {1, 2, 3};
  EXPECT_FALSE(v.empty());
}

TEST(vector, FunctionSize1) {
  const s21::vector<int> v;
  EXPECT_TRUE(v.size() == 0);
}

TEST(vector, FunctionSize2) {
  const s21::vector<int> v = {1, 2, 3};
  EXPECT_TRUE(v.size() == 3);
}

TEST(vector, FunctionReserve) {
  s21::vector<int> v;
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity + 10;
  v.reserve(newCapacity);
  EXPECT_TRUE(v.capacity() == newCapacity);
}

TEST(vector, Capacity) {
  const s21::vector<int> v;
  EXPECT_TRUE(v.capacity() == 0);
}

TEST(vector, FunctionShrinkToFit1) {
  s21::vector<int> v;
  v.shrink_to_fit();
  EXPECT_TRUE(v.capacity() == 0);
}

TEST(vector, FunctionShrinkToFit2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  v.pop_back();
  v.shrink_to_fit();
  EXPECT_LE(v.capacity(), v.size());
  EXPECT_LE(v.capacity(), initialCapacity);
}

TEST(vector, FunctionClear1) {
  s21::vector<int> v;
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_TRUE(v.size() == 0);
  EXPECT_TRUE(v.capacity() == 0);
}

TEST(vector, FunctionClear2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_TRUE(v.size() == 0);
  EXPECT_TRUE(v.capacity() == 0);
}

TEST(vector, FunctionInsert1) {
  s21::vector<int> v = {2, 3, 4};
  auto it = v.insert(v.begin(), 1);
  EXPECT_TRUE(v.size() == 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(*it, 1);
}

TEST(vector, FunctionInsert2) {
  s21::vector<int> v = {1, 3, 4};
  auto it = v.insert(v.begin() + 1, 2);
  EXPECT_TRUE(v.size() == 4);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(*it, 2);
}

TEST(vector, FunctionInsert3) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.insert(v.end(), 4);
  EXPECT_TRUE(v.size() == 4);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(*it, 4);
}

TEST(vector, FunctionErase1) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.begin());
  EXPECT_TRUE(v.size() == 3);
  EXPECT_EQ(v[0], 2);
}

TEST(vector, FunctionErase2) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.begin() + 1);
  EXPECT_TRUE(v.size() == 3);
  EXPECT_EQ(v[1], 3);
}

TEST(vector, FunctionErase3) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.end() - 1);
  EXPECT_TRUE(v.size() == 3);
  EXPECT_EQ(v[2], 3);
}

TEST(vector, FunctionPushBack1) {
  s21::vector<int> v;
  v.push_back(1);
  EXPECT_TRUE(v.size() == 1);
  EXPECT_EQ(v[0], 1);
}

TEST(vector, FunctionPushBack2) {
  s21::vector<int> v = {1, 2, 3};
  v.push_back(4);
  EXPECT_TRUE(v.size() == 4);
  EXPECT_EQ(v[3], 4);
}

TEST(vector, FunctionPopBack1) {
  s21::vector<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_TRUE(v.size() == 2);
  EXPECT_EQ(v.back(), 2);
}

TEST(vector, FunctionPopBack2) {
  s21::vector<int> v;

  v.pop_back();
  EXPECT_TRUE(v.empty());
}

TEST(vector, FunctionSwap1) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};

  v1.swap(v2);

  EXPECT_TRUE(v1.size() == 3);
  EXPECT_TRUE(v2.size() == 3);

  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[2], 6);

  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 3);
}

TEST(vector, FunctionSwap2) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {1, 2, 3};

  v1.swap(v2);

  EXPECT_TRUE(v1.size() == 3);
  EXPECT_FALSE(v1.empty());
  EXPECT_TRUE(v2.size() == 0);
  EXPECT_TRUE(v2.empty());
}

TEST(vector, FunctionInsertMany1) {
  s21::vector<int> vec = {1, 2, 3, 7, 8};
  s21::vector<int>::const_iterator pos = vec.cbegin() + 3;

  vec.insert_many(pos, 4, 5, 6);

  EXPECT_TRUE(vec.size() == 8);

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
  EXPECT_EQ(vec[6], 7);
  EXPECT_EQ(vec[7], 8);
}

TEST(vector, FunctionInsertMany2) {
  s21::vector<int> vec = {1, 2, 3};

  vec.insert_many_back(4, 5, 6);

  EXPECT_TRUE(vec.size() == 6);

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
}
