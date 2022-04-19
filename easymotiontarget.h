#ifndef EASYMOTIONTARGET_H
#define EASYMOTIONTARGET_H

#include <QObject>
#include <QVector>
#include <QTextDocument>
#include <QTextBlock>

namespace EasyMotion
{

template <class Editor>
QPair<int, int> getFirstAndLastVisiblePosition(Editor *editor)
{
  QTextCursor cursor = editor->textCursor();
  QTextDocument *doc = editor->document();
  int currentLine = doc->findBlock(cursor.position()).blockNumber();
  int cursorHeight = editor->cursorRect().height();
  int lineCountToFirstVisibleLine = editor->cursorRect().top() / cursorHeight;
  int firstVisibleLineNum = currentLine - lineCountToFirstVisibleLine;
  if (firstVisibleLineNum < 0) {
    firstVisibleLineNum = 0;
  }
  int maxLineNumOnScreen = (editor->viewport()->height() / cursorHeight);
  if (maxLineNumOnScreen < 1) {
    maxLineNumOnScreen = 1;
  }
  int firstPos = doc->findBlockByNumber(firstVisibleLineNum).position();
  int lastVisibleLineNum = firstVisibleLineNum + maxLineNumOnScreen - 1;
  QTextBlock lastVisibleTextBlock = doc->findBlockByNumber(lastVisibleLineNum);
  if (!lastVisibleTextBlock.isValid()) {
    lastVisibleTextBlock = doc->lastBlock();
  }
  int lastPos = lastVisibleTextBlock.position() + lastVisibleTextBlock.length() - 1;
  return QPair<int, int>(firstPos, lastPos);
}

class EasyMotionTarget : public QObject
{
    Q_OBJECT
public:
    EasyMotionTarget(void);

    template <class QEditor>
    void searchTargetFromCurrentLine(QEditor *editor)
    {
        m_targetPos.clear();
        if (editor == NULL) {
            return;
        }
        m_currentGroup = 0;
        QTextDocument *doc = editor->document();
        int cursorPos = editor->textCursor().position();
        QTextBlock currentLineBlock = doc->findBlock(cursorPos);
        int firstPos = currentLineBlock.position();
        int lastPos = firstPos + currentLineBlock.length() - 1;
        for (int offset = 1; cursorPos - offset >= firstPos || cursorPos + offset <= lastPos; offset++) {
            if (cursorPos + offset <= lastPos) {
                m_targetPos << (cursorPos + offset);
            }
            if (cursorPos - offset >= firstPos) {
                m_targetPos << (cursorPos - offset);
            }
        }
    }

    template <class QEditor>
    void searchTargetFromScreen(QEditor *editor, const QChar &target)
    {
        m_targetPos.clear();
        if (editor == NULL) {
            return;
        }
        m_currentGroup = 0;
        m_targetChar = target;
        QTextDocument *doc = editor->document();
        int cursorPos = editor->textCursor().position();
        QPair<int, int> visibleRange = getFirstAndLastVisiblePosition(editor);
        int  firstPos = visibleRange.first;
        int lastPos = visibleRange.second;
        bool notCaseSensative = target.category() != QChar::Letter_Uppercase;
        for (int offset = 1; cursorPos - offset >= firstPos || cursorPos + offset <= lastPos; offset++) {
            if (cursorPos + offset <= lastPos) {
                QChar c = doc->characterAt(cursorPos + offset);
                if (notCaseSensative) {
                    c = c.toLower();
                }
                if (c == target) {
                    m_targetPos << (cursorPos + offset);
                }
            }
            if (cursorPos - offset >= firstPos) {
                QChar c = doc->characterAt(cursorPos - offset);
                if (notCaseSensative) {
                    c = c.toLower();
                }
                if (c == target) {
                    m_targetPos << (cursorPos - offset);
                }
            }
        }
    }

    int size() const;
    bool isEmpty() const;
    void nextGroup(void);
    void previousGroup(void);
    void clear();
    int getFirstTargetIndex(void) const;
    int getLastTargetIndex(void) const;
    QPair<int, QChar> getTarget(int i) const;
    int getGroupNum(void);
    QChar getTargetChar(void) const;
    int getTargetPos(const QChar &c) const;

private:
    int parseCode(const QChar &c) const;
    void initCode(void);
    enum {
        LowerLetterCaseStart = 0,
        DigitStart = 26,
        UpperLetterCaseStart = 36,
        GroupSize = 62
    };
    int m_currentGroup;
    QChar m_targetChar;
    QVector<int> m_targetPos;
    QVector<QChar> m_code;
};

}

#endif // EASYMOTIONTARGET_H
