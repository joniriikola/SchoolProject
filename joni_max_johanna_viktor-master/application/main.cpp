#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QStringListModel>

#include "fileio.h"
#include "presetcontroller.h"
#include "uicontroller.h"

static QStringList& months();
static QStringList& years(int minYear);

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    app.setOrganizationName("OrganizationName");
    app.setOrganizationDomain("OrganizationDomain");
    app.setWindowIcon(QIcon(":/ui/icons/icon.svg"));

    auto fileIO = std::make_shared<FileIO>(&app);
    auto leftUiController = std::make_shared<UIController>(fileIO, &app);
    auto rightUiController = std::make_shared<UIController>(fileIO, &app);
    PresetController presetController(leftUiController, rightUiController, fileIO, &app);

    QQmlApplicationEngine engine;

    // Userinterface controllers
    engine.rootContext()->setContextProperty("LeftUIController", leftUiController.get());
    engine.rootContext()->setContextProperty("RightUIController", rightUiController.get());
    engine.rootContext()->setContextProperty("PresetController", &presetController);

    // Auxiliary models
    static auto yearModel = QStringListModel(years(1980));
    static auto monthModel = QStringListModel(months());

    engine.rootContext()->setContextProperty("MonthModel", &monthModel);
    engine.rootContext()->setContextProperty("YearModel", &yearModel);
    engine.rootContext()->setContextProperty("ChartTypesModel", &UIController::chartTypesModel());

    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
    QObject::connect(
            &engine,
            &QQmlApplicationEngine::objectCreated,
            &app,
            [url](QObject* obj, const QUrl& objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}

static QStringList& months()
{
    static QStringList monthList;
    static QLocale locale;
    for (auto i = 1; i <= 12; ++i)
    {
        monthList.append(locale.monthName(i));
    }
    return monthList;
}

static QStringList& years(int minYear)
{
    static QStringList yearList;

    for (auto i = QDate::currentDate().year(); i >= minYear; --i)
    {
        yearList.append(QString::number(i));
    }
    return yearList;
}
