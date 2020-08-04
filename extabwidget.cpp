#include "extabwidget.h"
#include "private/extabwidget_p.h"

ExTabWidget::ExTabWidget(QWidget* parent,
                         ExTabWidget::LoginType type,
                         AbstractLoginDialog* customDlg)
   : QFrame(parent)
   , m_loginType(type)
   , d_ptr(new ExTabWidgetPrivate(this, customDlg))
{}

int ExTabWidget::addTab(QWidget* page, const QString& label)
{
   Q_D(ExTabWidget);
   return d->m_tabs->addTab(page, label);
}

int ExTabWidget::addTab(QWidget* page, const QIcon& icon, const QString& label)
{
   Q_D(ExTabWidget);
   return d->m_tabs->addTab(page, icon, label);
}

void ExTabWidget::clear()
{
   Q_D(ExTabWidget);
   d->m_tabs->clear();
}

const QWidget* ExTabWidget::cornerWidget(Qt::Corner corner)
{
   Q_D(ExTabWidget);
   return d->m_tabs->cornerWidget(corner);
}

int ExTabWidget::count()
{
   Q_D(ExTabWidget);
   return d->m_tabs->count();
}

int ExTabWidget::currentIndex()
{
   Q_D(ExTabWidget);
   return d->m_tabs->currentIndex();
}

bool ExTabWidget::documentMode()
{
   Q_D(ExTabWidget);
   return d->m_tabs->documentMode();
}

Qt::TextElideMode ExTabWidget::elideMode()
{
   Q_D(ExTabWidget);
   return d->m_tabs->elideMode();
}

QSize ExTabWidget::iconSize()
{
   Q_D(ExTabWidget);
   return d->m_tabs->iconSize();
}

int ExTabWidget::indexOf(QWidget* w)
{
   Q_D(ExTabWidget);
   return d->m_tabs->indexOf(w);
}

int ExTabWidget::insertTab(int index, QWidget* page, const QString& label)
{
   Q_D(ExTabWidget);
   return d->m_tabs->insertTab(index, page, label);
}

int ExTabWidget::insertTab(int index,
                           QWidget* page,
                           const QIcon& icon,
                           const QString& label)
{
   Q_D(ExTabWidget);
   return d->m_tabs->insertTab(index, page, icon, label);
}

bool ExTabWidget::isMovable()
{
   Q_D(ExTabWidget);
   return d->m_tabs->isMovable();
}

bool ExTabWidget::isTabEnabled(int index)
{
   Q_D(ExTabWidget);
   return d->m_tabs->isTabEnabled(index);
}

bool ExTabWidget::isTabVisible(int index)
{
   Q_D(ExTabWidget);
   return d->m_tabs->isTabVisible(index);
}

void ExTabWidget::removeTab(int index)
{
   Q_D(ExTabWidget);
   d->m_tabs->removeTab(index);
}

void ExTabWidget::setCornerWidget(QWidget* widget, Qt::Corner corner)
{
   Q_D(ExTabWidget);
   d->m_tabs->setCornerWidget(widget, corner);
}

void ExTabWidget::setDocumentMode(bool set)
{
   Q_D(ExTabWidget);
   d->m_tabs->setDocumentMode(set);
}

void ExTabWidget::setElideMode(Qt::TextElideMode mode)
{
   Q_D(ExTabWidget);
   d->m_tabs->setElideMode(mode);
}

void ExTabWidget::setIconSize(const QSize& size)
{
   Q_D(ExTabWidget);
   d->m_tabs->setIconSize(size);
}

void ExTabWidget::setMovable(bool movable)
{
   Q_D(ExTabWidget);
   d->m_tabs->setMovable(movable);
}

void ExTabWidget::setTabBarAutoHide(bool enabled)
{
   Q_D(ExTabWidget);
   d->m_tabs->setTabBarAutoHide(enabled);
}

void ExTabWidget::setTabEnabled(int index, bool enable)
{
   Q_D(ExTabWidget);
   d->m_tabs->setTabEnabled(index, enable);
}

void ExTabWidget::setTabIcon(int index, const QIcon& icon)
{
   Q_D(ExTabWidget);
   d->m_tabs->setTabIcon(index, icon);
}

void ExTabWidget::setTabPosition(QTabWidget::TabPosition position)
{
   Q_D(ExTabWidget);
   d->m_tabs->setTabPosition(position);
}

void ExTabWidget::setTabShape(QTabWidget::TabShape s)
{
   Q_D(ExTabWidget);
   d->m_tabs->setTabShape(s);
}

void ExTabWidget::setTabText(int index, const QString& label)
{
   Q_D(ExTabWidget);
   d->m_tabs->setTabText(index, label);
}

void ExTabWidget::setTabToolTip(int index, const QString& tip)
{
   Q_D(ExTabWidget);
   d->m_tabs->setTabToolTip(index, tip);
}

void ExTabWidget::setTabVisible(int index, bool visible)
{
   Q_D(ExTabWidget);
   d->m_tabs->setTabVisible(index, visible);
}

void ExTabWidget::setTabWhatsThis(int index, const QString& text)
{
   Q_D(ExTabWidget);
   d->m_tabs->setTabWhatsThis(index, text);
}

void ExTabWidget::setTabsClosable(bool closeable)
{
   Q_D(ExTabWidget);
   d->m_tabs->setTabsClosable(closeable);
}

void ExTabWidget::setUsesScrollButtons(bool useButtons)
{
   Q_D(ExTabWidget);
   d->m_tabs->setUsesScrollButtons(useButtons);
}

QTabBar* ExTabWidget::tabBar()
{
   Q_D(ExTabWidget);
   return d->m_tabs->tabBar();
}

bool ExTabWidget::tabBarAutoHide()
{
   Q_D(ExTabWidget);
   return d->m_tabs->tabBarAutoHide();
}

QIcon ExTabWidget::tabIcon(int index)
{
   Q_D(ExTabWidget);
   return d->m_tabs->tabIcon(index);
}

QTabWidget::TabPosition ExTabWidget::tabPosition()
{
   Q_D(ExTabWidget);
   return d->m_tabs->tabPosition();
}

QTabWidget::TabShape ExTabWidget::tabShape()
{
   Q_D(ExTabWidget);
   return d->m_tabs->tabShape();
}

QString ExTabWidget::tabText(int index)
{
   Q_D(ExTabWidget);
   return d->m_tabs->tabText(index);
}

QString ExTabWidget::tabToolTip(int index)
{
   Q_D(ExTabWidget);
   return d->m_tabs->tabToolTip(index);
}

QString ExTabWidget::tabWhatsThis(int index)
{
   Q_D(ExTabWidget);
   return d->m_tabs->tabWhatsThis(index);
}

bool ExTabWidget::tabsClosable()
{
   Q_D(ExTabWidget);
   return d->m_tabs->tabsClosable();
}

bool ExTabWidget::usesScrollButtons()
{
   Q_D(ExTabWidget);
   return d->m_tabs->usesScrollButtons();
}

bool ExTabWidget::isLoggedIn()
{
   Q_D(ExTabWidget);
   return d->m_loggedIn;
}

QString ExTabWidget::username()
{
   Q_D(ExTabWidget);
   return d->m_username;
}

bool ExTabWidget::isClockEnabled()
{
   Q_D(ExTabWidget);
   return d->m_showClock;
}

bool ExTabWidget::isLoginEnabled()
{
   //  Q_D(ExTabWidget);
   return (m_loginType != None);
}

bool ExTabWidget::isMessagesEnabled()
{
   Q_D(ExTabWidget);
   return d->m_showMessages;
}

bool ExTabWidget::isIgnoreCase()
{
   Q_D(ExTabWidget);
   return d->m_ignoreCase;
}

bool ExTabWidget::isMarqueeEnabled()
{
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
}

void ExTabWidget::showLogin(bool showLogin)
{
   d_ptr->showLogin(showLogin);
}

void ExTabWidget::setLoginType(ExTabWidget::LoginType type)
{
   if (type != m_loginType) {
      m_loginType = type;
      d_ptr->setLoginType();
   }
}

ExTabWidget::LoginType ExTabWidget::loginType()
{
   return m_loginType;
}

void ExTabWidget::setCustomLoginDialog(AbstractLoginDialog* loginDlg)
{
   d_ptr->setCustomLoginDialog(loginDlg);
}

void ExTabWidget::showMessages(bool showMessages)
{
   d_ptr->showMessages(showMessages);
}

void ExTabWidget::showFrame(bool showFrame, QFrame::Shape style)
{
   d_ptr->showFrame(showFrame, style);
}

void ExTabWidget::showClockFrame(bool showFrame, QFrame::Shape style)
{
   d_ptr->showClockFrame(showFrame, style);
}

void ExTabWidget::showLoginFrame(bool showFrame, QFrame::Shape style)
{
   d_ptr->showLoginFrame(showFrame, style);
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
   Q_D(ExTabWidget);
   d->m_password.clear();
   d->m_passwords.clear();
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

void ExTabWidget::setLoginStyleSheet(const QString& styleSheet)
{
   d_ptr->setLoginStyleSheet(styleSheet);
}

void ExTabWidget::setMessageStyleSheet(const QString& styleSheet)
{
   d_ptr->setMessageStyleSheet(styleSheet);
}

void ExTabWidget::paintEvent(QPaintEvent* evt)
{
   d_ptr->paintEvent(evt);
   //   QTabWidget::paintEvent(evt);
   //   QStyleOption opt;
   //   opt.init(this);
   //   //  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
   //   QPainter* painter = new QPainter(this);
   //   d_ptr->paint(painter, evt->rect().width() - 10, style());
   //   delete painter;
}

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
   QFrame::resizeEvent(evt);
   d_ptr->resize();
}

void ExTabWidget::checkPassword(QString password)
{
   d_ptr->checkPassword(password);
}

void ExTabWidget::checkPassword(QString id, QString password)
{
   d_ptr->checkPassword(id, password);
}

void ExTabWidget::loginIsCorrect(QString username)
{
   d_ptr->loginIsCorrect();
}

void ExTabWidget::loginIsIncorrect()
{
   d_ptr->loginIsIncorrect();
}

void ExTabWidget::updateMarquee()
{
   d_ptr->updateMarquee();
}

void ExTabWidget::timeout()
{
   d_ptr->messageTimeout();
}
