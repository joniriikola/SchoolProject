#include "uicontroller.h"

UIController::UIController(std::shared_ptr<FileIO> fileIO, QObject* parent) :
    QObject(parent), m_fileIO(fileIO)
{
    createModels();
    connect(this, &UIController::chartTypeChanged, this, &UIController::resetControls);
    connect(this, &UIController::locationChanged, this, &UIController::updateLocationAutoComp);
    connect(m_fileIO.get(), &FileIO::newFileCreated, this, &UIController::updateSavedDatasetsModel);
}

void UIController::search()
{
    if (m_busyIndicator)
    {
        return;
    }

    auto location = m_location;

    showBusyIndicator(true);
    m_lineModel->clear();
    m_pieModel->clear();

    switch (m_chartTypes.indexOf(m_chartType))
    {
    case 0:
        searchWeatherForecast();
        break;
    case 1:
        searchWeatherHistory();
        break;
    case 2:
        searchMonthlyTemp();
        break;
    case 3:
        searchElectrProdCons();
        break;
    case 4:
        searchElectrForecast();
        break;
    case 5:
        searchRenewEnergyProd();
        break;
    case 6:
        searchElectricityProdMethods();
        break;
    case 7:
        searchElectrProdDistr();
        break;
    case 8:
        loadSavedDataSet();
        break;
    case 9:
        startRealTimeFrequency();
        break;
    case 10:
        startRealTimeConsumption();
        break;
    case 11:
        startRealTimeImport();
        break;
    }
    updateDictionary(location);
    showBusyIndicator(false);
}

LineChartModel* UIController::lineChartModel() const
{
    return m_lineModel.get();
}

PieChartModel* UIController::pieChartModel() const
{
    return m_pieModel.get();
}

QStringListModel& UIController::chartTypesModel()
{
    return m_chartTypesModel;
}

QStringListModel* UIController::savedFilesModel()
{
    return m_savedDatasetsModel.get();
}

void UIController::saveDataSet(const QString& name)
{
    m_fileIO->saveDataset(name, m_lineModel->getGraph());
}

int UIController::chartIndex() const
{
    return m_chartTypes.indexOf(m_chartType);
}

int UIController::fileIndex() const
{
    return m_savedDatasetsModel->stringList().indexOf(m_fileName);
}

void UIController::showBusyIndicator(bool show)
{
    m_busyIndicator = show;
    emit busyIndicatorChanged();
}

void UIController::resetControls()
{
    m_startDate = QDate::currentDate();
    m_endDate = QDate::currentDate();
    m_year = QDate::currentDate().year();
    m_month = QDate::currentDate().month();

    m_checkBox0 = true;
    m_checkBox1 = true;
    m_checkBox2 = true;

    m_location = "";
    m_fileName = "";
    m_locationAutoComp = "";

    m_lineModel->clear();
    m_lineModel->publish();

    m_pieModel->clear();
    m_pieModel->publish();

    m_realTimeTimer.stop();
    m_realTimeTimer.disconnect();

    emit checkBoxesChanged();
    emit locationChanged();
}

void UIController::updateLocationAutoComp()
{
    if (m_location.length() > 0)
    {
        m_locationAutoComp = m_autoCompleter->getSuggestion(m_location);
        emit locationAutoCompChanged();
    }
}

void UIController::createModels()
{
    m_lineModel = std::make_unique<LineChartModel>(new LineChartModel(this));
    qRegisterMetaType<LineChartModel*>("LineChartModel*");

    m_pieModel = std::make_unique<PieChartModel>(new PieChartModel(this));
    qRegisterMetaType<PieChartModel*>("PieChartModel*");

    m_savedDatasetsModel = std::make_unique<QStringListModel>(new QStringListModel(this));
    qRegisterMetaType<QStringListModel*>("QStringListModel*");
    updateSavedDatasetsModel();

    m_autoCompleter = std::make_unique<AutoCompleter>(new AutoCompleter(this));
    m_autoCompleter->openDictionary(m_finnishPlaceNamesDict);
}

void UIController::searchWeatherForecast()
{
    auto data = m_fmiClient.weatherForecast24h(m_location, m_checkBox1, m_checkBox0);
    data.error ? m_lineModel->setError(data.errorMessage) : m_lineModel->addGraph(data.graph);
    m_lineModel->publish();
}

void UIController::searchMonthlyTemp()
{
    auto data = m_fmiClient.monthlyTemperatureAverages(m_startDate.month(),
            m_startDate.year(),
            m_location,
            m_checkBox2,
            m_checkBox1,
            m_checkBox0);
    data.error ? m_lineModel->setError(data.errorMessage) : m_lineModel->addGraph(data.graph);
    m_lineModel->publish();
}

void UIController::searchElectrProdCons()
{
    auto data = m_fingridClient.energyThroughputHistory(
            m_startDate, m_endDate, m_checkBox0, m_checkBox1);
    data.error ? m_lineModel->setError(data.errorMessage) : m_lineModel->addGraph(data.lineGraph);
    m_lineModel->publish();
}

void UIController::searchElectrForecast()
{
    auto data = m_fingridClient.energyThroughputForecast24h(m_checkBox0, m_checkBox1);
    data.error ? m_lineModel->setError(data.errorMessage) : m_lineModel->addGraph(data.lineGraph);
    m_lineModel->publish();
}

void UIController::searchWeatherHistory()
{
    auto data = m_fmiClient.weatherHistory(
            m_startDate, m_endDate, m_location, m_checkBox2, m_checkBox1, m_checkBox0);
    data.error ? m_lineModel->setError(data.errorMessage) : m_lineModel->addGraph(data.graph);
    m_lineModel->publish();
}

void UIController::searchRenewEnergyProd()
{
    auto data = m_fingridClient.renewableEnergyProductionForecast24h(m_checkBox0, m_checkBox1);
    data.error ? m_lineModel->setError(data.errorMessage) : m_lineModel->addGraph(data.lineGraph);

    m_lineModel->publish();
}

void UIController::searchElectricityProdMethods()
{
    auto data = m_fingridClient.energyProductionMethods(
            m_startDate, m_endDate, m_checkBox2, m_checkBox1, m_checkBox0);
    data.error ? m_lineModel->setError(data.errorMessage) : m_lineModel->addGraph(data.lineGraph);
    m_lineModel->publish();
}

void UIController::searchElectrProdDistr()
{
    auto data = m_fingridClient.energyProductionDistribution(m_startDate, m_endDate);

    if (data.error)
    {
        m_pieModel->setError(data.errorMessage);
    }
    else
    {
        for (const auto& slice : data.pieGraph.slices)
        {
            m_pieModel->addSlice(slice);
        }
        m_pieModel->setTitle(data.pieGraph.title);
    }
    m_pieModel->publish();
}

void UIController::loadSavedDataSet()
{
    m_lineModel->clear();
    m_lineModel->addGraph(m_fileIO->readDataset(m_fileName));
    m_lineModel->publish();
}

void UIController::startRealTimeFrequency()
{
    auto data = m_realTimeTimer.isActive()
            ? m_fingridClient.realTimeFrequency(m_lineModel->getGraph())
            : m_fingridClient.realTimeFrequency(std::nullopt);
    m_lineModel->clear();
    data.error ? m_lineModel->setError(data.errorMessage) : m_lineModel->addGraph(data.lineGraph);
    m_lineModel->publish();

    if (!m_realTimeTimer.isActive())
    {
        connect(&m_realTimeTimer, &QTimer::timeout, this, &UIController::startRealTimeFrequency);
        m_realTimeTimer.start(m_realTimeInterval_ms);
    }
}

void UIController::startRealTimeConsumption()
{
    auto data = m_realTimeTimer.isActive()
            ? m_fingridClient.realTimeConsumption(m_lineModel->getGraph())
            : m_fingridClient.realTimeConsumption(std::nullopt);
    m_lineModel->clear();
    data.error ? m_lineModel->setError(data.errorMessage) : m_lineModel->addGraph(data.lineGraph);
    m_lineModel->publish();

    if (!m_realTimeTimer.isActive())
    {
        connect(&m_realTimeTimer, &QTimer::timeout, this, &UIController::startRealTimeConsumption);
        m_realTimeTimer.start(m_realTimeInterval_ms);
    }
}

void UIController::startRealTimeImport()
{
    auto data = m_realTimeTimer.isActive()
            ? m_fingridClient.realTimeEnergyImport(m_lineModel->getGraph())
            : m_fingridClient.realTimeEnergyImport(std::nullopt);
    m_lineModel->clear();
    data.error ? m_lineModel->setError(data.errorMessage) : m_lineModel->addGraph(data.lineGraph);
    m_lineModel->publish();

    if (!m_realTimeTimer.isActive())
    {
        connect(&m_realTimeTimer, &QTimer::timeout, this, &UIController::startRealTimeImport);
        m_realTimeTimer.start(m_realTimeInterval_ms);
    }
}

void UIController::updateDictionary(const QString& location)
{
    if ((m_lineModel->graphCount() > 0 || m_pieModel->graphCount() > 0)
            && m_locationAutoComp.isEmpty())
    {
        m_autoCompleter->addSuggestion(location);
    }
}

void UIController::updateSavedDatasetsModel()
{
    m_savedDatasetsModel->setStringList(m_fileIO->savedDatasets());
}
