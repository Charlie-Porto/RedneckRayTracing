#ifndef if_pair_in_vector_cpp
#define if_pair_in_vector_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
function that checks if a pair is in a vector.
returns true if found in vector, returns false if not found
-----------------------------------------------------------------*/
#include <vector>
#include <utility>

namespace pce {
namespace vfunc {

template <typename T1, typename T2>
bool if_pair_in_vector(const std::pair<T1, T2>& mpair,
                       const std::vector<std::pair<T1, T2>>& mvect) {
  for (int i = 0; i < mvect.size(); ++i) {
    if (mpair.first == mvect[i].first &&
        mpair.second == mvect[i].second) {
      return true; 
    }
  }
  return false;
}

}
}

#endif /* if_pair_in_vector_cpp */
