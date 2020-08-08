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

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QPainter>

#include "simplecrypt.h"

/*!
   \file abstractlogindialog.h abstractlogindialog.cpp
   \class AbstractLoginDialog abstractlogindialog.h
   \brief The AbstractLoginDialog is the base class for login dialogs
   for ExTabWidget.

   If you create your own custom login dialog it needs to extand this class,
   otherwise you will not have the correct signals to handle login interaction
   with the ExTabWidget.

   The Simple and Standard login dialogs supplied with the ExTabWidget handle
   login checking.

   In the case of Simple login only a password needs to be supplied using
   ExTabWidget::setPassword(QString). This is for use in the VERY simple
   and rare case of having a single common password for the application login.

   In the Standard login, similarly, you need to use ExTabWidget::addPassword(QString, QString)
   to add username/password pairs to the ExTabWidget. Any number may be added, only one
   case of each username is allowed.

   If you need a more complex login dialog, quite likely, then you will need to handle
   password checking within your dialog, then emit either
   AbstractLoginDialog::logingCorrect(QString) on success, with an optional username,
   or AbstractLoginDialog::loginIncorrect() on failure.
*/
class AbstractLoginDialog : public QDialog
{
   Q_OBJECT

public:
   /*!
       \enum ::LoginType

      Defines which type of login dialog will be displayed.
   */
   enum LoginType
   {
      Simple,   //!< A simple password only dialog.
      Standard, //!< A more standard username/password dialog type
      Custom,   //!< A custom login dialog.
      None,     //!< No login dialog is set up.
   };

   //! Constructor for AbstractLoginDialog.
   explicit AbstractLoginDialog(QWidget* parent = nullptr)
      : QDialog(parent)
   {}

   /*!
      \brief clears the username and password data  etc. from dialog.

      This needs to be declared/defined in your own login dialog.
   */
   virtual void clearText() = 0;

signals:

   /*!
      \fn ::loginCorrect()

      \brief This signal is should be emitted by your login dialog when the login
      data is correct.
   */
   void loginCorrect(QString username = QString());

   /*!
      \fn ::loginIncorrect()

      \brief This signal is should be emitted by your login dialog when the login
      data is not correct.
   */
   void loginIncorrect();

   /*!
      \fn ::loginData(QString)

      \brief This signal is emitted when the simple login dialog
      has been triggered, hence only the password is returned.

      \sa usernameBad(), loggedIn(), loggedOut();
   */
   void loginData(QString password);

   /*!
      \fn ::loginData(QString, QString)

      \brief This signal is emitted when either the standard login dialog
      has been triggered, hence both the username and the password are returned.

      \sa usernameBad(), loggedIn(), loggedOut();
   */
   void loginData(QString username, QString password);

};

class LoginDialog : public AbstractLoginDialog
{
   Q_OBJECT
public:
   explicit LoginDialog(QWidget* parent);
   ~LoginDialog();

   // AbstractLoginDialog interface
   void clearText() override;

private:
   QLineEdit* m_userEdit, *m_passEdit;

   void initGui(bool largeText);
   void acceptLogin();
};

class SimpleLoginDialog : public AbstractLoginDialog
{
   Q_OBJECT
public:
   explicit SimpleLoginDialog(QWidget* parent);
   ~SimpleLoginDialog();

   // AbstractLoginDialog interface
   void clearText() override;

private:
   QLineEdit* m_passEdit;

   void initGui(bool largeText);
   void acceptLogin();
};


class LoginWidget : public QPushButton
{
   Q_OBJECT
public:
   explicit LoginWidget(QWidget* parent = nullptr);

   bool isShowing();
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
//   void setIgnoreCase(bool ignoreCase);
//   bool isIgnoreCase();
   void setPassword(QString password);
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
//   bool m_ignoreCase;
   AbstractLoginDialog* m_loginDlg, *m_customLoginDlg;
   QString m_loginText, m_logoutText;
   int m_textLength;
   quint16 m_key = 0xf6e328eb11b3563ce52;

   void calculateMaxTextLength();
};

Q_DECLARE_METATYPE(AbstractLoginDialog::LoginType)

#endif // LOGINWIDGET_H
