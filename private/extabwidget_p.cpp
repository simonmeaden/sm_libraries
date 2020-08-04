#include "extabwidget_p.h"
#include "extabwidget.h"

/// \cond DO_NOT_DOCUMENT
const QString ExTabWidgetPrivate::LOGIN = "Log In";
const QString ExTabWidgetPrivate::LOGOUT = "Log Out";
const QString ExTabWidgetPrivate::WITHSECONDS = "00:00:00";
const QString ExTabWidgetPrivate::NOSECONDS = "00:00";

ExTabWidgetPrivate::ExTabWidgetPrivate(ExTabWidget* parent,
                                       AbstractLoginDialog* customDlg = nullptr)
   : q_ptr(parent)
   , m_clockWidget(nullptr)
   , m_loginWidget(nullptr)
   , m_messageWidget(nullptr)
   , m_loggedIn(false)
   , m_showLogin(false)
   , m_showClock(false)
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
   , m_marqueeSpeed(MARQUEE_TIME)
{
   m_loginText = LOGIN;
   m_timeout = 0;
   m_marqueePos = 0;
   q_ptr->setContentsMargins(0, 0, 0, 0);
   QVBoxLayout* layout = new QVBoxLayout;
   layout->setContentsMargins(0, 0, 0, 0);
   q_ptr->setLayout(layout);
   m_tabs = new QTabWidget(q_ptr);
   layout->addWidget(m_tabs);
   // TODO REMOVE BELOW
   m_tabs->tabBar()->setStyleSheet("background: red;");
   q_ptr->setStyleSheet("background: green;");
   // TODO UNTIL HERE
}

ExTabWidgetPrivate::~ExTabWidgetPrivate()
{
   clearFrames();
}

void ExTabWidgetPrivate::clearFrames()
{
   if (m_loginRect) {
      delete m_loginRect;
      m_loginRect = nullptr;
   }

   if (m_messageRect) {
      delete m_messageRect;
      m_messageRect = nullptr;
      delete m_messageClip;
      m_messageClip = nullptr;
   }

   q_ptr->update();
}

bool ExTabWidgetPrivate::hasCustomLoginDialog()
{
   return (m_customLoginDlg);
}

void ExTabWidgetPrivate::showFrame(bool frame, QFrame::Shape style)
{
   m_showFrame = frame;
   m_clockWidget->setFrameStyle(style);
   m_loginWidget->setFrameStyle(style);
   m_messageWidget->setFrameStyle(style);
   q_ptr->update();
}

void ExTabWidgetPrivate::showClockFrame(bool showFrame, QFrame::Shape style)
{
   if (!m_clockWidget) {
      return;
   }

   if (showFrame) {
      m_clockWidget->setFrameStyle(style);

   } else {
      m_clockWidget->setFrameStyle(QFrame::NoFrame);
   }
}

void ExTabWidgetPrivate::showLoginFrame(bool showFrame, QFrame::Shape style)
{
   if (!m_loginWidget) {
      return;
   }

   if (showFrame) {
      m_loginWidget->setFrameStyle(style);

   } else {
      m_loginWidget->setFrameStyle(QFrame::NoFrame);
   }
}

void ExTabWidgetPrivate::showMessageFrame(bool showFrame, QFrame::Shape style)
{
   if (!m_messageWidget) {
      return;
   }

   if (showFrame) {
      m_messageWidget->setFrameStyle(style);

   } else {
      m_messageWidget->setFrameStyle(QFrame::NoFrame);
   }
}

void ExTabWidgetPrivate::repositionWidgets()
{
   int availableWidth = m_frameWidth;

   if (m_loginWidget) {
      int loginWidth = m_loginWidget->calculateRequiredWidth();
      availableWidth -= loginWidth;
   }

   if (m_clockWidget) {
      int clockWidth = m_clockWidget->resize();
      //      int clockWidth = m_clockWidget->calculateRequiredWidth();
      int x = m_frameX + m_frameWidth - clockWidth;
      int y = m_frameY;
      int h = m_frameHeight;
      m_clockWidget->move(x, y);
      availableWidth -= clockWidth;
   }

   if (m_messageWidget) {
      int loginWidth = m_loginWidget->calculateRequiredWidth();
      availableWidth -= loginWidth;
   }
}

void ExTabWidgetPrivate::showClock(bool showClock)
{
   m_showClock = showClock;

   if (m_showClock) {
      if (!m_clockWidget) {
         m_clockWidget = new ClockWidget(q_ptr);
      }


      if (m_showMessages) {
         // TODO remove when LoginWidget done.
         m_messageRect = nullptr;
      }

      repositionWidgets();
      m_clockWidget->showClock(true);

   } else {

      m_clockWidget = nullptr;
   }

   clearFrames();
   q_ptr->update();
}

void ExTabWidgetPrivate::showMessages(bool messages)
{
   m_showMessages = messages;

   if (m_showMessages) {
      if (!m_messageWidget) {
         m_messageWidget = new MessageWidget(q_ptr);
      }

      if (m_marquee) {
         if (m_marqueeTimer) {
            startMarqueeTimerIfRequired();

         } else {
            stopMarqueeTimer();
         }
      }

   } else {
      stopMarqueeTimer();
   }

   clearFrames();

   q_ptr->update();
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
   m_marqueeSpeed = int(1000.0 / charPerSecond);
   m_marqueeTimer->setInterval(m_marqueeSpeed);
   q_ptr->update();
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
   if (m_marqueeTimer) {
      if (m_marqueeTimer->isActive()) {
         return;

      } else {
         m_marqueeTimer->start(MARQUEE_TIME);
      }

   } else {
      m_marqueeTimer = new QTimer(q_ptr);
      q_ptr->connect(m_marqueeTimer, &QTimer::timeout,
                     q_ptr, &ExTabWidget::updateMarquee,
                     Qt::UniqueConnection);
      m_marqueeTimer->start(MARQUEE_TIME);
   }
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
   if (showLogin != m_showLogin) {
      if (!m_loginWidget) {
         m_loginWidget = new LoginWidget(q_ptr);
      }

      if (m_showMessages) {
         m_messageRect = nullptr;
      }


      m_showLogin = showLogin;

      clearFrames();

      q_ptr->update();

   } else {
      m_loginWidget = nullptr;
   }
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

void ExTabWidgetPrivate::paintEvent(QPaintEvent* evt)
{
   if (m_loginWidget) {
      m_loginWidget->paintEvent(evt);
   }

   if (m_clockWidget) {
      m_clockWidget->paintEvent(evt);
   }

   if (m_messageWidget) {
      m_messageWidget->paintEvent(evt);
   }
}

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

void ExTabWidgetPrivate::resize()
{
   int tabWidth = m_tabs->tabBar()->width();
   m_frameX = m_tabs->tabBar()->x() + tabWidth;
   m_frameY = m_tabs->tabBar()->y();
   m_frameWidth = q_ptr->width() - tabWidth;
   m_frameHeight = m_tabs->tabBar()->height();

   repositionWidgets();

   clearFrames();
   q_ptr->update();
}

QString ExTabWidgetPrivate::styleSheet() const
{
   return m_clockWidget->styleSheet();
}

QString ExTabWidgetPrivate::clockStyleSheet() const
{
   return m_clockWidget->styleSheet();
}

QString ExTabWidgetPrivate::loginStyleSheet() const
{
   return m_loginWidget->styleSheet();
}

QString ExTabWidgetPrivate::messageStyleSheet() const
{
   return m_messageWidget->styleSheet();
}

void ExTabWidgetPrivate::setStyleSheet(const QString& styleSheet)
{
   m_stylesheet = styleSheet;
   m_clockWidget->setStyleSheet(styleSheet);
   m_loginWidget->setStyleSheet(styleSheet);
   m_messageWidget->setStyleSheet(styleSheet);
}

void ExTabWidgetPrivate::setClockStyleSheet(const QString& styleSheet)
{
   m_clockWidget->setStyleSheet(styleSheet);
}

void ExTabWidgetPrivate::setLoginStyleSheet(const QString& styleSheet)
{
   m_loginWidget->setStyleSheet(styleSheet);
}

void ExTabWidgetPrivate::setMessageStyleSheet(const QString& styleSheet)
{
   m_messageWidget->setStyleSheet(styleSheet);
}

void ExTabWidgetPrivate::paintLogin(QPainter* painter, int w, int h)
{
   if (m_showLogin) {
      int frameWidth;

      if (!m_loginRect) {
         m_loginRect = new QRect();
         QFontMetrics fm = painter->fontMetrics();
         m_stringAdvance = fm.horizontalAdvance(LOGOUT);
         frameWidth = m_stringAdvance + 20;
         m_loginRect->setX(w - frameWidth);
         m_loginRect->setY((h - (m_frameHeight + 6)) / 2);
         m_loginRect->setWidth(frameWidth);
         m_loginRect->setHeight(m_frameHeight + 2);

         w -= (frameWidth + 2);

      } else {
         w -= (m_loginRect->width() + 2);
      }

      if (m_showFrame) {
         if (m_loginPressed) {
            painter->setPen(m_palette.color(QPalette::Light));

         } else {
            painter->setPen(m_palette.color(QPalette::Dark));
         }

         painter->fillRect(*m_loginRect, painter->brush());

         painter->drawLine(m_loginRect->x(),
                           m_loginRect->y(),
                           m_loginRect->x(),
                           m_loginRect->y() + m_loginRect->height());
         painter->drawLine(m_loginRect->x() + 1,
                           m_loginRect->y() + 1,
                           m_loginRect->x() + 1,
                           m_loginRect->y() + m_loginRect->height() - 1);
         painter->drawLine(m_loginRect->x() + 1,
                           m_loginRect->y(),
                           m_loginRect->x() + m_loginRect->width(),
                           m_loginRect->y());
         painter->drawLine(m_loginRect->x() + 2,
                           m_loginRect->y() + 1,
                           m_loginRect->x() + m_loginRect->width() - 1,
                           m_loginRect->y() + 1);

         painter->setPen(m_palette.color(QPalette::Light));
         painter->drawLine(m_loginRect->x() + 1,
                           m_loginRect->y() + m_loginRect->height(),
                           m_loginRect->x() + m_loginRect->width(),
                           m_loginRect->y() + m_loginRect->height());
         painter->drawLine(m_loginRect->x() + 2,
                           m_loginRect->y() + m_loginRect->height() - 1,
                           m_loginRect->x() + m_loginRect->width() - 1,
                           m_loginRect->y() + m_loginRect->height() - 1);
         painter->drawLine(m_loginRect->x() + m_loginRect->width(),
                           m_loginRect->y() + 1,
                           m_loginRect->x() + m_loginRect->width(),
                           m_loginRect->y() + m_loginRect->height() - 1);
         painter->drawLine(m_loginRect->x() + m_loginRect->width() - 1,
                           m_loginRect->y() + 2,
                           m_loginRect->x() + m_loginRect->width() - 1,
                           m_loginRect->y() + m_loginRect->height() - 2);
      }

      if (m_loginPressed) {
         painter->setPen(m_palette.color(QPalette::Dark));

      } else {
         painter->setPen(m_palette.color(QPalette::Light));
      }

      painter->setPen(m_palette.color(QPalette::WindowText));
      painter->drawText(
         m_loginRect->x() + 10, m_loginRect->y() + m_frameHeight - 4, m_loginText);
   }
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
      int tw = m_tabs->tabBar()->width();

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
   m_loginText = LOGIN;
}

void ExTabWidgetPrivate::displayLogoutText()
{
   m_loginText = LOGOUT;
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
   if (showSeconds != m_clockWidget->showSeconds()) {
      if (m_showMessages) {
         // TODO remove
         m_messageRect = nullptr;
      }

      m_clockWidget->setShowSeconds(showSeconds);
      repositionWidgets();
      q_ptr->update();
   }
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


ExTabWidgetPrivate::ClockWidget::ClockWidget(QWidget* parent)
   : QFrame(parent)
   , m_clockTimer(nullptr)
   , m_showSeconds(false)
{
}

int ExTabWidgetPrivate::ClockWidget::calculateRequiredWidth()
{
   QFontMetrics fm = fontMetrics();

   // always use LOGOUT as it is the longer. Dont want width to change.
   if (m_showSeconds) {
      return fm.horizontalAdvance(WITHSECONDS) + 20;

   } else {
      return fm.horizontalAdvance(NOSECONDS) + 20;
   }
}

void ExTabWidgetPrivate::ClockWidget::showClock(bool showClock)
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

void ExTabWidgetPrivate::ClockWidget::paintEvent(QPaintEvent* evt)
{
   QFrame::paintEvent(evt);

   QPainter* painter = new QPainter(this);
   //   if (m_showFrame) {
   //     painter->fillRect(*m_clockRect, painter->brush());
   //     paintBorder(painter, m_clockRect->x(), m_clockRect->y(), m_clockRect->width(), m_clockRect->height(), false);
   //   }

   painter->setPen(palette().color(QPalette::WindowText));
   painter->drawText(
      x() + 10, y() + height() - 4, m_nowString);

}

int ExTabWidgetPrivate::ClockWidget::resize()
{
   int w = calculateRequiredWidth();
   int h = qobject_cast<ExTabWidget*>(parent())->d_ptr->m_frameX;
   setMinimumSize(QSize(w, h));
   setMaximumSize(QSize(w, h));
   return w;
}

void ExTabWidgetPrivate::ClockWidget::nextSecond()
{
   QString format = "hh:mm";

   if (m_showSeconds) {
      format += ":ss";
   }

   QDateTime now = QDateTime::currentDateTime();
   m_nowString = now.toString(format);
   m_now = now.toTime_t();

   update();
}

bool ExTabWidgetPrivate::ClockWidget::showSeconds() const
{
   return m_showSeconds;
}

void ExTabWidgetPrivate::ClockWidget::setShowSeconds(bool value)
{
   m_showSeconds = value;
   update();
}

/// \endcond

ExTabWidgetPrivate::LoginWidget::LoginWidget(QWidget* parent)
   : QFrame(parent)
{

}

int ExTabWidgetPrivate::LoginWidget::calculateRequiredWidth()
{
   if (isVisible()) {
      QFontMetrics fm = fontMetrics();
      // always use LOGOUT as it is the longer. Dont want width to change.
      return fm.horizontalAdvance(LOGOUT) + 20;

   } else {
      return 0;
   }
}

void ExTabWidgetPrivate::LoginWidget::paintEvent(QPaintEvent* evt)
{
   QFrame::paintEvent(evt);
}

ExTabWidgetPrivate::MessageWidget::MessageWidget(QWidget* parent)
{

}

void ExTabWidgetPrivate::MessageWidget::paintEvent(QPaintEvent* evt)
{
   QFrame::paintEvent(evt);
}
