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

    CuAssertTrue(tc,  !is_angle_between(45, 90, 270));
    CuAssertTrue(tc,  is_angle_between(45, 350, 270));

    CuAssertTrue(tc,  is_angle_between(350, 0, 10));
    CuAssertTrue(tc,  !is_angle_between(350, 180, 10));
    CuAssertTrue(tc,  is_angle_between(359, 0, 1));
    CuAssertTrue(tc,  is_angle_between(-10, -5, 5));

    CuAssertTrue(tc, is_angle_between(0, 180, 180));
    CuAssertTrue(tc, is_angle_between(180, 0, 0));
    CuAssertTrue(tc, is_angle_between(30, 210, 210));
    CuAssertTrue(tc, !is_angle_between(0, 180.001, 180));

    CuAssertTrue(tc, is_angle_between(30, 30, 30));
    CuAssertTrue(tc, !is_angle_between(30, 31, 30));
    CuAssertTrue(tc, is_angle_between(-330, 30, 390));

    CuAssertTrue(tc, is_angle_between(45 + 720.0, 50 + 1080.0, 60 - 360.0));
    CuAssertTrue(tc, !is_angle_between(350 + 360.0, 340 - 720.0, 10 + 720.0));

    CuAssertTrue(tc,  is_angle_between(0.5, 1.25, 2.0));
    CuAssertTrue(tc, !is_angle_between(0.5, 2.5, 2.0));

    CuAssertTrue(tc,  is_angle_between(359.5, 0.25, 1.0));
    CuAssertTrue(tc, !is_angle_between(359.5, 180.0, 1.0));

    CuAssertTrue(tc,  is_angle_between(170.0, 179.999, -170.0));
    CuAssertTrue(tc, !is_angle_between(170.0, -160.0, -170.0));

    CuAssertTrue(tc,  is_angle_between(-10.5, -9.25, -8.0));
    CuAssertTrue(tc, !is_angle_between(-10.5, -7.5, -8.0));

    CuAssertTrue(tc,  is_angle_between(45.25, 45.25, 90.75));
    CuAssertTrue(tc,  is_angle_between(45.25, 90.75, 90.75));
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
