/*
   Copyright 2020 Simon Meaden

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/
#include "messagewidget.h"

const qreal MessageWidget::DEF_MARQUEE_TIME = 500;

MessageWidget::MessageWidget(QWidget* parent)
   : QFrame(parent)
   , m_marqueeTime(DEF_MARQUEE_TIME)
   , m_showMessages(false)
   , m_marqueeEnabled(false)
   , m_marqueeTimer(nullptr)
   , m_marqueePos(0)
{}

void MessageWidget::showMessages(bool show)
{
   m_showMessages = show;

   if (m_showMessages) {

      startTimeoutIfRequired(m_timeout);
      startMarqueeIfRequired();

      update();

   } else {
      stopTimeoutIfRequired();
      stopMarqueeIfRequired();
   }
}

bool MessageWidget::isShowing()
{
   return m_showMessages;
}

void MessageWidget::stopTimeoutIfRequired()
{
   if (m_timeoutTimer && m_timeoutTimer->isActive()) {
      m_timeoutTimer->stop();
      m_timeoutTimer->deleteLater();
      m_timeoutTimer = nullptr;
   }
}

void MessageWidget::startTimeoutIfRequired(uint timeout)
{
   if (timeout <= 0) {
      stopTimeoutIfRequired();

   } else {
      if (m_timeoutTimer) {
         if (m_timeoutTimer->isActive()) {
            // reset if overwriting earlier message.
            m_timeoutTimer->stop();
         }

      } else {
         m_timeoutTimer = new QTimer(this);
         connect(m_timeoutTimer, &QTimer::timeout, this, &MessageWidget::timedout);
      }

      m_timeoutTimer->start(timeout);
   }
}

QString MessageWidget::cleanMessage(const QString& message)
{
   QString cleanMsg = message;
   int pos = cleanMsg.indexOf('\n');

   while (pos != -1) {
      cleanMsg.remove(pos, 1);
      pos = cleanMsg.indexOf('\n');
   }

   return cleanMsg;
}

void MessageWidget::setMessage(const QString& message, quint32 timeout)
{
   // remove all new line characters, only single line message.
   m_messageText = cleanMessage(message);
   m_timeout = timeout;
   m_marqueePos = 0;

   if (m_showMessages) {

      startTimeoutIfRequired(m_timeout);
      startMarqueeIfRequired();

      update();
   }
}

void MessageWidget::timedout()
{
   if (m_timeoutTimer) {
      if (m_timeoutTimer->isActive()) {
         m_timeoutTimer->stop();
         m_timeoutTimer->deleteLater();
         m_timeoutTimer = nullptr;
      }
   }
}

bool MessageWidget::isMarqueeEnabled()
{
   return m_marqueeEnabled;
}

void MessageWidget::startMarqueeIfRequired()
{
   if (m_marqueeTimer) {
      if (m_marqueeTimer->isActive()) {
         return;

      } else {
         m_marqueeTimer->start(m_marqueeTime);
      }

   } else {
      m_marqueeTimer = new QTimer(this);
      connect(m_marqueeTimer,
              &QTimer::timeout,
              this,
              &MessageWidget::updateMarquee,
              Qt::UniqueConnection);
      m_marqueeTimer->start(m_marqueeTime);
   }
}

void MessageWidget::stopMarqueeIfRequired()
{
   m_marqueeTimer->stop();
   m_marqueeTimer->deleteLater();
   m_marqueeTimer = nullptr;
}

void MessageWidget::enableMarquee(bool enable)
{
   m_marqueeEnabled = enable;

   if (m_showMessages && enable) {
      startMarqueeIfRequired();

   } else {
      if (m_marqueeTimer) {
         stopMarqueeIfRequired();
      }
   }
}

void MessageWidget::setMarqueeSpeed(qreal charPerSecond)
{
   m_marqueeTime = 1000.0 / charPerSecond;
}

void MessageWidget::setMessageFrame(QFrame::Shape style)
{
   setFrameStyle(style);
}

void MessageWidget::clearMessage()
{
   m_messageText.clear();
   update();
}

void MessageWidget::paintEvent(QPaintEvent* evt)
{
   QFrame::paintEvent(evt);
   QPainter painter(this);
   QString text;
   QFontMetrics fm = painter.fontMetrics();
   QRect msgRect = rect();

   if (m_showMessages) {
      int h = fm.height(); // TOD adjust font Y ??
      int msgWidth = fm.horizontalAdvance(m_messageText);

      if (msgWidth > msgRect.width()) {
         if (isMarqueeEnabled()) { // text is marqueed

            QString messageText =
               m_messageText + "\u2026 "; // ellipsis ... character followed by a space.
            int pos = m_marqueePos % messageText.length();
            text = messageText.mid(pos).append(messageText.left(pos));

         } else { // text is not marqueed so just put an ellipsis at the end
            text =
               fm.elidedText(m_messageText, Qt::ElideRight, msgRect.width());
         }

      }

      painter.drawText(
         msgRect.x() + 10, msgRect.y() + msgRect.height() - 5, text);
   }
}

void MessageWidget::setSizeHint(QSize size)
{
   if (m_size != size) {
      m_size = size;
      updateGeometry();
   }
}

QSize MessageWidget::sizeHint() const
{
   return m_size;
}

void MessageWidget::updateMarquee()
{
   m_marqueePos++;
   update();
}

//void MessageWidget::resetMessageData(const QString& message)
//{
//}
