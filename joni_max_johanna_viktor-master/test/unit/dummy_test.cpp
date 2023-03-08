#include "gtest/gtest.h"

#include <QDebug>

TEST(DummyTest, Dummy)
{
    qDebug() << "This is a test template.";
    EXPECT_EQ(true, true);
}
