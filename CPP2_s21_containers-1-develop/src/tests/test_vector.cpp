#include <gtest/gtest.h>

#include <utility>
#include <vector>

#include "../src/s21_containerplus.h"
#include "../src/s21_containers.h"

using s21::vector;

/* to make sure constructors and destructors work correctly
   and there are no memory leaks */
TEST(TestVector, TestConstructors_1) {
  vector<int> v0;

  vector<int>* v1 = new vector<int>();
  vector<double>* v2 = new vector<double>();
  vector<double>* v3 = new vector<double>(10);
  vector<double>* v4 = new vector<double>({1, 2, 3});
  vector<double>* v5 = new vector<double>(*v4);
  vector<double>* v6 = new vector<double>(std::move(*v2));

  delete v1;
  delete v2;
  delete v3;
  delete v4;
  delete v5;
  delete v6;

  EXPECT_TRUE(1);
}

TEST(TestVector, TestMoveAssignment_2) {
  vector<int>* v1 = new vector<int>({1, 2, 3});
  vector<int>* v2 = new vector<int>({4, 5});
  *v1 = std::move(*v2);
  EXPECT_EQ(2, v1->size());
  EXPECT_EQ(2, v1->capacity());
  EXPECT_EQ(4, (*v1)[0]);
  EXPECT_EQ(5, (*v1)[1]);
  EXPECT_EQ(0, v2->size());
  EXPECT_EQ(0, v2->capacity());
  delete v1;
  delete v2;
}

TEST(TestVector, TestAt_1) {
  vector<int>* v = new vector<int>({1, 2, 3, -5});

  EXPECT_EQ(1, v->at(0));
  EXPECT_EQ(2, v->at(1));
  EXPECT_EQ(3, v->at(2));
  EXPECT_EQ(-5, v->at(3));
  EXPECT_THROW(v->at(-1), std::out_of_range);
  EXPECT_THROW(v->at(4), std::out_of_range);

  delete v;
}

TEST(TestVector, TestAt_2) {
  vector<int>* v = new vector<int>();

  EXPECT_THROW(v->at(0), std::out_of_range);
  EXPECT_THROW(v->at(-1), std::out_of_range);
  EXPECT_THROW(v->at(1), std::out_of_range);

  delete v;
}

TEST(TestVector, TestOperatorGetItem_1) {
  vector<int>* v = new vector<int>({1, 2, 3, -5});

  EXPECT_EQ(1, (*v)[0]);
  EXPECT_EQ(2, (*v)[1]);
  EXPECT_EQ(3, (*v)[2]);
  EXPECT_EQ(-5, (*v)[3]);
  EXPECT_THROW((*v)[-1], std::out_of_range);
  EXPECT_THROW((*v)[4], std::out_of_range);

  delete v;
}

TEST(TestVector, TestOperatorGetItem_2) {
  vector<int>* v = new vector<int>();

  EXPECT_THROW((*v)[0], std::out_of_range);
  EXPECT_THROW((*v)[-1], std::out_of_range);
  EXPECT_THROW((*v)[1], std::out_of_range);

  delete v;
}

TEST(TestVector, TestFront_1) {
  vector<int>* v = new vector<int>();
  EXPECT_THROW(v->front(), std::invalid_argument);
  delete v;
}

TEST(TestVector, TestFront_2) {
  vector<int>* v = new vector<int>(2);
  EXPECT_EQ(0, v->front());
  delete v;
}

TEST(TestVector, TestFront_3) {
  vector<int>* v = new vector<int>({100, 2, 3});
  EXPECT_EQ(100, v->front());
  delete v;
}

TEST(TestVector, TestFront_4) {
  vector<int>* v = new vector<int>({3});
  EXPECT_EQ(3, v->front());
  delete v;
}

TEST(TestVector, TestBack_1) {
  vector<int>* v = new vector<int>();
  EXPECT_THROW(v->back(), std::invalid_argument);
  delete v;
}

TEST(TestVector, TestBack_2) {
  vector<int>* v = new vector<int>(2);
  EXPECT_EQ(0, v->back());
  delete v;
}

TEST(TestVector, TestBack_3) {
  vector<int>* v = new vector<int>({100, 2, 3});
  EXPECT_EQ(3, v->back());
  delete v;
}

TEST(TestVector, TestBack_4) {
  vector<int>* v = new vector<int>({3});
  EXPECT_EQ(3, v->back());
  delete v;
}

TEST(TestVector, TestData_1) {
  vector<int>* v = new vector<int>();
  int* data = v->data();
  EXPECT_TRUE(data == nullptr);
  delete v;
}

TEST(TestVector, TestData_2) {
  vector<int>* v = new vector<int>(1);
  int* data = v->data();
  EXPECT_TRUE(data != nullptr);
  delete v;
}

TEST(TestVector, TestEmpty_1) {
  vector<int>* v = new vector<int>();
  EXPECT_TRUE(v->empty());
  delete v;
}

TEST(TestVector, TestEmpty_2) {
  vector<int>* v = new vector<int>(2);
  EXPECT_FALSE(v->empty());
  delete v;
}

TEST(TestVector, TestEmpty_3) {
  vector<int>* v = new vector<int>({1});
  EXPECT_FALSE(v->empty());
  delete v;
}

TEST(TestVector, TestSize_1) {
  vector<int>* v = new vector<int>();
  EXPECT_EQ(0, v->size());
  delete v;
}

TEST(TestVector, TestSize_2) {
  vector<int>* v = new vector<int>(2);
  EXPECT_EQ(2, v->size());
  delete v;
}

TEST(TestVector, TestSize_3) {
  vector<int>* v = new vector<int>({1, 2, 3, 4});
  EXPECT_EQ(4, v->size());
  delete v;
}

TEST(TestVector, TestMaxSize_1) {
  vector<double> v = vector<double>();
  std::vector<double> orig_v = std::vector<double>();
  EXPECT_EQ(v.max_size(), orig_v.max_size());
}

TEST(TestVector, TestReserve_1) {
  vector<int>* v = new vector<int>();
  v->reserve(10);
  EXPECT_EQ(0, v->size());
  EXPECT_EQ(10, v->capacity());
  delete v;
}

TEST(TestVector, TestReserve_2) {
  vector<int>* v = new vector<int>();
  v->reserve(0);
  EXPECT_EQ(0, v->size());
  EXPECT_EQ(0, v->capacity());
  delete v;
}

TEST(TestVector, TestReserve_3) {
  vector<int>* v = new vector<int>(10);
  v->reserve(0);
  EXPECT_EQ(10, v->size());
  EXPECT_EQ(10, v->capacity());
  delete v;
}

TEST(TestVector, TestReserve_4) {
  vector<int>* v = new vector<int>(10);
  v->reserve(20);
  EXPECT_EQ(10, v->size());
  EXPECT_EQ(20, v->capacity());
  delete v;
}

TEST(TestVector, TestCapacity_1) {
  vector<int>* v = new vector<int>();
  EXPECT_EQ(0, v->capacity());
  delete v;
}

TEST(TestVector, TestCapacity_2) {
  vector<int>* v = new vector<int>(5);
  EXPECT_EQ(5, v->capacity());
  delete v;
}

TEST(TestVector, TestCapacity_3) {
  vector<int>* v = new vector<int>({1, 2, 3, 4});
  EXPECT_EQ(4, v->capacity());
  delete v;
}

TEST(TestVector, TestShrinkToFit_1) {
  vector<int>* v = new vector<int>();
  v->shrink_to_fit();
  EXPECT_EQ(0, v->size());
  EXPECT_EQ(0, v->capacity());
  delete v;
}

TEST(TestVector, TestShrinkToFit_2) {
  vector<int>* v = new vector<int>({1, 2});
  v->reserve(10);
  v->shrink_to_fit();
  EXPECT_EQ(2, v->size());
  EXPECT_EQ(2, v->capacity());
  delete v;
}

TEST(TestVector, TestShrinkToFit_3) {
  vector<int>* v = new vector<int>({1, 2});
  v->shrink_to_fit();
  EXPECT_EQ(2, v->size());
  EXPECT_EQ(2, v->capacity());
  delete v;
}

TEST(TestVector, TestClear_1) {
  vector<int>* v = new vector<int>{};
  v->clear();
  EXPECT_EQ(0, v->size());
  EXPECT_EQ(0, v->capacity());
  delete v;
}

TEST(TestVector, TestClear_2) {
  vector<int>* v = new vector<int>{{1}};
  v->clear();
  EXPECT_EQ(0, v->size());
  EXPECT_EQ(1, v->capacity());
  delete v;
}

TEST(TestVector, TestClear_3) {
  vector<int>* v = new vector<int>{{1, 2, 3}};
  v->clear();
  EXPECT_EQ(0, v->size());
  EXPECT_EQ(3, v->capacity());
  delete v;
}

TEST(TestVector, TestInsert_1) {
  vector<int>* v = new vector<int>{};
  v->insert(v->begin(), 10);
  EXPECT_EQ(1, v->size());
  EXPECT_EQ(1, v->capacity());
  EXPECT_EQ(10, (*v)[0]);
  delete v;
}

TEST(TestVector, TestInsert_2) {
  vector<int>* v = new vector<int>({1, 2, 3});
  v->reserve(10);
  v->insert(v->begin(), 10);
  EXPECT_EQ(4, v->size());
  EXPECT_EQ(10, v->capacity());
  EXPECT_EQ(10, (*v)[0]);
  EXPECT_EQ(1, (*v)[1]);
  EXPECT_EQ(2, (*v)[2]);
  EXPECT_EQ(3, (*v)[3]);
  delete v;
}

TEST(TestVector, TestInsert_3) {
  vector<int>* v = new vector<int>({1, 2, 3});
  v->reserve(10);
  v->insert(v->begin() + 1, 10);
  EXPECT_EQ(4, v->size());
  EXPECT_EQ(10, v->capacity());
  EXPECT_EQ(1, (*v)[0]);
  EXPECT_EQ(10, (*v)[1]);
  EXPECT_EQ(2, (*v)[2]);
  EXPECT_EQ(3, (*v)[3]);
  delete v;
}

TEST(TestVector, TestInsert_5) {
  vector<int>* v = new vector<int>({1, 2, 3});
  v->reserve(10);
  v->insert(v->begin() + 3, 10);
  EXPECT_EQ(4, v->size());
  EXPECT_EQ(10, v->capacity());
  EXPECT_EQ(1, (*v)[0]);
  EXPECT_EQ(2, (*v)[1]);
  EXPECT_EQ(3, (*v)[2]);
  EXPECT_EQ(10, (*v)[3]);
  delete v;
}

TEST(TestVector, TestInsert_6) {
  vector<int>* v = new vector<int>({1, 2, 3});
  v->reserve(10);
  v->insert(v->end(), 10);
  EXPECT_EQ(4, v->size());
  EXPECT_EQ(10, v->capacity());
  EXPECT_EQ(1, (*v)[0]);
  EXPECT_EQ(2, (*v)[1]);
  EXPECT_EQ(3, (*v)[2]);
  EXPECT_EQ(10, (*v)[3]);
  delete v;
}

TEST(TestVector, TestInsert_8) {
  vector<int>* v = new vector<int>;
  v->insert(v->end(), 10);
  EXPECT_EQ(1, v->size());
  EXPECT_EQ(1, v->capacity());
  EXPECT_EQ(10, (*v)[0]);
  delete v;
}

TEST(TestVector, TestInsert_9) {
  vector<int>* v = new vector<int>;
  v->reserve(10);
  v->insert(v->end(), 10);
  EXPECT_EQ(1, v->size());
  EXPECT_EQ(10, v->capacity());
  EXPECT_EQ(10, (*v)[0]);
  delete v;
}

// TEST(TestVector, TestInsertMany) {
//   vector<int>* v = new vector<int>{1, 4, 5};
//   v->insert_many(v->begin() + 1, 2, 3);
//   EXPECT_EQ(5, v->size());

//   int values[] = {1, 2, 3, 4, 5};
//   int i = 0;
//   for (auto item : *v) EXPECT_EQ(item, values[i++]);
//   delete v;
// }

// TEST(TestVector, TestInsertManBack) {
//   vector<int>* v = new vector<int>{1, 2, 3};
//   v->insert_many_back(4, 5);
//   EXPECT_EQ(5, v->size());

//   int values[] = {1, 2, 3, 4, 5};
//   int i = 0;
//   for (auto item : *v) EXPECT_EQ(item, values[i++]);
//   delete v;
// }

TEST(TestVector, TestErase_1) {
  vector<int>* v = new vector<int>({1, 2, 3});
  v->erase(v->begin());
  EXPECT_EQ(2, v->size());
  EXPECT_EQ(3, v->capacity());
  EXPECT_EQ(2, (*v)[0]);
  EXPECT_EQ(3, (*v)[1]);
  delete v;
}

TEST(TestVector, TestErase_2) {
  vector<int>* v = new vector<int>({1, 2, 3});
  v->erase(v->begin() + 1);
  EXPECT_EQ(2, v->size());
  EXPECT_EQ(3, v->capacity());
  EXPECT_EQ(1, (*v)[0]);
  EXPECT_EQ(3, (*v)[1]);
  delete v;
}

TEST(TestVector, TestErase_3) {
  vector<int>* v = new vector<int>({1, 2, 3});
  v->erase(v->begin() + 2);
  EXPECT_EQ(2, v->size());
  EXPECT_EQ(3, v->capacity());
  EXPECT_EQ(1, (*v)[0]);
  EXPECT_EQ(2, (*v)[1]);
  delete v;
}

TEST(TestVector, TestErase_4) {
  vector<int>* v = new vector<int>({1});
  v->erase(v->begin());
  EXPECT_EQ(0, v->size());
  EXPECT_EQ(1, v->capacity());
  EXPECT_THROW((*v)[0], std::out_of_range);
  delete v;
}

TEST(TestVector, TestPushBack_1) {
  vector<int>* v = new vector<int>();
  v->push_back(1);
  EXPECT_EQ(1, v->size());
  EXPECT_EQ(1, v->capacity());
  EXPECT_EQ(1, (*v)[0]);
  delete v;
}

TEST(TestVector, TestPushBack_2) {
  vector<int>* v = new vector<int>();
  v->reserve(10);
  v->push_back(1);
  EXPECT_EQ(1, v->size());
  EXPECT_EQ(10, v->capacity());
  EXPECT_EQ(1, (*v)[0]);
  delete v;
}

TEST(TestVector, TestPushBack_3) {
  vector<int>* v = new vector<int>();
  int value = 1;
  v->push_back(value);
  EXPECT_EQ(1, v->size());
  EXPECT_EQ(1, v->capacity());
  EXPECT_EQ(value, (*v)[0]);
  delete v;
}

TEST(TestVector, TestPushBack_4) {
  vector<int>* v = new vector<int>();
  v->reserve(10);
  int value = 1;
  v->push_back(value);
  EXPECT_EQ(1, v->size());
  EXPECT_EQ(10, v->capacity());
  EXPECT_EQ(value, (*v)[0]);
  delete v;
}

TEST(TestVector, TestPushBack_6) {
  vector<int>* v = new vector<int>({1, 2});
  int value = 3;
  v->reserve(10);
  v->push_back(value);
  EXPECT_EQ(3, v->size());
  EXPECT_EQ(10, v->capacity());
  EXPECT_EQ(1, (*v)[0]);
  EXPECT_EQ(2, (*v)[1]);
  EXPECT_EQ(3, (*v)[2]);
  delete v;
}

TEST(TestVector, TestPopBack_1) {
  vector<int>* v = new vector<int>({1});
  v->pop_back();
  EXPECT_EQ(0, v->size());
  EXPECT_EQ(1, v->capacity());
  delete v;
}

TEST(TestVector, TestPopBack_2) {
  vector<int>* v = new vector<int>({1, 2});
  v->pop_back();
  EXPECT_EQ(1, v->size());
  EXPECT_EQ(2, v->capacity());
  EXPECT_EQ(1, (*v)[0]);
  delete v;
}

TEST(TestVector, TestSwap_1) {
  vector<int>* v1 = new vector<int>({1, 2});
  vector<int>* v2 = new vector<int>({3, 5, 5});
  v1->swap((*v2));
  EXPECT_EQ(3, v1->size());
  EXPECT_EQ(3, v1->capacity());
  EXPECT_EQ(3, (*v1)[0]);
  EXPECT_EQ(5, (*v1)[1]);
  EXPECT_EQ(5, (*v1)[2]);
  EXPECT_EQ(2, v2->size());
  EXPECT_EQ(2, v2->capacity());
  EXPECT_EQ(1, (*v2)[0]);
  EXPECT_EQ(2, (*v2)[1]);
  delete v1;
  delete v2;
}
