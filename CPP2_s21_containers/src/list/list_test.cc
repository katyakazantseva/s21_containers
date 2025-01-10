#include <gtest/gtest.h>

#include <list>

#include "s21_list.h"

TEST(ListConstructors, Default1) {
  s21::list<int> own_list;
  std::list<int> orig_list;

  EXPECT_EQ(own_list.size(), orig_list.size());
}

TEST(ListConstructors, Parameterized1) {
  s21::list<int> own_list(2);
  std::list<int> orig_list(2);

  EXPECT_EQ(own_list.size(), orig_list.size());
}

TEST(ListConstructors, InitialiserList1) {
  s21::list<int> own_list = {5, 7, 4};
  std::list<int> orig_list = {5, 7, 4};

  EXPECT_EQ(own_list.size(), orig_list.size());
  EXPECT_EQ(own_list.front(), orig_list.front());
  EXPECT_EQ(own_list.back(), orig_list.back());
}

TEST(ListConstructors, InitialiserList_2) {
  s21::list<int> own_list{5, 7, 4};
  std::list<int> orig_list{5, 7, 4};

  EXPECT_EQ(own_list.size(), orig_list.size());
  EXPECT_EQ(own_list.front(), orig_list.front());
  EXPECT_EQ(own_list.back(), orig_list.back());
}

TEST(ListConstructors, InitialiserListAssigment3) {
  s21::list<int> own_list;
  own_list = {5, 7, 4};
  std::list<int> orig_list;
  orig_list = {5, 7, 4};

  EXPECT_EQ(own_list.size(), orig_list.size());
  EXPECT_EQ(own_list.front(), orig_list.front());
  EXPECT_EQ(own_list.back(), orig_list.back());
}

TEST(ListConstructors, CopyConstructor1) {
  s21::list<int> original = {123, 132, 321, 231, 312, 213};
  s21::list<int>::iterator itr_orig = original.begin();

  s21::list<int> copied(original);

  EXPECT_EQ(original.size(), copied.size());
  for (const auto &itr_cp : copied) {
    EXPECT_EQ(itr_cp, *(itr_orig++));
  }
}

TEST(ListConstructors, CopyConstructor2) {
  s21::list<int> original = {123, 132, 321, 231, 312, 213};
  s21::list<int>::iterator itr_orig = original.begin();

  s21::list<int> copied;
  copied = original;

  EXPECT_EQ(original.size(), copied.size());
  for (const auto &itr_cp : copied) {
    EXPECT_EQ(itr_cp, *(itr_orig++));
  }
}

TEST(ListConstructors, MoveConstructor1) {
  s21::list<int> original = {123, 132, 321, 231, 312, 213};
  s21::list<int> expected = {123, 132, 321, 231, 312, 213};

  s21::list<int> moved(std::move(original));
  s21::list<int>::iterator itr_moved = moved.begin();

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(expected.size(), moved.size());

  for (const auto &itr_exp : expected) {
    EXPECT_EQ(itr_exp, *(itr_moved++));
  }
}

TEST(ListConstructors, MoveAssigment1) {
  s21::list<int> original = {123, 132, 321, 231, 312, 213};
  s21::list<int> expected = {123, 132, 321, 231, 312, 213};

  s21::list<int> moved;
  moved = std::move(original);
  s21::list<int>::iterator itr_moved = moved.begin();

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(expected.size(), moved.size());

  for (const auto &itr_exp : expected) {
    EXPECT_EQ(itr_exp, *(itr_moved++));
  }
}

TEST(ListOperators, IsEqual1) {
  s21::list<int> A = {1, 2, 3};
  s21::list<int> B = {1, 2, 3};
  EXPECT_TRUE(A == B);
}

TEST(ListOperators, IsEqual2) {
  s21::list<int> A = {1, 2, 3};
  s21::list<int> B = {1, 2, 3, 4};
  EXPECT_FALSE(A == B);
}

TEST(ListOperators, IsEqual3) {
  s21::list<int> A = {1, 2, 3, 1234};
  s21::list<int> B = {1, 2, 3, 4};
  EXPECT_FALSE(A == B);
}

TEST(ListOperators, IsEqual4) {
  s21::list<int> A;
  s21::list<int> B;
  EXPECT_TRUE(A == B);
}

TEST(ListOperators, IsNotEqual1) {
  s21::list<int> A = {1, 2, 3};
  s21::list<int> B = {1, 2, 3};
  EXPECT_FALSE(A != B);
}

TEST(ListOperators, IsNotEqual2) {
  s21::list<int> A = {1, 2, 3};
  s21::list<int> B = {1, 2, 3, 4};
  EXPECT_TRUE(A != B);
}

TEST(ListOperators, IsNotEqual3) {
  s21::list<int> A = {1, 2, 3, 1234};
  s21::list<int> B = {1, 2, 3, 4};
  EXPECT_TRUE(A != B);
}

TEST(ListOperators, IsNotEqual4) {
  s21::list<int> A;
  s21::list<int> B;
  EXPECT_FALSE(A != B);
}

TEST(ListIterators, Test1) {
  s21::list<int> A = {12, 2, 3};
  s21::list<int>::iterator it = A.begin();

  EXPECT_EQ(12, *it);
}

TEST(ListIterators, Test2) {
  s21::list<int> A = {12, 22, 32};
  s21::list<int>::iterator it = A.begin();
  EXPECT_EQ(12, *(it++));
  EXPECT_EQ(22, *it);
}

TEST(ListIterators, Test3) {
  s21::list<int> A = {12, 22, 32};
  s21::list<int>::iterator it = A.begin();
  EXPECT_EQ(22, *(++it));
}

TEST(ListIterators, Test4) {
  s21::list<int> A = {12, 22, 32};
  s21::list<int>::iterator it = A.end();
  EXPECT_EQ(12, *(++it));
}

TEST(ListIterators, Test5) {
  s21::list<int> A = {12, 22, 32};
  s21::list<int>::iterator it = A.end();
  EXPECT_EQ(32, *(--it));
}

TEST(ListIterators, Test6) {
  s21::list<int> A = {12, 22, 32};
  s21::list<int>::iterator it_1 = A.end();
  s21::list<int>::iterator it_2 = A.end();

  EXPECT_TRUE(it_1 == it_2);
}

TEST(ListIterators, Test7) {
  s21::list<int> A = {12, 22, 32};
  s21::list<int>::iterator it_1 = A.end();
  s21::list<int>::iterator it_2 = A.end();

  EXPECT_FALSE(it_1 != it_2);
}

TEST(ListIterators, Test8) {
  s21::list<int> A = {12, 22, 32};
  s21::list<int>::iterator it_1 = A.end();
  s21::list<int>::iterator it_2 = A.end();

  EXPECT_FALSE(it_1 != it_2);
}

TEST(ListIterators, Test9) {
  s21::list<int> A = {12, 22, 32};
  s21::list<int>::iterator it_1 = A.end();
  s21::list<int>::iterator it_2 = A.end();

  EXPECT_FALSE(it_1 != it_2);
}

TEST(ListIterators, Test10) {
  s21::list<int> A = {12, 22, 32};
  s21::list<int>::iterator it_1 = A.end();
  it_1--;
  EXPECT_EQ(32, *it_1);
}

TEST(ListElementAccess, Front1) {
  s21::list<int> A = {5, 7, 4};
  EXPECT_EQ(5, A.front());
}

TEST(ListElementAccess, Front2) {
  const s21::list<int> A = {5, 7, 4};
  EXPECT_EQ(5, A.front());
}

TEST(ListElementAccess, Front3) {
  s21::list<int> A = {5, 7, 4};
  A.push_front(15);
  EXPECT_EQ(15, A.front());
}

TEST(ListElementAccess, Front6) {
  s21::list<int> A = {10, 20, 30};
  s21::list<int>::iterator itr = A.begin();
  EXPECT_EQ(*itr, A.front());
}

TEST(ListElementAccess, Front7) {
  const s21::list<int> A = {10, 20, 30};
  s21::list<int>::const_iterator itr = A.cbegin();
  EXPECT_EQ(*itr, A.front());
}

TEST(ListElementAccess, Front8) {
  s21::list<int> A = {10, 20, 30};
  A.clear();
  EXPECT_ANY_THROW(A.front());
}

TEST(ListElementAccess, Back2) {
  s21::list<int> A = {10, 20, 30};
  A.clear();
  EXPECT_ANY_THROW(A.back());
}

TEST(ListElementAccess, Back3) {
  s21::list<int> A = {10, 20, 30};
  s21::list<int>::iterator itr = A.end();
  EXPECT_EQ(*(--itr), A.back());
}

TEST(ListElementAccess, Back5) {
  s21::list<int> A = {5, 7, 4};
  EXPECT_EQ(4, A.back());
}

TEST(ListElementAccess, Back6) {
  const s21::list<int> A = {5, 7, 4};
  EXPECT_EQ(4, A.back());
}

TEST(ListElementAccess, Back7) {
  s21::list<int> A = {5, 7, 4};
  A.push_back(15);
  EXPECT_EQ(15, A.back());
}

TEST(ListCapacity, MaxSize1) {
  s21::list<int> A;
  std::list<int> B;
  EXPECT_EQ(A.max_size(), B.max_size());
}

TEST(ListCapacity, MaxSize2) {
  s21::list<double> A;
  std::list<double> B;
  EXPECT_EQ(A.max_size(), B.max_size());
}

TEST(ListCapacity, MaxSize3) {
  s21::list<long double> A;
  std::list<long double> B;
  EXPECT_EQ(A.max_size(), B.max_size());
}

TEST(ListCapacity, MaxSize4) {
  s21::list<std::string> A;
  std::list<std::string> B;
  EXPECT_EQ(A.max_size(), B.max_size());
}

TEST(ListCapacity, Size1) {
  s21::list<long double> A(3);
  EXPECT_EQ(A.size(), 3);
}

TEST(ListCapacity, Size2) {
  s21::list<long double> A = {1, 2, 3};
  std::list<long double> B = {1, 2, 3};
  EXPECT_EQ(A.max_size(), B.max_size());
}

TEST(ListCapacity, Empty1) {
  s21::list<long double> A;
  std::list<long double> B;
  EXPECT_EQ(A.empty(), B.empty());
}

TEST(ListCapacity, Empty2) {
  s21::list<long double> A = {1, 2, 3};
  std::list<long double> B = {1, 2, 3};
  EXPECT_EQ(A.empty(), B.empty());
}

TEST(ListCapacity, Empty3) {
  s21::list<long double> A(2);
  std::list<long double> B(2);
  EXPECT_EQ(A.empty(), B.empty());
}

TEST(ListModifiers, Clear1) {
  s21::list<int> own_list(5);
  std::list<int> orig_list(5);
  EXPECT_EQ(own_list.size(), orig_list.size());

  own_list.clear();
  orig_list.clear();
  EXPECT_EQ(own_list.size(), orig_list.size());
}

TEST(ListModifiers, Clear2) {
  s21::list<int> own_list = {10, 5, 13, 34, 64, 33};
  std::list<int> orig_list = {10, 5, 13, 34, 64, 33};
  EXPECT_EQ(own_list.size(), orig_list.size());

  own_list.clear();
  orig_list.clear();
  EXPECT_EQ(own_list.size(), orig_list.size());
}

TEST(ListModifiers, PushBack1) {
  s21::list<int> A = {10, 20, 30};
  s21::list<int> B;

  B.push_back(10);
  B.push_back(20);
  B.push_back(30);

  EXPECT_TRUE(A == B);
}

TEST(ListModifiers, PushBack2) {
  s21::list<int> A;
  A.push_back(42);

  EXPECT_EQ(A.size(), 1);
  EXPECT_EQ(A.front(), 42);
  EXPECT_EQ(A.back(), 42);
}

TEST(ListModifiers, PushBack3) {
  s21::list<double> A;
  A.push_back(3.14);
  A.push_back(2.71);
  A.push_back(1.618);

  EXPECT_EQ(A.size(), 3);
  EXPECT_EQ(A.front(), 3.14);
  EXPECT_EQ(A.back(), 1.618);
}

TEST(ListModifiers, PushBack4) {
  s21::list<std::string> myList;
  myList.push_back("Hello");
  myList.push_back("World");

  EXPECT_EQ(myList.size(), 2);
  EXPECT_EQ(myList.front(), "Hello");
  EXPECT_EQ(myList.back(), "World");
}

TEST(ListModifiers, PushFront1) {
  s21::list<int> A = {10, 20, 30};
  s21::list<int> B;

  B.push_front(30);
  B.push_front(20);
  B.push_front(10);

  EXPECT_TRUE(A == B);
}

TEST(ListModifiers, PushFront2) {
  s21::list<int> A;
  A.push_front(42);

  EXPECT_EQ(A.size(), 1);
  EXPECT_EQ(A.front(), 42);
  EXPECT_EQ(A.back(), 42);
}

TEST(ListModifiers, PushFront3) {
  s21::list<double> A;
  A.push_front(1.618);
  A.push_front(2.71);
  A.push_front(3.14);

  EXPECT_EQ(A.size(), 3);
  EXPECT_EQ(A.front(), 3.14);
  EXPECT_EQ(A.back(), 1.618);
}

TEST(ListModifiers, PushFront4) {
  s21::list<std::string> myList;
  myList.push_front("World");
  myList.push_front("Hello");

  EXPECT_EQ(myList.size(), 2);
  EXPECT_EQ(myList.front(), "Hello");
  EXPECT_EQ(myList.back(), "World");
}

TEST(ListModifiers, PopBack1) {
  s21::list<int> A = {10, 20, 30};
  s21::list<int> B = {10, 20};

  A.pop_back();

  EXPECT_TRUE(A == B);
}

TEST(ListModifiers, PopBack2) {
  s21::list<int> A;
  A.push_back(42);
  A.pop_back();

  EXPECT_TRUE(A.empty());
  EXPECT_EQ(A.size(), 0);
}

TEST(ListModifiers, PopBack3) {
  s21::list<double> A = {3.14, 2.71, 1.618};
  A.pop_back();

  EXPECT_EQ(A.size(), 2);
  EXPECT_EQ(A.back(), 2.71);
}

TEST(ListModifiers, PopFront1) {
  s21::list<int> A = {10, 20, 30};
  s21::list<int> B = {20, 30};

  A.pop_front();

  EXPECT_TRUE(A == B);
}

TEST(ListModifiers, PopFront2) {
  s21::list<int> A;
  A.push_back(42);
  A.pop_front();

  EXPECT_TRUE(A.empty());
  EXPECT_EQ(A.size(), 0);
}

TEST(ListModifiers, PopFront3) {
  s21::list<double> A = {3.14, 2.71, 1.618};
  A.pop_front();

  EXPECT_EQ(A.size(), 2);
  EXPECT_EQ(A.front(), 2.71);
}

TEST(ListModifiers, InsertInEmptyList) {
  s21::list<int> list;
  s21::list<int> expected = {42};

  auto it = list.begin();
  it = list.insert(it, 42);

  EXPECT_EQ(*it, 42);
  EXPECT_EQ(list.size(), 1);
  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, InsertAtBeginning) {
  s21::list<int> list = {2, 3, 4};
  s21::list<int> expected = {1, 2, 3, 4};
  auto it = list.begin();
  it = list.insert(it, 1);

  EXPECT_EQ(*it, 1);
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list.front(), 1);
  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, InsertInMiddle) {
  s21::list<int> expected = {1, 2, 3, 4};
  s21::list<int> list = {1, 3, 4};
  s21::list<int>::iterator it = ++list.begin();
  it = list.insert(it, 2);

  EXPECT_EQ(*it, 2);
  EXPECT_EQ(list.size(), 4);

  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, InsertAtEnd) {
  s21::list<int> list = {1, 2, 3};
  s21::list<int> expected = {1, 2, 3, 4};
  auto it = list.end();
  it = list.insert(it, 4);

  EXPECT_EQ(*it, 4);
  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list.back(), 4);
  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, EraseInEmptyList) {
  s21::list<int> list;
  s21::list<int> expected;

  auto it = list.begin();
  it = list.erase(it);

  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, EraseAtBeginning) {
  s21::list<int> list = {1, 2, 3, 4};
  s21::list<int> expected = {2, 3, 4};

  auto it = list.begin();
  it = list.erase(it);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 2);
  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, EraseInMiddle) {
  s21::list<int> list = {1, 2, 3, 4};
  s21::list<int> expected = {1, 3, 4};

  auto it = ++list.begin();
  it = list.erase(it);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(*it, 3);
  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, EraseAtEnd) {
  s21::list<int> list = {1, 2, 3, 4};
  s21::list<int> expected = {1, 2, 3};

  auto it = --list.end();
  it = list.erase(it);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.back(), 3);
  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, EraseInvalidIterator) {
  s21::list<int> list = {1, 2, 3};

  auto it = list.end();
  it = list.erase(it);

  EXPECT_EQ(list.size(), 3);
  EXPECT_TRUE(list == s21::list<int>({1, 2, 3}));
  EXPECT_TRUE(it == list.end());
}

TEST(ListModifiers, ReverseEmptyList) {
  s21::list<int> list;
  s21::list<int> expected;

  list.reverse();

  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, ReverseSingleElementList) {
  s21::list<int> list = {42};
  s21::list<int> expected = {42};

  list.reverse();

  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, ReverseMultipleElementList) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int> expected = {5, 4, 3, 2, 1};

  list.reverse();

  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, ReverseStringList) {
  s21::list<std::string> list = {"apple", "banana", "orange"};
  s21::list<std::string> expected = {"orange", "banana", "apple"};

  list.reverse();

  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, ReverseMixedTypeList) {
  s21::list<double> list = {1.1, 2.2, 3.3, 4.4};
  s21::list<double> expected = {4.4, 3.3, 2.2, 1.1};

  list.reverse();

  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, SwapEmptyLists) {
  s21::list<int> list1;
  s21::list<int> list2;

  list1.swap(list2);

  EXPECT_TRUE(list1.empty());
  EXPECT_TRUE(list2.empty());
}

TEST(ListModifiers, SwapNonEmptyLists) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {4, 5, 6};

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 3);
  EXPECT_EQ(list2.size(), 3);

  EXPECT_EQ(list1.front(), 4);
  EXPECT_EQ(list1.back(), 6);

  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 3);
}

TEST(ListModifiers, SwapListWithEmptyList) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2;

  list1.swap(list2);

  EXPECT_TRUE(list1.empty());
  EXPECT_EQ(list2.size(), 3);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 3);
}

TEST(ListModifiers, SwapListWithItself) {
  s21::list<int> list = {1, 2, 3};
  size_t size_before = list.size();

  list.swap(list);

  EXPECT_EQ(list.size(), size_before);
}

TEST(ListModifiers, SwapDoubleLists) {
  s21::list<double> list1 = {1.1, 2.2, 3.3};
  s21::list<double> list2 = {4.4, 5.5, 6.6};

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 3);
  EXPECT_EQ(list2.size(), 3);

  EXPECT_DOUBLE_EQ(list1.front(), 4.4);
  EXPECT_DOUBLE_EQ(list1.back(), 6.6);

  EXPECT_DOUBLE_EQ(list2.front(), 1.1);
  EXPECT_DOUBLE_EQ(list2.back(), 3.3);
}

TEST(ListModifiers, SwapStringLists) {
  s21::list<std::string> list1 = {"one", "two", "three"};
  s21::list<std::string> list2 = {"four", "five", "six"};

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 3);
  EXPECT_EQ(list2.size(), 3);

  EXPECT_EQ(list1.front(), "four");
  EXPECT_EQ(list1.back(), "six");

  EXPECT_EQ(list2.front(), "one");
  EXPECT_EQ(list2.back(), "three");
}

TEST(ListModifiers, SwapListWithEmptyDoubleList) {
  s21::list<double> list1 = {1.1, 2.2, 3.3};
  s21::list<double> list2;

  list1.swap(list2);

  EXPECT_TRUE(list1.empty());
  EXPECT_EQ(list2.size(), 3);
  EXPECT_DOUBLE_EQ(list2.front(), 1.1);
  EXPECT_DOUBLE_EQ(list2.back(), 3.3);
}

TEST(ListModifiers, SwapListWithItselfString) {
  s21::list<std::string> list = {"one", "two", "three"};
  size_t size_before = list.size();

  list.swap(list);

  EXPECT_EQ(list.size(), size_before);
}

TEST(ListModifiers, SwapedListIteratorCompare) {
  s21::list<int> units = {1, 2, 3, 4, 5};
  s21::list<int> thousands = {1000, 2000, 3000, 4000, 5000};

  s21::list<int>::iterator itr_units = units.begin();
  s21::list<int>::iterator itr_thousands = thousands.begin();

  units.swap(thousands);

  s21::list<int>::iterator new_itr_units = units.begin();
  s21::list<int>::iterator new_itr_thousands = thousands.begin();

  for (auto i = units.size(); i > 0; --i) {
    EXPECT_TRUE(itr_units++ == new_itr_thousands++);
    EXPECT_TRUE(itr_thousands++ == new_itr_units++);
  }
}

TEST(ListMergeTest, MergeEmptyLists) {
  s21::list<int> list1;
  s21::list<int> list2;

  list1.merge(list2);

  EXPECT_TRUE(list1.empty());
  EXPECT_TRUE(list2.empty());
}

TEST(ListMergeTest, MergeWithEmptyList) {
  s21::list<int> list1 = {1, 3, 5};
  s21::list<int> list2;

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 3);
  EXPECT_EQ(list2.size(), 0);
  EXPECT_TRUE(std::is_sorted(list1.begin(), list1.end()));
}

TEST(ListMergeTest, MergeEmptyWithNonEmptyList) {
  s21::list<int> list1;
  s21::list<int> list2 = {2, 4, 6};

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 3);
  EXPECT_EQ(list2.size(), 0);
  EXPECT_TRUE(std::is_sorted(list1.begin(), list1.end()));
}

TEST(ListMergeTest, MergeNonEmptyLists) {
  s21::list<int> list1 = {1, 3, 5};
  s21::list<int> list2 = {2, 4, 6};

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 6);
  EXPECT_EQ(list2.size(), 0);
  EXPECT_TRUE(std::is_sorted(list1.begin(), list1.end()));
}

TEST(ListMergeTest, MergeWithEqualValues) {
  s21::list<int> list1 = {1, 3, 5};
  s21::list<int> list2 = {3, 4, 6};

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 6);
  EXPECT_EQ(list2.size(), 0);
  EXPECT_TRUE(std::is_sorted(list1.begin(), list1.end()));
}

TEST(ListMergeTest, MergeSameList) {
  s21::list<int> list1 = {1, 3, 5};

  list1.merge(list1);

  EXPECT_EQ(list1.size(), 3);
  EXPECT_TRUE(std::is_sorted(list1.begin(), list1.end()));
}

TEST(ListMergeTest, MergeEmptyListWithDifferentTypes) {
  s21::list<double> list1;
  s21::list<double> list2 = {2.5, 4.5, 6.5};
  s21::list<double> expected = {2.5, 4.5, 6.5};

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 3);
  EXPECT_EQ(list2.size(), 0);
  EXPECT_TRUE(std::is_sorted(list1.begin(), list1.end()));
  EXPECT_EQ(list1, expected);
}

TEST(ListMergeTest, MergeListsWithDifferentTypes) {
  s21::list<double> list1 = {1, 3, 5};
  s21::list<double> list2 = {2.5, 4.5, 6.5};
  s21::list<double> expected = {1, 2.5, 3, 4.5, 5, 6.5};

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 6);
  EXPECT_EQ(list2.size(), 0);
  EXPECT_TRUE(std::is_sorted(list1.begin(), list1.end()));
  EXPECT_EQ(list1, expected);
}

TEST(ListSpliceTest, SpliceEmptyLists) {
  s21::list<int> list1;
  s21::list<int> list2;

  s21::list<int>::iterator it1 = list1.begin();

  list1.splice(it1, list2);

  EXPECT_TRUE(list1.empty());
  EXPECT_TRUE(list2.empty());
}

TEST(ListSpliceTest, SpliceEmptyListIntoNonEmptyList) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2;
  s21::list<int> expected = {1, 2, 3};

  s21::list<int>::iterator it1 = list1.begin();
  s21::list<int>::iterator it2 = list2.begin();

  list1.splice(it1, list2);

  EXPECT_EQ(list1.size(), 3);
  EXPECT_TRUE(list2.empty());
  EXPECT_EQ(it1, list1.begin());
  EXPECT_EQ(it2, list2.begin());
  EXPECT_TRUE(list1 == expected);
}

TEST(ListSpliceTest, SpliceAtBeginning) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {4, 5, 6};
  s21::list<int> expected = {4, 5, 6, 1, 2, 3};

  auto it1 = list1.begin();

  list1.splice(it1, list2);

  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());
  EXPECT_TRUE(list1 == expected);
}

TEST(ListSpliceTest, SpliceAtEnd) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {4, 5, 6};
  s21::list<int> expected = {1, 2, 3, 4, 5, 6};

  auto it1 = list1.end();

  list1.splice(it1, list2);

  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());
  EXPECT_TRUE(list1 == expected);
}

TEST(ListSpliceTest, SpliceInMiddle) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {4, 5, 6};
  s21::list<int> expected = {1, 4, 5, 6, 2, 3};

  auto it1 = ++list1.begin();

  list1.splice(it1, list2);

  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());
  EXPECT_TRUE(list1 == expected);
}

TEST(ListOperations, UniqueEmptyList) {
  s21::list<int> list;
  list.unique();
  EXPECT_TRUE(list.empty());
}

TEST(ListOperations, UniqueSingleElement) {
  s21::list<int> list = {42};
  list.unique();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.front(), 42);
}

TEST(ListOperations, UniqueNoDuplicates) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int> expected = {1, 2, 3, 4, 5};
  list.unique();
  EXPECT_EQ(list, expected);
}

TEST(ListOperations, UniqueConsecutiveDuplicates) {
  s21::list<int> list = {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 5};
  s21::list<int> expected = {1, 2, 3, 4, 5};
  list.unique();
  EXPECT_EQ(list, expected);
}

TEST(ListOperations, UniqueEmptyListCustomType) {
  s21::list<std::string> list;
  list.unique();
  EXPECT_TRUE(list.empty());
}

TEST(ListOperations, UniqueCustomTypeWithDuplicates) {
  s21::list<std::string> list = {"apple", "apple", "orange", "banana",
                                 "banana"};
  s21::list<std::string> expected = {"apple", "orange", "banana"};
  list.unique();
  EXPECT_EQ(list, expected);
}

TEST(ListOperations, UniqueCustomTypeAllUnique) {
  s21::list<std::string> list = {"apple", "banana", "orange", "grape"};
  s21::list<std::string> expected = {"apple", "banana", "orange", "grape"};
  list.unique();
  EXPECT_EQ(list, expected);
}

TEST(ListOperations, UniqueCustomTypeDuplicatesAtStart) {
  s21::list<std::string> list = {"apple", "apple", "banana", "orange", "grape"};
  s21::list<std::string> expected = {"apple", "banana", "orange", "grape"};
  list.unique();
  EXPECT_EQ(list, expected);
}

TEST(ListSort, EmptyList) {
  s21::list<int> list;
  s21::list<int> expected;
  list.sort();
  EXPECT_EQ(list, expected);
}

TEST(ListSort, AlreadySorted) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int> expected = {1, 2, 3, 4, 5};
  list.sort();
  EXPECT_EQ(list, expected);
}

TEST(ListSort, ReverseSorted) {
  s21::list<int> list = {5, 4, 3, 2, 1};
  s21::list<int> expected = {1, 2, 3, 4, 5};
  list.sort();
  EXPECT_EQ(list, expected);
}

TEST(ListSort, RandomOrder) {
  s21::list<int> list = {3, 5, 2, 4, 1};
  s21::list<int> expected = {1, 2, 3, 4, 5};
  list.sort();
  EXPECT_EQ(list, expected);
}

TEST(ListSort, Duplicates) {
  s21::list<int> list = {3, 5, 2, 3, 4, 1, 2};
  s21::list<int> expected = {1, 2, 2, 3, 3, 4, 5};
  list.sort();
  EXPECT_EQ(list, expected);
}

TEST(ListSort, SingleElement) {
  s21::list<int> list = {1};
  s21::list<int> expected = {1};
  list.sort();
  EXPECT_EQ(list, expected);
}

TEST(ListSort, MultipleTypes) {
  s21::list<char> list = {'d', 'c', 'a', 'b'};
  s21::list<char> expected = {'a', 'b', 'c', 'd'};
  list.sort();
  EXPECT_EQ(list, expected);
}

TEST(ListSort, StringElements) {
  s21::list<std::string> list = {"banana", "apple", "orange", "grape"};
  s21::list<std::string> expected = {"apple", "banana", "grape", "orange"};
  list.sort();
  EXPECT_EQ(list, expected);
}

TEST(ListSort, SortEmptyList) {
  s21::list<int> list;
  s21::list<int> expected;
  list.sort();
  EXPECT_EQ(list, expected);
}

TEST(ListModifiers, InsertManyInEmptyList) {
  s21::list<int> list;
  s21::list<int> expected = {42, 1, 2, 3};

  auto it = list.cbegin();
  list.insert_many(it, 42, 1, 2, 3);

  EXPECT_EQ(list.size(), 4);
  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, InsertManyAtBeginning) {
  s21::list<int> list = {2, 3, 4};
  s21::list<int> expected = {1, 2, 3, 4};
  auto it = list.begin();
  list.insert_many(it, 1);

  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list.front(), 1);
  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, InsertManyFrontAtBeginning) {
  s21::list<int> list = {2, 3, 4};
  s21::list<int> expected = {1, 2, 3, 4};
  list.insert_many_front(1);

  EXPECT_EQ(list.size(), 4);
  EXPECT_EQ(list.front(), 1);
  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, InsertManyInMiddle) {
  s21::list<int> expected = {1, 2, 3, 4};
  s21::list<int> list = {1, 3, 4};
  s21::list<int>::iterator it = ++list.begin();
  list.insert_many(it, 2);

  EXPECT_EQ(list.size(), 4);

  EXPECT_TRUE(list == expected);
}

TEST(ListModifiers, InsertManyBackAtEnd) {
  s21::list<int> list = {1, 2, 3};
  s21::list<int> expected = {1, 2, 3, 4, 5};
  list.insert_many_back(4, 5);

  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(list.back(), 5);
  EXPECT_TRUE(list == expected);
}