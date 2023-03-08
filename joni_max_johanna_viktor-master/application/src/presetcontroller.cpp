#include "presetcontroller.h"
#include "fileio.h"
#include "uicontroller.h"

PresetController::PresetController(std::shared_ptr<UIController> leftUIcontroller,
        std::shared_ptr<UIController> rightUIcontroller,
        std::shared_ptr<FileIO> fileIO,
        QObject* parent) :
    QObject(parent),
    m_leftController(leftUIcontroller),
    m_rightController(rightUIcontroller),
    m_fileIO(fileIO)
{
    createModels();
}

void PresetController::savePreset(const QString& name)
{
    if (name.isEmpty())
        return;

    auto left = readUiControllerState(m_leftController);
    auto right = readUiControllerState(m_rightController);
    m_fileIO->savePreset(name, Preset{left, right});
    updateSavedPresetsModel();
}

void PresetController::loadPreset(const QString& name)
{
    if (name.isEmpty())
        return;

    auto state = m_fileIO->readPreset(name);
    setUiControllerState(m_leftController, state.left);
    setUiControllerState(m_rightController, state.right);
}

QStringListModel* PresetController::savedPresetsModel()
{
    return m_savedPresetsModel.get();
}

PresetController::UIControllerState PresetController::readUiControllerState(
        std::shared_ptr<UIController> controller) const
{
    return UIControllerState{controller->m_chartType,
            controller->m_location,
            controller->m_fileName,
            controller->m_checkBox0,
            controller->m_checkBox1,
            controller->m_checkBox2};
}

void PresetController::setUiControllerState(std::shared_ptr<UIController> controller,
        UIControllerState state)
{
    controller->m_chartType = state.chartType;
    emit controller->chartTypeChanged();
    controller->m_location = state.location;
    emit controller->locationChanged();
    controller->m_fileName = state.fileName;
    emit controller->fileNameChanged();
    controller->m_startDate = QDate::currentDate();
    controller->m_endDate = QDate::currentDate();
    emit controller->dateChanged();
    controller->m_checkBox0 = state.checkBox0;
    controller->m_checkBox1 = state.checkBox1;
    controller->m_checkBox2 = state.checkBox2;
    emit controller->checkBoxesChanged();
    controller->search();
}

void PresetController::createModels()
{
    m_savedPresetsModel = std::make_unique<QStringListModel>(new QStringListModel(this));
    qRegisterMetaType<QStringListModel*>("QStringListModel*");
    updateSavedPresetsModel();
}

void PresetController::updateSavedPresetsModel()
{
    m_savedPresetsModel->setStringList(m_fileIO->savedPresets());
}
