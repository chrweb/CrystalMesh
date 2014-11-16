#include "TestIncludes.h"
using namespace Mathbox;


//comparing doubles in ULPs
TEST(ULP, cmpDouble)
{
    
    double const dRef = 1.0;
    double const d0 = 1.000000000100000;
    double const d1 = 1.000000000010000;
    double const d2 = 1.000000000001000;
    double const d3 = 1.000000000000100;
    double const d4 = 1.000000000000010;
    double const d5 = 1.000000000000001;
    
    //expected diffs in ULP
    uint64_t const ulp0 = 450360;
    uint64_t const ulp1 = 45036;
    uint64_t const ulp2 = 4504;
    uint64_t const ulp3 = 450;
    uint64_t const ulp4 = 45;
    uint64_t const ulp5 = 5;
    
    uint64_t const diff0 = diffInUlps(dRef, d0);
    uint64_t const diff1 = diffInUlps(dRef, d1);
    uint64_t const diff2 = diffInUlps(dRef, d2);
    uint64_t const diff3 = diffInUlps(dRef, d3);
    uint64_t const diff4 = diffInUlps(dRef, d4);
    uint64_t const diff5 = diffInUlps(dRef, d5);
    
    // Test
    EXPECT_EQ(ulp0, diff0);
    EXPECT_EQ(ulp1, diff1);
    EXPECT_EQ(ulp2, diff2);
    EXPECT_EQ(ulp3, diff3);
    EXPECT_EQ(ulp4, diff4);
    EXPECT_EQ(ulp5, diff5);
    
    //Test almostequal in ULP:
    EXPECT_TRUE(almostEqual(dRef, d5, 6ul));
    EXPECT_TRUE(almostEqual(dRef, d5, 5ul));
    EXPECT_FALSE(almostEqual(dRef, d5, 4ul));         
}

//Test some others:
TEST(ULP, others)
{
    //auto const ulp0 = diffInUlps( 0.20000000000000001
    //                            , 0.19999999999999996);
    //uint64_t const excp0 = 2ul;
    
    auto const ulp1 = diffInUlps( 2.2204460492503131e-16
                                , 0.0);
    uint64_t const excp1 = 2ul;
    
    auto const ulp2 = diffInUlps( 2.4825341532472731e-16
                                , 0.0);
    uint64_t const expc2 = 2ul;
    
    auto const ulp3 = diffInUlps( 0.000000000000000248, 0.0);
    
    uint64_t const expc3 = 2ul;
}

TEST(ULP, someFloats){
    int diff0 = diffInUlps(1.4012985e-045f, 0.0f);
    uint64_t const expc3 = 2ul;
}

TEST(ULP, someDoubles){
    int diff0 = diffInUlpsD(1.4012985e-045, 0.0);
    uint64_t const expc3 = 2ul;
}