/*
   Copyright 2020 Simon Meaden

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/
#include "sm_widgets/loginwidget.h"

/// \cond DO_NOT_DOCUMENT

const QString LoginWidget::LOGIN = tr("Log In");
const QString LoginWidget::LOGOUT = tr("Log Out");

LoginWidget::LoginWidget(QWidget* parent, quint64 key)
  : QPushButton(parent)
  , m_loginText(LOGIN)
  , m_logoutText(LOGOUT)
  , m_loginType(AbstractLoginDialog::Standard)
  , m_loggedIn(false)
  , m_textLength(0)
  , m_key(key)
{
  setText(m_loginText);
  setLoginType(m_loginType);
}

bool
LoginWidget::isShowing()
{
  return m_showLogin;
}

bool
LoginWidget::isLoggedIn()
{
  return m_loggedIn;
}

bool
LoginWidget::isLoginEnabled()
{
  return (m_loginType != AbstractLoginDialog::None);
}

void
LoginWidget::showLogin(bool showLogin)
{
  if (showLogin != m_showLogin) {
    m_showLogin = showLogin;
  }
}

void
LoginWidget::setCustomLoginDialog(AbstractLoginDialog* loginDlg)
{
  m_loginDlg = loginDlg;
  m_customLoginDlg = loginDlg;
  connect(m_loginDlg,
          &AbstractLoginDialog::loginSucceeded,
          this,
          &LoginWidget::loginSucceeded);
  connect(m_loginDlg,
          &AbstractLoginDialog::loginFailed,
          this,
          &LoginWidget::loginFailed);
}

bool
LoginWidget::hasCustomLoginDialog()
{
  return (m_customLoginDlg != nullptr);
}

void
LoginWidget::setSimplePassword(const QString& password)
{
  SimpleLoginDialog* dlg = qobject_cast<SimpleLoginDialog*>(m_loginDlg);

  if (dlg) {
    dlg->setPassword(password);
  }
}

void
LoginWidget::addUser(const QString& username, const QString& password)
{
  StandardLoginDialog* dlg = qobject_cast<StandardLoginDialog*>(m_loginDlg);

  if (dlg) {
    dlg->addUser(username, password);
    return;

  } else {

    AbstractCustomLoginDialog* customDlg =
      qobject_cast<AbstractCustomLoginDialog*>(m_loginDlg);

    if (customDlg) {
      dlg->addUser(username, password);
      return;
    }
  }
}

void
LoginWidget::removeUser(const QString& username)
{
  StandardLoginDialog* dlg = qobject_cast<StandardLoginDialog*>(m_loginDlg);

  if (dlg) {
    dlg->removeUser(username);

  } else {

    AbstractCustomLoginDialog* customDlg =
      qobject_cast<AbstractCustomLoginDialog*>(m_loginDlg);

    if (customDlg) {
      dlg->removeUser(username);
      return;
    }
  }
}

void
LoginWidget::clearUsers()
{
  StandardLoginDialog* dlg = qobject_cast<StandardLoginDialog*>(m_loginDlg);

  if (dlg) {
    dlg->clearUsers();

  } else {

    AbstractCustomLoginDialog* customDlg =
      qobject_cast<AbstractCustomLoginDialog*>(m_loginDlg);

    if (customDlg) {
      dlg->clearUsers();
      return;
    }
  }
}

AbstractLoginDialog::LoginType
LoginWidget::loginType() const
{
  return m_loginType;
}

void
LoginWidget::setLoginType(const AbstractLoginDialog::LoginType& loginType)
{
  m_loginType = loginType;

  disconnect(this, &LoginWidget::clicked, this, &LoginWidget::loginBtnClicked);

  switch (m_loginType) {
    case AbstractLoginDialog::Simple:
      m_loginDlg = new SimpleLoginDialog(m_key, this);
      break;

    case AbstractLoginDialog::Standard:
      m_loginDlg = new StandardLoginDialog(m_key, 6, 6, this);
      break;

    case AbstractLoginDialog::Custom:
      if (m_customLoginDlg) {
        m_loginDlg = m_customLoginDlg;

      } else {
        m_loginDlg = new StandardLoginDialog(m_key, 6, 6, this);
      }

      break;

    default:
      break;
  }

  if (m_loginDlg) {
    connect(this, &LoginWidget::clicked, this, &LoginWidget::loginBtnClicked);
    connect(m_loginDlg,
            &AbstractLoginDialog::loginSucceeded,
            this,
            &LoginWidget::loginWasSuccessful);
    connect(m_loginDlg,
            &AbstractLoginDialog::loginFailed,
            this,
            &LoginWidget::loginHasFailed);
  }
}

void
LoginWidget::loginWasSuccessful(const QString& username)
{
  m_loggedIn = true;
  emit loginSucceeded(username);
  setText(m_logoutText);
}

void
LoginWidget::loginHasFailed(AbstractLoginDialog::LoginFailureTypes types)
{
  m_loggedIn = false;
  emit loginFailed(types);
  setText(m_loginText);
}

void
LoginWidget::loginBtnClicked()
{
  if (m_loggedIn) {
    m_loggedIn = false;
    setText(m_loginText);
    emit loggedOut();

  } else {
    if (m_loginDlg) {
      m_loginDlg->exec();
    }
  }
}

void
LoginWidget::setLoginText(const QString& loginText)
{
  m_loginText = loginText;

  if (!isLoggedIn()) {
    setText(m_loginText);
  }
}

void
LoginWidget::setLogoutText(const QString& logoutText)
{
  m_logoutText = logoutText;

  if (isLoggedIn()) {
    setText(m_logoutText);
  }
}

void
LoginWidget::setKey(quint64 key)
{
  if (m_loginDlg) {
    m_loginDlg->setKey(key);
  }

  m_key = key;
}

int
LoginWidget::minUsernameLength() const
{
  if (m_loginDlg) {
    return m_loginDlg->minUsernameLength();
  }

  return 0;
}

void
LoginWidget::setMinUsernameLength(int length)
{
  if (m_loginDlg) {
    m_loginDlg->setMinUsernameLength(length);
  }
}

int
LoginWidget::minPasswordLength() const
{
  if (m_loginDlg) {
    return m_loginDlg->minPasswordLength();
  }

  return 0;
}

void
LoginWidget::setMinPasswordLength(int length)
{
  if (m_loginDlg) {
    m_loginDlg->setMinPasswordLength(length);
  }
}

StandardLoginDialog::StandardLoginDialog(quint64 key,
                                         int minUsernameLength,
                                         int minPasswordLength,
                                         QWidget* parent)
  : AbstractCustomLoginDialog(parent, key, minUsernameLength, minPasswordLength)
  , m_minUsernameLength(minUsernameLength)
  , m_minPasswordLength(minPasswordLength)
{
  initGui(false);
}

StandardLoginDialog::~StandardLoginDialog() {}

void
StandardLoginDialog::addUser(const QString& username, const QString& password)
{
  m_passwords.insert(username, AbstractLoginDialog::encrypt(password, m_key));
}

void
StandardLoginDialog::removeUser(const QString& username)
{
  m_passwords.remove(username);
}

void
StandardLoginDialog::clearUsers()
{
  m_passwords.clear();
}

void
StandardLoginDialog::clearText()
{
  m_userEdit->clear();
  m_passEdit->clear();
}

int
StandardLoginDialog::minUsernameLength() const
{
  return m_minUsernameLength;
}

void
StandardLoginDialog::setMinUsernameLength(int minUsernameLength)
{
  m_minUsernameLength = minUsernameLength;
}

int
StandardLoginDialog::minPasswordLength() const
{
  return m_minPasswordLength;
}

void
StandardLoginDialog::setMinPasswordLength(int minPasswordLength)
{
  m_minPasswordLength = minPasswordLength;
}

int
StandardLoginDialog::exec()
{
  clearText();
  QDialog::exec();
}

void
StandardLoginDialog::checkPassword()
{
  QString username = m_userEdit->text();
  QString password = m_passEdit->text();
  AbstractLoginDialog::LoginFailureTypes failures =
    AbstractLoginDialog::NoFailure;

  if (username.isEmpty()) {
    failures |= AbstractLoginDialog::NoUsernameSupplied;
  }

  if (password.isEmpty()) {
    failures |= AbstractLoginDialog::NoPasswordSupplied;
  }

  if (failures != AbstractLoginDialog::NoFailure) {
    emit loginFailed(failures);
    return;
  }

  if (!m_passwords.contains(username)) {
    emit loginFailed(AbstractLoginDialog::NoSuchUser);
    return;
  }

  QString pw = m_passwords.value(username);
  QString decryptPw = AbstractLoginDialog::decrypt(pw, m_key);

  if (password == decryptPw) {
    emit loginSucceeded();

  } else {
    emit loginFailed(AbstractLoginDialog::PasswordWrong);
  }
}

void
StandardLoginDialog::modifyStoredPassword(quint64 key)
{
  QString pw;

  for (auto username : m_passwords.keys()) {
    QString password = m_passwords.value(username);
    pw = AbstractLoginDialog::decrypt(password, m_key);
    m_passwords.insert(username, AbstractLoginDialog::encrypt(password, key));
  }

  m_key = key;
}

void
StandardLoginDialog::initGui(bool largeText)
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
  connect(m_userEdit,
          &QLineEdit::textChanged,
          this,
          &StandardLoginDialog::enableOkBtn);
  QLabel* lbl2 = new QLabel("Password :", this);
  lbl2->setFont(f);
  m_passEdit = new QLineEdit(this);
  m_passEdit->setEchoMode(QLineEdit::Password);
  connect(m_passEdit,
          &QLineEdit::textChanged,
          this,
          &StandardLoginDialog::enableOkBtn);

  QGridLayout* layout = new QGridLayout(this);
  setLayout(layout);

  layout->addWidget(lbl1, 0, 0);
  layout->addWidget(m_userEdit, 0, 1);
  layout->addWidget(lbl2, 1, 0);
  layout->addWidget(m_passEdit, 1, 1);

  m_buttons = new QDialogButtonBox(this);
  m_buttons->addButton(QDialogButtonBox::Ok);
  m_buttons->addButton(QDialogButtonBox::Cancel);
  m_buttons->button(QDialogButtonBox::Ok)->setText(tr("Login"));
  m_buttons->button(QDialogButtonBox::Ok)->setFont(f);
  m_buttons->button(QDialogButtonBox::Cancel)->setText(tr("Abort"));
  m_buttons->button(QDialogButtonBox::Cancel)->setFont(f);
  layout->addWidget(m_buttons, 2, 0, 1, 2);

  m_buttons->button(QDialogButtonBox::Ok)->setEnabled(false);

  // close on abort
  connect(m_buttons->button(QDialogButtonBox::Cancel),
          &QPushButton::clicked,
          this,
          &StandardLoginDialog::close);

  // acceptLogin and abort on accept.
  // should acceptLogin first.
  connect(m_buttons->button(QDialogButtonBox::Ok),
          &QPushButton::clicked,
          this,
          &StandardLoginDialog::checkPassword);
  connect(m_buttons->button(QDialogButtonBox::Ok),
          &QPushButton::clicked,
          this,
          &StandardLoginDialog::close);
}

void
StandardLoginDialog::enableOkBtn(const QString&)
{
  QString username = m_userEdit->text();
  QString password = m_passEdit->text();

  if (username.length() < m_minUsernameLength ||
      password.length() < m_minPasswordLength) {
    m_buttons->button(QDialogButtonBox::Ok)->setEnabled(false);

  } else {
    m_buttons->button(QDialogButtonBox::Ok)->setEnabled(true);
  }
}

SimpleLoginDialog::SimpleLoginDialog(quint64 key, QWidget* parent)
  : AbstractLoginDialog(parent, key)
{
  initGui(false);
}

SimpleLoginDialog::~SimpleLoginDialog() {}

void
SimpleLoginDialog::clearText()
{
  m_passEdit->clear();
}

void
SimpleLoginDialog::setPassword(const QString& password)
{
  m_password = AbstractLoginDialog::encrypt(password, m_key);
}

void
SimpleLoginDialog::clearUsers()
{
  m_password.clear();
}

int
SimpleLoginDialog::exec()
{
  clearText();
  QDialog::exec();
}

void
SimpleLoginDialog::initGui(bool largeText)
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
          &SimpleLoginDialog::checkPassword);
  connect(buttons->button(QDialogButtonBox::Ok),
          &QPushButton::clicked,
          this,
          &SimpleLoginDialog::close);
}

void
SimpleLoginDialog::checkPassword()
{
  QString password = m_passEdit->text();

  if (password.isEmpty()) {
    emit loginFailed(AbstractLoginDialog::NoPasswordSupplied);
    return;
  }

  QString pw = AbstractLoginDialog::decrypt(m_password, m_key);

  if (password == pw) {
    emit loginSucceeded();

  } else {
    emit loginFailed(AbstractLoginDialog::PasswordWrong);
  }
}

void
SimpleLoginDialog::modifyStoredPassword(quint64 key)
{
  QString pw;

  if (!m_password.isEmpty()) {
    SimpleCrypt crypto;
    crypto.setKey(m_key);
    crypto.setCompressionMode(SimpleCrypt::CompressionAlways);
    crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);
    pw = AbstractLoginDialog::decrypt(m_password, m_key);
  }

  m_key = key;
  m_password = AbstractLoginDialog::encrypt(pw, m_key);
}

void
AbstractLoginDialog::setKey(quint64 key)
{
  m_key = key;
  modifyStoredPassword(key);
}

int
AbstractLoginDialog::minUsernameLength() const
{
  return m_minUsernameLength;
}

void
AbstractLoginDialog::setMinUsernameLength(int length)
{
  m_minUsernameLength = length;
}

int
AbstractLoginDialog::minPasswordLength() const
{
  return m_minPasswordlength;
}

void
AbstractLoginDialog::setMinPasswordLength(int length)
{
  m_minPasswordlength = length;
}

QString
AbstractLoginDialog::encrypt(const QString& password, quint64 key)
{
  SimpleCrypt crypto;
  crypto.setKey(key);
  crypto.setCompressionMode(SimpleCrypt::CompressionAlways);
  crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);
  return crypto.encryptToString(password);
}

QString
AbstractLoginDialog::decrypt(const QString& password, quint64 key)
{
  SimpleCrypt crypto;
  crypto.setKey(key);
  crypto.setCompressionMode(SimpleCrypt::CompressionAlways);
  crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);
  return crypto.decryptToString(password);
}

/// \endcond
