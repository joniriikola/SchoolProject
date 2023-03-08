#pragma once

#include <QDebug>
#include <QLocale>
#include <QObject>
#include <QQuickItem>
#include <QStringListModel>
#include <QTimer>

#include <memory>

#include "autocompleter.h"
#include "fileio.h"
#include "fingridclient.h"
#include "fmiclient.h"
#include "linechartmodel.h"
#include "piechartmodel.h"

class FileIO;
/**
 * @brief UIController tracks the state of user interface elements ans mediates the searches made by
 * user.
 */
class UIController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString chartType MEMBER m_chartType NOTIFY chartTypeChanged);
    Q_PROPERTY(int chartIndex READ chartIndex NOTIFY chartTypeChanged);
    Q_PROPERTY(QString location MEMBER m_location NOTIFY locationChanged);
    Q_PROPERTY(QString locationHint MEMBER m_locationHint CONSTANT);
    Q_PROPERTY(QString locationAutoComp MEMBER m_locationAutoComp NOTIFY locationAutoCompChanged);
    Q_PROPERTY(QString fileName MEMBER m_fileName NOTIFY fileNameChanged);
    Q_PROPERTY(int fileIndex READ fileIndex NOTIFY fileNameChanged);
    Q_PROPERTY(QDate startDate MEMBER m_startDate NOTIFY dateChanged);
    Q_PROPERTY(QDate endDate MEMBER m_endDate NOTIFY dateChanged);
    Q_PROPERTY(bool checkBox0 MEMBER m_checkBox0 NOTIFY checkBoxesChanged);
    Q_PROPERTY(bool checkBox1 MEMBER m_checkBox1 NOTIFY checkBoxesChanged);
    Q_PROPERTY(bool checkBox2 MEMBER m_checkBox2 NOTIFY checkBoxesChanged);
    Q_PROPERTY(bool busyIndicator MEMBER m_busyIndicator NOTIFY busyIndicatorChanged);

public:
    friend class PresetController;
    /**
     * @brief Constructor.
     * @param fileIO: Shared Pointer to FileIO.
     * @param parent: Pointer to parent QObject.
     */
    explicit UIController(std::shared_ptr<FileIO> fileIO, QObject* parent = nullptr);

    /**
     * @brief Queries data from clients and fills and published models based on ui state.
     */
    Q_INVOKABLE void search();

    /**
     * @brief Returns pointer to LineChartModel this controller contontrols.
     * @return LineChartModel*: Pointer to LineChartModel.
     */
    Q_INVOKABLE LineChartModel* lineChartModel() const;

    /**
     * @brief Returns pointer to PieChartModel this controller contontrols.
     * @return PieChartModel*: Pointer to PieChartModel.
     */
    Q_INVOKABLE PieChartModel* pieChartModel() const;

    /**
     * @brief Returns pointer to model with names of saved data sets.
     * @return QStringListModel*: Pointer to model with saved dataset names.
     */
    Q_INVOKABLE QStringListModel* savedFilesModel();

    /**
     * @brief Saves currently displayed linechart with given name.
     * @param name: Name of the data set.
     */
    Q_INVOKABLE void saveDataSet(const QString& name);

    /**
     * @brief Returns static model with list of available chart types.
     * @return QStringListModel&: Model with names of available chart types.
     */
    static QStringListModel& chartTypesModel();

public slots:
    /**
     * @brief Resets all ui element variables, called when chart type is changed.
     */
    void resetControls();
    /**
     * @brief Updates the autocompletion quess based on current location string.
     */
    void updateLocationAutoComp();
    /**
     * @brief Updates saved data sets model.
     */
    void updateSavedDatasetsModel();

signals:
    void chartTypeChanged() const;
    void locationChanged() const;
    void fileNameChanged() const;
    void dateChanged() const;
    void checkBoxesChanged() const;
    void locationAutoCompChanged() const;
    void busyIndicatorChanged() const;
    void errorChanged() const;

private:
    /**
     * @brief Creates model objects of UIController.
     */
    void createModels();
    /**
     * @brief Replaces line model with model with weather forecast.
     */
    void searchWeatherForecast();

    /**
     * @brief Replaces line model with model with weather history.
     */
    void searchWeatherHistory();

    /**
     * @brief Replaces line model with model with monthly temperature data.
     */
    void searchMonthlyTemp();

    /**
     * @brief Replaces line model with model with electricity troughput.
     */
    void searchElectrProdCons();

    /**
     * @brief Replaces line model with model with electricity forecast.
     */
    void searchElectrForecast();

    /**
     * @brief Replaces line model with model with renewable power produciton forecast.
     */
    void searchRenewEnergyProd();

    /**
     * @brief Replaces line model with model with electricity production method data.
     */
    void searchElectricityProdMethods();

    /**
     * @brief Replaces piechart model with electricity production method distribution.
     */
    void searchElectrProdDistr();

    /**
     * @brief Replaces line model with model with previously saved data set.
     */
    void loadSavedDataSet();

    /**
     * @brief Starts realtime frequency monitoring.
     */
    void startRealTimeFrequency();

    /**
     * @brief Starts realtime consumption monitoring.
     */
    void startRealTimeConsumption();

    /**
     * @brief Starts realtime import/export monitoring.
     */
    void startRealTimeImport();

    /**
     * @brief Sets UIController in busy state.
     * @param show: Should busy indicator be shown.
     */
    void showBusyIndicator(bool show);

    /**
     * @brief If autocomplete came up empty but model was populated, location is added to auto
     * complete suggestions.
     * @param: location: String used in query that was not quessed but resulted in data.
     */
    void updateDictionary(const QString& location);

    /**
     * @brief Returns the index of current chartType.
     * @return int: Index of current chartType.
     */
    int chartIndex() const;

    /**
     * @brief Returns the index of currently selected saved data set.
     * @return Qint: Index of currently selected saved data set.
     */
    int fileIndex() const;

    // Index of these entries is used in qml to show correct ui elements.
    // Keep in mind if changing the order.
    inline static QStringList m_chartTypes = {"Weather Forecast 24h",
            "Weather History",
            "Monthly Temperature Averages",
            "Electricity Production And Consumption",
            "Electricity Production And Consumption Forecast 24h",
            "Renewable Energy Production Forecast 24h",
            "Electricity Production Methods",
            "Electricity Production Method Distribution",
            "Saved Datasets",
            "Real Time Frequency",
            "Real Time Consumption",
            "Real Time Import/Export"};

    inline static QStringListModel m_chartTypesModel = QStringListModel(m_chartTypes);

    std::shared_ptr<FileIO> m_fileIO = nullptr;
    std::unique_ptr<LineChartModel> m_lineModel = nullptr;
    std::unique_ptr<PieChartModel> m_pieModel = nullptr;
    std::unique_ptr<QStringListModel> m_savedDatasetsModel = nullptr;

    QString m_chartType = m_chartTypes[0];
    QString m_location;
    QString m_fileName;
    QString m_locationHint = "Location";

    QDate m_startDate = QDate::currentDate();
    QDate m_endDate = QDate::currentDate();

    unsigned int m_month = QDate::currentDate().month();
    unsigned int m_year = QDate::currentDate().year();

    bool m_checkBox0 = true;
    bool m_checkBox1 = true;
    bool m_checkBox2 = true;

    bool m_busyIndicator = false;

    FmiClient m_fmiClient;
    FingridClient m_fingridClient;

    std::unique_ptr<AutoCompleter> m_autoCompleter = nullptr;
    QString m_finnishPlaceNamesDict = "data/fmiLocationDictionary.txt";
    QString m_locationAutoComp = "";

    QTimer m_realTimeTimer;
    inline static int m_realTimeInterval_ms = 30000;
};
