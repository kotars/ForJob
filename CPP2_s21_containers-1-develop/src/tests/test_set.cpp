#include <gtest/gtest.h>

#include <set>

#include "../src/s21_containerplus.h"
#include "../src/s21_containers.h"

TEST(setTest, InitiConstructor) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}
TEST(setTest, DefaultConstructor) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

// TEST(SET, InsertMany) {
//   s21::set<int> s2 = {1, 2, 3, 0};

//   s2.insert_many(4, 5);
//   EXPECT_EQ(s2.size(), 6);
//   EXPECT_TRUE(s2.contains(4));
// }
TEST(setTest, CopyConstructor) {
  s21::set<int> s1 = {1, 2, 3, 16, 5, -14, 48, 92, 104};
  s21::set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(setTest, MoveConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}
TEST(setTest, Find) {
  s21::set<int> s{1, 2, 3};
  auto it1 = s.find(2);
  EXPECT_EQ(*it1, 2);
}
// TEST(setTest, Merge) {
//   s21::set<int> s1{1, 2, 3};
//   s21::set<int> s2{3, 4, 5};
//   s1.merge(s2);
//   EXPECT_EQ(s1.size(), 5);
//   EXPECT_EQ(s2.size(), 0);
//   EXPECT_TRUE(s1.contains(4));
//   EXPECT_FALSE(s2.contains(3));
// }
TEST(setTest, Swap) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s1.contains(4));
}

TEST(setTest, Erase) {
  s21::set<int> s{1, 2, 3, 4, 5};
  s.erase(s.find(2));
  EXPECT_EQ(s.size(), 4);
  EXPECT_FALSE(s.contains(2));
}
TEST(S21_set, Constructor) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());
}
