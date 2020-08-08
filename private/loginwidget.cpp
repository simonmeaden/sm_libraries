/*
  Copyright 2020 Simon Meaden

Permission is hereby granted, free of charge, to any person obtaining a copy of this
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify, merge,
  publish, distribute, sublicense, and/or sell copies of the Software, and to permit
                                                                         persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or
  substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
    PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
      SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
        */
#include "loginwidget.h"

/// \cond DO_NOT_DOCUMENT

LoginWidget::LoginWidget(QWidget *parent)
  : QPushButton(parent)
  , m_loggedIn(false)
  , m_loginText(LOGIN)
  , m_logoutText(LOGOUT)
  , m_textLength(0)
{
  calculateMaxTextLength();
}

bool LoginWidget::isLoggedIn() {
  return m_loggedIn;
}

void LoginWidget::logOut() {
  m_loggedIn = false;
  // TODO the actual logout.
}

bool LoginWidget::isLoginEnabled() {
  return (m_loginType != AbstractLoginDialog::None);
}

void LoginWidget::loginIsCorrect(QString username) {
  emit loggedIn();
  m_loggedIn = true;
  m_username = username;
}

void LoginWidget::loginIsIncorrect() {
  emit loginBad();
  m_username = "";
}

QString LoginWidget::username() {
  return m_username;
}

void LoginWidget::showLogin(bool showLogin) {
  if (showLogin != m_showLogin) {
    m_showLogin = showLogin;
  }
}

void LoginWidget::setCustomLoginDialog(AbstractLoginDialog *loginDlg) {
  m_customLoginDlg = loginDlg;
  connect(m_customLoginDlg, &AbstractLoginDialog::loginCorrect,
          this, &LoginWidget::loginIsCorrect);
  connect(m_customLoginDlg, &AbstractLoginDialog::loginIncorrect,
          this, &LoginWidget::loginIsIncorrect);
}

bool LoginWidget::hasCustomLoginDialog() {
  return (m_customLoginDlg);
}

AbstractLoginDialog *LoginWidget::loginDialog() {
  if (m_loginType == AbstractLoginDialog::Custom && m_customLoginDlg) {
    return m_customLoginDlg;

  } else {
    switch (m_loginType) {
    case AbstractLoginDialog::Custom:
      if (m_customLoginDlg) {
        return m_customLoginDlg;

      } else {
        return new LoginDialog(this);
      }

    case AbstractLoginDialog::Simple:
      return new SimpleLoginDialog(this);

    case AbstractLoginDialog::Standard:
      return new LoginDialog(this);

    case AbstractLoginDialog::None:
      return nullptr;
    }
  }

  return nullptr;
}

void LoginWidget::displayLoginText() {
  m_loginText = LOGIN;
}

void LoginWidget::displayLogoutText() {
  m_loginText = LOGOUT;
}

int LoginWidget::calculateRequiredWidth(int w) {
  if (w < 0) {
    return -1;
  }

  QFontMetrics fm = fontMetrics();
  int reqWidth;

  // always use WITHSECONDS as it is the longer. Dont want width to change.
  if (m_showLogin) {
    int loginWidth = fm.horizontalAdvance(LOGIN) + 25;
    int logoutWidth = fm.horizontalAdvance(LOGOUT) + 25;
    reqWidth = (loginWidth < logoutWidth ? logoutWidth : loginWidth);
  }

  if (reqWidth > w) {
    reqWidth = w;
  }

  return reqWidth;
}

void LoginWidget::checkPassword(QString password)
{
  if (m_loginType == AbstractLoginDialog::Simple) {
    bool result;

    if (m_ignoreCase) {
      result = (password.toLower() == m_password.toLower());

    } else {
      result = (password == m_password);
    }

    if (result) {
      emit loggedIn();
      m_loggedIn = true;

    } else {
      emit passwordBad();
    }
  }
}

void LoginWidget::checkPassword(QString username, QString password)
{
  QString pw, un;

  if (m_loginType == AbstractLoginDialog::Standard) {
    if (!m_ignoreCase) {
      pw = m_passwords.value(username);

      if (pw.isEmpty()) {
        emit usernameBad();
        m_loggedIn = false;
        return;
      }

      bool result = (password == pw);

      if (result) {
        emit loggedIn();
        m_loggedIn = true;
        m_username = "";

      } else {
        emit passwordBad();
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
            emit loggedIn();
            m_username = un;
            m_loggedIn = true;
            return;
          }

          if (unFound) {
            emit usernameBad();
            return;
          }
        }
      }

      emit passwordBad();
      m_username = "";
      m_loggedIn = false;
    }
  }
}

void LoginWidget::setIgnoreCase(bool ignoreCase)
{
  m_ignoreCase = ignoreCase;
}

bool LoginWidget::isIgnoreCase()
{
  return m_ignoreCase;
}

void LoginWidget::addPassword(QString password)
{
  m_password = password.toLatin1();
}

void LoginWidget::addPassword(QString id, QString password)
{
  m_passwords.insert(id, password.toLatin1());
}

void LoginWidget::clearPasswords()
{
  m_password.clear();
  m_passwords.clear();
}

void LoginWidget::paintEvent(QPaintEvent *evt) {
  QPushButton::paintEvent(evt);
  QPainter painter(this);

  if (m_showLogin) {
    QFontMetrics fm = painter.fontMetrics();
    int h = fm.height();
    int x = (m_size.width() - m_textLength) / 2;
    int y = m_size.height() - ((m_size.height() - h) / 2);
    painter.drawText(x, y, m_loginText);
  }
}

QSize LoginWidget::sizeHint() const {
  return m_size;
}

void LoginWidget::setSizeHint(const QSize &size) {
  if (m_size != size) {
    m_size = size;
    updateGeometry();
  }
}

AbstractLoginDialog::LoginType LoginWidget::loginType() const
{
  return m_loginType;
}

void LoginWidget::setLoginType(const AbstractLoginDialog::LoginType& loginType)
{
  m_loginType = loginType;
  // TODO pass on to dialog
}

QString LoginWidget::loginText() const
{
  return m_loginText;
}

void LoginWidget::calculateMaxTextLength()
{
  QFontMetrics fm = fontMetrics();
  int l1 = fm.horizontalAdvance(m_loginText);
  int l2 = fm.horizontalAdvance(m_logoutText);
  m_textLength = (l1 > l2 ? l1 : l2);
}

void LoginWidget::setLoginText(const QString& loginText)
{
  m_loginText = loginText;
  calculateMaxTextLength();
}

QString LoginWidget::logoutText() const
{
  return m_logoutText;
}

void LoginWidget::setLogoutText(const QString& logoutText)
{
  m_logoutText = logoutText;
  calculateMaxTextLength();
}

/// \endcond
