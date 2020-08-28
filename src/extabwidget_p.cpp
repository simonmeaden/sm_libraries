#include "extabwidget_p.h"
#include "sm_widgets/extabwidget.h"

/// \cond DO_NOT_DOCUMENT
ExTabWidgetPrivate::ExTabWidgetPrivate(ExTabWidget* parent,
                                       AbstractLoginDialog* customDlg = nullptr,
                                       quint64 key = 0)
   : q_ptr(parent)
   , m_wrapper(new WrapperWidget(q_ptr, key))
{
   q_ptr->setContentsMargins(0, 0, 0, 0);

   if (customDlg) {
      m_wrapper->setLoginType(AbstractLoginDialog::Custom);
      m_wrapper->setCustomLoginDialog(customDlg);
   }

   // send wrapper signals on to ExTabWidget
   q_ptr->connect(m_wrapper, &WrapperWidget::loginSucceeded, q_ptr, &ExTabWidget::loginSucceeded);
   q_ptr->connect(m_wrapper, &WrapperWidget::loginFailed, q_ptr, &ExTabWidget::loginFailed);
   q_ptr->connect(m_wrapper, &WrapperWidget::loggedOut, q_ptr, &ExTabWidget::loggedOut);
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
   m_wrapper->setClockFrame(style);
}

void ExTabWidgetPrivate::setLoginText(const QString& text)
{
   m_wrapper->setLoginText(text);
}

void ExTabWidgetPrivate::setLogoutText(const QString& text)
{
   m_wrapper->setLogoutText(text);
}

void ExTabWidgetPrivate::setMessageFrame(QFrame::Shape style)
{
   m_wrapper->setMessageFrame(style);
}

bool ExTabWidgetPrivate::isMarqueeEnabled()
{
   return m_wrapper->isMarqueeEnabled();
}

void ExTabWidgetPrivate::showClock(bool showClock)
{
   m_wrapper->showClock(showClock);
   m_wrapper->calculateWidgetSizes(m_frameWidth, m_frameHeight);
   q_ptr->update();
}

bool ExTabWidgetPrivate::isShowClock()
{
   return m_wrapper->isShowClock();
}

void ExTabWidgetPrivate::showMessages(bool show)
{
   m_wrapper->showMessages(show);
   m_wrapper->calculateWidgetSizes(m_frameWidth, m_frameHeight);
}

bool ExTabWidgetPrivate::isShowMessages()
{
   return m_wrapper->isShowMessages();
}

void ExTabWidgetPrivate::enableMarquee(bool enable)
{
   m_wrapper->enableMarquee(enable);
}

void ExTabWidgetPrivate::setMarqueeSpeed(qreal charPerSecond)
{
   m_wrapper->setMarqueeSpeed(charPerSecond);
}

void ExTabWidgetPrivate::showLogin(bool showLogin)
{
   m_wrapper->showLogin(showLogin);
   m_wrapper->calculateWidgetSizes(m_frameWidth, m_frameHeight);
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

void ExTabWidgetPrivate::tabwidgetStatusChanged()
{
   int tabWidth = q_ptr->tabBar()->width();
   m_frameWidth = q_ptr->width() - tabWidth;
   m_frameHeight = q_ptr->tabBar()->height() - 2;

   m_wrapper->setGeometry(q_ptr->tabBar()->width(),
                          q_ptr->tabBar()->y(),
                          m_frameWidth,
                          m_frameHeight);
   q_ptr->update();
}

QString ExTabWidgetPrivate::styleSheet() const
{
   return m_stylesheet;
}

QString ExTabWidgetPrivate::setStyleSheet(const QString& stylesheet)
{
   if (stylesheet.isEmpty()) {
      setClockStyleSheet(stylesheet);
      setLoginStyleSheet(stylesheet);
      setMessageStyleSheet(stylesheet);
      m_wrapper->calculateWidgetSizes(m_frameWidth, m_frameHeight);
      return stylesheet;
   }

   // simplified() cleans extra whitespace.
   QString sheet = stylesheet.simplified();
   QString reExTabWidget, reClock, reMessage, reLogin, reBetweenCurly;
   QString resExTabWidget, resClock, resMessage, resLogin;
   QString exTabWidget, clock, login, message;

   reExTabWidget = "ExTabWidget[\\s]*{[\\-\\w:;\\s]*}";
   reClock = "ExTabWidget::clock[\\s]*{[\\-\\w:;\\s]*}";
   reMessage = "ExTabWidget::message[\\s]*{[\\-\\w:;\\s]*}";
   reLogin = "ExTabWidget::login[\\s]*{[\\-\\w:;\\s]*}";
   reBetweenCurly = "{([^}]*)}";

   QRegularExpression re;
   re.setPattern(reLogin);
   QRegularExpressionMatchIterator it = re.globalMatch(sheet);

   while (it.hasNext()) {
      QRegularExpressionMatch match = it.next();

      for (auto m : match.capturedTexts()) {
         re.setPattern(reBetweenCurly);
         match = re.match(m);

         if (match.hasMatch()) {
            m = match.captured(0);
            // remove curly braces.
            resLogin += m.mid(1, m.length() - 2);
         }
      }
   }

   resLogin = resLogin.simplified();

   re.setPattern(reMessage);
   it = re.globalMatch(sheet);

   while (it.hasNext()) {
      QRegularExpressionMatch match = it.next();

      for (auto m : match.capturedTexts()) {
         re.setPattern(reBetweenCurly);
         match = re.match(m);

         if (match.hasMatch()) {
            m = match.captured(0);
            resMessage += m.mid(1, m.length() - 2);
         }
      }
   }

   resMessage = resMessage.simplified();

   re.setPattern(reClock);
   it = re.globalMatch(sheet);

   while (it.hasNext()) {
      QRegularExpressionMatch match = it.next();

      for (auto m : match.capturedTexts()) {
         re.setPattern(reBetweenCurly);
         match = re.match(m);

         if (match.hasMatch()) {
            m = match.captured(0);
            resClock += m.mid(1, m.length() - 2);
         }
      }
   }

   resClock = resClock.simplified();

   re.setPattern(reExTabWidget);
   it = re.globalMatch(sheet);

   while (it.hasNext()) {
      QRegularExpressionMatch match = it.next();

      for (auto m : match.capturedTexts()) {
         re.setPattern(reBetweenCurly);
         match = re.match(m);

         if (match.hasMatch()) {
            m = match.captured(0);
            resExTabWidget += m.mid(1, m.length() - 2);
         }
      }
   }

   resExTabWidget = resExTabWidget.simplified();

   setClockStyleSheet(resClock);
   setLoginStyleSheet(resLogin);
   setMessageStyleSheet(resMessage);

   m_wrapper->calculateWidgetSizes(m_frameWidth, m_frameHeight);

   // Setting the Overall stylesheet is done in ExTabWidget as this
   // has access to the parent setStyleSheet() method.
   return resExTabWidget;
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
   m_wrapper->setLoginStyleSheet(styleSheet);
}

void ExTabWidgetPrivate::setMessageStyleSheet(const QString& styleSheet)
{
   m_wrapper->setMessageStyleSheet(styleSheet);
}

void ExTabWidgetPrivate::setLargeTextForLoginDialog(bool)
{
   // TODO
}

bool ExTabWidgetPrivate::isLoginEnabled()
{
   return m_wrapper->isLoginEnabled();
}

void ExTabWidgetPrivate::setPassword(QString password)
{
   m_wrapper->setSimplePassword(password);
}

void ExTabWidgetPrivate::addUser(QString username, QString password)
{
   m_wrapper->addUser(username, password);
}

void ExTabWidgetPrivate::removeUser(const QString& username)
{
   m_wrapper->removeUser(username);
}

void ExTabWidgetPrivate::clearUsers()
{
   m_wrapper->clearUsers();
}

void ExTabWidgetPrivate::setKey(quint64 key)
{
   m_wrapper->setKey(key);
}

void ExTabWidgetPrivate::showSeconds(bool showSeconds)
{
   m_wrapper->setShowSeconds(showSeconds);
   m_wrapper->calculateWidgetSizes(m_frameWidth, m_frameHeight - 1);
}

void ExTabWidgetPrivate::clearMessage()
{
   m_wrapper->clearMessageText();
}

void ExTabWidgetPrivate::messageTimeout()
{
   //   m_useTempColor = false;
   //   m_timeoutTimer->stop();
   //   m_timeoutTimer->deleteLater();
   //   m_timeoutTimer = nullptr;
   //   clearMessage();
}

void ExTabWidgetPrivate::setMessage(const QString& message, uint timeout)
{
   m_wrapper->setMessageText(message, timeout);
   //   resetMessageData(message, false);
   //   setMessage(timeout);
}


//== WrapperWidget ========================================================================

WrapperWidget::WrapperWidget(QWidget* parent, quint64 key)
   : QFrame(parent)
   , m_parent(parent)
   , m_layout(new QGridLayout)
   , m_clockWidget(nullptr)
   , m_loginWidget(nullptr)
   , m_messageWidget(nullptr)
   , m_filler(nullptr)
   , m_marqueeSpeed(MessageWidget::DEF_MARQUEE_TIME)
   , m_key(key)
   , m_ignoreCase(false)
   , m_showSeconds(false)
   , m_clockFrame(QFrame::Shape::StyledPanel)
{
   //   setStyleSheet("background: lightgreen;");
   setContentsMargins(0, 0, 3, 0);
   m_layout->setContentsMargins(0, 0, 0, 0);
   setLayout(m_layout);
}

void WrapperWidget::setKey(quint64 key)
{
   if (m_loginWidget) {
      m_loginWidget->setKey(key);
   }

   m_key = key;
}

void WrapperWidget::setLoginText(const QString& text)
{
   if (m_loginWidget) {
      m_loginWidget->setLoginText(text);
   }
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

//QString WrapperWidget::username()
//{
//   if (m_loginWidget) {
//      return m_loginWidget->username();
//   }

//   return QString();
//}

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

void WrapperWidget::rebuildPasswords()
{
   if (m_loginWidget->loginType() == AbstractLoginDialog::Simple) {
      if (!m_simplePassword.isEmpty()) {
         m_loginWidget->setSimplePassword(AbstractLoginDialog::decrypt(m_simplePassword, m_key));
      }

   } else if (m_loginWidget->loginType() == AbstractLoginDialog::Standard ||
              m_loginWidget->loginType() == AbstractLoginDialog::Custom) {
      m_loginWidget->clearUsers();

      for (auto user : m_passwords.keys()) {
         QString password = m_passwords.value(user);
         m_loginWidget->addUser(user, AbstractLoginDialog::decrypt(password, m_key));
      }
   }
}

void WrapperWidget::showLogin(bool show)
{
   removeWidgetsFromLayout();

   if (show) {
      if (!m_loginWidget) {
         m_loginWidget = new LoginWidget(m_parent, m_key);
         m_loginWidget->setSizePolicy(QSizePolicy::Preferred,
                                      QSizePolicy::Fixed);
         m_loginWidget->showLogin(true);

         rebuildPasswords();

         if (!m_loginStylesheet.isEmpty()) {
            m_loginWidget->setStyleSheet(m_loginStylesheet);
         }

         connect(m_loginWidget, &LoginWidget::loginSucceeded, this, &WrapperWidget::loginSucceeded);
         connect(m_loginWidget, &LoginWidget::loginFailed, this, &WrapperWidget::loginFailed);
         connect(m_loginWidget, &LoginWidget::loggedOut, this, &WrapperWidget::loggedOut);
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
}

bool WrapperWidget::hasCustomLoginDialog()
{
   if (m_loginWidget) {
      return m_loginWidget->hasCustomLoginDialog();
   }

   return false;
}

void WrapperWidget::setSimplePassword(QString password)
{
   if (m_loginWidget) {
      m_loginWidget->setSimplePassword(password);
      m_simplePassword = AbstractLoginDialog::encrypt(password, m_key);
   }
}

void WrapperWidget::clearUsers()
{
   if (m_loginWidget) {
      m_loginWidget->clearUsers();
      m_passwords.clear();
   }
}

void WrapperWidget::addUser(QString username, QString password)
{
   if (m_loginWidget) {
      m_loginWidget->addUser(username, password);
      m_passwords[username] = AbstractLoginDialog::encrypt(password, m_key);
   }
}

void WrapperWidget::removeUser(const QString& username)
{
   if (m_loginWidget) {
      m_loginWidget->removeUser(username);
      m_passwords.remove(username);
   }
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
         m_clockWidget->setFrameStyle(m_clockFrame);
         m_clockWidget->setSizePolicy(QSizePolicy::Preferred,
                                      QSizePolicy::Fixed);
         m_clockWidget->setShowSeconds(m_showSeconds);
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

bool WrapperWidget::isShowMessages()
{
   if (m_messageWidget) {
      return m_messageWidget->isShowing();
   }

   return false;
}

bool WrapperWidget::isMarqueeEnabled()
{
   if (m_messageWidget) {
      return m_messageWidget->isMarqueeEnabled();
   }

   return false;
}

void WrapperWidget::clearMessageText()
{
   if (m_messageWidget) {
      m_messageWidget->clearMessage();
   }
}

void WrapperWidget::enableMarquee(bool enable)
{
   if (m_messageWidget) {
      m_messageWidget->enableMarquee(enable);
   }
}

void WrapperWidget::setMessageFrame(QFrame::Shape style)
{
   if (m_messageWidget) {
      m_messageWidget->setMessageFrame(style);
   }
}

void WrapperWidget::setMessageText(const QString& message, quint32 timeout)
{
   if (m_messageWidget) {
      m_messageWidget->setMessage(message, timeout);
   }
}

void WrapperWidget::setMarqueeSpeed(qreal charPerSecond)
{
   if (m_messageWidget) {
      m_messageWidget->setMarqueeSpeed(charPerSecond);
   }

   m_marqueeSpeed = charPerSecond;
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

void WrapperWidget::calculateWidgetSizes(int w, int h)
{
   int availableWidth = w;

   if (m_loginWidget) {
      int reqWidth =
         m_loginWidget->width();

      if (reqWidth < 0) {
         return;
      }

      //      QSize size = QSize(reqWidth, h  - 1);
      //      m_loginWidget->setSizeHint(size);
      availableWidth -= reqWidth;
   }

   if (m_clockWidget) {
      int reqWidth =
         m_clockWidget->calculateRequiredWidth(availableWidth);

      if (reqWidth < 0) {
         return;
      }

      QSize size = QSize(reqWidth, h - 1);
      m_clockWidget->setSizeHint(size);
      availableWidth -= reqWidth;
   }

   if (m_messageWidget) {
      m_messageWidget->setSizeHint(QSize(availableWidth, h - 1));
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

void WrapperWidget::showMessages(bool show)
{
   // we need to remove the widgets from the layout then after creating
   // or destroying the clock widget reload them in the right order.
   removeWidgetsFromLayout();

   if (show) {
      if (!m_messageWidget) {
         m_messageWidget = new MessageWidget(m_parent);
         m_messageWidget->setSizePolicy(QSizePolicy::Expanding,
                                        QSizePolicy::Fixed);
         m_messageWidget->showMessages(true);

         if (!m_messageStylesheet.isEmpty()) {
            m_messageWidget->setStyleSheet(m_messageStylesheet);
         }
      }

   } else {

      m_messageWidget->deleteLater();
      m_messageWidget = nullptr;
   }

   addWidgetsToLayout();
}

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

void ClockWidget::setClockFrame(QFrame::Shape style = QFrame::NoFrame)
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

const qreal MessageWidget::DEF_MARQUEE_TIME = 500;

MessageWidget::MessageWidget(QWidget* parent)
   : QFrame(parent)
   , m_marqueeTime(DEF_MARQUEE_TIME)
   , m_showMessages(false)
   , m_marqueeEnabled(false)
   , m_marqueeTimer(nullptr)
   , m_timeoutTimer(nullptr)
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
      //      int h = fm.height(); // TODO adjust font Y ??
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

      } else {
         text = m_messageText;
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

/// \endcond DO_NOT_DOCUMENT


