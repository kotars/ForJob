#include <gtest/gtest.h>

#include <list>

#include "../src/s21_containerplus.h"
#include "../src/s21_containers.h"
using s21::list;

TEST(ListTest, DefaultConstructor) {
  list<int> my_list;
  EXPECT_TRUE(my_list.empty());
  EXPECT_EQ(my_list.size(), 0);
}

TEST(ListTest, DefaultConstructor1) {
  list<int> my_list;
  std::list<int> std_list;

  EXPECT_EQ(my_list.size(), std_list.size());
  EXPECT_TRUE(my_list.empty());
  EXPECT_TRUE(std_list.empty());
}

TEST(ListTest, Constructor_Default3) {
  list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(ListTest, ParameterizedConstructor) {
  list<int> my_list(5);
  EXPECT_EQ(my_list.size(), 5);
  EXPECT_FALSE(my_list.empty());
}

TEST(ListTest, PushBack) {
  list<int> my_list;
  my_list.push_back(10);
  EXPECT_EQ(my_list.size(), 1);
  EXPECT_FALSE(my_list.empty());
}

TEST(ListTest, PopBack) {
  list<int> my_list;
  my_list.push_back(10);
  my_list.pop_back();
  EXPECT_TRUE(my_list.empty());
  EXPECT_EQ(my_list.size(), 0);
}

TEST(ListTest, PopBack1) {
  list<int> my_list;
  std::list<int> std_list;

  my_list.push_back(10);
  std_list.push_back(10);

  my_list.pop_back();
  std_list.pop_back();

  EXPECT_EQ(my_list.size(), std_list.size());
  EXPECT_TRUE(my_list.empty());
  EXPECT_TRUE(std_list.empty());
}

TEST(ListTest, Clear) {
  list<int> my_list;
  my_list.push_back(10);
  my_list.push_back(20);
  my_list.clear();
  EXPECT_TRUE(my_list.empty());
  EXPECT_EQ(my_list.size(), 0);
}

TEST(ListTest, Constructor_Size) {
  list<int> s21_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, Constructor_InitializerList) {
  list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, CopyConstructor) {
  list<int> original_list;
  original_list.push_back(1);
  original_list.push_back(2);
  original_list.push_back(3);

  list<int> copied_list(original_list);

  ASSERT_EQ(original_list.size(), copied_list.size());

  auto orig_it = original_list.begin();
  auto copy_it = copied_list.begin();
  while (orig_it != original_list.end()) {
    ASSERT_EQ(*orig_it, *copy_it);
    ++orig_it;
    ++copy_it;
  }
}

TEST(ListTest, MoveConstructor) {
  list<int> original_list;
  original_list.push_back(1);
  original_list.push_back(2);
  original_list.push_back(3);

  list<int> moved_list(std::move(original_list));

  ASSERT_EQ(moved_list.size(), 3);
  auto it = moved_list.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);

  ASSERT_TRUE(original_list.empty());
}

TEST(ListTest, MoveConstructorWithStdList) {
  std::list<int> std_original_list = {1, 2, 3};
  std::list<int> std_moved_list(std::move(std_original_list));
  list<int> s21_original_list;
  s21_original_list.push_back(1);
  s21_original_list.push_back(2);
  s21_original_list.push_back(3);
  list<int> s21_moved_list(std::move(s21_original_list));

  ASSERT_EQ(std_moved_list.size(), 3);
  auto std_it = std_moved_list.begin();
  ASSERT_EQ(*std_it, 1);
  ++std_it;
  ASSERT_EQ(*std_it, 2);
  ++std_it;
  ASSERT_EQ(*std_it, 3);

  ASSERT_TRUE(std_original_list.empty());

  ASSERT_EQ(s21_moved_list.size(), 3);
  auto s21_it = s21_moved_list.begin();
  ASSERT_EQ(*s21_it, 1);
  ++s21_it;
  ASSERT_EQ(*s21_it, 2);
  ++s21_it;
  ASSERT_EQ(*s21_it, 3);

  ASSERT_TRUE(s21_original_list.empty());
}

TEST(ListTest, DestructorTest) {
  list<int>* test_list = new list<int>();
  test_list->push_back(1);
  test_list->push_back(2);
  test_list->push_back(3);

  ASSERT_EQ(test_list->size(), 3);
  delete test_list;
  SUCCEED();
}

TEST(ListTest, TestIDS) {
  list<int> s21_list_int;
  list<double> s21_list_double;
  list<std::string> s21_list_string;

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(ListTest, TestIDS_front) {
  list<int> s21_list_int{1, 4, 8, 9};
  list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_list_int.size(), 4U);
  EXPECT_EQ(s21_list_int.front(), 1);

  EXPECT_EQ(s21_list_double.size(), 4U);
  EXPECT_EQ(s21_list_double.front(), 1.4);

  EXPECT_EQ(s21_list_string.size(), 4U);
  EXPECT_EQ(s21_list_string.front(), "Hello");
}

TEST(ListTest, TestIDS_front1) {
  list<int> s21_list_ref_int{1, 4, 8, 9};
  list<int> s21_list_res_int(s21_list_ref_int);

  list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  list<double> s21_list_res_double(s21_list_ref_double);

  list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  list<std::string> s21_list_res_string(s21_list_ref_string);

  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(ListTest, IteratorBeginEnd) {
  s21::list<int> test_list;
  test_list.push_back(1);
  test_list.push_back(2);
  test_list.push_back(3);

  auto it = test_list.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;

  ASSERT_EQ(it, test_list.end());
}

TEST(ListTest, Increment) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  auto it = lst.cbegin();

  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(ListTest, IteratorEnd) {
  s21::list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  auto it = myList.end();
  --it;
  EXPECT_EQ(*it, 3);
}

TEST(ListTest, IteratorDecrementTest) {
  s21::list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  auto it = myList.end();
  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
  --it;
  EXPECT_EQ(it, myList.end());
}

TEST(ListTest, PushBackTest) {
  s21::list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 3);
  EXPECT_EQ(myList.size(), 3);
}

TEST(ListTest, PopBackTest) {
  s21::list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  myList.pop_back();
  EXPECT_EQ(myList.back(), 2);
  EXPECT_EQ(myList.size(), 2);
}

TEST(ListTest, PushFrontTest) {
  s21::list<int> myList;
  myList.push_front(3);
  myList.push_front(2);
  myList.push_front(1);

  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 3);
  EXPECT_EQ(myList.size(), 3);
}

TEST(ListTest, PopFrontTest) {
  s21::list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  myList.pop_front();
  EXPECT_EQ(myList.front(), 2);
  EXPECT_EQ(myList.size(), 2);
}

// TEST(ListTest, MaxSize) {
//   s21::list<size_t> my_list_empty;
//   std::list<size_t> std_list_empty;
//   EXPECT_EQ(my_list_empty.max_size(), std_list_empty.max_size());
// }

TEST(ListTest, IteratorTest) {
  s21::list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  auto it = myList.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, myList.end());
}

TEST(ListTest, ConstIteratorTest) {
  s21::list<int> test_list;
  test_list.push_back(100);
  test_list.push_back(200);
  test_list.push_back(300);

  s21::list<int>::const_iterator cit = test_list.cbegin();
  ASSERT_EQ(*cit, 100);
  ++cit;
  ASSERT_EQ(*cit, 200);
  ++cit;
  ASSERT_EQ(*cit, 300);
  ++cit;

  ASSERT_EQ(cit, test_list.cend());
}

TEST(ListTest, IteratorWrite) {
  s21::list<int> test_list;
  test_list.push_back(5);
  test_list.push_back(10);
  test_list.push_back(15);

  auto it = test_list.begin();
  *it = 50;
  ++it;
  *it = 100;
  ++it;
  *it = 150;

  it = test_list.begin();
  ASSERT_EQ(*it, 50);
  ++it;
  ASSERT_EQ(*it, 100);
  ++it;
  ASSERT_EQ(*it, 150);
}

TEST(ListTest, IteratorEqualityOperator) {
  s21::list<int> test_list;
  test_list.push_back(1);
  test_list.push_back(2);
  test_list.push_back(3);

  auto it1 = test_list.begin();
  auto it2 = test_list.begin();

  ASSERT_EQ(it1, it2);
  ++it2;
  ASSERT_NE(it1, it2);
  ++it1;

  ASSERT_EQ(it1, it2);
}

TEST(ListTest, IteratorInequalityOperator) {
  s21::list<int> test_list;
  test_list.push_back(100);
  test_list.push_back(200);
  test_list.push_back(300);

  auto it_begin = test_list.begin();
  auto it_end = test_list.end();

  ASSERT_NE(it_begin, it_end);

  ++it_begin;
  ++it_begin;
  ++it_begin;

  ASSERT_EQ(it_begin, it_end);
}

TEST(ListTest, Swap) {
  s21::list<int> list1{1, 2, 3};
  s21::list<int> list2{4, 5, 6, 7};

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 4UL);
  EXPECT_EQ(list2.size(), 3UL);
}

TEST(List, Merge_SortedLists) {
  s21::list<int> list1 = {1, 3, 5};
  s21::list<int> list2 = {2, 4, 6};

  list1.merge(list2);

  std::list<int> expected = {1, 2, 3, 4, 5, 6};
  auto it = list1.begin();

  for (const auto& exp : expected) {
    EXPECT_EQ(exp, *it);
    ++it;
  }
}

TEST(ListTest, MergeTest) {
  s21::list<int> list1;
  s21::list<int> list2;

  list1.push_back(1);
  list1.push_back(3);
  list1.push_back(5);

  list2.push_back(2);
  list2.push_back(4);
  list2.push_back(6);

  list1.merge(list2);

  auto it = list1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}

TEST(ListTest, SortTest) {
  s21::list<int> myList;

  myList.push_back(5);
  myList.push_back(3);
  myList.push_back(8);
  myList.push_back(1);
  myList.push_back(4);

  myList.sort();
  auto it = myList.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 8);
}

// TEST(ListTest, Splice_IntoEmpty) {
//   s21::list<int> s21_list;
//   s21::list<int> other = {1, 2, 3};
//   std::list<int> std_list;
//   std::list<int> std_other = {1, 2, 3};

//   s21_list.splice(s21_list.cbegin(), other);
//   std_list.splice(std_list.begin(), std_other);

//   EXPECT_EQ(s21_list.size(), std_list.size());
// }

TEST(ListTest, Splice_AtBeginning) {
  s21::list<int> s21_list = {4, 5, 6};
  s21::list<int> other = {1, 2, 3};
  std::list<int> std_list = {4, 5, 6};
  std::list<int> std_other = {1, 2, 3};

  s21_list.splice(s21_list.cbegin(), other);
  std_list.splice(std_list.begin(), std_other);

  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, Splice_AtEnd) {
  s21::list<int> s21_list = {1, 2, 3};
  s21::list<int> other = {4, 5, 6};
  std::list<int> std_list = {1, 2, 3};
  std::list<int> std_other = {4, 5, 6};

  s21_list.splice(s21_list.cend(), other);
  std_list.splice(std_list.end(), std_other);

  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, Insert_Begin) {
  s21::list<int> s21_list = {2, 3, 4};
  std::list<int> std_list = {2, 3, 4};

  s21_list.insert(s21_list.begin(), 1);
  std_list.insert(std_list.begin(), 1);

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.front(), std_list.front());
}

TEST(ListTest, Insert_Middle) {
  s21::list<int> s21_list = {1, 3, 4};
  std::list<int> std_list = {1, 3, 4};

  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  ++s21_it;
  ++std_it;

  s21_list.insert(s21_it, 2);
  std_list.insert(std_it, 2);

  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, Insert_End) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  s21_list.insert(s21_list.end(), 4);
  std_list.insert(std_list.end(), 4);

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.back(), std_list.back());
}

TEST(ListTest, Insert_EmptyList) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  s21_list.insert(s21_list.begin(), 1);
  std_list.insert(std_list.begin(), 1);

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
}

TEST(ListTest, Erase_Begin) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  s21_list.erase(s21_list.begin());
  std_list.erase(std_list.begin());

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.front(), std_list.front());
}

TEST(ListTest, Erase_Middle) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  auto s21_it = ++s21_list.begin();
  auto std_it = ++std_list.begin();

  s21_list.erase(s21_it);
  std_list.erase(std_it);

  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, Erase_SingleElement) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  s21_list.erase(s21_list.begin());
  std_list.erase(std_list.begin());
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, Constructor_Default) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(ListTest, FrontBack) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
}

TEST(ListTest, Iterators) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();

  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(ListTest, Exceptions) {
  s21::list<int> s21_list;
  EXPECT_THROW(s21_list.front(), std::out_of_range);
  EXPECT_THROW(s21_list.back(), std::out_of_range);
}

TEST(ListTest, LargeSize) {
  const int N = 100000;
  s21::list<int> s21_list(N);
  EXPECT_EQ(static_cast<int>(s21_list.size()), N);
}

TEST(ListTest, PopBack_NonEmpty) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  s21_list.pop_back();
  std_list.pop_back();

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.back(), std_list.back());
}

TEST(ListTest, PopBack_SingleElement) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};

  s21_list.pop_back();
  std_list.pop_back();

  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, PushFront_EmptyList) {
  s21::list<int> s21_list;
  s21_list.push_front(1);
  EXPECT_EQ(s21_list.front(), 1);
  EXPECT_EQ(s21_list.back(), 1);
}

TEST(ListTest, PushFront_NonEmptyList) {
  s21::list<int> s21_list = {2, 3};
  s21_list.push_front(1);
  EXPECT_EQ(s21_list.front(), 1);
}

TEST(ListTest, Merge_EmptyList) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2;

  list1.merge(list2);

  std::list<int> expected = {1, 2, 3};
  auto it = list1.begin();

  for (const auto& exp : expected) {
    EXPECT_EQ(exp, *it);
    ++it;
  }
}

TEST(ListTest, Merge_IntoEmptyList) {
  s21::list<int> list1;
  s21::list<int> list2 = {1, 2, 3};

  list1.merge(list2);

  std::list<int> expected = {1, 2, 3};
  auto it = list1.begin();

  for (const auto& exp : expected) {
    EXPECT_EQ(exp, *it);
    ++it;
  }
}

TEST(ListTest, Merge_IdenticalLists) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {1, 2, 3};

  list1.merge(list2);

  std::list<int> expected = {1, 1, 2, 2, 3, 3};
  auto it = list1.begin();

  for (const auto& exp : expected) {
    EXPECT_EQ(exp, *it);
    ++it;
  }
}

TEST(ListTest, Reverse_NonEmptyList) {
  s21::list<int> list1 = {1, 2, 3};
  list1.reverse();

  std::list<int> expected = {3, 2, 1};
  auto it = list1.begin();

  for (const auto& exp : expected) {
    EXPECT_EQ(exp, *it);
    ++it;
  }
}

TEST(ListTest, Reverse_EmptyList) {
  s21::list<int> list1;
  list1.reverse();

  EXPECT_TRUE(list1.empty());
}

TEST(ListTest, Reverse_SingleElement) {
  s21::list<int> list1 = {1};
  list1.reverse();

  EXPECT_EQ(1, list1.front());
}

TEST(ListTest, Unique_EmptyList) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  s21_list.unique();
  std_list.unique();

  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, Unique_SingleElement) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};

  s21_list.unique();
  std_list.unique();

  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, Unique_MultipleElements) {
  s21::list<int> s21_list = {1, 1, 2, 2, 2, 3, 4, 4, 5};
  std::list<int> std_list = {1, 1, 2, 2, 2, 3, 4, 4, 5};

  s21_list.unique();
  std_list.unique();

  EXPECT_EQ(s21_list.size(), std_list.size());

  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  while (s21_it != ++s21_list.end() && std_it != std_list.end()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
}

TEST(ListTest, Front_OnEmptyList) {
  s21::list<int> lst;

  EXPECT_THROW(lst.front(), std::out_of_range);
}

TEST(ListTest, Back_OnEmptyList) {
  s21::list<int> lst;

  EXPECT_THROW(lst.back(), std::out_of_range);
}

TEST(ListTest, Front_OnNonEmptyList) {
  s21::list<int> lst{1, 2, 3, 4, 5};

  EXPECT_EQ(lst.front(), 1);
}

TEST(ListTest, Back_OnNonEmptyList) {
  s21::list<int> lst{1, 2, 3, 4, 5};

  EXPECT_EQ(lst.back(), 5);
}

TEST(ListTest, Dereference_ValidIterator) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  auto it = lst.cbegin();

  EXPECT_EQ(*it, 1);
}

TEST(ListTest, Decrement) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  auto it = lst.cend();
  --it;
  EXPECT_EQ(*it, 5);
}

TEST(ListTest, Equality) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  auto it1 = lst.cbegin();
  auto it2 = lst.cbegin();

  EXPECT_TRUE(it1 == it2);
}

TEST(ListTest, Inequality) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  auto it1 = lst.cbegin();
  auto it2 = ++lst.cbegin();

  EXPECT_TRUE(it1 != it2);
}

TEST(ListTest, Front_ValidList) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  EXPECT_EQ(lst.front(), 1);
}

TEST(ListTest, Front_EmptyList) {
  s21::list<int> lst;

  EXPECT_THROW(lst.front(), std::out_of_range);
}

TEST(ListTest, Merge) {
  s21::list<int> list1{1, 3, 5};
  s21::list<int> list2{2, 4, 6};

  s21::list<int> mainList;
  mainList.merge(list1);
  mainList.merge(list2);

  EXPECT_EQ(mainList.size(), 6UL);

  auto it = mainList.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(ListTest, MoveAssignmentWithNonEmptyList) {
  s21::list<int> list1;
  s21::list<int> list2;

  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  list2 = std::move(list1);

  EXPECT_EQ(list2.size(), 3UL);
  EXPECT_EQ(list1.size(), 0UL);
}

TEST(ListTest, IteratorBegin) {
  s21::list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  auto it = myList.begin();
  EXPECT_EQ(*it, 1);
}

TEST(LIST_EMPLACE_BACK, case1) {
  s21::list<int> our = {1, 2, 7, 8, 9};
  our.insert_many_back(4, 5, 6);
  EXPECT_EQ(our.back(), 6);
}

TEST(LIST_EMPLACE_BACK, case2) {
  s21::list<int> our;
  our.insert_many_back(4, 5, 6);
  EXPECT_EQ(our.back(), 6);
  EXPECT_EQ(our.front(), 4);
}

TEST(LIST_EMPLACE_FRONT, case1) {
  s21::list<int> our{1, 2, 7, 8, 9};
  our.insert_many_front(4, 5, 6);
  EXPECT_EQ(our.front(), 6);
}

TEST(LIST_EMPLACE_FRONT, case2) {
  s21::list<int> our;
  our.insert_many_front(4, 5, 6);
  EXPECT_EQ(our.front(), 6);
  EXPECT_EQ(our.back(), 4);
}

TEST(s21_bonus, emplace) {
  s21::list<int> s21list{6, 7, 9};
  s21list.insert_many(++(++s21list.cbegin()), 1, 2, 8);  // Вставка перед 9

  EXPECT_EQ(s21list.front(), 6);
  EXPECT_EQ(s21list.back(), 9);
  auto it = ++(++s21list.begin());
  EXPECT_EQ(*it, 1);  // Проверка, что элементы вставлены в нужное место
}

TEST(s21_bonus, emplace_front) {
  s21::list<int> s21list{6, 7, 9};
  s21list.insert_many_front(1, 2, 8);

  EXPECT_EQ(s21list.front(), 8);
  EXPECT_EQ(s21list.back(), 9);
}

TEST(s21_bonus, emplace_back) {
  s21::list<int> s21list{6, 7, 9};
  s21list.insert_many_back(1, 2, 8);

  EXPECT_EQ(s21list.front(), 6);
  EXPECT_EQ(s21list.back(), 8);
}
