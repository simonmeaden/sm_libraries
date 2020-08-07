#include "extabwidget_p.h"
#include "extabwidget.h"
#include "extabwidget_p.h"

/// \cond DO_NOT_DOCUMENT
const QString LoginWidget::LOGIN = "Log In";
const QString LoginWidget::LOGOUT = "Log Out";
const QString ClockWidget::WITHSECONDS = "00:00:00";
const QString ClockWidget::NOSECONDS = "00:00";

ExTabWidgetPrivate::ExTabWidgetPrivate(ExTabWidget* parent,
                                       AbstractLoginDialog* customDlg = nullptr)
   : q_ptr(parent)
   , m_wrapper(new WrapperWidget(q_ptr))
   , m_loggedIn(false)
   , m_showLogin(false)
     //   , m_showClock(false)
   , m_showMessages(false)
   , m_loginDlg(new LoginDialog(q_ptr))
   , m_customLoginDlg(customDlg)
   , m_loginRect(nullptr)
   , m_messageRect(nullptr)
   , m_now(0)
   , m_showFrame(true)
   , m_isInframe(false)
   , m_loginPressed(false)
   , m_ignoreCase(false)
   , m_marqueeTimer(nullptr)
   , m_timeoutTimer(nullptr)
   , m_textColor(QColor("black"))
   , m_background(m_palette.window())
   , m_marquee(false)
{
   m_timeout = 0;
   m_marqueePos = 0;
   q_ptr->setContentsMargins(0, 0, 0, 0);
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
   return (m_customLoginDlg);
}

void ExTabWidgetPrivate::showClockFrame(bool showFrame, QFrame::Shape style)
{
   // TODO show/hide clock frames
   if (m_wrapper) {
      m_wrapper->showClockFrame(showFrame, style);
   }
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
   if (m_marqueeTimer) {
      m_marqueeTimer->stop();
      m_marqueeTimer->deleteLater();
      m_marqueeTimer = nullptr;
   }
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
   //   if (showLogin != m_showLogin) {
   //      if (!m_loginWidget) {
   //         m_loginWidget = new LoginWidget(q_ptr);
   //      }

   //      if (m_showMessages) {
   //         m_messageRect = nullptr;
   //      }


   //      m_showLogin = showLogin;

   //      q_ptr->update();

   //   } else {
   //      m_loginWidget = nullptr;
   //   }
}

void ExTabWidgetPrivate::setLoginType()
{
   Q_Q(ExTabWidget);

   q->disconnect(m_loginDlg, nullptr, nullptr, nullptr);

   switch (q->m_loginType) {
   case ExTabWidget::Simple:
      m_loginDlg = new SimpleLoginDialog(q_ptr);
      q->connect(m_loginDlg,
                 qOverload<QString>(&AbstractLoginDialog::loginData),
                 q_ptr,
                 qOverload<QString>(&ExTabWidget::checkPassword));
      break;

   case ExTabWidget::Standard:
      m_loginDlg = new LoginDialog(q_ptr);
      q->connect(m_loginDlg,
                 qOverload<QString, QString>(&AbstractLoginDialog::loginData),
                 q_ptr,
                 qOverload<QString, QString>(&ExTabWidget::checkPassword));
      break;

   case ExTabWidget::Custom:
      if (m_customLoginDlg) {
         m_loginDlg = m_customLoginDlg;
         q->connect(m_loginDlg,
                    &AbstractLoginDialog::loginCorrect,
                    q_ptr,
                    &ExTabWidget::loginIsCorrect);
         q->connect(m_loginDlg,
                    &AbstractLoginDialog::loginIncorrect,
                    q_ptr,
                    &ExTabWidget::loginIsIncorrect);
      }

      break;

   case ExTabWidget::None:
      break;
   }

}

void ExTabWidgetPrivate::setCustomLoginDialog(AbstractLoginDialog* loginDlg)
{
   m_customLoginDlg = loginDlg;
}

bool ExTabWidgetPrivate::mousePressEvent(QMouseEvent* event)
{
   //    Q_Q(ExTabWidget);
   int x = event->x();
   int y = event->y();

   if (isInLoginFrame(x, y)) {
      m_isInframe = true;
      m_loginPressed = true;

   } else {
      m_isInframe = false;
      m_loginPressed = false;
   }

   return m_isInframe;
}

bool ExTabWidgetPrivate::mouseReleaseEvent(QMouseEvent* /*event*/)
{
   Q_Q(ExTabWidget);

   if (m_showLogin) {
      if (m_isInframe) {
         m_loginPressed = false;

         if (isLoggedIn()) { // if it's logged in already then log out.
            m_loggedIn = false;
            displayLoginText();
            emit q->loggedOut();

         } else {
            switch (q->m_loginType) {
            case ExTabWidget::Simple:
               m_loginDlg->setAttribute(Qt::WA_DeleteOnClose, true);
               m_loginDlg->exec();

               if (isLoggedIn()) {
                  displayLogoutText();
               }

               break;

            case ExTabWidget::Standard:
               m_loginDlg->setAttribute(Qt::WA_DeleteOnClose, true);

               m_loginDlg->exec();

               if (isLoggedIn()) {
                  displayLogoutText();
               }

               break;

            case ExTabWidget::Custom:
               m_loginDlg->setAttribute(Qt::WA_DeleteOnClose, true);
               m_loginDlg->exec();

               if (isLoggedIn()) {
                  displayLogoutText();
               }

               break;

            case ExTabWidget::None:
               break;
            }
         }
      }

      return true;

   } else {
      return false;
   }

   q_ptr->update();
}

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

/*!
   \internal

   \brief checks whether the click is inside the login frame.
*/
bool ExTabWidgetPrivate::isInLoginFrame(int x, int y)
{
   if (m_loginRect) {
      return m_loginRect->contains(x, y, false);
   }

   return false;
}

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

QString ExTabWidgetPrivate::styleSheet() const
{
   //   return m_clockWidget->styleSheet();
}

QString ExTabWidgetPrivate::clockStyleSheet() const
{
   //   return m_clockWidget->styleSheet();
}

QString ExTabWidgetPrivate::loginStyleSheet() const
{
   //   return m_loginWidget->styleSheet();
}

QString ExTabWidgetPrivate::messageStyleSheet() const
{
   //   return m_messageWidget->styleSheet();
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

void ExTabWidgetPrivate::displayLoginText()
{
   //   m_loginText = LOGIN;
}

void ExTabWidgetPrivate::displayLogoutText()
{
   //   m_loginText = LOGOUT;
}

void ExTabWidgetPrivate::checkPassword(QString password)
{
   Q_Q(ExTabWidget);

   if (q->m_loginType == ExTabWidget::Simple) {
      Q_Q(ExTabWidget);
      bool result;

      if (m_ignoreCase) {
         result = (password.toLower() == m_password.toLower());

      } else {
         result = (password == m_password);
      }

      if (result) {
         emit q->loggedIn();
         m_loggedIn = true;

      } else {
         emit q->passwordBad();
      }
   }
}

void ExTabWidgetPrivate::checkPassword(QString username, QString password)
{
   Q_Q(ExTabWidget);

   QString pw, un;

   if (q->m_loginType == ExTabWidget::Standard) {
      if (!m_ignoreCase) {
         pw = m_passwords.value(username);

         if (pw.isEmpty()) {
            emit q->usernameBad();
            m_loggedIn = false;
            return;
         }

         bool result = (password == pw);

         if (result) {
            emit q->loggedIn();
            m_loggedIn = true;
            m_username = "";

         } else {
            emit q->passwordBad();
            m_loggedIn = false;
         }

      } else {

         pw = password.toLower();
         un = username.toLower();
         bool unFound = false;

         QListIterator<QString> it(m_passwords.keys());

         while (it.hasNext()) {
            QString id = it.next();

            if (id.toLower() == un) {
               unFound = true;
               QString storedPw = m_passwords.value(id);

               if (storedPw.toLower() == pw) {
                  emit q->loggedIn();
                  m_username = un;
                  m_loggedIn = true;
                  return;
               }

               if (unFound) {
                  emit q->usernameBad();
                  return;
               }
            }
         }

         emit q->passwordBad();
         m_username = "";
         m_loggedIn = false;
      }
   }
}

void ExTabWidgetPrivate::loginIsCorrect(QString username)
{
   Q_Q(ExTabWidget);

   emit q->loggedIn();
   m_loggedIn = true;
   m_username = username;
}

void ExTabWidgetPrivate::loginIsIncorrect()
{
   Q_Q(ExTabWidget);

   emit q->loginBad();
   m_username = "";
   m_loggedIn = false;
}

void ExTabWidgetPrivate::setIgnoreCase(bool ignoreCase)
{
   m_ignoreCase = ignoreCase;
}

void ExTabWidgetPrivate::setLargeTextForLoginDialog(bool)
{

}

bool ExTabWidgetPrivate::isLoggedIn()
{
   return m_loggedIn;
}

void ExTabWidgetPrivate::addPassword(QString password)
{
   m_password = password.toLatin1();
}

void ExTabWidgetPrivate::addPassword(QString id, QString password)
{
   m_passwords.insert(id, password.toLatin1());
}

//void ExTabWidgetPrivate::nextSecond()
//{
//   QString format = "hh:mm";

//   if (m_showSeconds) {
//      format += ":ss";
//   }

//   QDateTime now = QDateTime::currentDateTime();
//   m_nowString = now.toString(format);
//   m_now = now.toTime_t();

//   q_ptr->update();
//}

void ExTabWidgetPrivate::showSeconds(bool showSeconds)
{
   m_wrapper->setShowSeconds(showSeconds);
   m_wrapper->calculateWidgetSizes(m_frameX, m_frameY, m_frameWidth, m_frameHeight);
//   q_ptr->updateGeometry();
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
   m_useTempColor = false;
   m_timeoutTimer->stop();
   m_timeoutTimer->deleteLater();
   m_timeoutTimer = nullptr;
   clearMessage();
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
   if (m_timeoutTimer) { // new message before timeout cancel timeout.
      if (m_timeoutTimer->isActive()) {
         m_timeoutTimer->stop();
         m_timeoutTimer->deleteLater();
         m_timeoutTimer = nullptr;
      }
   }

   if (timeout > 0) {
      if (m_timeoutTimer) {
         if (m_timeoutTimer->isActive()) {
            m_timeoutTimer->stop();
         }

      } else {
         m_timeoutTimer = new QTimer(q_ptr);
      }

      m_timeoutTimer->start(timeout);
   }

   // remove all new line characters, only single line message.
   int pos = m_messageText.indexOf('\n');

   while (pos != -1) {
      m_messageText.remove(pos, 1);
      pos = m_messageText.indexOf('\n');
   }

   q_ptr->update();
}

LoginDialog::LoginDialog(QWidget* parent)
   : AbstractLoginDialog(parent)
{
   initGui(false);
}

LoginDialog::~LoginDialog() {}

void LoginDialog::clearText()
{
   m_userEdit->clear();
   m_passEdit->clear();
}

void LoginDialog::acceptLogin()
{
   emit loginData(m_userEdit->text(), m_passEdit->text());
}

void LoginDialog::initGui(bool largeText)
{
   QFont f = font();

   if (largeText) {
      f.setPointSize(20);
      f.setWeight(QFont::Bold);
      setFont(f);
   }

   QLabel* lbl1 = new QLabel("User name :", this);
   lbl1->setFont(f);
   m_userEdit = new QLineEdit(this);
   QLabel* lbl2 = new QLabel("Password :", this);
   lbl2->setFont(f);
   m_passEdit = new QLineEdit(this);
   m_passEdit->setEchoMode(QLineEdit::Password);

   QGridLayout* layout = new QGridLayout(this);
   setLayout(layout);

   layout->addWidget(lbl1, 0, 0);
   layout->addWidget(m_userEdit, 0, 1);
   layout->addWidget(lbl2, 1, 0);
   layout->addWidget(m_passEdit, 1, 1);

   QDialogButtonBox* buttons = new QDialogButtonBox(this);
   buttons->addButton(QDialogButtonBox::Ok);
   buttons->addButton(QDialogButtonBox::Cancel);
   buttons->button(QDialogButtonBox::Ok)->setText(tr("Login"));
   buttons->button(QDialogButtonBox::Ok)->setFont(f);
   buttons->button(QDialogButtonBox::Cancel)->setText(tr("Abort"));
   buttons->button(QDialogButtonBox::Cancel)->setFont(f);
   layout->addWidget(buttons, 2, 0, 1, 2);

   // close on abort
   connect(buttons->button(QDialogButtonBox::Cancel),
           &QPushButton::clicked,
           this,
           &LoginDialog::close);

   // acceptLogin and abort on accept.
   // should acceptLogin first.
   connect(buttons->button(QDialogButtonBox::Ok),
           &QPushButton::clicked,
           this,
           &LoginDialog::acceptLogin);
   connect(buttons->button(QDialogButtonBox::Ok),
           &QPushButton::clicked,
           this,
           &LoginDialog::close);
}

SimpleLoginDialog::SimpleLoginDialog(QWidget* parent)
   : AbstractLoginDialog(parent)
{
   initGui(false);
}

SimpleLoginDialog::~SimpleLoginDialog() {}

void SimpleLoginDialog::clearText()
{
   m_passEdit->clear();
}

void SimpleLoginDialog::initGui(bool largeText)
{
   QFont f = font();

   if (largeText) {
      f.setPointSize(20);
      f.setWeight(QFont::Bold);
      setFont(f);
   }

   QLabel* lbl1 = new QLabel("Password :", this);
   lbl1->setFont(f);

   m_passEdit = new QLineEdit(this);
   m_passEdit->setFont(f);
   m_passEdit->setEchoMode(QLineEdit::Password);

   QGridLayout* layout = new QGridLayout(this);
   setLayout(layout);

   layout->addWidget(lbl1, 0, 0);
   layout->addWidget(m_passEdit, 0, 1);

   QDialogButtonBox* buttons = new QDialogButtonBox(this);
   buttons->addButton(QDialogButtonBox::Ok);
   buttons->addButton(QDialogButtonBox::Cancel);
   buttons->button(QDialogButtonBox::Ok)->setText(tr("Login"));
   buttons->button(QDialogButtonBox::Ok)->setFont(f);
   buttons->button(QDialogButtonBox::Cancel)->setText(tr("Abort"));
   buttons->button(QDialogButtonBox::Cancel)->setFont(f);
   layout->addWidget(buttons, 1, 0, 1, 2);

   // close on abort
   connect(buttons->button(QDialogButtonBox::Cancel),
           &QPushButton::clicked,
           this,
           &SimpleLoginDialog::close);

   // acceptLogin and abort on accept.
   // should acceptLogin first.
   connect(buttons->button(QDialogButtonBox::Ok),
           &QPushButton::clicked,
           this,
           &SimpleLoginDialog::acceptLogin);
   connect(buttons->button(QDialogButtonBox::Ok),
           &QPushButton::clicked,
           this,
           &SimpleLoginDialog::close);
}

void SimpleLoginDialog::acceptLogin()
{
   emit loginData(m_passEdit->text());
}

//== ClockWidget ========================================================================

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

void ClockWidget::showClockFrame(bool showFrame, QFrame::Shape style) {
  if (showFrame) {
    setFrameStyle(style);

  } else {
    setFrameStyle(QFrame::NoFrame);
  }
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

int ClockWidget::calculateRequiredWidth(int x, int y, int w, int h)
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
  if (m_size != size){
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

//== WrapperWidget ========================================================================

bool WrapperWidget::isShowClock()
{
   if (m_clockWidget) {
      return m_clockWidget->isShowing();
   }

   return false;
}

/// \endcond
