#include <iostream>
#include <stdfloat>
int main() {
#ifdef __STDCPP_FLOAT32_T__
    std::float32_t f = 1.0f;
    std::cout << "float32_t supported: " << sizeof(f) << std::endl;
#else
    std::cout << "float32_t NOT supported" << std::endl;
#endif
    return 0;
}
