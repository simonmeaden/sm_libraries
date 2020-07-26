#include "extabwidget_p.h"
#include "extabwidget.h"

const QString ExTabWidgetPrivate::LOGIN = "Log In";
const QString ExTabWidgetPrivate::LOGOUT = "Log Out";
const QString ExTabWidgetPrivate::WITHSECONDS = "00:00:00";
const QString ExTabWidgetPrivate::NOSECONDS = "00:00";

ExTabWidgetPrivate::ExTabWidgetPrivate(ExTabWidget* parent,
                                       AbstractLoginDialog* customDlg = nullptr)
   : q_ptr(parent)
   , m_loggedIn(false)
   , // control flags for extensions
     m_showLogin(false)
   ,
     //  m_login(true),
     //  m_simplelogin(false),
     m_showClock(false)
   , m_showMessages(false)
   , m_loginDlg(new LoginDialog(q_ptr))
   , m_customLoginDlg(customDlg)
   , m_loginRect(nullptr)
   , m_clockRect(nullptr)
   , m_messageRect(nullptr)
   , m_now(0)
   , // Clock time
     m_showSeconds(false)
   , // show seconds in clock
     m_showFrame(true)
   , // show frames around extensions
     m_isInframe(false)
   , // mouse test flags for login
     m_loginPressed(false)
   , m_ignoreCase(false)
   , // case in login names and passwords.
     m_clockTimer(nullptr)
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

   if (m_clockRect) {
      delete m_clockRect;
      m_clockRect = nullptr;
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

void ExTabWidgetPrivate::showFrame(bool frame)
{
   m_showFrame = frame;
   q_ptr->update();
}

void ExTabWidgetPrivate::showClock(bool clock)
{
   m_showClock = clock;

   if (m_showClock) {
      if (m_clockTimer) {
         if (m_clockTimer->isActive()) {
            return;

         } else {
            m_clockTimer->start(CLOCK_TIME);
         }

      } else {
         m_clockTimer = new QTimer(q_ptr);
         q_ptr->connect(m_clockTimer, &QTimer::timeout,
                        q_ptr, &ExTabWidget::nextSecond,
                        Qt::UniqueConnection);
         m_clockTimer->start(CLOCK_TIME);
      }

   } else {
      if (m_clockTimer && m_clockTimer->isActive()) {
         m_clockTimer->stop();
         m_clockTimer->deleteLater();
         m_clockTimer = nullptr;
      }
   }

   clearFrames();

   q_ptr->update();
}

void ExTabWidgetPrivate::showMessages(bool messages)
{
   m_showMessages = messages;

   if (m_showMessages) {
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

void ExTabWidgetPrivate::setMarqueeSpeed(int speed)
{
   m_marqueeSpeed = 1000 / speed;
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
      q_ptr->connect(m_marqueeTimer,
                     SIGNAL(timeout()),
                     q_ptr,
                     SLOT(updateMarquee()),
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

void ExTabWidgetPrivate::showLogin(bool login)
{
   m_showLogin = login;

   clearFrames();

   q_ptr->update();
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
            }
         }
      }

      return true;

   } else {
      return false;
   }

   q_ptr->update();
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
   clearFrames();
   q_ptr->update();
}

void ExTabWidgetPrivate::paint(QPainter* painter, QPaintEvent* event)
{

   int w = event->rect().width() - 10;
   int h = q_ptr->tabBar()->height();
   int tw = q_ptr->tabBar()->width();
   int sh = h * 0.6; // set the font height to be 60% of the total height.
   int frameWidth;

   QFont font = painter->font();
   font.setPixelSize(sh);
   painter->setFont(font);
   QFontMetrics fm = painter->fontMetrics();
   m_frameHeight = fm.height();

   if (m_showLogin) {

      if (!m_loginRect) {
         m_loginRect = new QRect();
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

   if (m_showClock) {

      if (!m_clockRect) {
         m_clockRect = new QRect();

         if (m_showSeconds) {
            m_stringAdvance = fm.horizontalAdvance(WITHSECONDS);

         } else {
            m_stringAdvance = fm.horizontalAdvance(NOSECONDS);
         }

         frameWidth = m_stringAdvance + 20;
         // not used unless another thing is added before message
         m_clockRect->setX(w - frameWidth);
         m_clockRect->setY((h - (m_frameHeight + 6)) / 2);
         m_clockRect->setWidth(frameWidth);
         m_clockRect->setHeight(m_frameHeight + 2);

         w -= (frameWidth + 2);

      } else {
         w -= (m_clockRect->width() + 2);
      }

      if (m_showFrame) {
         painter->setPen(m_palette.color(QPalette::Dark));
         painter->drawLine(m_clockRect->x(),
                           m_clockRect->y(),
                           m_clockRect->x(),
                           m_clockRect->y() + m_clockRect->height());
         painter->drawLine(m_clockRect->x() + 1,
                           m_clockRect->y() + 1,
                           m_clockRect->x() + 1,
                           m_clockRect->y() + m_clockRect->height() - 1);
         painter->drawLine(m_clockRect->x() + 1,
                           m_clockRect->y(),
                           m_clockRect->x() + m_clockRect->width(),
                           m_clockRect->y());
         painter->drawLine(m_clockRect->x() + 2,
                           m_clockRect->y() + 1,
                           m_clockRect->x() + m_clockRect->width() - 1,
                           m_clockRect->y() + 1);

         painter->setPen(m_palette.color(QPalette::Light));
         painter->drawLine(m_clockRect->x() + 1,
                           m_clockRect->y() + m_clockRect->height(),
                           m_clockRect->x() + m_clockRect->width(),
                           m_clockRect->y() + m_clockRect->height());
         painter->drawLine(m_clockRect->x() + 2,
                           m_clockRect->y() + m_clockRect->height() - 1,
                           m_clockRect->x() + m_clockRect->width() - 1,
                           m_clockRect->y() + m_clockRect->height() - 1);
         painter->drawLine(m_clockRect->x() + m_clockRect->width(),
                           m_clockRect->y() + 1,
                           m_clockRect->x() + m_clockRect->width(),
                           m_clockRect->y() + m_clockRect->height() - 1);
         painter->drawLine(m_clockRect->x() + m_clockRect->width() - 1,
                           m_clockRect->y() + 2,
                           m_clockRect->x() + m_clockRect->width() - 1,
                           m_clockRect->y() + m_clockRect->height() - 2);
      }

      painter->setPen(m_palette.color(QPalette::WindowText));
      painter->drawText(
         m_clockRect->x() + 10, m_clockRect->y() + m_frameHeight - 4, m_nowString);
   }

   if (m_showMessages) {

      QString text;

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

      if (m_useTempColor) {
         messagePalette.setColor(QPalette::WindowText, m_tempColor);

      } else {
         messagePalette.setColor(QPalette::WindowText, m_textColor);
      }

      if (m_useTempBack && m_tempBackground.color().isValid()) {
         painter->fillRect(*m_messageRect, m_tempBackground);

      } else if (m_background.color().isValid()) {
         painter->fillRect(*m_messageRect, m_background);
      }

      if (m_showFrame) {
         painter->setPen(m_palette.color(QPalette::Dark));
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
         m_messageRect->x() + 10, m_messageRect->y() + m_frameHeight - 6, text);
   }
}

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

void ExTabWidgetPrivate::nextSecond()
{
   QString format = "hh:mm";

   if (m_showSeconds) {
      format += ":ss";
   }

   QDateTime now = QDateTime::currentDateTime();
   m_nowString = now.toString(format);
   m_now = now.toTime_t();

   q_ptr->update();
}

void ExTabWidgetPrivate::showSeconds(bool show)
{
   m_showSeconds = show;
   q_ptr->update();
   m_clockRect = nullptr;
   q_ptr->update();
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

void ExTabWidgetPrivate::timeout()
{
   m_useTempColor = false;
   m_timeoutTimer->stop();
   m_timeoutTimer->deleteLater();
   m_timeoutTimer = nullptr;
   clearMessage();
}

void ExTabWidgetPrivate::setMessage(QString message, uint timeout)
{
   m_messageText = message;
   m_marqueePos = 0;
   m_useTempColor = false;
   setMessage(timeout);
}

void ExTabWidgetPrivate::setMessage(QColor color, QString message, uint timeout)
{
   m_messageText = message;
   m_useTempColor = true;
   m_tempColor = color;
   setMessage(timeout);
}

void ExTabWidgetPrivate::setMessage(QColor color,
                                    QColor back,
                                    QString message,
                                    uint timeout)
{
   m_messageText = message;
   m_useTempBack = true;
   m_useTempColor = true;
   m_tempColor = color;
   m_tempBackground = QBrush(back);
   setMessage(timeout);
}

void ExTabWidgetPrivate::setMessage(QColor color,
                                    QBrush back,
                                    QString message,
                                    uint timeout)
{
   m_messageText = message;
   m_useTempBack = true;
   m_useTempColor = true;
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
