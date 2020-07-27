#include "extabwidget.h"
#include "private/extabwidget_p.h"

ExTabWidget::ExTabWidget(QWidget *parent, ExTabWidget::LoginType type, AbstractLoginDialog *customDlg)
  : QTabWidget(parent)
  , m_loginType(type)
  , d_ptr(new ExTabWidgetPrivate(this, customDlg)) {

}

bool ExTabWidget::isLoggedIn() {
  Q_D(ExTabWidget);
  return d->m_loggedIn;
}

QString ExTabWidget::username() {
  Q_D(ExTabWidget);
  return d->m_username;
}

bool ExTabWidget::isClockEnabled() {
  Q_D(ExTabWidget);
  return d->m_showClock;
}

bool ExTabWidget::isLoginEnabled() {
  Q_D(ExTabWidget);
  return (m_loginType != None);
}

bool ExTabWidget::isMessagesEnabled() {
  Q_D(ExTabWidget);
  return d->m_showMessages;
}

bool ExTabWidget::isIgnoreCase() {
  Q_D(ExTabWidget);
  return d->m_ignoreCase;
}

bool ExTabWidget::isMarqueeEnabled() {
  Q_D(ExTabWidget);
  return d->m_marquee;
}

QBrush ExTabWidget::messageBackground() {
  return d_ptr->messageBackgroundBrush();
}

QColor ExTabWidget::messageTextColor() {
  return d_ptr->messageTextColor();
}

void ExTabWidget::showClock(bool showClock) {
  d_ptr->showClock(showClock);
}

void ExTabWidget::showLogin(bool showLogin) {
  d_ptr->showLogin(showLogin);
}

void ExTabWidget::setLoginType(ExTabWidget::LoginType type) {
  if (type != m_loginType) {
    m_loginType = type;
    d_ptr->setLoginType();
  }
}

ExTabWidget::LoginType ExTabWidget::loginType() {
  return m_loginType;
}

void ExTabWidget::setCustomLoginDialog(AbstractLoginDialog *loginDlg) {
  d_ptr->setCustomLoginDialog(loginDlg);
}

void ExTabWidget::showMessages(bool showMessages) {
  d_ptr->showMessages(showMessages);
}

void ExTabWidget::showFrame(bool showFrame) {
  d_ptr->showFrame(showFrame);
}

void ExTabWidget::setPassword(QString password) {
  d_ptr->addPassword(password);
}

void ExTabWidget::addPassword(QString id, QString password) {
  d_ptr->addPassword(id, password);
}

void ExTabWidget::clearPasswords() {
  Q_D(ExTabWidget);
  d->m_password.clear();
  d->m_passwords.clear();
}

void ExTabWidget::setIgnoreCase(bool ignoreCase) {
  d_ptr->setIgnoreCase(ignoreCase);
}

void ExTabWidget::showSeconds(bool showSeconds) {
  d_ptr->showSeconds(showSeconds);
}

void ExTabWidget::setMessageColor(QColor color) {
  d_ptr->setMessageColor(color);
}

void ExTabWidget::setMessageBackground(QColor color) {
  d_ptr->setMessageBackground(color);
}

void ExTabWidget::setMessageBackground(QBrush brush) {
  d_ptr->setMessageBackground(brush);
}

void ExTabWidget::setMessage(QString message, uint timeout) {
  d_ptr->setMessage(message, timeout);
}

void ExTabWidget::setMessage(QColor color, QString message, uint timeout) {
  d_ptr->setMessage(color, message, timeout);
}

void ExTabWidget::setMessage(QColor color, QColor back, QString message, uint timeout) {
  d_ptr->setMessage(color, back, message, timeout);
}

void ExTabWidget::setMessage(QColor color, QBrush back, QString message, uint timeout) {
  d_ptr->setMessage(color, back, message, timeout);
}

void ExTabWidget::setMarquee(bool marquee) {
  d_ptr->setMarquee(marquee);
}

void ExTabWidget::setMarqueeSpeed(qreal charPerSecond) {
  d_ptr->setMarqueeSpeed(charPerSecond);
}

void ExTabWidget::clearMessage() {
  d_ptr->clearMessage();
}

void ExTabWidget::paintEvent(QPaintEvent *evt) {
  QTabWidget::paintEvent(evt);
  QPainter* painter = new QPainter(this);
  d_ptr->paint(painter, evt);
  delete painter;
}

void ExTabWidget::mousePressEvent(QMouseEvent *event) {
  if (!d_ptr->mousePressEvent(event)) {
    QTabWidget::mousePressEvent(event);
  }
}

void ExTabWidget::mouseReleaseEvent(QMouseEvent *event) {
  if (!d_ptr->mouseReleaseEvent(event)) {
    QTabWidget::mouseReleaseEvent(event);
  }
}

void ExTabWidget::resizeEvent(QResizeEvent *evt) {
  d_ptr->resize();
  QTabWidget::resizeEvent(evt);
}

void ExTabWidget::checkPassword(QString password) {
  d_ptr->checkPassword(password);
}

void ExTabWidget::checkPassword(QString id, QString password) {
  d_ptr->checkPassword(id, password);
}

void ExTabWidget::loginIsCorrect(QString username) {
  d_ptr->loginIsCorrect();
}

void ExTabWidget::loginIsIncorrect() {
  d_ptr->loginIsIncorrect();
}

void ExTabWidget::nextSecond() {
  d_ptr->nextSecond();
}

void ExTabWidget::updateMarquee() {
  d_ptr->updateMarquee();
}

void ExTabWidget::timeout() {
  d_ptr->timeout();
}
