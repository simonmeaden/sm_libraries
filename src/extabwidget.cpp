#include "sm_widgets/loginwidget.h"
#include "sm_widgets/extabwidget.h"
#include "extabwidget_p.h"

ExTabWidget::ExTabWidget(QWidget* parent,
                         AbstractLoginDialog::LoginType type,
                         AbstractLoginDialog* customDlg,
                         quint64 key)
   : QTabWidget(parent)
   , d_ptr(new ExTabWidgetPrivate(this, customDlg, key))
{
   setObjectName("ExTabWidget");
   d_ptr->setLoginType(type);
   connect(this, &ExTabWidget::statusChanged, this, &ExTabWidget::statusHasChanged);
}

int ExTabWidget::addTab(QWidget* page, const QString& label)
{
   emit statusChanged();
   return QTabWidget::addTab(page, label);
}

int ExTabWidget::addTab(QWidget* page, const QIcon& icon, const QString& label)
{
   emit statusChanged();
   return QTabWidget::addTab(page, icon, label);
}

void ExTabWidget::clear()
{
   emit statusChanged();
   QTabWidget::clear();
}

int ExTabWidget::insertTab(int index, QWidget* page, const QString& label)
{
   emit statusChanged();
   return QTabWidget::insertTab(index, page, label);
}

int ExTabWidget::insertTab(int index,
                           QWidget* page,
                           const QIcon& icon,
                           const QString& label)
{
   emit statusChanged();
   return QTabWidget::insertTab(index, page, icon, label);
}

void ExTabWidget::removeTab(int index)
{
   emit statusChanged();
   QTabWidget::removeTab(index);
}

void ExTabWidget::setIconSize(const QSize& size)
{
   emit statusChanged();
   QTabWidget::setIconSize(size);
}

void ExTabWidget::setTabIcon(int index, const QIcon& icon)
{
   emit statusChanged();
   QTabWidget::setTabIcon(index, icon);
}

void ExTabWidget::setTabShape(QTabWidget::TabShape s)
{
   emit statusChanged();
   QTabWidget::setTabShape(s);
}

void ExTabWidget::setTabText(int index, const QString& label)
{
   emit statusChanged();
   QTabWidget::setTabText(index, label);
}
void ExTabWidget::setTabVisible(int index, bool visible)
{
   emit statusChanged();
  QTabWidget::setTabVisible(index, visible);
}

QString ExTabWidget::styleSheet() const
{
  return d_ptr->styleSheet();
}

void ExTabWidget::setStyleSheet(const QString &stylesheet) {
  QString sheet = d_ptr->setStyleSheet(stylesheet);
  QTabWidget::setStyleSheet(sheet);
}



//== Clock shit =========================================================
void ExTabWidget::showSeconds(bool showSeconds)
{
   d_ptr->showSeconds(showSeconds);
}

bool ExTabWidget::isClockEnabled()
{
   return d_ptr->isShowClock();
}

//QString ExTabWidget::clockStyleSheet() const
//{
//   return d_ptr->clockStyleSheet();
//}

//void ExTabWidget::setClockStyleSheet(const QString& styleSheet)
//{
//   d_ptr->setClockStyleSheet(styleSheet);
//}

void ExTabWidget::setClockFrameStyle(QFrame::Shape style)
{
   d_ptr->setClockFrame(style);
}

void ExTabWidget::enableClock(bool showClock)
{
   d_ptr->showClock(showClock);
   d_ptr->tabwidgetStatusChanged();
}


//== Message shit =======================================================
void ExTabWidget::setMessage(QString message, uint timeout)
{
   d_ptr->setMessage(message, timeout);
}

void ExTabWidget::enableMarquee(bool enable)
{
   d_ptr->enableMarquee(enable);
}

void ExTabWidget::setMarqueeSpeed(qreal charPerSecond)
{
   d_ptr->setMarqueeSpeed(charPerSecond);
}

void ExTabWidget::clearMessage()
{
   d_ptr->clearMessage();
}

bool ExTabWidget::isMessagesEnabled()
{
   return d_ptr->isShowMessages();
}

bool ExTabWidget::isMarqueeEnabled()
{
   return d_ptr->isMarqueeEnabled();
}

//QString ExTabWidget::messageStyleSheet() const
//{
//   return d_ptr->messageStyleSheet();
//}

void ExTabWidget::enableMessages(bool showMessages)
{
   d_ptr->showMessages(showMessages);
}

void ExTabWidget::setMessageFrame(QFrame::Shape style)
{
   d_ptr->setMessageFrame(style);
}

//== Login shit =========================================================

void ExTabWidget::enableLogin(bool showLogin)
{
   d_ptr->showLogin(showLogin);
   d_ptr->tabwidgetStatusChanged();
}

bool ExTabWidget::isLoginEnabled()
{
   return d_ptr->isLoginEnabled();
}

void ExTabWidget::setLoginType(AbstractLoginDialog::LoginType type)
{
   d_ptr->setLoginType(type);
}

AbstractLoginDialog::LoginType ExTabWidget::loginType()
{
   return d_ptr->loginType();
}

void ExTabWidget::setCustomLoginDialog(AbstractLoginDialog* loginDlg)
{
   d_ptr->setCustomLoginDialog(loginDlg);
}

//QString ExTabWidget::loginStyleSheet() const
//{
//   return d_ptr->loginStyleSheet();
//}

void ExTabWidget::setLoginText(const QString& text)
{
   d_ptr->setLoginText(text);
}

void ExTabWidget::setLogoutText(const QString& text)
{
   d_ptr->setLogoutText(text);
}

void ExTabWidget::setSimplePassword(QString password)
{
   d_ptr->setPassword(password);
}

void ExTabWidget::addStandardPassword(QString username, QString password)
{
   d_ptr->addUser(username, password);
}

void ExTabWidget::clearPasswords()
{
   d_ptr->clearUsers();
}

bool ExTabWidget::isLoggedIn()
{
   return d_ptr->isLoggedIn();
}

//void ExTabWidget::setLoginStyleSheet(const QString& styleSheet)
//{
//   d_ptr->setLoginStyleSheet(styleSheet);
//}

//void ExTabWidget::setMessageStyleSheet(const QString& styleSheet)
//{
//   d_ptr->setMessageStyleSheet(styleSheet);
//}

void ExTabWidget::statusHasChanged()
{
   d_ptr->tabwidgetStatusChanged();
}

void ExTabWidget::setKey(quint64 key)
{
   d_ptr->setKey(key);
}

void ExTabWidget::resizeEvent(QResizeEvent* evt)
{
   QTabWidget::resizeEvent(evt);
   d_ptr->tabwidgetStatusChanged();
}

void ExTabWidget::addUser(QString username, QString password)
{
   d_ptr->addUser(username, password);
}

void ExTabWidget::removeUser(const QString& username)
{
   d_ptr->removeUser(username);
}

void ExTabWidget::clearUsers()
{
   d_ptr->clearUsers();
}

//}
