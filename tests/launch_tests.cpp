#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../BasicTape.cpp"
#include "../TapeSort.cpp"

TEST(CreationTapeTest, CreateEmpty)
{
    BasicTape t(5);
    ASSERT_EQ(t.GetTapeSize(), 5);
    ASSERT_EQ(t.GetCurrentPosition(), 0);
    ASSERT_EQ(t.GetData(), 0);
}

TEST(FunctionsTapeTest, Record)
{
    BasicTape t(5);
    t.Record(129);
    ASSERT_EQ(t.GetData(), 129);
    t.Record(3);
    ASSERT_EQ(t.GetData(), 3);
    ASSERT_EQ(t.GetCurrentPosition(), 0);
}

TEST(FunctionsTapeTest, Forward)
{
    BasicTape t(5);
    t.Record(129);
    ASSERT_EQ(t.GetData(), 129);
    t.Forward();
    t.Record(3);
    ASSERT_EQ(t.GetData(), 3);
    t.Forward();
    ASSERT_EQ(t.GetCurrentPosition(), 2);
}

TEST(FunctionsTapeTest, Backward)
{
    BasicTape t(5);
    t.Record(129);
    ASSERT_EQ(t.GetData(), 129);
    t.Forward();
    t.Record(3);
    ASSERT_EQ(t.GetData(), 3);
    t.Backward();
    ASSERT_EQ(t.GetCurrentPosition(), 0);
    ASSERT_EQ(t.GetData(), 129);
}

TEST(CreationTapeTest, LoadElements)
{
    BasicTape in(5);
    int unsorted[] = {129, 3, 675, 332, 357654};

    for (int i = 0; i < 4; ++i)
    {
        in.Record(unsorted[i]);
        in.Forward();
    }
    in.Record(unsorted[4]);
    ASSERT_EQ(in.GetCurrentPosition(), 4);
}

TEST(FunctionsTapeTest, Rewind)
{
    BasicTape in(5);
    int unsorted[] = {129, 3, 675, 332, 357654};

    for (int i = 0; i < 4; ++i)
    {
        in.Record(unsorted[i]);
        in.Forward();
    }
    in.Record(unsorted[4]);
    in.Rewind(-4);
    ASSERT_EQ(in.GetCurrentPosition(), 0);
}

TEST(SortTest, Sort)
{
    BasicTape in(5);
    int unsorted[] = {129, 3, 675, 332, 357654};
    int sorted[] = {3, 129, 332, 675, 357654};

    for (int i = 0; i < 4; ++i)
    {
        in.Record(unsorted[i]);
        in.Forward();
    }
    in.Record(unsorted[4]);
    in.Rewind(-4);

    BasicTape out(in.GetTapeSize());
    TapeSort srt((AbstractTape &)in, (AbstractTape &)out);

    for (int i = 0; i < 4; ++i)
    {
        ASSERT_EQ(out.GetData(), sorted[i]);
        out.Forward();
    }
    ASSERT_EQ(out.GetData(), sorted[4]);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}