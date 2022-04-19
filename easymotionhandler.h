#ifndef EASYMOTIONHANDLER_H
#define EASYMOTIONHANDLER_H

#include <QObject>
#include <QKeyEvent>
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

#include "easymotiontarget.h"

namespace EasyMotion
{

class EasyMotionHandler : public QObject
{
    Q_OBJECT

public:
    EasyMotionHandler(QObject *parent = 0);
    ~EasyMotionHandler();

public slots:
    void easyMotionForCurrentLineTriggered(void);
    void easyMotionForEntireScreenTriggered(void);

private slots:
    void doInstallEventFilter();
    void findFakeVimStatusWidget();

private:
    void installEventFilter();
    void initEasyMotion();
    void resetEasyMotion(void);
    bool isVisualMode() const;
    bool eventFilter(QObject *obj, QEvent *event);
    bool handleKeyPress(QKeyEvent *e);
    bool handlePaintEvent(QPaintEvent *e);
    void setTextPosition(QRect &rect);
    bool isModifierKey(int key);
    bool setEditor(Core::IEditor *e);
    void unsetEditor();

    enum EasyMotionState {
        DefaultState,
        EasyMotionTriggered,
        WaitForInputTargetCode
    };
    Core::IEditor *m_currentEditor;
    QPlainTextEdit *m_plainEdit;
    QTextEdit *m_textEdit;
    QLabel *m_fakeVimStatusWidget;
    EasyMotionState m_state;
    EasyMotion::EasyMotionTarget m_target;
    int m_easyMotionSearchRange;
    enum SearchRange {
        EntireScreen,
        CurrentLine
    };
};

}

#endif // EASYMOTIONHANDLER_H
