#include <unity.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_simple_assertion(void) { TEST_ASSERT_EQUAL(1, 1); }

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_simple_assertion);
    return UNITY_END();
}
