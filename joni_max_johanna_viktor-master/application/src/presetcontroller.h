#pragma once

#include <QObject>
#include <QStringListModel>

#include <memory>

class UIController;
class FileIO;

/**
 * @brief The Preset handles reading and writing state of UIControllers as presets.
 */
class PresetController : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Abstraction for the state of the user interface state defined by UIController.
     */
    struct UIControllerState
    {
        QString chartType;
        QString location;
        QString fileName;
        bool checkBox0;
        bool checkBox1;
        bool checkBox2;
    };

    /**
     * @brief Abstraction preset with states for each UIController.
     */
    struct Preset
    {
        UIControllerState left;
        UIControllerState right;
    };

    /**
     * @brief Constructor.
     * @param leftUIController: Shared pointer to left UIController.
     * @param rightUIController: Shared pointer to right UIController.
     * @param fileIO: Shared pointer to FileIO.
     * @param parent: Pointer to parent QObject.
     */
    explicit PresetController(std::shared_ptr<UIController> leftUIcontroller,
            std::shared_ptr<UIController> rightUIcontroller,
            std::shared_ptr<FileIO> fileIO,
            QObject* parent = nullptr);

    /**
     * @brief Saves UI preset based on current state of UI controllers.
     * @param name: Name to save preset with.
     */
    Q_INVOKABLE void savePreset(const QString& name);

    /**
     * @brief Loads preset and sets UIController to correspoinding state.
     * @param name: Name of the preset to load.
     */
    Q_INVOKABLE void loadPreset(const QString& name);

    /**
     * @brief Returns pointer to model with names of saved data sets.
     * @return QStringListModel: Model of saved data set names.
     */
    Q_INVOKABLE QStringListModel* savedPresetsModel();

private:
    /**
     * @brief Reads the state of given UIController to UICotrollerState struct.
     * @param controller: Pointer to UIController.
     * @return UIControllerState: State of the given UIController.
     */
    UIControllerState readUiControllerState(std::shared_ptr<UIController> controller) const;

    /**
     * @brief Sets the state of given UIController to given state.
     * @param controller: Pointer to UIController.
     * @param state: State to put UIController in.
     */
    void setUiControllerState(std::shared_ptr<UIController> controller, UIControllerState state);

    /**
     * @brief Creates models that class PresetController uses.
     */
    void createModels();

    /**
     * @brief Updates presetFilesModel with current files.
     */
    void updateSavedPresetsModel();

    std::shared_ptr<UIController> m_leftController = nullptr;
    std::shared_ptr<UIController> m_rightController = nullptr;
    std::shared_ptr<FileIO> m_fileIO = nullptr;
    std::unique_ptr<QStringListModel> m_savedPresetsModel = nullptr;
};
