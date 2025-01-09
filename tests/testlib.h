
static int success_cnt = 0;
static int fail_cnt = 0;
static int fail_func = 0;

// Custom ASSERT macro
#define TEST_ASSERT(cond) do { \
    if (!(cond)) { \
        fail_func = 1; \
        fprintf(stderr, "[%s:%d %s] Assertion failed: %s\n", __FILE__, __LINE__, __func__, #cond); \
    } \
} while(0)

#define RUN_TEST(func) do { \
    fail_func = 0; \
    printf("running test %s...\n", #func);\
    func(); \
    if(fail_func) fail_cnt++; \
    else success_cnt++; \
} while(0)

#define RUN_TEST_BUNDLE(bundle) int main(int argc, char *argv[]) {\
    printf("----- RUN TESTS: %s:%s -----\n", argv[0], #bundle); \
    bundle(); \
    printf("Total %d, passed %d tests, failed %d tests.\n", fail_cnt+success_cnt, success_cnt, fail_cnt); \
    if(fail_cnt == 0) printf("ALL TESTS PASSED\n"); \
    return 0; \
}
