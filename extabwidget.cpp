#include "extabwidget.h"
#include "private/extabwidget_p.h"

ExTabWidget::ExTabWidget(QWidget* parent,
                         AbstractLoginDialog::LoginType type,
                         AbstractLoginDialog* customDlg)
   : QTabWidget(parent)
   , d_ptr(new ExTabWidgetPrivate(this, customDlg))
{
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

bool ExTabWidget::isLoggedIn()
{
   return d_ptr->isLoggedIn();
}

QString ExTabWidget::username()
{
   return d_ptr->username();
}

bool ExTabWidget::isClockEnabled()
{
   return d_ptr->isShowClock();
}

bool ExTabWidget::isLoginEnabled()
{
   return d_ptr->isLoginEnabled();
}

bool ExTabWidget::isMessagesEnabled()
{
  // TODO
   Q_D(ExTabWidget);
   return d->m_showMessages;
}

bool ExTabWidget::isIgnoreCase()
{
  return d_ptr->isIgnoreCase();
}

bool ExTabWidget::isMarqueeEnabled()
{
  // TODO
   Q_D(ExTabWidget);
   return d->m_marquee;
}

QBrush ExTabWidget::messageBackground()
{
   return d_ptr->messageBackgroundBrush();
}

QColor ExTabWidget::messageColor()
{
   return d_ptr->messageTextColor();
}

void ExTabWidget::showClock(bool showClock)
{
   d_ptr->showClock(showClock);
   d_ptr->tabwidgetStatusChanged();
}

void ExTabWidget::showLogin(bool showLogin)
{
   d_ptr->showLogin(showLogin);
   d_ptr->tabwidgetStatusChanged();
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

void ExTabWidget::showMessages(bool showMessages)
{
   d_ptr->showMessages(showMessages);
}

void ExTabWidget::setClockFrameStyle(QFrame::Shape style)
{
   d_ptr->setClockFrame(style);
}

void ExTabWidget::showMessageFrame(bool showFrame, QFrame::Shape style)
{
   d_ptr->showMessageFrame(showFrame, style);
}

void ExTabWidget::setPassword(QString password)
{
   d_ptr->addPassword(password);
}

void ExTabWidget::addPassword(QString id, QString password)
{
   d_ptr->addPassword(id, password);
}

void ExTabWidget::clearPasswords()
{
   d_ptr->clearPasswords();
}

void ExTabWidget::setIgnoreCase(bool ignoreCase)
{
   d_ptr->setIgnoreCase(ignoreCase);
}

void ExTabWidget::showSeconds(bool showSeconds)
{
   d_ptr->showSeconds(showSeconds);
}

void ExTabWidget::setMessageColor(QColor color)
{
   d_ptr->setMessageColor(color);
}

void ExTabWidget::setMessageBackground(QColor color)
{
   d_ptr->setMessageBackground(color);
}

void ExTabWidget::setMessageBackground(QBrush brush)
{
   d_ptr->setMessageBackground(brush);
}

void ExTabWidget::setMessage(QString message, uint timeout)
{
   d_ptr->setMessage(message, timeout);
}

// void ExTabWidget::setMessage(QColor color, QString message, uint timeout) {
//  d_ptr->setMessage(color, message, timeout);
//}

// void ExTabWidget::setMessage(QColor color, QColor back, QString message, uint
// timeout) {
//  d_ptr->setMessage(color, back, message, timeout);
//}

// void ExTabWidget::setMessage(QColor color, QBrush back, QString message, uint
// timeout) {
//  d_ptr->setMessage(color, back, message, timeout);
//}

void ExTabWidget::setMarquee(bool marquee)
{
   d_ptr->setMarquee(marquee);
}

void ExTabWidget::setMarqueeSpeed(qreal charPerSecond)
{
   d_ptr->setMarqueeSpeed(charPerSecond);
}

void ExTabWidget::clearMessage()
{
   d_ptr->clearMessage();
}

QString ExTabWidget::clockStyleSheet() const
{
   return d_ptr->clockStyleSheet();
}

QString ExTabWidget::loginStyleSheet() const
{
   return d_ptr->loginStyleSheet();
}

QString ExTabWidget::messageStyleSheet() const
{
   return d_ptr->messageStyleSheet();
}

// void ExTabWidget::setStyleSheet(const QString &styleSheet)
//{
//  QTabWidget::setStyleSheet(styleSheet);
//}

void ExTabWidget::setClockStyleSheet(const QString& styleSheet)
{
  d_ptr->setClockStyleSheet(styleSheet);
}

QString ExTabWidget::loginText() const
{
  return d_ptr->loginText();
}

void ExTabWidget::setLoginText(const QString &text)
{
  d_ptr->setLoginText(text);
}

QString ExTabWidget::logoutText() const
{
  return d_ptr->logoutText();
}

void ExTabWidget::setLogoutText(const QString &text)
{
  d_ptr->setLogoutText(text);
}

void ExTabWidget::setLoginStyleSheet(const QString& styleSheet)
{
   d_ptr->setLoginStyleSheet(styleSheet);
}

void ExTabWidget::setMessageStyleSheet(const QString& styleSheet)
{
   d_ptr->setMessageStyleSheet(styleSheet);
}

void ExTabWidget::statusHasChanged()
{
   d_ptr->tabwidgetStatusChanged();
}

//void ExTabWidget::paintEvent(QPaintEvent* evt)
//{
//   d_ptr->paintEvent(evt);
//   //   QTabWidget::paintEvent(evt);
//   //   QStyleOption opt;
//   //   opt.init(this);
//   //   //  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//   //   QPainter* painter = new QPainter(this);
//   //   d_ptr->paint(painter, evt->rect().width() - 10, style());
//   //   delete painter;
//}

// void ExTabWidget::mousePressEvent(QMouseEvent* event)
//{
//   if (!d_ptr->mousePressEvent(event)) {
//      QTabWidget::mousePressEvent(event);
//   }
//}

// void ExTabWidget::mouseReleaseEvent(QMouseEvent* event)
//{
//   if (!d_ptr->mouseReleaseEvent(event)) {
//      QTabWidget::mouseReleaseEvent(event);
//   }
//}

void ExTabWidget::resizeEvent(QResizeEvent* evt)
{
   QTabWidget::resizeEvent(evt);
   d_ptr->tabwidgetStatusChanged();
}

void ExTabWidget::checkPassword(QString password)
{
   d_ptr->checkPassword(password);
}

void ExTabWidget::checkPassword(QString id, QString password)
{
   d_ptr->checkPassword(id, password);
}

void ExTabWidget::updateMarquee()
{
   d_ptr->updateMarquee();
}

void ExTabWidget::timeout()
{
   d_ptr->messageTimeout();
}
