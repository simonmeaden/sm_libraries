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
#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QFrame>
#include <QTimer>
#include <QPainter>
#include <QDateTime>

class ClockWidget : public QFrame
{
public:
  explicit ClockWidget(QWidget* parent = nullptr);

  bool isShowing();
  void showClock(bool showClock);
  void setClockFrame(QFrame::Shape style);

  bool showSeconds() const;
  void setShowSeconds(bool value);

  void paintEvent(QPaintEvent* evt) override;
  int calculateRequiredWidth(int w);

  QSize sizeHint() const override;
  void setSizeHint(const QSize& size);

protected:
  void nextSecond();

private:
  QTimer* m_clockTimer;
  QRect m_rect;
  bool m_showSeconds, m_showClock;
  QString m_nowString;
  QSize m_size;
  //   QString m_stylesheet;

  static const QString WITHSECONDS;
  static const QString NOSECONDS;
  const static int CLOCK_TIME = 1000;
};


#endif // CLOCKWIDGET_H
