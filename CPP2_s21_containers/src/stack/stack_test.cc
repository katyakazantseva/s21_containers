#include <gtest/gtest.h>

#include <list>
#include <stack>
#include <vector>

#include "s21_stack.h"

TEST(StackTestConstructorDefault, Test0) {
  s21::stack<int> stack0;
  std::stack<int> stack1;

  ASSERT_EQ(stack0.size(), stack1.size());
}

TEST(StackTestPush, test0) {
  s21::stack<int> stack0;
  std::stack<int> stack1;

  stack0.push(13);
  stack1.push(13);

  ASSERT_EQ(stack0.size(), stack1.size());
  ASSERT_EQ(stack0.top(), stack1.top());
}

TEST(StackTestDestructor, Test0) {
  bool answer = false;

  {
    s21::stack<int> stack0;
    std::stack<int> stack1;
    answer = true;
  }

  ASSERT_TRUE(answer);
}

TEST(StackTestConstructorTop, Test0) {
  s21::stack<int> stack0;
  std::stack<int> stack1;

  stack0.push(13);
  stack1.push(13);

  ASSERT_EQ(stack0.size(), stack1.size());
  ASSERT_EQ(stack0.top(), stack1.top());
}

TEST(StackTestConstructorCopy, Test1) {
  s21::stack<int> stack0;
  std::stack<int> stack1;

  stack0.push(13);
  stack1.push(13);
  stack0.push(12);
  stack1.push(12);

  s21::stack<int> stack01 = stack0;
  std::stack<int> stack02 = stack1;

  ASSERT_EQ(stack02.size(), 2);
  ASSERT_EQ(stack01.size(), 2);

  ASSERT_EQ(stack02.top(), 12);
  ASSERT_EQ(stack01.top(), 12);

  ASSERT_EQ(stack0.size(), 2);
  ASSERT_EQ(stack1.size(), 2);
}

TEST(StackTestConstructorMove, Test0) {
  s21::stack<int> stack2{1, 2, 3};
  s21::stack<int> stack0(std::move(stack2));

  ASSERT_EQ(stack0.size(), 3);
}

TEST(StackTestPop, Test0) {
  s21::stack<int> stack0;
  std::stack<int> stack1;

  stack0.push(13);
  stack1.push(13);
  stack0.push(12);
  stack1.push(12);

  stack0.pop();
  stack1.pop();

  ASSERT_EQ(stack0.top(), 13);
  ASSERT_EQ(stack1.top(), 13);
  ASSERT_EQ(stack0.size(), 1);
  ASSERT_EQ(stack1.size(), 1);
}

TEST(StackTestSwap, Test0) {
  s21::stack<int> stack0;
  s21::stack<int> stack01;
  std::stack<int> stack1;
  std::stack<int> stack2;

  stack0.push(100);
  stack01.push(99);
  stack1.push(100);
  stack2.push(99);

  stack0.swap(stack01);
  stack2.swap(stack1);

  ASSERT_EQ(stack01.top(), 100);
  ASSERT_EQ(stack0.top(), 99);
  ASSERT_EQ(stack1.top(), 99);
  ASSERT_EQ(stack2.top(), 100);
}

TEST(StackTestGetContainer, Test1) {
  s21::stack<int, s21::list<int>> stack0;
  std::stack<int, std::list<int>> stack1;

  stack0.push(13);
  stack1.push(13);
  ASSERT_EQ(stack1.size(), 1);

  ASSERT_EQ(stack0.size(), stack1.size());
  ASSERT_EQ(stack0.top(), stack1.top());
}

TEST(StackTestEmpty, Test0) {
  s21::stack<int> stack0;
  std::stack<int> stack1;
  ASSERT_TRUE(stack0.empty());
  ASSERT_TRUE(stack1.empty());
}

TEST(StackTestOperatorCopy, Test0) {
  s21::stack<int> stack0{1, 2, 3};
  s21::stack<int> stack1;
  stack1 = stack0;
  std::stack<int> stack2;
  stack2.push(1);
  stack2.push(2);
  stack2.push(3);
  std::stack<int> stack3;
  stack3 = stack2;
  ASSERT_EQ(stack1.size(), 3);
  ASSERT_EQ(stack3.size(), 3);

  ASSERT_EQ(stack1.top(), 3);
  ASSERT_EQ(stack3.top(), 3);
}

TEST(StackTestOperatorMove, Test0) {
  s21::stack<int> stack0{1, 2, 3};
  s21::stack<int> stack1;
  stack1 = std::move(stack0);
  std::stack<int> stack2;
  stack2.push(1);
  stack2.push(2);
  stack2.push(3);
  std::stack<int> stack3;
  stack3 = std::move(stack2);
  ASSERT_EQ(stack1.size(), 3);
  ASSERT_EQ(stack3.size(), 3);

  ASSERT_EQ(stack1.top(), 3);
  ASSERT_EQ(stack3.top(), 3);
}