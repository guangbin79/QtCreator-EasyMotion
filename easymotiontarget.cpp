#include "easymotiontarget.h"

namespace EasyMotion
{

EasyMotionTarget::EasyMotionTarget(void)
{
    initCode();
    m_targetPos.clear();
}

int EasyMotionTarget::size() const
{
    return m_targetPos.size();
}

bool EasyMotionTarget::isEmpty() const
{
    return m_targetPos.size() == 0;
}

void EasyMotionTarget::nextGroup(void)
{
    m_currentGroup++;
    if (m_currentGroup >= getGroupNum()) {
        m_currentGroup = 0;
    }
}

void EasyMotionTarget::previousGroup(void)
{
    m_currentGroup--;
    if (m_currentGroup  < 0) {
        m_currentGroup = getGroupNum() - 1;
        if (m_currentGroup < 0) {
            m_currentGroup = 0;
        }
    }
}

void EasyMotionTarget::clear()
{
    m_currentGroup = 0;
    m_targetPos.clear();
}

int EasyMotionTarget::getFirstTargetIndex(void) const
{
    return m_currentGroup * GroupSize;
}

int EasyMotionTarget::getLastTargetIndex(void) const
{
    int onePastLastIndex = m_currentGroup * GroupSize + GroupSize;
    if (onePastLastIndex > m_targetPos.size()) {
        onePastLastIndex = m_targetPos.size();
    }
    return onePastLastIndex;
}

QPair<int, QChar> EasyMotionTarget::getTarget(int i) const
{
    if (i < 0 || i > m_targetPos.size()) {
        return QPair<int, QChar>(int(-1), QChar(0));
    } else {
        return QPair<int, QChar>(m_targetPos[i], m_code[i % GroupSize]);
    }
}

int EasyMotionTarget::getGroupNum(void)
{
    if (m_targetPos.size() == 0) {
        return 0;
    } else {
        return (m_targetPos.size() - 1) / GroupSize + 1;
    }
}

QChar EasyMotionTarget::getTargetChar(void) const
{
    return m_targetChar;
}

int EasyMotionTarget::getTargetPos(const QChar &c) const
{
    int pos = parseCode(c);
    if (pos < 0) {
        return pos;
    } else {
        pos += m_currentGroup * GroupSize;
        if (pos < m_targetPos.size()) {
            return m_targetPos[pos];
        } else {
            return -1;
        }
    }
}

int EasyMotionTarget::parseCode(const QChar &c) const
{
    int index = -1;
    if (c.isLower()) {
        index = LowerLetterCaseStart + c.unicode() - ushort('a');
    } else if (c.isDigit()) {
        index = DigitStart + c.unicode() - ushort('0');
    } else if (c.isUpper()) {
        index = UpperLetterCaseStart + c.unicode() - ushort('A');
    }
    return index;
}

void EasyMotionTarget::initCode(void)
{
    m_code.reserve(GroupSize);
    for (int i = 0; i < 26; ++i) {
        m_code << QChar(i + 'a');
    }
    for (int i = 0; i < 10; ++i) {
        m_code << QChar(i + '0');
    }
    for (int i = 0; i < 26; ++i) {
        m_code << QChar(i + 'A');
    }
}

}
