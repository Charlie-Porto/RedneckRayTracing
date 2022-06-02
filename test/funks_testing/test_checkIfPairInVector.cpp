#ifndef t_if_pair_in_vector_cpp
#define t_if_pair_in_vector_cpp

#include <gtest/gtest.h>

#include "../../src/ecs/systems/funks/if_pair_in_vector.cpp"

// test_case_1
std::pair<int, int> a_input_pair = std::make_pair(1, 1);
std::pair<int, int> ta_pair = std::make_pair(1, 0);
std::pair<int, int> tb_pair = std::make_pair(0, 1);
std::pair<int, int> tc_pair = std::make_pair(0, 0);
std::pair<int, int> td_pair = std::make_pair(1, 1);
std::vector<std::pair<int, int>> a_input_vect_a{ta_pair};
std::vector<std::pair<int, int>> a_input_vect_b{ta_pair, tb_pair};
std::vector<std::pair<int, int>> a_input_vect_c{ta_pair, tb_pair, tc_pair};
std::vector<std::pair<int, int>> a_input_vect_d{ta_pair, tb_pair, tc_pair, td_pair};
bool result_a = pce::vfunc::if_pair_in_vector<int, int>(a_input_pair, a_input_vect_a);
bool result_b = pce::vfunc::if_pair_in_vector<int, int>(a_input_pair, a_input_vect_b);
bool result_c = pce::vfunc::if_pair_in_vector<int, int>(a_input_pair, a_input_vect_c);
bool result_d = pce::vfunc::if_pair_in_vector<int, int>(a_input_pair, a_input_vect_d);

TEST(test_funks, case_1) {
  ASSERT_EQ(result_a, false);
}

TEST(test_funks, case_2) {
  ASSERT_EQ(result_b, false);
}

TEST(test_funks, case_3) {
  ASSERT_EQ(result_c, false);
}

TEST(test_funks, case_4) {
  ASSERT_EQ(result_d, true);
}
#endif /* t_if_pair_in_vector_cpp */
