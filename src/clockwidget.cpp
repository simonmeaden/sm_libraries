/*
  Copyright 2020 Simon Meaden

Permission is hereby granted, free of charge, to any person obtaining a copy of this
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify, merge,
  publish, distribute, sublicense, and/or sell copies of the Software, and to permit
                                                                         persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or
  substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
    PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
      SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
        */
#include "clockwidget.h"

const QString ClockWidget::WITHSECONDS = "00:00:00";
const QString ClockWidget::NOSECONDS = "00:00";

ClockWidget::ClockWidget(QWidget* parent)
  : QFrame(parent)
  , m_clockTimer(nullptr)
  , m_showSeconds(false)
{
  //   setStyleSheet("background: yellow;");
}

bool ClockWidget::isShowing()
{
  return m_showClock;
}

void ClockWidget::showClock(bool showClock)
{
  if (showClock != m_showClock) {
    m_showClock = showClock;

    if (showClock) {
      if (m_clockTimer && m_clockTimer->isActive()) {
        return;

      } else {
        if (!m_clockTimer) {
          m_clockTimer = new QTimer(this);
          connect(m_clockTimer, &QTimer::timeout,
                  this, &ClockWidget::nextSecond,
                  Qt::UniqueConnection);
        }

        m_clockTimer->start(CLOCK_TIME);
      }

    } else {
      if (m_clockTimer) {
        if (m_clockTimer->isActive()) {
          m_clockTimer->stop();
        }

        m_clockTimer->deleteLater();
        m_clockTimer = nullptr;
      }
    }
  }
}

void ClockWidget::setClockFrame(QFrame::Shape style=QFrame::NoFrame)
{
    setFrameStyle(style);
}

bool ClockWidget::showSeconds() const
{
  return m_showSeconds;
}

void ClockWidget::setShowSeconds(bool value)
{
  m_showSeconds = value;
  update();
}

void ClockWidget::paintEvent(QPaintEvent* evt)
{
  QFrame::paintEvent(evt);
  QPainter painter(this);

  if (m_showClock) {
    QFontMetrics fm = painter.fontMetrics();
    int h = fm.height();
    int w = fm.horizontalAdvance(m_nowString);
    int x = (m_size.width() - w) / 2;
    int y = m_size.height() - ((m_size.height() - h) / 2);
    painter.drawText(x, y, m_nowString);
  }
}

int ClockWidget::calculateRequiredWidth(/*int x, int y,*/ int w/*, int h*/)
{
  if (w < 0) {
    return -1;
  }

  QFontMetrics fm = fontMetrics();
  int reqWidth;

  // always use WITHSECONDS as it is the longer. Dont want width to change.
  if (m_showSeconds) {
    reqWidth = fm.horizontalAdvance(WITHSECONDS) + 25;

  } else {
    reqWidth = fm.horizontalAdvance(NOSECONDS) + 25;
  }

  if (reqWidth > w) {
    reqWidth = w;
  }

  return reqWidth;
}

QSize ClockWidget::sizeHint() const
{
  return m_size;
}

void ClockWidget::setSizeHint(const QSize& size)
{
  if (m_size != size) {
    m_size = size;
    updateGeometry();
  }
}

void ClockWidget::nextSecond()
{
  QString format = "hh:mm";

  if (m_showSeconds) {
    format += ":ss";
  }

  QDateTime now = QDateTime::currentDateTime();
  m_nowString = now.toString(format);

  update();
}
