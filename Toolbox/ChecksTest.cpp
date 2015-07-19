#include <gtest/gtest.h>

#include "Checks.h"

TEST(Checks, should_be_throw){
    EXPECT_ANY_THROW(SHOULD_BE(false));
}

TEST(Checks, should_be_noi_throw){
    EXPECT_NO_THROW(SHOULD_BE(true));
}

TEST(Checks, must_be_throw){
    EXPECT_ANY_THROW(MUST_BE(false));
}

TEST(Checks, must_be_no_throw){
    EXPECT_NO_THROW(MUST_BE(true));
}
 