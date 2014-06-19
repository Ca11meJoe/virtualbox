/** @file
 * VBox Qt GUI - UIExtraDataManager class declaration.
 */

/*
 * Copyright (C) 2010-2014 Oracle Corporation
 *
 * This file is part of VirtualBox Open Source Edition (OSE), as
 * available from http://www.virtualbox.org. This file is free software;
 * you can redistribute it and/or modify it under the terms of the GNU
 * General Public License (GPL) as published by the Free Software
 * Foundation, in version 2 as it comes in the "COPYING" file of the
 * VirtualBox OSE distribution. VirtualBox OSE is distributed in the
 * hope that it will be useful, but WITHOUT ANY WARRANTY of any kind.
 */

#ifndef ___UIExtraDataManager_h___
#define ___UIExtraDataManager_h___

/* Qt includes: */
#include <QObject>
#include <QMap>

/* GUI includes: */
#include "UIExtraDataDefs.h"

/* COM includes: */
#include "CEventListener.h"

/* Forward declarations: */
class UIExtraDataEventHandler;

/* Type definitions: */
typedef QMap<QString, QString> ExtraDataMap;

/** Singleton QObject extension
  * providing GUI with corresponding extra-data values,
  * and notifying it whenever any of those values changed. */
class UIExtraDataManager : public QObject
{
    Q_OBJECT;

    /** Extra-data Manager constructor. */
    UIExtraDataManager();
    /** Extra-data Manager destructor. */
    ~UIExtraDataManager();

signals:

    /** Notifies about GUI language change. */
    void sigLanguageChange(QString strLanguage);

    /** Notifies about Selector UI keyboard shortcut change. */
    void sigSelectorUIShortcutChange();
    /** Notifies about Runtime UI keyboard shortcut change. */
    void sigRuntimeUIShortcutChange();

    /** Notifies about HID LEDs synchronization state change. */
    void sigHidLedsSyncStateChange(bool fEnabled);

#ifdef RT_OS_DARWIN
    /** Mac OS X: Notifies about 'presentation mode' status change. */
    void sigPresentationModeChange(bool fEnabled);
    /** Mac OS X: Notifies about 'dock icon' appearance change. */
    void sigDockIconAppearanceChange(bool fEnabled);
#endif /* RT_OS_DARWIN */

public:

    /** Static Extra-data Manager instance/constructor. */
    static UIExtraDataManager* instance();
    /** Static Extra-data Manager destructor. */
    static void destroy();

    /** Returns version for which user wants to prevent BETA warning. */
    QString preventBETAwarningForVersion() const;

#ifdef VBOX_GUI_WITH_NETWORK_MANAGER
    /** Returns whether we should allow Application Update. */
    bool shouldWeAllowApplicationUpdate() const;
    /** Returns last Application Update date. */
    QString applicationUpdateData() const;
    /** Defines last Application Update date as @a strValue. */
    void setApplicationUpdateData(const QString &strValue);
    /** Returns Application Update check counter. */
    qulonglong applicationUpdateCheckCounter() const;
    /** Increments Application Update check counter. */
    void incrementApplicationUpdateCheckCounter();
#endif /* VBOX_GUI_WITH_NETWORK_MANAGER */

    /** Returns shortcut overrides for shortcut-pool with @a strPoolExtraDataID. */
    QStringList shortcutOverrides(const QString &strPoolExtraDataID) const;

    /** Returns recent hard-drive folder. */
    QString recentFolderForHardDrives() const;
    /** Returns recent optical-disk folder. */
    QString recentFolderForOpticalDisks() const;
    /** Returns recent floppy-disk folder. */
    QString recentFolderForFloppyDisks() const;
    /** Defines recent hard-drive folder as @a strValue. */
    void setRecentFolderForHardDrives(const QString &strValue);
    /** Defines recent optical-disk folder as @a strValue. */
    void setRecentFolderForOpticalDisks(const QString &strValue);
    /** Defines recent floppy-disk folder as @a strValue. */
    void setRecentFolderForFloppyDisks(const QString &strValue);

    /** Returns recent hard-drive list. */
    QStringList recentListOfHardDrives() const;
    /** Returns recent optical-disk list. */
    QStringList recentListOfOpticalDisks() const;
    /** Returns recent floppy-disk list. */
    QStringList recentListOfFloppyDisks() const;
    /** Defines recent hard-drive list as @a value. */
    void setRecentListOfHardDrives(const QStringList &value);
    /** Defines recent optical-disk list as @a value. */
    void setRecentListOfOpticalDisks(const QStringList &value);
    /** Defines recent floppy-disk list as @a value. */
    void setRecentListOfFloppyDisks(const QStringList &value);

    /** Returns list of the supressed messages for the Message/Popup center frameworks. */
    QStringList suppressedMessages() const;
    /** Defines list of the supressed messages for the Message/Popup center frameworks as @a value. */
    void setSuppressedMessages(const QStringList &value);

    /** Returns list of the messages for the Message/Popup center frameworks with inverted check-box state. */
    QStringList messagesWithInvertedOption() const;

    /** Returns mode (basic/expert) for wizard of @a type. */
    WizardMode modeForWizard(WizardType type);
    /** Defines @a mode (basic/expert) for wizard of @a type. */
    void setModeForWizard(WizardType type, WizardMode mode);

    /** Returns selector-window geometry using @a pHintWidget as the hint. */
    QRect selectorWindowGeometry(QWidget *pHintWidget = 0) const;
    /** Returns whether selector-window should be maximized or not. */
    bool isSelectorWindowShouldBeMaximized() const;
    /** Defines selector-window geometry to passed @a geometry which is @a fMaximized. */
    void setSelectorWindowGeometry(const QRect &geometry, bool fMaximized);

    /** Returns selector-window splitter hints. */
    QList<int> selectorWindowSplitterHints() const;
    /** Defines selector-window splitter @a hints. */
    void setSelectorWindowSplitterHints(const QList<int> &hints);

    /** Returns whether selector-window tool-bar visible. */
    bool selectorWindowToolBarVisible() const;
    /** Defines whether selector-window tool-bar @a fVisible. */
    void setSelectorWindowToolBarVisible(bool fVisible);
    /** Returns whether selector-window status-bar visible. */
    bool selectorWindowStatusBarVisible() const;
    /** Defines whether selector-window status-bar @a fVisible. */
    void setSelectorWindowStatusBarVisible(bool fVisible);

    /** Clears all the existing selector-window chooser-pane' group definitions. */
    void clearSelectorWindowGroupsDefinitions();
    /** Returns selector-window chooser-pane' groups definitions for passed @a strGroupID. */
    QStringList selectorWindowGroupsDefinitions(const QString &strGroupID) const;
    /** Defines selector-window chooser-pane' groups definitions for passed @a strGroupID as @a definitions. */
    void setSelectorWindowGroupsDefinitions(const QString &strGroupID, const QStringList &definitions);

    /** Returns last item chosen in selector-window chooser-pane. */
    QString selectorWindowLastItemChosen() const;
    /** Defines last item chosen in selector-window chooser-pane as @a strItemID. */
    void setSelectorWindowLastItemChosen(const QString &strItemID);

    /** Returns selector-window details-pane elements. */
    QMap<DetailsElementType, bool> selectorWindowDetailsElements();
    /** Defines selector-window details-pane @a elements. */
    void setSelectorWindowDetailsElements(const QMap<DetailsElementType, bool> &elements);

    /** Returns selector-window preview update interval. */
    PreviewUpdateIntervalType selectorWindowPreviewUpdateInterval() const;
    /** Defines selector-window preview update @a interval. */
    void setSelectorWindowPreviewUpdateInterval(PreviewUpdateIntervalType interval);

    /** Returns geometry for machine-window with @a uScreenIndex in @a visualStateType. */
    QRect machineWindowGeometry(UIVisualStateType visualStateType, ulong uScreenIndex, const QString &strId) const;
    /** Returns whether machine-window with @a uScreenIndex in @a visualStateType should be maximized or not. */
    bool isMachineWindowShouldBeMaximized(UIVisualStateType visualStateType, ulong uScreenIndex, const QString &strId) const;
    /** Defines geometry for machine-window with @a uScreenIndex in @a visualStateType as @a geometry and @a fMaximized. */
    void setMachineWindowGeometry(UIVisualStateType visualStateType, ulong uScreenIndex, const QRect &geometry, bool fMaximized, const QString &strId);

    /** Returns last guest-screen size-hint for screen with @a uScreenIndex. */
    QSize lastGuestSizeHint(ulong uScreenIndex, const QString &strId) const;
    /** Defines last guest-screen size-hint for screen with @a uScreenIndex as @a size. */
    void setLastGuestSizeHint(ulong uScreenIndex, const QSize &size, const QString &strId);
    /** Returns whether guest size hint was for full or seamless screen with @a uScreenIndex. */
    bool wasLastGuestSizeHintForFullScreen(ulong uScreenIndex, const QString &strId) const;
    /** Defines whether guest size hint @a fWas for full or seamless screen with @a uScreenIndex. */
    void markLastGuestSizeHintAsFullScreen(ulong uScreenIndex, bool fWas, const QString &strId);

    /** Returns whether this machine started for the first time. */
    bool isFirstRun(const QString &strId) const;
    /** Defines whether this machine started for the first time. */
    void setFirstRun(bool fIsFirstRun, const QString &strId);

    /** Returns whether we should show machine. */
    bool shouldWeShowMachine(const QString &strID) const;
    /** Returns whether we should show machine details. */
    bool shouldWeShowMachineDetails(const QString &strID) const;

    /** Returns whether we should allow machine reconfiguration. */
    bool shouldWeAllowMachineReconfiguration(const QString &strID) const;
    /** Returns whether we should allow machine snapshot operations. */
    bool shouldWeAllowMachineSnapshotOperations(const QString &strID) const;

    /** Returns whether we should automatically mount/unmount guest-screens. */
    bool shouldWeAutoMountGuestScreens(const QString &strID) const;

    /** Returns restricted Runtime UI menu types. */
    RuntimeMenuType restrictedRuntimeMenuTypes(const QString &strID) const;
#ifdef Q_WS_MAC
    /** Mac OS X: Returns restricted Runtime UI action types for Application menu. */
    RuntimeMenuApplicationActionType restrictedRuntimeMenuApplicationActionTypes(const QString &strID) const;
#endif /* Q_WS_MAC */
    /** Returns restricted Runtime UI action types for Machine menu. */
    RuntimeMenuMachineActionType restrictedRuntimeMenuMachineActionTypes(const QString &strID) const;
    /** Returns restricted Runtime UI action types for View menu. */
    RuntimeMenuViewActionType restrictedRuntimeMenuViewActionTypes(const QString &strID) const;
    /** Returns restricted Runtime UI action types for Devices menu. */
    RuntimeMenuDevicesActionType restrictedRuntimeMenuDevicesActionTypes(const QString &strID) const;
#ifdef VBOX_WITH_DEBUGGER_GUI
    /** Returns restricted Runtime UI action types for Debugger menu. */
    RuntimeMenuDebuggerActionType restrictedRuntimeMenuDebuggerActionTypes(const QString &strID) const;
#endif /* VBOX_WITH_DEBUGGER_GUI */
    /** Returns restricted Runtime UI action types for Help menu. */
    RuntimeMenuHelpActionType restrictedRuntimeMenuHelpActionTypes(const QString &strID) const;

    /** Returns restricted Runtime UI visual-states. */
    UIVisualStateType restrictedVisualStates(const QString &strID) const;

    /** Returns requested Runtime UI visual-state. */
    UIVisualStateType requestedVisualState(const QString &strID) const;
    /** Defines requested Runtime UI visual-state as @a visualState. */
    void setRequestedVisualState(UIVisualStateType visualState, const QString &strID);

    /** Returns host-screen index corresponding to passed guest-screen @a iGuestScreenIndex. */
    int hostScreenForPassedGuestScreen(int iGuestScreenIndex, const QString &strID);
    /** Defines host-screen index corresponding to passed guest-screen @a iGuestScreenIndex as @a iHostScreenIndex. */
    void setHostScreenForPassedGuestScreen(int iGuestScreenIndex, int iHostScreenIndex, const QString &strID);

    /** Returns whether guest-screen should auto-resize according machine-window size. */
    bool guestScreenAutoResize(const QString &strID) const;
    /** Defines whether guest-screen auto-resize according machine-window size is @a fEnabled. */
    void setGuestScreenAutoResize(bool fEnabled, const QString &strID);

    /** Returns restricted Runtime UI status-bar indicators. */
    QList<IndicatorType> restrictedStatusBarIndicators(const QString &strID) const;

    /** Returns global settings pages. */
    QList<GlobalSettingsPageType> restrictedGlobalSettingsPages() const;
    /** Returns machine settings pages. */
    QList<MachineSettingsPageType> restrictedMachineSettingsPages(const QString &strID) const;

#ifndef Q_WS_MAC
    /** Except Mac OS X: Returns redefined machine-window icon names. */
    QStringList machineWindowIconNames(const QString &strID) const;
    /** Except Mac OS X: Returns redefined machine-window name postfix. */
    QString machineWindowNamePostfix(const QString &strID) const;
#endif /* !Q_WS_MAC */

    /** Returns redefined guru-meditation handler type. */
    GuruMeditationHandlerType guruMeditationHandlerType(const QString &strID) const;

    /** Returns Runtime UI HiDPI optimization type. */
    HiDPIOptimizationType hiDPIOptimizationType(const QString &strID) const;

    /** Returns whether VM should pass CAD to guest. */
    bool passCADtoGuest(const QString &strID) const;

    /** Returns whether VM should perform HID LEDs synchronization. */
    bool hidLedsSyncState(const QString &strID) const;

    /** Returns whether mini-toolbar should be shown for full and seamless screens. */
    bool showMiniToolbar(const QString &strID) const;
    /** Defines whether mini-toolbar should be @a fShown for full and seamless screens. */
    void setShowMiniToolbar(bool fShown, const QString &strID);

    /** Returns whether mini-toolbar should auto-hide itself. */
    bool autoHideMiniToolbar(const QString &strID) const;
    /** Defines whether mini-toolbar should @a fAutoHide itself. */
    void setAutoHideMiniToolbar(bool fAutoHide, const QString &strID);

    /** Returns mini-toolbar alignment. */
    Qt::AlignmentFlag miniToolbarAlignment(const QString &strID) const;
    /** Returns mini-toolbar @a alignment. */
    void setMiniToolbarAlignment(Qt::AlignmentFlag alignment, const QString &strID);

    /** Returns default machine close action. */
    MachineCloseAction defaultMachineCloseAction(const QString &strID) const;
    /** Returns restricted machine close actions. */
    MachineCloseAction restrictedMachineCloseActions(const QString &strID) const;

    /** Returns last machine close action. */
    MachineCloseAction lastMachineCloseAction(const QString &strID) const;
    /** Defines last @a machineCloseAction. */
    void setLastMachineCloseAction(MachineCloseAction machineCloseAction, const QString &strID);

private slots:

    /** Handles 'extra-data change' event: */
    void sltExtraDataChange(QString strMachineID, QString strKey, QString strValue);

private:

    /** Prepare Extra-data Manager. */
    void prepare();
    /** Prepare global extra-data map. */
    void prepareGlobalExtraDataMap();
    /** Prepare extra-data event-handler. */
    void prepareExtraDataEventHandler();
    /** Prepare Main event-listener. */
    void prepareMainEventListener();

    /** Cleanup Extra-data Manager. */
    void cleanup();
    /** Cleanup Main event-listener. */
    void cleanupMainEventListener();
    // /** Cleanup extra-data event-handler. */
    // void cleanupExtraDataEventHandler();
    // /** Cleanup extra-data map. */
    // void cleanupExtraDataMap();

    /** Hot-load machine extra-data map. */
    void hotloadMachineExtraDataMap(const QString &strID) const;

    /** Determines whether feature corresponding to passed @a strKey is allowed.
      * If valid @a strID is set => applies to machine extra-data, otherwise => to global one. */
    bool isFeatureAllowed(const QString &strKey, const QString &strID = m_sstrGlobalID) const;
    /** Determines whether feature corresponding to passed @a strKey is restricted.
      * If valid @a strID is set => applies to machine extra-data, otherwise => to global one. */
    bool isFeatureRestricted(const QString &strKey, const QString &strID = m_sstrGlobalID) const;

    /** Translates bool flag into 'allowed' value. */
    QString toFeatureAllowed(bool fAllowed);
    /** Translates bool flag into 'restricted' value. */
    QString toFeatureRestricted(bool fRestricted);

    /** Returns extra-data value corresponding to passed @a strKey as QString.
      * If valid @a strID is set => applies to machine extra-data, otherwise => to global one. */
    QString extraDataString(const QString &strKey, const QString &strID = m_sstrGlobalID) const;
    /** Defines extra-data value corresponding to passed @a strKey as strValue.
      * If valid @a strID is set => applies to machine extra-data, otherwise => to global one. */
    void setExtraDataString(const QString &strKey, const QString &strValue, const QString &strID = m_sstrGlobalID);

    /** Returns extra-data value corresponding to passed @a strKey as QStringList.
      * If valid @a strID is set => applies to machine extra-data, otherwise => to global one. */
    QStringList extraDataStringList(const QString &strKey, const QString &strID = m_sstrGlobalID) const;
    /** Defines extra-data value corresponding to passed @a strKey as strValue.
      * If valid @a strID is set => applies to machine extra-data, otherwise => to global one. */
    void setExtraDataStringList(const QString &strKey, const QStringList &strValue, const QString &strID = m_sstrGlobalID);

    /** Returns string consisting of @a strBase appended with @a uScreenIndex for the *non-primary* screen-index.
      * If @a fSameRuleForPrimary is 'true' same rule will be used for *primary* screen-index. Used for storing per-screen extra-data. */
    static QString extraDataKeyPerScreen(const QString &strBase, ulong uScreenIndex, bool fSameRuleForPrimary = false);

    /** Singleton Extra-data Manager instance. */
    static UIExtraDataManager *m_pInstance;

    /** Global extra-data ID. */
    static QString m_sstrGlobalID;

    /** Main event-listener instance. */
    CEventListener m_listener;
    /** Extra-data event-handler instance. */
    UIExtraDataEventHandler *m_pHandler;

    /** Extra-data map. */
    mutable QMap<QString, ExtraDataMap> m_data;
};

/** Singleton Extra-data Manager 'official' name. */
#define gEDataManager UIExtraDataManager::instance()

#endif /* !___UIExtraDataManager_h___ */
