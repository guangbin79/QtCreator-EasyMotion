#include "easymotionplugin.h"
#include "easymotionconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <texteditor/texteditor.h>
#include <extensionsystem/pluginmanager.h>
#include <QListWidget>
#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

#include <QtPlugin>
#include <QObject>
#include <QApplication>
#include <QPlainTextEdit>
#include <QLabel>
#include <QStatusBar>
#include <QDebug>
#include <QPainter>
#include <QString>
#include <QTextBlock>
#include <QChar>
#include <QTextDocument>
#include <QTextBlock>
#include <QPair>
#include <algorithm>

using namespace EasyMotion::Internal;
using namespace EasyMotion;
using namespace Core;

EasyMotionPlugin::EasyMotionPlugin()
  : m_handler(new EasyMotionHandler)
{
  // Create your members
}

EasyMotionPlugin::~EasyMotionPlugin()
{
  // Unregister objects from the plugin manager's object pool
  // Delete members
  delete m_handler;
}

bool EasyMotionPlugin::initialize(const QStringList &arguments, QString *errorString)
{
  // Register objects in the plugin manager's object pool
  // Load settings
  // Add actions to menus
  // Connect to other plugins' signals
  // In the initialize function, a plugin can be sure that the plugins it
  // depends on have initialized their members.
  Q_UNUSED(arguments)
  Q_UNUSED(errorString)
  QAction *easyMotionSearchEntireScreen = new QAction(tr("Search entire screen"), this);
  Core::Command *searchScreenCmd = Core::ActionManager::registerAction(easyMotionSearchEntireScreen , Constants::SEARCH_SCREEN_ID,
                                   Core::Context(Core::Constants::C_GLOBAL));
  searchScreenCmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+;")));
  connect(easyMotionSearchEntireScreen , SIGNAL(triggered()), m_handler, SLOT(easyMotionForEntireScreenTriggered()));
  return true;
}

void EasyMotionPlugin::extensionsInitialized()
{
  // Retrieve objects from the plugin manager's object pool
  // In the extensionsInitialized function, a plugin can be sure that all
  // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag EasyMotionPlugin::aboutToShutdown()
{
  // Save settings
  // Disconnect from signals that are not needed during shutdown
  // Hide UI (if you add UI that is not in the main window directly)
  return SynchronousShutdown;
}

//Q_EXPORT_PLUGIN2(EasyMotion, EasyMotionPlugin)




