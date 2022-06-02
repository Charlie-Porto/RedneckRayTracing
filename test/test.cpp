#ifndef testing_cpp
#define testing_cpp


/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
testing, broh.
-----------------------------------------------------------------*/

#include <gtest/gtest.h>

// #include "funks_testing/test_checkIfPairInVector.cpp"
// #include "funks_testing/test_checkIfLineVectorFormIntersectsSphere.cpp"
#include "funks_testing/test_calculateClosestPointLineIntersectsSphere.cpp"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}





#endif /* testing_cpp */
