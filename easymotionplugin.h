#pragma once

#include "easymotion_global.h"

#include <extensionsystem/iplugin.h>

#include "easymotiontarget.h"
#include "easymotionhandler.h"

namespace EasyMotion {
class EasyMotionHandler;
namespace Internal {

class EasyMotionPlugin : public ExtensionSystem::IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "EasyMotion.json")

public:
  EasyMotionPlugin();
  ~EasyMotionPlugin();

  bool initialize(const QStringList &arguments, QString *errorString);
  void extensionsInitialized();
  ShutdownFlag aboutToShutdown();

private slots:
private:
  EasyMotionHandler* m_handler;
};

} // namespace Internal
} // namespace EasyMotion
