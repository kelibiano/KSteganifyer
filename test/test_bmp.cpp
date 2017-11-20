
#include <gtest/gtest.h>
#include <algorithm>

int main(int argc, char ** argv) { 
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); 
}

// simple sorter for arrays
template <typename T>
void array_sort(T * arr, size_t len)
{
    std::sort(arr, arr + len);
}


TEST(cpp_sorter_test, null_term_str_sort)
{
    char arr[] = "abcdefghab";
    char eq[] = "aabbcdefgh";
    int sz = sizeof(arr) / sizeof(arr[0]) - 1; // we need it, to avoid terminating \0 in "" definition case
    array_sort(arr, sz);

    for (int i = 0; i<sz; i++)
        EXPECT_EQ(arr[i], eq[i]);
}