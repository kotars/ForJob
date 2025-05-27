#include <gtest/gtest.h>

#include <array>

#include "../src/s21_containerplus.h"
#include "../src/s21_containers.h"

TEST(array_member_functions, 1) {
  std::array<int, 3> original_int;
  s21::array<int, 3> my_arr_int;
  std::array<double, 3> original_double;
  s21::array<double, 3> my_arr_double;
  std::array<std::string, 3> original_str;
  s21::array<std::string, 3> my_arr_str;
  EXPECT_EQ(original_int.size(), my_arr_int.size());
  EXPECT_EQ(original_double.size(), my_arr_double.size());
  EXPECT_EQ(original_str.size(), my_arr_str.size());
}

TEST(array_member_functions, 2) {
  s21::array<int, 5> my_arr_int{1, 2, 3, 4, 5};
  std::array<int, 5> or_arr_int{1, 2, 3, 4, 5};
  s21::array<double, 5> my_arr_double{1.1, 1.2, 1.3, 1.4, 1.5};
  std::array<double, 5> or_arr_double{1.1, 1.2, 1.3, 1.4, 1.5};
  s21::array<std::string, 5> my_arr_str{"C++", "is", "hard", "!", "!"};
  std::array<std::string, 5> or_arr_str{"C++", "is", "hard", "!", "!"};

  EXPECT_EQ(my_arr_int.size(), or_arr_int.size());
  EXPECT_EQ(my_arr_int[0], or_arr_int[0]);

  EXPECT_EQ(my_arr_double.size(), or_arr_double.size());
  EXPECT_EQ(my_arr_double[0], or_arr_double[0]);

  EXPECT_EQ(my_arr_str.size(), or_arr_str.size());
  EXPECT_EQ(my_arr_str[0], or_arr_str[0]);
}

TEST(array_member_functions, 3) {
  s21::array<int, 4> my_arr_ref_int{1, 2, 3, 4};
  s21::array<int, 4> my_arr_copy_int(my_arr_ref_int);
  std::array<int, 4> or_arr_ref_int{1, 2, 3, 4};
  std::array<int, 4> or_arr_copy_int(or_arr_ref_int);

  s21::array<std::string, 4> my_arr_ref_str{"C++", "is", "hard", "!"};
  s21::array<std::string, 4> my_arr_copy_str(my_arr_ref_str);
  s21::array<std::string, 4> or_arr_ref_str{"C++", "is", "hard", "!"};
  s21::array<std::string, 4> or_arr_copy_str(or_arr_ref_str);

  EXPECT_EQ(my_arr_copy_int.size(), or_arr_copy_int.size());
  EXPECT_EQ(my_arr_copy_int[0], or_arr_copy_int[0]);
  EXPECT_EQ(my_arr_copy_int[1], or_arr_copy_int[1]);
  EXPECT_EQ(my_arr_copy_int[2], or_arr_copy_int[2]);
  EXPECT_EQ(my_arr_copy_int[3], or_arr_copy_int[3]);

  EXPECT_EQ(my_arr_copy_str.size(), or_arr_copy_str.size());
  EXPECT_EQ(my_arr_copy_str[0], or_arr_copy_str[0]);
  EXPECT_EQ(my_arr_copy_str[1], or_arr_copy_str[1]);
  EXPECT_EQ(my_arr_copy_str[2], or_arr_copy_str[2]);
  EXPECT_EQ(my_arr_copy_str[3], or_arr_copy_str[3]);
}

TEST(array_member_functions, 4) {
  s21::array<int, 4> my_arr_ref_int{1, 2, 3, 4};
  s21::array<int, 4> my_arr_copy_int = std::move(my_arr_ref_int);

  s21::array<int, 4> or_arr_ref_int{1, 2, 3, 4};
  s21::array<int, 4> or_arr_copy_int = std::move(or_arr_ref_int);

  s21::array<std::string, 4> my_arr_ref_str{"C++", "is", "hard", "!"};
  s21::array<std::string, 4> my_arr_copy_str = std::move(my_arr_ref_str);

  s21::array<std::string, 4> or_arr_ref_str{"C++", "is", "hard", "!"};
  s21::array<std::string, 4> or_arr_copy_str = std::move(or_arr_ref_str);

  EXPECT_EQ(my_arr_copy_int.size(), or_arr_copy_int.size());
  EXPECT_EQ(my_arr_copy_int[0], or_arr_copy_int[0]);
  EXPECT_EQ(my_arr_copy_int[1], or_arr_copy_int[1]);
  EXPECT_EQ(my_arr_copy_int[2], or_arr_copy_int[2]);
  EXPECT_EQ(my_arr_copy_int[3], or_arr_copy_int[3]);

  EXPECT_EQ(my_arr_copy_str.size(), or_arr_copy_str.size());
  EXPECT_EQ(my_arr_copy_str[0], or_arr_copy_str[0]);
  EXPECT_EQ(my_arr_copy_str[1], or_arr_copy_str[1]);
  EXPECT_EQ(my_arr_copy_str[2], or_arr_copy_str[2]);
  EXPECT_EQ(my_arr_copy_str[3], or_arr_copy_str[3]);
}

TEST(array_member_functions, 5) {
  s21::array<int, 4> my_arr_ref_int{1, 2, 3, 4};
  s21::array<int, 4> my_arr_copy_int;
  my_arr_copy_int = std::move(my_arr_ref_int);

  s21::array<int, 4> or_arr_ref_int{1, 2, 3, 4};
  s21::array<int, 4> or_arr_copy_int;
  or_arr_copy_int = std::move(or_arr_ref_int);

  s21::array<std::string, 4> my_arr_ref_str{"C++", "is", "hard", "!"};
  s21::array<std::string, 4> my_arr_copy_str;
  my_arr_copy_str = std::move(my_arr_ref_str);

  s21::array<std::string, 4> or_arr_ref_str{"C++", "is", "hard", "!"};
  s21::array<std::string, 4> or_arr_copy_str;
  or_arr_copy_str = std::move(or_arr_ref_str);

  EXPECT_EQ(my_arr_copy_int.size(), or_arr_copy_int.size());
  EXPECT_EQ(my_arr_copy_int[0], or_arr_copy_int[0]);
  EXPECT_EQ(my_arr_copy_int[1], or_arr_copy_int[1]);
  EXPECT_EQ(my_arr_copy_int[2], or_arr_copy_int[2]);
  EXPECT_EQ(my_arr_copy_int[3], or_arr_copy_int[3]);

  EXPECT_EQ(my_arr_copy_str.size(), or_arr_copy_str.size());
  EXPECT_EQ(my_arr_copy_str[0], or_arr_copy_str[0]);
  EXPECT_EQ(my_arr_copy_str[1], or_arr_copy_str[1]);
  EXPECT_EQ(my_arr_copy_str[2], or_arr_copy_str[2]);
  EXPECT_EQ(my_arr_copy_str[3], or_arr_copy_str[3]);
}

TEST(array_element_access, 1) {
  s21::array<int, 4> my_arr_int{1, 4, 8, 9};
  s21::array<std::string, 4> my_arr_str{"C++", "is", "hard", "!"};

  EXPECT_EQ(my_arr_int.at(0), 1);
  EXPECT_EQ(my_arr_str.at(0), "C++");
}

TEST(array_element_access, 2) {
  s21::array<int, 4> my_arr_int{1, 2, 3, 4};
  s21::array<std::string, 4> my_arr_str{"C++", "is", "hard", "!"};

  EXPECT_THROW(my_arr_int.at(5), std::out_of_range);
  EXPECT_THROW(my_arr_str.at(5), std::out_of_range);
}

TEST(array_element_access, 3) {
  s21::array<int, 4> my_arr_int{1, 2, 3, 4};
  s21::array<std::string, 4> my_arr_str{"C++", "is", "hard", "!"};

  EXPECT_EQ(my_arr_int[1], 2);
  EXPECT_EQ(my_arr_str[0], "C++");
}

TEST(array_element_access, 4) {
  s21::array<int, 4> my_arr_int{1, 2, 3, 4};
  s21::array<std::string, 4> my_arr_str{"C++", "is", "hard", "!"};

  EXPECT_EQ(my_arr_int.front(), 1);
  EXPECT_EQ(my_arr_str.front(), "C++");
}

TEST(array_element_access, 5) {
  s21::array<int, 4> my_arr_int{1, 2, 3, 4};
  s21::array<std::string, 4> my_arr_str{"C++", "is", "hard", "!"};

  EXPECT_EQ(my_arr_int.back(), 4);
  EXPECT_EQ(my_arr_str.back(), "!");
}

TEST(array_element_access, 6) {
  s21::array<int, 4> my_arr_int{1, 2, 3, 4};
  s21::array<std::string, 4> my_arr_str{"C++", "is", "hard", "!"};

  EXPECT_EQ(my_arr_int.data(), &my_arr_int[0]);
  EXPECT_EQ(my_arr_str.data(), &my_arr_str[0]);
}

TEST(array_iterators, 1) {
  s21::array<int, 4> my_arr_int{1, 2, 3, 4};
  s21::array<std::string, 4> my_arr_string{"C++", "is", "hard", "!"};

  EXPECT_EQ(my_arr_int.begin(), &my_arr_int[0]);
  EXPECT_EQ(my_arr_string.begin(), &my_arr_string[0]);
}

TEST(array_iterators, 2) {
  s21::array<int, 4> my_arr_int{1, 2, 3, 4};
  s21::array<std::string, 4> my_arr_string{"C++", "is", "hard", "!"};

  EXPECT_EQ(my_arr_int.end(), &my_arr_int[0] + 4);
  EXPECT_EQ(my_arr_string.end(), &my_arr_string[0] + 4);
}

TEST(array_capacity, 1) {
  s21::array<int, 4> my_arr_int{1, 2, 3, 4};
  s21::array<std::string, 4> my_arr_string{"C++", "is", "hard", "!"};

  EXPECT_EQ(my_arr_int.empty(), 0);
  EXPECT_EQ(my_arr_string.empty(), 0);
}

TEST(array_capacity, 2) {
  s21::array<int, 0> my_arr_int;
  s21::array<std::string, 0> my_arr_string;

  EXPECT_EQ(my_arr_int.empty(), 1);
  EXPECT_EQ(my_arr_string.empty(), 1);
}

TEST(array_capacity, 3) {
  s21::array<int, 4> my_arr_int{1, 2, 3, 4};
  s21::array<std::string, 4> my_arr_string{"C++", "is", "hard", "!"};

  EXPECT_EQ(my_arr_int.size(), 4U);
  EXPECT_EQ(my_arr_string.size(), 4U);
}

TEST(array_capacity, 4) {
  s21::array<int, 0> my_arr_int;
  s21::array<std::string, 0> my_arr_string;

  EXPECT_EQ(my_arr_int.size(), 0U);
  EXPECT_EQ(my_arr_string.size(), 0U);
}

TEST(array_modifiers, 1) {
  s21::array<int, 4> my_arr_ref_int{1, 2, 3, 4};
  s21::array<int, 4> my_arr_copy_int{21, 21, 21, 21};

  s21::array<std::string, 4> my_arr_ref_str{"C++", "is", "hard", "!"};
  s21::array<std::string, 4> my_arr_copy_str{"21", "21", "21", "21"};

  my_arr_ref_int.swap(my_arr_copy_int);
  my_arr_ref_str.swap(my_arr_copy_str);

  EXPECT_EQ(my_arr_ref_int[3], 21);
  EXPECT_EQ(my_arr_copy_int[0], 1);
  EXPECT_EQ(my_arr_copy_int[1], 2);
  EXPECT_EQ(my_arr_copy_int[2], 3);
  EXPECT_EQ(my_arr_copy_int[3], 4);

  EXPECT_EQ(my_arr_ref_str[3], "21");
  EXPECT_EQ(my_arr_copy_str[0], "C++");
  EXPECT_EQ(my_arr_copy_str[1], "is");
  EXPECT_EQ(my_arr_copy_str[2], "hard");
  EXPECT_EQ(my_arr_copy_str[3], "!");
}

TEST(array_modifiers, 2) {
  s21::array<int, 4> my_arr_int;
  my_arr_int.fill(21);

  EXPECT_EQ(my_arr_int[0], 21);
  EXPECT_EQ(my_arr_int[1], 21);
  EXPECT_EQ(my_arr_int[2], 21);
  EXPECT_EQ(my_arr_int[3], 21);
}