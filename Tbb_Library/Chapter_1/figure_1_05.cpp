// #include <pstl/experimental/algorithm>
// #include <pstl/internal/algorithm_impl.h>

#include <pstl/algorithm>
#include <pstl/execution>
#include <iostream>
#include <vector>

int main() { 
  std::vector<std::string> v = { " Hello ", " Parallel STL! " };
  std::for_each(pstl::execution::par, v.begin(), v.end(),
    [](std::string& s) { std::cout << s << std::endl; }
  ); 
  return 0;
}

