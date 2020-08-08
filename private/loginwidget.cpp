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

LoginWidget::LoginWidget(QWidget* parent)
   : QPushButton(parent)
   , m_loggedIn(false)
   , m_loginText(LOGIN)
   , m_logoutText(LOGOUT)
   , m_textLength(0)
{
   calculateMaxTextLength();
}

bool LoginWidget::isShowing()
{
   return m_showLogin;
}

bool LoginWidget::isLoggedIn()
{
   return m_loggedIn;
}

void LoginWidget::logOut()
{
   m_loggedIn = false;
   displayLoginText();
}

bool LoginWidget::isLoginEnabled()
{
   return (m_loginType != AbstractLoginDialog::None);
}

void LoginWidget::loginIsCorrect(QString username)
{
   emit loggedIn();
   m_loggedIn = true;
   m_username = username;
}

void LoginWidget::loginIsIncorrect()
{
   emit loginBad();
   m_username = "";
}

QString LoginWidget::username()
{
   return m_username;
}

void LoginWidget::showLogin(bool showLogin)
{
   if (showLogin != m_showLogin) {
      m_showLogin = showLogin;
   }
}

void LoginWidget::setCustomLoginDialog(AbstractLoginDialog* loginDlg)
{
   m_customLoginDlg = loginDlg;
   connect(m_customLoginDlg, &AbstractLoginDialog::loginCorrect,
           this, &LoginWidget::loginIsCorrect);
   connect(m_customLoginDlg, &AbstractLoginDialog::loginIncorrect,
           this, &LoginWidget::loginIsIncorrect);
}

bool LoginWidget::hasCustomLoginDialog()
{
   return (m_customLoginDlg);
}

AbstractLoginDialog* LoginWidget::loginDialog()
{
   AbstractLoginDialog* dlg = nullptr;

   switch (m_loginType) {
   case AbstractLoginDialog::Custom:
      if (m_customLoginDlg) {
         dlg = m_customLoginDlg;
         connect(dlg, &AbstractLoginDialog::loginCorrect,
                 this, &LoginWidget::loginIsCorrect);
         connect(dlg, &AbstractLoginDialog::loginIncorrect,
                 this, &LoginWidget::loginIsIncorrect);

      } else {
         dlg = new LoginDialog(this);
         connect(dlg, qOverload<QString, QString>(&AbstractLoginDialog::loginData),
                 this, qOverload<QString, QString>(&LoginWidget::checkPassword));
      }

      break;

   case AbstractLoginDialog::Simple:
      dlg = new SimpleLoginDialog(this);
      connect(dlg, qOverload<QString>(&AbstractLoginDialog::loginData),
              this, qOverload<QString>(&LoginWidget::checkPassword));
      break;

   case AbstractLoginDialog::Standard:
      dlg = new LoginDialog(this);
      connect(dlg, qOverload<QString, QString>(&AbstractLoginDialog::loginData),
              this, qOverload<QString, QString>(&LoginWidget::checkPassword));
      break;

   case AbstractLoginDialog::None:
      break;
   }

   return dlg;
}

void LoginWidget::displayLoginText()
{
   m_loginText = LOGIN;
}

void LoginWidget::displayLogoutText()
{
   m_loginText = LOGOUT;
}

int LoginWidget::calculateRequiredWidth(int w)
{
   if (w < 0) {
      return -1;
   }

   QFontMetrics fm = fontMetrics();
   int reqWidth = 0;

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
      SimpleCrypt crypto;
      crypto.setKey(m_key);
      crypto.setCompressionMode(SimpleCrypt::CompressionAlways);
      crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);
      QString pw = crypto.decryptToString(m_password);

      if (password == pw) {
         emit loggedIn();
         m_loggedIn = true;
         displayLogoutText();

      } else {
         emit passwordBad();
         displayLogoutText();
      }
   }
}

void LoginWidget::checkPassword(QString username, QString password)
{
   QString pw, epassword;

   if (m_loginType == AbstractLoginDialog::Standard) {
      if (password.isEmpty()) {
         emit usernameBad();
         m_loggedIn = false;
         displayLoginText();
         return;
      }

      SimpleCrypt crypto;
      crypto.setKey(m_key);
      crypto.setCompressionMode(SimpleCrypt::CompressionAlways);
      crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);
      pw = crypto.decryptToString(m_passwords.value(username));

      if (password == pw) {
         emit loggedIn();
         m_username = username;
         m_loggedIn = true;
         displayLogoutText();

      } else {
         emit passwordBad();
         m_username = QString();
         m_loggedIn = false;
         displayLoginText();
      }
   }
}


void LoginWidget::setPassword(QString password)
{
   SimpleCrypt crypto;
   crypto.setKey(m_key);
   crypto.setCompressionMode(SimpleCrypt::CompressionAlways);
   crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);
   m_password = crypto.encryptToString(password.toLatin1());
}

void LoginWidget::addPassword(QString username, QString password)
{
   SimpleCrypt crypto;
   crypto.setKey(m_key);
   crypto.setCompressionMode(SimpleCrypt::CompressionAlways);
   crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);
   m_passwords.insert(username, crypto.encryptToString(password.toLatin1()));
}

void LoginWidget::clearPasswords()
{
   m_password.clear();
   m_passwords.clear();
}

void LoginWidget::paintEvent(QPaintEvent* evt)
{
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

QSize LoginWidget::sizeHint() const
{
   return m_size;
}

void LoginWidget::setSizeHint(const QSize& size)
{
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


/// \endcond
