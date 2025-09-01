#include "stdio.h"
#include "cutest/CuTest.h"
#include "standard_calc.h"

/**************** Tests for bound_to_180() *******************/
void test_bound_basic1(CuTest *tc) {
    CuAssertDblEquals(tc, 0, bound_to_180(0), 0.0001);
    CuAssertDblEquals(tc, 90, bound_to_180(90), 0.0001);
    CuAssertDblEquals(tc, -90, bound_to_180(-90), 0.0001);
    CuAssertDblEquals(tc, 156, bound_to_180(876), 0.0001);
    CuAssertDblEquals(tc, -101, bound_to_180(2059), 0.0001);
    CuAssertDblEquals(tc, 60, bound_to_180(-300), 0.0001);
    CuAssertDblEquals(tc, 179.999, bound_to_180(179.999), 0.0001);
    CuAssertDblEquals(tc, -179.999, bound_to_180(-179.999), 0.0001);
    CuAssertDblEquals(tc, -180.00, bound_to_180(180.00), 0.0001);
    CuAssertDblEquals(tc, -180.00, bound_to_180(-180.00), 0.0001);
    CuAssertDblEquals(tc, -179.999, bound_to_180(180.001), 0.0001);
    CuAssertDblEquals(tc, 179.999, bound_to_180(-180.001), 0.0001);
    CuAssertDblEquals(tc, 30.00, bound_to_180(9943590.00), 0.0001);
    CuAssertDblEquals(tc, 0.909, bound_to_180(0.909), 0.0001);
    CuAssertDblEquals(tc, -0.909, bound_to_180(-0.909), 0.0001);
    CuAssertDblEquals(tc, 0.0, bound_to_180(360.0), 0.0001);
    CuAssertDblEquals(tc, 0.0, bound_to_180(-360.0), 0.0001);
    CuAssertDblEquals(tc, -0.001, bound_to_180(359.999), 0.0001);
    CuAssertDblEquals(tc,  0.001, bound_to_180(-359.999), 0.0001);
    CuAssertDblEquals(tc, -180.0, bound_to_180( 540.0), 0.0001);
    CuAssertDblEquals(tc, -180.0, bound_to_180(-540.0), 0.0001);
}

/**************** Tests for is_angle_between() *******************/
void test_between_basic1(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(0, 1, 2));
    CuAssertTrue(tc,  is_angle_between(0, 45, 90));
    CuAssertTrue(tc,  is_angle_between(10, 10, 100));
    CuAssertTrue(tc,  is_angle_between(10, 100, 100));
    CuAssertTrue(tc, !is_angle_between(0, 91, 90));
    CuAssertTrue(tc, !is_angle_between(0, -1, 90));
}

int main(int argc, char const *argv[]) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_bound_basic1);
    SUITE_ADD_TEST(suite, test_between_basic1);

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    return suite->failCount > 0 ? 1 : 0;
}
