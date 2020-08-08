#include "extabwidget_p.h"
#include "extabwidget.h"
#include "extabwidget_p.h"

/// \cond DO_NOT_DOCUMENT
const QString LoginWidget::LOGIN = "Log In";
const QString LoginWidget::LOGOUT = "Log Out";

ExTabWidgetPrivate::ExTabWidgetPrivate(ExTabWidget* parent,
                                       AbstractLoginDialog* customDlg = nullptr)
   : q_ptr(parent)
   , m_wrapper(new WrapperWidget(q_ptr))
   , m_showLogin(false)
     //   , m_showClock(false)
   , m_showMessages(false)
   , m_loginRect(nullptr)
   , m_messageRect(nullptr)
   , m_now(0)
   , m_showFrame(true)
   , m_isInframe(false)
   , m_textColor(QColor("black"))
   , m_background(m_palette.window())
   , m_marquee(false)
{
   m_timeout = 0;
   m_marqueePos = 0;
   q_ptr->setContentsMargins(0, 0, 0, 0);

   if (customDlg) {
      m_wrapper->setLoginType(AbstractLoginDialog::Custom);
      m_wrapper->setCustomLoginDialog(customDlg);
   }

   // send wrapper signals on to ExTabWidget
   q_ptr->connect(m_wrapper, &WrapperWidget::loggedIn, q_ptr, &ExTabWidget::loggedIn);
   q_ptr->connect(m_wrapper, &WrapperWidget::loggedOut, q_ptr, &ExTabWidget::loggedOut);
   q_ptr->connect(m_wrapper, &WrapperWidget::passwordBad, q_ptr, &ExTabWidget::passwordBad);
   q_ptr->connect(m_wrapper, &WrapperWidget::usernameBad, q_ptr, &ExTabWidget::usernameBad);
   q_ptr->connect(m_wrapper, &WrapperWidget::loginBad, q_ptr, &ExTabWidget::loginBad);

   // TODO REMOVE BELOW
   //   q_ptr->tabBar()->setStyleSheet("background: red;");
   //   q_ptr->setStyleSheet("background: green;");
   // TODO UNTIL HERE
}

ExTabWidgetPrivate::~ExTabWidgetPrivate()
{

}


bool ExTabWidgetPrivate::hasCustomLoginDialog()
{
   return m_wrapper->hasCustomLoginDialog();
}

void ExTabWidgetPrivate::setClockFrame(QFrame::Shape style)
{
   // TODO show/hide clock frames
   m_wrapper->setClockFrame(style);
}

QString ExTabWidgetPrivate::loginText() const
{
   return m_wrapper->loginText();
}

void ExTabWidgetPrivate::setLoginText(const QString& text)
{
   m_wrapper->setLoginText(text);
}

QString ExTabWidgetPrivate::logoutText() const
{
   return m_wrapper->logoutText();
}

void ExTabWidgetPrivate::setLogoutText(const QString& text)
{
   m_wrapper->setLogoutText(text);
}

void ExTabWidgetPrivate::showMessageFrame(bool showFrame, QFrame::Shape style)
{
   //   if (!m_messageWidget) {
   //      return;
   //   }

   //   if (showFrame) {
   //      m_messageWidget->setFrameStyle(style);

   //   } else {
   //      m_messageWidget->setFrameStyle(QFrame::NoFrame);
   //   }
}

void ExTabWidgetPrivate::showClock(bool showClock)
{
   m_wrapper->showClock(showClock);
   m_wrapper->calculateWidgetSizes(m_frameX, m_frameY, m_frameWidth, m_frameHeight);
   q_ptr->update();
}

bool ExTabWidgetPrivate::isShowClock() {
  return m_wrapper->isShowClock();
}

void ExTabWidgetPrivate::showMessages(bool messages)
{
  //   m_showMessages = messages;

   //   if (m_showMessages) {
   //      if (!m_messageWidget) {
   //         m_messageWidget = new MessageWidget(q_ptr);
   //      }

   //      if (m_marquee) {
   //         if (m_marqueeTimer) {
   //            startMarqueeTimerIfRequired();

   //         } else {
   //            stopMarqueeTimer();
   //         }
   //      }

   //   } else {
   //      stopMarqueeTimer();
   //   }

   //   q_ptr->update();
}

void ExTabWidgetPrivate::setMarquee(bool marquee)
{
   m_marquee = marquee;

   if (m_showMessages) {
      if (m_marquee) {
         startMarqueeTimerIfRequired();

      } else {
         stopMarqueeTimer();
      }

      q_ptr->update();
   }
}

void ExTabWidgetPrivate::setMarqueeSpeed(qreal charPerSecond)
{
   //   m_marqueeSpeed = int(1000.0 / charPerSecond);
   //   m_marqueeTimer->setInterval(m_marqueeSpeed);
   //   q_ptr->update();
}

void ExTabWidgetPrivate::stopMarqueeTimer()
{
   // TODO
   //   if (m_marqueeTimer) {
   //      m_marqueeTimer->stop();
   //      m_marqueeTimer->deleteLater();
   //      m_marqueeTimer = nullptr;
   //   }
}

void ExTabWidgetPrivate::startMarqueeTimerIfRequired()
{
   //   if (m_marqueeTimer) {
   //      if (m_marqueeTimer->isActive()) {
   //         return;

   //      } else {
   //         m_marqueeTimer->start(MARQUEE_TIME);
   //      }

   //   } else {
   //      m_marqueeTimer = new QTimer(q_ptr);
   //      q_ptr->connect(m_marqueeTimer, &QTimer::timeout,
   //                     q_ptr, &ExTabWidget::updateMarquee,
   //                     Qt::UniqueConnection);
   //      m_marqueeTimer->start(MARQUEE_TIME);
   //   }
}

QBrush ExTabWidgetPrivate::messageBackgroundBrush()
{
   return m_background;
}

QColor ExTabWidgetPrivate::messageTextColor()
{
   return m_textColor;
}

void ExTabWidgetPrivate::updateMarquee()
{
   m_marqueePos++;
   q_ptr->update();
}

void ExTabWidgetPrivate::showLogin(bool showLogin)
{
   m_wrapper->showLogin(showLogin);
   m_wrapper->calculateWidgetSizes(m_frameX, m_frameY, m_frameWidth, m_frameHeight);
   q_ptr->update();
}

AbstractLoginDialog::LoginType ExTabWidgetPrivate::loginType()
{
   return m_wrapper->loginType();
}

bool ExTabWidgetPrivate::isLoggedIn()
{
   return m_wrapper->isLoggedIn();
}

void ExTabWidgetPrivate::setLoginType(AbstractLoginDialog::LoginType type)
{
   m_wrapper->setLoginType(type);
}

void ExTabWidgetPrivate::setCustomLoginDialog(AbstractLoginDialog* loginDlg)
{
   m_wrapper->setCustomLoginDialog(loginDlg);
}

QString ExTabWidgetPrivate::username()
{
   return m_wrapper->username();
}

//bool ExTabWidgetPrivate::mousePressEvent(QMouseEvent* event)
//{
//   //    Q_Q(ExTabWidget);
//   int x = event->x();
//   int y = event->y();

//   if (isInLoginFrame(x, y)) {
//      m_isInframe = true;
////      m_loginPressed = true;

//   } else {
//      m_isInframe = false;
////      m_loginPressed = false;
//   }

//   return m_isInframe;
//}

//bool ExTabWidgetPrivate::mouseReleaseEvent(QMouseEvent* /*event*/)
//{
//   Q_Q(ExTabWidget);

//   if (m_showLogin) {
//      if (m_isInframe) {
//         m_loginPressed = false;

//         if (isLoggedIn()) { // if it's logged in already then log out.
//            m_loggedIn = false;
//            displayLoginText();
//            emit q->loggedOut();

//         } else {
//            switch (q->m_loginType) {
//            case ExTabWidget::Simple:
//               m_loginDlg->setAttribute(Qt::WA_DeleteOnClose, true);
//               m_loginDlg->exec();

//               if (isLoggedIn()) {
//                  displayLogoutText();
//               }

//               break;

//            case ExTabWidget::Standard:
//               m_loginDlg->setAttribute(Qt::WA_DeleteOnClose, true);

//               m_loginDlg->exec();

//               if (isLoggedIn()) {
//                  displayLogoutText();
//               }

//               break;

//            case ExTabWidget::Custom:
//               m_loginDlg->setAttribute(Qt::WA_DeleteOnClose, true);
//               m_loginDlg->exec();

//               if (isLoggedIn()) {
//                  displayLogoutText();
//               }

//               break;

//            case ExTabWidget::None:
//               break;
//            }
//         }
//      }

//      return true;

//   } else {
//      return false;
//   }

//   q_ptr->update();
//}

//void ExTabWidgetPrivate::paintEvent(QPaintEvent* evt)
//{
//   if (m_loginWidget) {
//      m_loginWidget->paintEvent(evt);
//   }

//   if (m_clockWidget) {
//      m_clockWidget->paintEvent(evt);
//   }

//   if (m_messageWidget) {
//      m_messageWidget->paintEvent(evt);
//   }
//}

///*!
//   \internal

//   \brief checks whether the click is inside the login frame.
//*/
//bool ExTabWidgetPrivate::isInLoginFrame(int x, int y)
//{
//   if (m_loginRect) {
//      return m_loginRect->contains(x, y, false);
//   }

//   return false;
//}

void ExTabWidgetPrivate::tabwidgetStatusChanged()
{
   int tabWidth = q_ptr->tabBar()->width();
   m_frameX = q_ptr->tabBar()->x() + tabWidth;
   m_frameY = q_ptr->tabBar()->y();
   m_frameWidth = q_ptr->width() - tabWidth;
   m_frameHeight = q_ptr->tabBar()->height();

   m_wrapper->setGeometry(q_ptr->tabBar()->width(),
                          q_ptr->tabBar()->y(),
                          m_frameWidth,
                          m_frameHeight);
   q_ptr->update();
}

QString ExTabWidgetPrivate::clockStyleSheet() const
{
   return m_wrapper->clockStyleSheet();
}

QString ExTabWidgetPrivate::loginStyleSheet() const
{
   return m_wrapper->loginStyleSheet();
}

QString ExTabWidgetPrivate::messageStyleSheet() const
{
   return m_wrapper->messageStyleSheet();
}

void ExTabWidgetPrivate::setClockStyleSheet(const QString& styleSheet)
{
   m_wrapper->setClockStyleSheet(styleSheet);
}

void ExTabWidgetPrivate::setLoginStyleSheet(const QString& styleSheet)
{
   //   m_loginWidget->setStyleSheet(styleSheet);
}

void ExTabWidgetPrivate::setMessageStyleSheet(const QString& styleSheet)
{
   //   m_messageWidget->setStyleSheet(styleSheet);
}

void ExTabWidgetPrivate::paintLogin(QPainter* painter, int w, int h)
{
   //   if (m_showLogin) {
   //      int frameWidth;

   //      if (!m_loginRect) {
   //         m_loginRect = new QRect();
   //         QFontMetrics fm = painter->fontMetrics();
   //         m_stringAdvance = fm.horizontalAdvance(LOGOUT);
   //         frameWidth = m_stringAdvance + 20;
   //         m_loginRect->setX(w - frameWidth);
   //         m_loginRect->setY((h - (m_frameHeight + 6)) / 2);
   //         m_loginRect->setWidth(frameWidth);
   //         m_loginRect->setHeight(m_frameHeight + 2);

   //         w -= (frameWidth + 2);

   //      } else {
   //         w -= (m_loginRect->width() + 2);
   //      }

   //      if (m_showFrame) {
   //         if (m_loginPressed) {
   //            painter->setPen(m_palette.color(QPalette::Light));

   //         } else {
   //            painter->setPen(m_palette.color(QPalette::Dark));
   //         }

   //         painter->fillRect(*m_loginRect, painter->brush());

   //         painter->drawLine(m_loginRect->x(),
   //                           m_loginRect->y(),
   //                           m_loginRect->x(),
   //                           m_loginRect->y() + m_loginRect->height());
   //         painter->drawLine(m_loginRect->x() + 1,
   //                           m_loginRect->y() + 1,
   //                           m_loginRect->x() + 1,
   //                           m_loginRect->y() + m_loginRect->height() - 1);
   //         painter->drawLine(m_loginRect->x() + 1,
   //                           m_loginRect->y(),
   //                           m_loginRect->x() + m_loginRect->width(),
   //                           m_loginRect->y());
   //         painter->drawLine(m_loginRect->x() + 2,
   //                           m_loginRect->y() + 1,
   //                           m_loginRect->x() + m_loginRect->width() - 1,
   //                           m_loginRect->y() + 1);

   //         painter->setPen(m_palette.color(QPalette::Light));
   //         painter->drawLine(m_loginRect->x() + 1,
   //                           m_loginRect->y() + m_loginRect->height(),
   //                           m_loginRect->x() + m_loginRect->width(),
   //                           m_loginRect->y() + m_loginRect->height());
   //         painter->drawLine(m_loginRect->x() + 2,
   //                           m_loginRect->y() + m_loginRect->height() - 1,
   //                           m_loginRect->x() + m_loginRect->width() - 1,
   //                           m_loginRect->y() + m_loginRect->height() - 1);
   //         painter->drawLine(m_loginRect->x() + m_loginRect->width(),
   //                           m_loginRect->y() + 1,
   //                           m_loginRect->x() + m_loginRect->width(),
   //                           m_loginRect->y() + m_loginRect->height() - 1);
   //         painter->drawLine(m_loginRect->x() + m_loginRect->width() - 1,
   //                           m_loginRect->y() + 2,
   //                           m_loginRect->x() + m_loginRect->width() - 1,
   //                           m_loginRect->y() + m_loginRect->height() - 2);
   //      }

   //      if (m_loginPressed) {
   //         painter->setPen(m_palette.color(QPalette::Dark));

   //      } else {
   //         painter->setPen(m_palette.color(QPalette::Light));
   //      }

   //      painter->setPen(m_palette.color(QPalette::WindowText));
   //      painter->drawText(
   //         m_loginRect->x() + 10, m_loginRect->y() + m_frameHeight - 4, m_loginText);
   //   }
}

void ExTabWidgetPrivate::paintUpperBorder(QPainter* painter, int x, int y, int w, int h)
{
   painter->drawLine(x, y, x, y + h);
   painter->drawLine(x + 1, y + 1, x + 1, y + h - 1);
   painter->drawLine(x + 1, y, x + w, y);
   painter->drawLine(x + 2, y + 1, x + w - 1, y + 1);
}

void ExTabWidgetPrivate::paintLowerBorder(QPainter* painter, int x, int y, int w, int h)
{
   painter->drawLine(x + 1, y + h, x + w, y + h);
   painter->drawLine(x + 2, y + h - 1, x + w - 1, y + h - 1);
   painter->drawLine(x + w, y + 1, x + w, y + h - 1);
   painter->drawLine(x + w - 1, y + 2, x + w - 1, y + h - 2);
}

void ExTabWidgetPrivate::paintBorder(QPainter* painter, int x, int y, int w, int h, bool darkFirst)
{
   //   painter->fillRect(*m_clockRect, painter->brush());

   if (darkFirst) {
      painter->setPen(m_palette.color(QPalette::Dark));
      paintUpperBorder(painter, x, y, w, h);
      painter->setPen(m_palette.color(QPalette::Light));
      paintLowerBorder(painter, x, y, w, h);

   } else {
      painter->setPen(m_palette.color(QPalette::Light));
      paintUpperBorder(painter, x, y, w, h);
      painter->setPen(m_palette.color(QPalette::Dark));
      paintLowerBorder(painter, x, y, w, h);
   }
}

//void ExTabWidgetPrivate::paintClock(QPainter* painter, int w, int h)
//{
//   if (m_showClock) {

//      int frameWidth;

//      if (!m_clockRect) {
//         m_clockRect = new QRect();

//         QFontMetrics fm = painter->fontMetrics();

//         if (m_showSeconds) {
//            m_stringAdvance = fm.horizontalAdvance(WITHSECONDS);

//         } else {
//            m_stringAdvance = fm.horizontalAdvance(NOSECONDS);
//         }

//         frameWidth = m_stringAdvance + 20;
//         // not used unless another thing is added before message
//         m_clockRect->setX(w - frameWidth);
//         m_clockRect->setY((h - (m_frameHeight + 6)) / 2);
//         m_clockRect->setWidth(frameWidth);
//         m_clockRect->setHeight(m_frameHeight + 2);

//         w -= (frameWidth + 2);

//      } else {
//         w -= (m_clockRect->width() + 2);
//      }

//      if (m_showFrame) {
//         painter->fillRect(*m_clockRect, painter->brush());
//         paintBorder(painter, m_clockRect->x(), m_clockRect->y(), m_clockRect->width(), m_clockRect->height(), false);
//      }

//      painter->setPen(m_palette.color(QPalette::WindowText));
//      painter->drawText(
//         m_clockRect->x() + 10, m_clockRect->y() + m_frameHeight - 4, m_nowString);
//   }
//}

void ExTabWidgetPrivate::paintMessages(QPainter* painter, int w, int h)
{
   if (m_showMessages) {

      int frameWidth;
      QString text;
      int tw = q_ptr->tabBar()->width();

      QFontMetrics fm = painter->fontMetrics();

      if (!m_messageRect) {

         m_messageRect = new QRect();
         m_messageWidth = fm.horizontalAdvance(m_messageText);
         frameWidth = w - tw - 2;
         m_messageRect->setX(w - frameWidth);
         m_messageRect->setY((h - (m_frameHeight + 6)) / 2);
         m_messageRect->setWidth(frameWidth);
         m_messageRect->setHeight(m_frameHeight + 2);
         m_messageClip = new QRect();
         m_messageClip->setX(m_messageRect->x() + 4);
         m_messageClip->setY(m_messageRect->y() + 4);
         m_messageClip->setWidth(m_messageRect->width() - 8);
         m_messageClip->setHeight(m_messageRect->height() - 8);
      }

      if (m_messageWidth > m_messageRect->width()) { // message is too long.

         if (m_marquee) { // text is marqueed

            QString messageText =
               m_messageText +
               "\u2026 "; // ellipsis ... character followed by a space.
            int pos = m_marqueePos % messageText.length();
            text = messageText.mid(pos).append(messageText.left(pos));

         } else { // text is not marqueed so just put an ellipsis at the end
            text =
               fm.elidedText(m_messageText, Qt::ElideRight, m_messageRect->width());
         }

      } else {

         text = m_messageText;
      }

      QPalette messagePalette(m_palette);

      //      if (m_useTempColor) {
      //         messagePalette.setColor(QPalette::WindowText, m_tempColor);

      //      } else {
      //         messagePalette.setColor(QPalette::WindowText, m_textColor);
      //      }

      //      if (m_useTempBack && m_tempBackground.color().isValid()) {
      //         painter->fillRect(*m_messageRect, m_tempBackground);

      //      } else if (m_background.color().isValid()) {
      //         painter->fillRect(*m_messageRect, m_background);
      //      }

      if (m_showFrame) {
         //         painter->setPen(m_palette.color(QPalette::Dark));
         painter->fillRect(*m_messageRect, painter->brush());
         painter->drawLine(m_messageRect->x(),
                           m_messageRect->y(),
                           m_messageRect->x(),
                           m_messageRect->y() + m_messageRect->height());
         painter->drawLine(m_messageRect->x() + 1,
                           m_messageRect->y() + 1,
                           m_messageRect->x() + 1,
                           m_messageRect->y() + m_messageRect->height() - 1);
         painter->drawLine(m_messageRect->x() + 1,
                           m_messageRect->y(),
                           m_messageRect->x() + m_messageRect->width(),
                           m_messageRect->y());
         painter->drawLine(m_messageRect->x() + 2,
                           m_messageRect->y() + 1,
                           m_messageRect->x() + m_messageRect->width() - 1,
                           m_messageRect->y() + 1);

         painter->setPen(m_palette.color(QPalette::Light));
         painter->drawLine(m_messageRect->x() + 1,
                           m_messageRect->y() + m_messageRect->height(),
                           m_messageRect->x() + m_messageRect->width(),
                           m_messageRect->y() + m_messageRect->height());
         painter->drawLine(m_messageRect->x() + 2,
                           m_messageRect->y() + m_messageRect->height() - 1,
                           m_messageRect->x() + m_messageRect->width() - 1,
                           m_messageRect->y() + m_messageRect->height() - 1);
         painter->drawLine(m_messageRect->x() + m_messageRect->width(),
                           m_messageRect->y() + 1,
                           m_messageRect->x() + m_messageRect->width(),
                           m_messageRect->y() + m_messageRect->height() - 1);
         painter->drawLine(m_messageRect->x() + m_messageRect->width() - 1,
                           m_messageRect->y() + 2,
                           m_messageRect->x() + m_messageRect->width() - 1,
                           m_messageRect->y() + m_messageRect->height() - 2);
      }

      painter->setClipRect(*m_messageClip);

      painter->setPen(messagePalette.color(QPalette::WindowText));
      painter->drawText(
         m_messageRect->x() + 10, m_messageRect->y() + m_frameHeight - 5, text);
   }
}

//void ExTabWidgetPrivate::paint(QPainter* painter, int w, QStyle* style)
//{

//   int h = m_tabs->tabBar()->height();
//   int sh = h * 0.6; // set the font height to be 60% of the total height.
//   QFont font = painter->font();
//   font.setPixelSize(sh);
//   painter->setFont(font);
//   QFontMetrics fm = painter->fontMetrics();
//   //   m_frameHeight = fm.height();

//   paintLogin(painter, w, h);
//   //   paintClock(painter, w, h);
//   paintMessages(painter, w, h);
//}

//void ExTabWidgetPrivate::displayLoginText()
//{
//   //   m_loginText = LOGIN;
//}

//void ExTabWidgetPrivate::displayLogoutText()
//{
//   //   m_loginText = LOGOUT;
//}

void ExTabWidgetPrivate::checkPassword(QString password)
{
   m_wrapper->checkPassword(password);
}

void ExTabWidgetPrivate::checkPassword(QString username, QString password)
{
   m_wrapper->checkPassword(username, password);
}

void ExTabWidgetPrivate::setIgnoreCase(bool ignoreCase)
{
   m_wrapper->setIgnoreCase(ignoreCase);
}

bool ExTabWidgetPrivate::isIgnoreCase()
{
   return m_wrapper->isIgnoreCase();
}

void ExTabWidgetPrivate::setLargeTextForLoginDialog(bool)
{
   // TODO
}

bool ExTabWidgetPrivate::isLoginEnabled()
{
   return m_wrapper->isLoginEnabled();
}

void ExTabWidgetPrivate::addPassword(QString password)
{
   m_wrapper->addPassword(password);
}

void ExTabWidgetPrivate::addPassword(QString username, QString password)
{
   m_wrapper->addPassword(username, password);
}

void ExTabWidgetPrivate::clearPasswords()
{
   m_wrapper->clearPasswords();
}

void ExTabWidgetPrivate::showSeconds(bool showSeconds)
{
   m_wrapper->setShowSeconds(showSeconds);
   m_wrapper->calculateWidgetSizes(m_frameX, m_frameY, m_frameWidth, m_frameHeight);
}

void ExTabWidgetPrivate::clearMessage()
{
   m_messageText.clear();
   q_ptr->update();
}

void ExTabWidgetPrivate::setMessageColor(QColor color)
{
   m_textColor = color;
   q_ptr->update();
}

void ExTabWidgetPrivate::setMessageBackground(QColor color)
{
   m_background = QBrush(color);
   q_ptr->update();
}

void ExTabWidgetPrivate::setMessageBackground(QBrush brush)
{
   m_background = brush;
   q_ptr->update();
}

void ExTabWidgetPrivate::messageTimeout()
{
   //   m_useTempColor = false;
   //   m_timeoutTimer->stop();
   //   m_timeoutTimer->deleteLater();
   //   m_timeoutTimer = nullptr;
   //   clearMessage();
}

void ExTabWidgetPrivate::resetMessageData(const QString& message, bool tempColor)
{
   m_messageText = message;
   m_useTempColor = tempColor;
   m_messageRect = nullptr;
   m_marqueePos = 0;
}

void ExTabWidgetPrivate::setMessage(const QString& message, uint timeout)
{
   resetMessageData(message, false);
   setMessage(timeout);
}

void ExTabWidgetPrivate::setMessage(QColor color, QString message, uint timeout)
{
   resetMessageData(message, true);
   m_tempColor = color;
   setMessage(timeout);
}

void ExTabWidgetPrivate::setMessage(QColor color,
                                    QColor back,
                                    QString message,
                                    uint timeout)
{
   resetMessageData(message, true);
   m_useTempBack = true;
   m_tempColor = color;
   m_tempBackground = QBrush(back);
   setMessage(timeout);
}

void ExTabWidgetPrivate::setMessage(QColor color,
                                    QBrush back,
                                    QString message,
                                    uint timeout)
{
   resetMessageData(message, true);
   m_useTempBack = true;
   m_tempColor = color;
   m_tempBackground = back;
   setMessage(timeout);
}

void ExTabWidgetPrivate::setMessage(uint timeout)
{
   //   if (m_timeoutTimer) { // new message before timeout cancel timeout.
   //      if (m_timeoutTimer->isActive()) {
   //         m_timeoutTimer->stop();
   //         m_timeoutTimer->deleteLater();
   //         m_timeoutTimer = nullptr;
   //      }
   //   }

   //   if (timeout > 0) {
   //      if (m_timeoutTimer) {
   //         if (m_timeoutTimer->isActive()) {
   //            m_timeoutTimer->stop();
   //         }

   //      } else {
   //         m_timeoutTimer = new QTimer(q_ptr);
   //      }

   //      m_timeoutTimer->start(timeout);
   //   }

   //   // remove all new line characters, only single line message.
   //   int pos = m_messageText.indexOf('\n');

   //   while (pos != -1) {
   //      m_messageText.remove(pos, 1);
   //      pos = m_messageText.indexOf('\n');
   //   }

   //   q_ptr->update();
}


//== WrapperWidget ========================================================================

WrapperWidget::WrapperWidget(QWidget* parent)
   : QFrame(parent)
   , m_parent(parent)
   , m_layout(new QGridLayout)
   , m_clockWidget(nullptr)
   , m_loginWidget(nullptr)
   , m_messageWidget(nullptr)
   , m_filler(nullptr)
   , m_ignoreCase(false)
   , m_showSeconds(false)
   , m_clockFrame(QFrame::Shape::NoFrame)
{
   setStyleSheet("background: lightgreen;");
   setContentsMargins(0, 0, 3, 0);
   m_layout->setContentsMargins(0, 0, 0, 0);
   setLayout(m_layout);
}

QString WrapperWidget::loginText() const
{
   if (m_loginWidget) {
      return m_loginWidget->loginText();
   }

   return LoginWidget::LOGIN;
}

void WrapperWidget::setLoginText(const QString& text)
{
   if (m_loginWidget) {
      m_loginWidget->setLoginText(text);
   }
}

QString WrapperWidget::logoutText() const
{
   if (m_loginWidget) {
      return m_loginWidget->logoutText();
   }

   return LoginWidget::LOGOUT;
}

void WrapperWidget::setLogoutText(const QString& text)
{
   if (m_loginWidget) {
      m_loginWidget->setLogoutText(text);
   }
}

bool WrapperWidget::isLoggedIn()
{
   if (m_loginWidget) {
      return m_loginWidget->isLoggedIn();
   }

   return false;
}

bool WrapperWidget::isLoginEnabled()
{
   if (m_loginWidget) {
      return m_loginWidget->isLoginEnabled();
   }

   return false;
}

bool WrapperWidget::isShowLogin()
{
   return false;
}

QString WrapperWidget::username()
{
   if (m_loginWidget) {
      return m_loginWidget->username();
   }

   return QString();
}

AbstractLoginDialog::LoginType WrapperWidget::loginType() const
{
   if (m_loginWidget) {
      return m_loginWidget->loginType();
   }

   return AbstractLoginDialog::None;
}

void WrapperWidget::setLoginType(const AbstractLoginDialog::LoginType& loginType)
{
   if (m_loginWidget) {
      m_loginWidget->setLoginType(loginType);
   }
}

void WrapperWidget::showLogin(bool show)
{
   removeWidgetsFromLayout();

   if (show) {
      if (!m_loginWidget) {
         m_loginWidget = new LoginWidget(m_parent);
         m_loginWidget->setSizePolicy(QSizePolicy::Preferred,
                                      QSizePolicy::Fixed);
         m_loginWidget->showLogin(true);

         if (!m_loginStylesheet.isEmpty()) {
            m_loginWidget->setStyleSheet(m_loginStylesheet);
         }

         connect(m_loginWidget, &LoginWidget::clicked, this, &WrapperWidget::loginClicked);
         // pass login signals signals on to wrapper signals
         connect(m_loginWidget, &LoginWidget::loggedIn, this, &WrapperWidget::loggedIn);
         connect(m_loginWidget, &LoginWidget::loggedOut, this, &WrapperWidget::loggedOut);
         connect(m_loginWidget, &LoginWidget::passwordBad, this, &WrapperWidget::passwordBad);
         connect(m_loginWidget, &LoginWidget::usernameBad, this, &WrapperWidget::usernameBad);
         connect(m_loginWidget, &LoginWidget::loginBad, this, &WrapperWidget::loginBad);
      }

   } else {

      m_loginWidget->deleteLater();
      m_loginWidget = nullptr;
   }

   addWidgetsToLayout();
}

void WrapperWidget::setLoginStyleSheet(const QString& stylesheet)
{
   if (m_loginWidget) {
      m_loginWidget->setStyleSheet(stylesheet);
   }

   m_loginStylesheet = stylesheet;
}

QString WrapperWidget::loginStyleSheet()
{
   return m_loginStylesheet;
}

void WrapperWidget::setCustomLoginDialog(AbstractLoginDialog* loginDlg)
{
   if (m_loginWidget) {
      m_loginWidget->setCustomLoginDialog(loginDlg);
   }

   // TODO maybe store dialog in no widget.
}

bool WrapperWidget::hasCustomLoginDialog()
{
   if (m_loginWidget) {
      return m_loginWidget->hasCustomLoginDialog();
   }

   return false;
}

void WrapperWidget::checkPassword(QString password)
{
   if (m_loginWidget) {
      m_loginWidget->checkPassword(password);
   }
}

void WrapperWidget::checkPassword(QString username, QString password)
{
   if (m_loginWidget) {
      m_loginWidget->checkPassword(username, password);
   }
}

void WrapperWidget::addPassword(QString password)
{
   if (m_loginWidget) {
      m_loginWidget->addPassword(password);
   }
}

void WrapperWidget::clearPasswords()
{
   if (m_loginWidget) {
      m_loginWidget->clearPasswords();
   }
}

void WrapperWidget::addPassword(QString id, QString password)
{
   if (m_loginWidget) {
      m_loginWidget->addPassword(id, password);
   }
}

void WrapperWidget::setIgnoreCase(bool ignoreCase)
{
   if (m_loginWidget) {
      m_loginWidget->setIgnoreCase(ignoreCase);
   }

   m_ignoreCase = ignoreCase;
}

bool WrapperWidget::isIgnoreCase()
{
   return m_ignoreCase;
}


bool WrapperWidget::isShowClock()
{
   if (m_clockWidget) {
      return m_clockWidget->isShowing();
   }

   return false;
}

void WrapperWidget::showClock(bool show)
{
   // we need to remove the widgets from the layout then after creating
   // or destroying the clock widget reload them in the right order.
   removeWidgetsFromLayout();

   if (show) {
      if (!m_clockWidget) {
         m_clockWidget = new ClockWidget(m_parent);
         m_clockWidget->setSizePolicy(QSizePolicy::Preferred,
                                      QSizePolicy::Fixed);
         m_clockWidget->showClock(true);

         if (!m_clockStylesheet.isEmpty()) {
            m_clockWidget->setStyleSheet(m_clockStylesheet);
         }
      }

   } else {

      m_clockWidget->deleteLater();
      m_clockWidget = nullptr;
   }

   addWidgetsToLayout();
}

void WrapperWidget::setClockFrame(QFrame::Shape style)
{
   if (m_clockWidget) {
      m_clockWidget->setClockFrame(style);
   }

   m_clockFrame = style;
}

void WrapperWidget::setShowSeconds(bool show)
{
   if (m_clockWidget) {
      m_clockWidget->setShowSeconds(show);
   }

   m_showSeconds = show;
}

void WrapperWidget::setClockStyleSheet(const QString& stylesheet)
{
   if (m_clockWidget) {
      m_clockWidget->setStyleSheet(stylesheet);
   }

   m_clockStylesheet = stylesheet;
}

QString WrapperWidget::clockStyleSheet()
{
   return  m_clockStylesheet;
}

void WrapperWidget::setMessageStyleSheet(const QString& stylesheet)
{
   if (m_messageWidget) {
      m_messageWidget->setStyleSheet(stylesheet);
   }

   m_messageStylesheet = stylesheet;
}

QString WrapperWidget::messageStyleSheet()
{
   return m_messageStylesheet;
}

void WrapperWidget::calculateWidgetSizes(int x, int y, int w, int h)
{
   int availableWidth = w;

   if (m_loginWidget) {
      int reqWidth =
         m_loginWidget->calculateRequiredWidth(availableWidth);

      if (reqWidth < 0) {
         return;
      }

      QSize size = QSize(reqWidth, h);
      m_loginWidget->setSizeHint(size);
      availableWidth -= reqWidth;
   }

   if (m_clockWidget) {
      int reqWidth =
         m_clockWidget->calculateRequiredWidth(availableWidth);

      if (reqWidth < 0) {
         return;
      }

      QSize size = QSize(reqWidth, h);
      m_clockWidget->setSizeHint(size);
      availableWidth -= reqWidth;
   }

   if (m_messageWidget) {
      m_messageWidget->calculateRequiredWidth(x, y, availableWidth, h);
   }
}

void WrapperWidget::removeWidgetsFromLayout()
{
  for (int i = m_layout->count(); i > 0; --i) {
    m_layout->takeAt(i - 1);
  }
}

void WrapperWidget::addWidgetsToLayout()
{
  int column = 0;

  if (m_messageWidget) {
    m_layout->addWidget(m_messageWidget, 0, column++);

    if (m_filler) {
      // filler not needed if messages exists.
      m_filler->deleteLater();
      m_filler = nullptr;
    }

  } else {
    if (!m_filler) {
      m_filler = new QFrame(this);
      m_filler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
      m_filler->setStyleSheet("background: lightblue");
    }

    m_layout->addWidget(m_filler, 0, column++);
  }

  if (m_clockWidget) {
    m_layout->addWidget(m_clockWidget, 0, column++);
  }

  if (m_loginWidget) {
    m_layout->addWidget(m_loginWidget, 0, column++);
  }

  updateGeometry();
}

/// \endcond


