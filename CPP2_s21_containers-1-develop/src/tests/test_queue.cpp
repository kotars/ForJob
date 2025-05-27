#include <gtest/gtest.h>

#include "../src/s21_containerplus.h"
#include "../src/s21_containers.h"

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> myQueue;
  ASSERT_TRUE(myQueue.empty());
  ASSERT_EQ(myQueue.size(), 0);
}

// Test the constructor with initializer list
TEST(QueueTest, ConstructorWithInitializerList) {
  s21::queue<int> myQueue({1, 2, 3});
  ASSERT_FALSE(myQueue.empty());
  ASSERT_EQ(myQueue.size(), 3);
  ASSERT_EQ(myQueue.front(), 1);
  ASSERT_EQ(myQueue.back(), 3);
}

// Test copy constructor
TEST(QueueTest, CopyConstructor) {
  s21::queue<int> original({1, 2, 3});
  s21::queue<int> copied(original);
  ASSERT_EQ(original.size(), copied.size());
  ASSERT_EQ(original.front(), copied.front());
  ASSERT_EQ(original.back(), copied.back());
}

// Test move constructor
TEST(QueueTest, MoveConstructor) {
  s21::queue<int> original({1, 2, 3});
  s21::queue<int> moved(std::move(original));
  ASSERT_EQ(original.size(), 0);
  ASSERT_EQ(moved.size(), 3);
  ASSERT_EQ(moved.front(), 1);
  ASSERT_EQ(moved.back(), 3);
}

// Test move assignment operator
TEST(QueueTest, MoveAssignment) {
  s21::queue<int> original({1, 2, 3});
  s21::queue<int> moved;
  moved = std::move(original);
  ASSERT_EQ(original.size(), 0);
  ASSERT_EQ(moved.size(), 3);
  ASSERT_EQ(moved.front(), 1);
  ASSERT_EQ(moved.back(), 3);
}

// Test push and pop
TEST(QueueTest, PushAndPop) {
  s21::queue<int> myQueue;
  myQueue.push(1);
  myQueue.push(2);
  myQueue.push(3);
  ASSERT_EQ(myQueue.size(), 3);
  ASSERT_EQ(myQueue.front(), 1);
  ASSERT_EQ(myQueue.back(), 3);
  myQueue.pop();
  ASSERT_EQ(myQueue.size(), 2);
  ASSERT_EQ(myQueue.front(), 2);
}

// Test swap
TEST(QueueTest, Swap) {
  s21::queue<int> queue1({1, 2, 3});
  s21::queue<int> queue2({4, 5});
  queue1.swap(queue2);
  ASSERT_EQ(queue1.size(), 2);
  ASSERT_EQ(queue1.front(), 4);
  ASSERT_EQ(queue1.back(), 5);
  ASSERT_EQ(queue2.size(), 3);
  ASSERT_EQ(queue2.front(), 1);
  ASSERT_EQ(queue2.back(), 3);
}

// Test front and back functions
TEST(QueueTest, FrontAndBack) {
  s21::queue<int> myQueue({1, 2, 3});
  const s21::queue<int> constQueue({4, 5});
  ASSERT_EQ(myQueue.front(), 1);
  ASSERT_EQ(myQueue.back(), 3);
}

// Test empty function
TEST(QueueTest, Empty) {
  s21::queue<int> myQueue;
  ASSERT_TRUE(myQueue.empty());
  myQueue.push(1);
  ASSERT_FALSE(myQueue.empty());
  myQueue.pop();
  ASSERT_TRUE(myQueue.empty());
}

// Test size function
TEST(QueueTest, Size) {
  s21::queue<int> myQueue;
  ASSERT_EQ(myQueue.size(), 0);
  myQueue.push(1);
  myQueue.push(2);
  myQueue.push(3);
  ASSERT_EQ(myQueue.size(), 3);
  myQueue.pop();
  ASSERT_EQ(myQueue.size(), 2);
}

// Test move semantics with rvalue references
TEST(QueueTest, MoveSemantics) {
  s21::queue<std::string> original({"Hello", "World"});
  s21::queue<std::string> moved(std::move(original));
  ASSERT_EQ(original.size(), 0);
  ASSERT_EQ(moved.size(), 2);
  ASSERT_EQ(moved.front(), "Hello");
  ASSERT_EQ(moved.back(), "World");
}

// Test swapping empty queues
TEST(QueueTest, SwapEmptyQueues) {
  s21::queue<int> queue1;
  s21::queue<int> queue2;
  queue1.swap(queue2);
  ASSERT_TRUE(queue1.empty());
  ASSERT_TRUE(queue2.empty());
}

// Test swapping with one empty queue
TEST(QueueTest, SwapWithOneEmptyQueue) {
  s21::queue<int> queue1;
  s21::queue<int> queue2({1, 2, 3});
  queue1.swap(queue2);
  ASSERT_EQ(queue1.size(), 3);
  ASSERT_EQ(queue1.front(), 1);
  ASSERT_EQ(queue1.back(), 3);
  ASSERT_TRUE(queue2.empty());
}

// Test pushing and popping large number of elements
TEST(QueueTest, PushAndPopManyElements) {
  s21::queue<int> myQueue;
  for (int i = 1; i <= 1000; ++i) {
    myQueue.push(i);
  }
  ASSERT_EQ(myQueue.size(), 1000);
  for (int i = 1; i <= 500; ++i) {
    myQueue.pop();
  }
  ASSERT_EQ(myQueue.size(), 500);
  ASSERT_EQ(myQueue.front(), 501);
  ASSERT_EQ(myQueue.back(), 1000);
}

// Test swapping large queues
TEST(QueueTest, SwapLargeQueues) {
  s21::queue<int> queue1;
  s21::queue<int> queue2;
  for (int i = 1; i <= 1000; ++i) {
    queue1.push(i);
  }
  for (int i = 1001; i <= 2000; ++i) {
    queue2.push(i);
  }
  queue1.swap(queue2);
  ASSERT_EQ(queue1.size(), 1000);
  ASSERT_EQ(queue1.front(), 1001);
  ASSERT_EQ(queue1.back(), 2000);
  ASSERT_EQ(queue2.size(), 1000);
  ASSERT_EQ(queue2.front(), 1);
  ASSERT_EQ(queue2.back(), 1000);
}

// Test copying large queues
TEST(QueueTest, CopyLargeQueues) {
  s21::queue<int> original;
  for (int i = 1; i <= 1000; ++i) {
    original.push(i);
  }
  s21::queue<int> copied(original);
  ASSERT_EQ(original.size(), 1000);
  ASSERT_EQ(copied.size(), 1000);
  ASSERT_EQ(original.front(), 1);
  ASSERT_EQ(copied.front(), 1);
  ASSERT_EQ(original.back(), 1000);
  ASSERT_EQ(copied.back(), 1000);
}

// Test moving large queues
TEST(QueueTest, MoveLargeQueues) {
  s21::queue<int> original;
  for (int i = 1; i <= 1000; ++i) {
    original.push(i);
  }
  s21::queue<int> moved(std::move(original));
  ASSERT_EQ(original.size(), 0);
  ASSERT_EQ(moved.size(), 1000);
  ASSERT_EQ(original.empty(), true);
  ASSERT_EQ(moved.front(), 1);
  ASSERT_EQ(moved.back(), 1000);
}

// Test pushing and popping elements of custom class
class CustomClass {
 public:
  CustomClass(int val) : value(val) {}
  int getValue() const { return value; }

 private:
  int value;
};

// Test copying queues with custom container
TEST(QueueTest, CopyWithCustomContainer) {
  s21::queue<int, s21::list<int>> original({1, 2, 3});
  s21::queue<int, s21::list<int>> copied(original);
  ASSERT_EQ(original.size(), copied.size());
  ASSERT_EQ(original.front(), copied.front());
  ASSERT_EQ(original.back(), copied.back());
}

// Test moving queues with custom container
TEST(QueueTest, MoveWithCustomContainer) {
  s21::queue<int, s21::list<int>> original({1, 2, 3});
  s21::queue<int, s21::list<int>> moved(std::move(original));
  ASSERT_EQ(original.size(), 0);
  ASSERT_EQ(moved.size(), 3);
  ASSERT_EQ(moved.front(), 1);
  ASSERT_EQ(moved.back(), 3);
}

// Test swapping queues with custom container
TEST(QueueTest, SwapWithCustomContainer) {
  s21::queue<int, s21::list<int>> queue1({1, 2, 3});
  s21::queue<int, s21::list<int>> queue2({4, 5});
  queue1.swap(queue2);
  ASSERT_EQ(queue1.size(), 2);
  ASSERT_EQ(queue1.front(), 4);
  ASSERT_EQ(queue1.back(), 5);
  ASSERT_EQ(queue2.size(), 3);
  ASSERT_EQ(queue2.front(), 1);
  ASSERT_EQ(queue2.back(), 3);
}
