#include "unity.h"

/* * This function runs before EVERY test. 
 * Ideal for resetting variables or structures.
 */
void setUp(void) {
    // Setup code here
}

/* * This function runs after EVERY test.
 * Ideal for memory cleanup if dynamic allocation is used.
 */
void tearDown(void) {
    // Teardown code here
}

/* A temporary dummy C function to verify the framework works */
int test_sum(int a, int b) {
    return a + b;
}

/* A simple test case using Unity macros */
void test_BasicMathWorks(void) {
    TEST_ASSERT_EQUAL_INT(4, test_sum(2, 2));
    TEST_ASSERT_EQUAL_INT(0, test_sum(-1, 1));
}

/* Main function that runs all tests */
int main(void) {
    UNITY_BEGIN();
    
    // Register each test function here
    RUN_TEST(test_BasicMathWorks);
    
    return UNITY_END();
}