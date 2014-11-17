#include "TestIncludes.h"
using namespace Mathbox;

/**
 * I'm testing ULPs and make some experiments,
 * to learn about ULPs.
 */

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

TEST(ULP,CloseToZero){
    double const dRef = 0.0;
    // Let's ses, how many ULP are now between:
    double const d0 = 0.000000000100000;
    double const d1 = 0.000000000010000;
    double const d2 = 0.000000000001000;
    double const d3 = 0.000000000000100;
    double const d4 = 0.000000000000010;
    double const d5 = 0.000000000000001;
    
    //expected diffs in ULP
    uint64_t const ulp0 = 4457293557087583675;
    uint64_t const ulp1 = 4442235333156365461;
    uint64_t const ulp2 = 4427486594234968593;
    uint64_t const ulp3 = 4412443251819771522;
    uint64_t const ulp4 = 4397347889687374747;
    uint64_t const ulp5 = 4382569440205035030;
    
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
}

TEST(ULP, LSB){
    double const dRef = 0.0;
    // Due to some IEE, a double's resolution is 2**-52:
    double const d0 = 2.2204460492503131e-16;
    double const d1 = 4.44089209850063e-16;
    
    auto const diff0 = diffInUlps(dRef, d0);
    auto const diff1 = diffInUlps(dRef, d1);
    auto const diff2 = diffInUlps(d1, d0);

    // But this does not matter, there many states between:
    uint64_t const ulp0 = 4372995238176751616;
    uint64_t const ulp1 = 4377498837804122116;
    uint64_t const ulp2 = 4503599627370500;
                          
                         
     // Test
    EXPECT_EQ(ulp0, diff0);
    EXPECT_EQ(ulp1, diff1);
    EXPECT_EQ(ulp2, diff2);
}

TEST(ULP, veryCloseToZero){
    
    double const d0n = -0.0;
    double const d0p = 0.0;
    double const d1p = 1e-300;
    double const d2p = 1e-100;
    double const d3p = 1e-90;
    double const d4p = 1e-16;

    auto const ulp00 = diffInUlps(d0n, d0p);
    auto const ulp01 = diffInUlps(d0n, d1p);
    auto const ulp02 = diffInUlps(d0n, d2p);
    auto const ulp03 = diffInUlps(d0n, d3p);
    auto const ulp04 = diffInUlps(d0n, d4p);
    
    //Event for numbers close to 0.0, there is much
    //space left...
    EXPECT_EQ(                   0, ulp00);
    EXPECT_EQ(  118622047889322841, ulp01);
    EXPECT_EQ( 3110860544497550640, ulp02); 
    EXPECT_EQ( 3260689527820848751, ulp03);
    EXPECT_EQ( 4367597403136100796, ulp04);
    
    return;
}

