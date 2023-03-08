#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "basechartmodel.h"

#include <QDebug>
#include <QRandomGenerator>

class MockChartModel : public BaseChartModel
{
    // BaseChartModel interface
public:
    MockChartModel(QObject* parent = nullptr) : BaseChartModel(parent)
    {
        connect(this, &BaseChartModel::graphsChanged, this, &MockChartModel::publishTrap);
    }
    quint64 graphCount() const
    {
        return 0;
    }
    void clear()
    {
    }

    MOCK_METHOD0(publishTrap, void());
};

TEST(BaseChartModel_Test, titleTest)
{
    MockChartModel model;
    EXPECT_EQ(model.title(), "");
    model.setTitle("title");
    EXPECT_EQ(model.title(), "title");
}

TEST(BaseChartModel_Test, labelTest)
{
    MockChartModel model;
    EXPECT_EQ(model.labelX(), "");
    EXPECT_EQ(model.labelY(), "");
    model.setAxisLabels("axis x", "axis y");
    EXPECT_EQ(model.labelX(), "axis x");
    EXPECT_EQ(model.labelY(), "axis y");
}

TEST(BaseChartModel_Test, publishTest)
{
    MockChartModel model;
    EXPECT_CALL(model, publishTrap).Times(1);
    model.publish();
}
