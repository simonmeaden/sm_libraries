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
#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QFrame>
#include <QTimer>
#include <QPainter>
#include <QFontMetrics>

class MessageWidget : public QFrame
{
public:
   explicit MessageWidget(QWidget* parent = nullptr);

   void showMessages(bool show);
   bool isShowing();
   void setMessage(const QString& message, quint32 timeout = 0);
   void setMessageFrame(QFrame::Shape style);
   void clearMessage();

   bool isMarqueeEnabled();
   void enableMarquee(bool enable);
   void setMarqueeSpeed(qreal charPerSecond);

   void paintEvent(QPaintEvent* evt) override;
   void setSizeHint(QSize size);
   QSize sizeHint() const override;

   const static qreal DEF_MARQUEE_TIME;

protected:
private:
   int m_marqueeTime;
   quint32 m_timeout;
   bool m_showMessages, m_marqueeEnabled;
   QTimer* m_marqueeTimer, *m_timeoutTimer;
   QString m_messageText;
   int m_marqueePos;
   QSize m_size;

   void updateMarquee();
   void timedout();

//   void resetMessageData(const QString& message);
   void startMarqueeIfRequired();

   //   void startTimeoutTimer();
   void stopMarqueeIfRequired();
   void startTimeoutIfRequired(uint timeout);
   QString cleanMessage(const QString &message);
   void stopTimeoutIfRequired();
};

#endif // MESSAGEWIDGET_H
