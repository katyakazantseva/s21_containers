#include <gtest/gtest.h>

#include "s21_map.h"

TEST(map, ConstructorDefault) {
  s21::map<int, int> my_map;
  std::map<int, int> map;
  EXPECT_EQ(my_map.empty(), map.empty());
}

TEST(map, ConstructorInitializer) {
  s21::map<int, int> my_map = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  std::map<int, int> map = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  EXPECT_EQ(my_map.size(), map.size());
  auto my_it = my_map.begin();
  auto it = map.begin();
  for (; my_it != my_map.end(); ++my_it, ++it) {
    EXPECT_TRUE((*it).first == (*my_it).first);
    EXPECT_TRUE((*it).second == (*my_it).second);
  }
}

TEST(map, ConstructorCopy) {
  s21::map<int, int> my_map = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  s21::map<int, int> my_map1 = my_map;
  std::map<int, int> map = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  std::map<int, int> map1 = map;
  map = map1;
  EXPECT_EQ(my_map1.size(), map1.size());
  auto my_it = my_map1.begin();
  auto it = map1.begin();
  for (; my_it != my_map1.end(); ++my_it, ++it) {
    EXPECT_TRUE((*it).first == (*my_it).first);
    EXPECT_TRUE((*it).second == (*my_it).second);
  }
}

TEST(map, ConstructorMove) {
  s21::map<int, int> my_map = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  s21::map<int, int> my_map1 = std::move(my_map);
  std::map<int, int> map = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  std::map<int, int> map1 = std::move(map);
  EXPECT_EQ(my_map1.size(), map1.size());
  auto my_it = my_map1.begin();
  auto it = map1.begin();
  for (; my_it != my_map1.end(); ++my_it, ++it) {
    EXPECT_TRUE((*it).first == (*my_it).first);
    EXPECT_TRUE((*it).second == (*my_it).second);
  }
}

TEST(map, OperatorEq) {
  s21::map<int, int> my_map = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  s21::map<int, int> my_map1;
  my_map1 = my_map;
  std::map<int, int> map = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  std::map<int, int> map1;
  map1 = map;
  EXPECT_EQ(my_map1.size(), map1.size());
  auto my_it = my_map1.begin();
  auto it = map1.begin();
  for (; my_it != my_map1.end(); ++my_it, ++it) {
    EXPECT_TRUE((*it).first == (*my_it).first);
    EXPECT_TRUE((*it).second == (*my_it).second);
  }
}

TEST(map, FunctionAt) {
  s21::map<int, char> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  my_map.at(1) = 'A';
  map.at(1) = 'A';
  EXPECT_TRUE(my_map.at(1) == map.at(1));
  EXPECT_TRUE(my_map.at(2) == map.at(2));
}

TEST(map, OperatorBrekets) {
  s21::map<int, char> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_TRUE(my_map[1] == map[1]);
  my_map[4] = 'd';
  map[4] = 'd';
  EXPECT_TRUE(my_map[4] == map[4]);
}

TEST(map, IteratorBegin) {
  s21::map<int, int> my_map = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  std::map<int, int> map = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  auto my_it = my_map.begin();
  auto it = map.begin();
  EXPECT_TRUE((*it).first == (*my_it).first);
  EXPECT_TRUE((*it).second == (*my_it).second);
}

TEST(map, FunctionEmpty) {
  s21::map<int, int> my_map;
  std::map<int, int> map;
  EXPECT_TRUE(my_map.empty() == map.empty());
}

TEST(map, FunctionSize) {
  s21::map<int, int> my_map = {{1, 1}};
  std::map<int, int> map = {{1, 1}};
  EXPECT_TRUE(my_map.size() == map.size());
}

TEST(map, FunctionClear) {
  s21::map<int, int> my_map = {{1, 1}};
  std::map<int, int> map = {{1, 1}};
  my_map.clear();
  map.clear();
  EXPECT_TRUE(my_map.size() == map.size());
}

TEST(map, FunctionInsert1) {
  s21::map<int, char> my_map;
  std::map<int, char> map;
  my_map.insert(std::make_pair(1, 'a'));
  my_map.insert(std::make_pair(2, 'a'));
  my_map.insert(std::make_pair(3, 'a'));
  map.insert(std::make_pair(1, 'a'));
  map.insert(std::make_pair(2, 'a'));
  map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto it = map.begin();
  for (; my_it != my_map.end(); ++my_it, ++it) {
    EXPECT_TRUE((*my_it).first == (*it).first);
    EXPECT_TRUE((*my_it).second == (*it).second);
  }
  auto pr1 = my_map.insert(std::make_pair(1, 'a'));
  auto pr2 = map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, FunctionInsert2) {
  s21::map<int, char> my_map;
  std::map<int, char> map;
  my_map.insert(1, 'a');
  my_map.insert(2, 'a');
  my_map.insert(3, 'a');
  map.insert(std::make_pair(1, 'a'));
  map.insert(std::make_pair(2, 'a'));
  map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto it = map.begin();
  for (; my_it != my_map.end(); ++my_it, ++it) {
    EXPECT_TRUE((*my_it).first == (*it).first);
    EXPECT_TRUE((*my_it).second == (*it).second);
  }

  auto pr1 = my_map.insert(1, 'a');
  auto pr2 = map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, FunctionInsertOrAssign) {
  s21::map<int, char> my_map;
  std::map<int, char> map;
  my_map.insert(1, 'a');
  my_map.insert(2, 'a');
  my_map.insert(3, 'a');
  map.insert(std::make_pair(1, 'a'));
  map.insert(std::make_pair(2, 'a'));
  map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto it = map.begin();
  for (; my_it != my_map.end(); ++my_it, ++it) {
    EXPECT_TRUE((*my_it).first == (*it).first);
    EXPECT_TRUE((*my_it).second == (*it).second);
  }
  auto pr1 = my_map.insert_or_assign(1, 'b');
  auto i = map.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
}

TEST(map, FunctionErase) {
  s21::map<int, int> my_map = {{1, 2}, {2, 3}};
  std::map<int, int> map = {{1, 2}, {2, 3}};
  auto my_it = my_map.begin();
  auto it = map.begin();
  my_map.erase(my_it);
  map.erase(it);
  EXPECT_TRUE(my_map.size() == map.size());
}

TEST(map, FunctionSwap) {
  s21::map<int, int> my_map = {{1, 2}, {2, 3}};
  s21::map<int, int> my_map1 = {{1, 1}};
  std::map<int, int> map = {{1, 2}, {2, 3}};
  std::map<int, int> map1 = {{1, 1}};
  my_map.swap(my_map1);
  map.swap(map1);
  EXPECT_TRUE(my_map.size() == map.size());
  EXPECT_TRUE(my_map1.size() == map1.size());
}

TEST(map, FunctionMerge) {
  s21::map<int, int> my_map = {{1, 2}, {2, 3}};
  s21::map<int, int> my_map1 = {{3, 4}};
  std::map<int, int> map = {{1, 2}, {2, 3}};
  std::map<int, int> map1 = {{3, 4}};
  my_map.merge(my_map1);
  map.merge(map1);
  auto my_it = my_map.begin();
  auto it = map.begin();
  for (; my_it != my_map.end(); ++my_it, ++it) {
    EXPECT_TRUE((*my_it).first == (*it).first);
    EXPECT_TRUE((*my_it).second == (*it).second);
  }
}
