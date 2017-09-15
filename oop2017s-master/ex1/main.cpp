#include <gtest/gtest.h>

int main( int argc , char **argv )
{
    testing :: InitGoogleTest( &argc , argv ) ;
    return RUN_ALL_TESTS( ) ;
}

TEST (test1,first) {
    ASSERT_FALSE(false);
}

TEST (test1, second) {
    ASSERT_TRUE(true);
}
