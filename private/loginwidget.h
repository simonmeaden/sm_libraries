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
#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QPushButton>
#include <QPainter>

#include "logindialog.h"

class LoginWidget : public QPushButton
{
  Q_OBJECT
public:
  explicit LoginWidget(QWidget* parent = nullptr);

  bool isShowing() {
    return m_showLogin;
  }
  //! Returns true if the user is logged in, otherwise false.
  bool isLoggedIn();

  void logOut();

  bool isLoginEnabled();

  void loginIsCorrect(QString username);
  void loginIsIncorrect();

  QString username();

  void showLogin(bool showLogin);

  void setCustomLoginDialog(AbstractLoginDialog* loginDlg);

  bool hasCustomLoginDialog();


  AbstractLoginDialog* loginDialog();

  void displayLoginText();
  void displayLogoutText();

  int calculateRequiredWidth(int w);

  void checkPassword(QString password);
  void checkPassword(QString username, QString password);
  void setIgnoreCase(bool ignoreCase);
  bool isIgnoreCase();
  void addPassword(QString password);
  void addPassword(QString id, QString password);
  void clearPasswords();

  void paintEvent(QPaintEvent* evt) override;

  QSize sizeHint() const override;
  void setSizeHint(const QSize& size);

  AbstractLoginDialog::LoginType loginType() const;
  void setLoginType(const AbstractLoginDialog::LoginType& loginType);

  QString loginText() const;
  void setLoginText(const QString& loginText);
  QString logoutText() const;
  void setLogoutText(const QString& logoutText);

  static const QString LOGIN;
  static const QString LOGOUT;

signals:
  void loggedOut();
  void loggedIn();
  void passwordBad();
  void usernameBad();
  void loginBad();

private:
  QSize m_size;
  QString m_username, m_password;
  QMap<QString, QString> m_passwords;
  bool m_showLogin;
  AbstractLoginDialog::LoginType m_loginType;
  bool m_loggedIn;
  bool m_ignoreCase;
  AbstractLoginDialog* m_loginDlg, *m_customLoginDlg;
  QString m_loginText, m_logoutText;
  int m_textLength;

  void calculateMaxTextLength();
};
#endif // LOGINWIDGET_H
