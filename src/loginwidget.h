#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QPushButton>
#include <QDialog>
//#include "abstractlogindialog.h"

class AbstractLoginDialog : public QDialog
{
   Q_OBJECT

public:
  enum LoginType
  {
     Simple, //!< A simple password only dialog.
     Standard, //!< A more standard username/password dialog type
     Custom, //!< A custom login dialog.
     None, //!< No login dialog is set up.
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

class AbstractCustomLoginDialog {
  Q_OBJECT
public:

};

class SimpleLoginDialog : public AbstractLoginDialog{
  Q_OBJECT
public:

  SimpleLoginDialog(quint64 key, QWidget *parent);
  ~SimpleLoginDialog();


  void clearText();
  void setPassword(const QString &password);
  void clearUsers();
  int exec();

  void checkPassword();
  void modifyStoredPassword(quint64 key);
private:
  void initGui(bool largeText);

};

class StandardLoginDialog : public AbstractCustomLoginDialog {
  Q_OBJECT
public:
  StandardLoginDialog(quint64 key, int minUsernameLength, int minPasswordLength, QWidget *parent);
  ~StandardLoginDialog();


  void addUser(const QString &username, const QString &password);
  void removeUser(const QString &username);
  void clearUsers();
  void clearText();
  int minUsernameLength() const;
  void setMinUsernameLength(int minUsernameLength);
  int minPasswordLength() const;
  void setMinPasswordLength(int minPasswordLength);
  int exec();
  void checkPassword();
  void modifyStoredPassword(quint64 key);
  void initGui(bool largeText);
};

class LoginWidget : public QPushButton {
  Q_OBJECT
public:
  LoginWidget(QWidget *parent, quint64 key);


  static const QString LOGIN;
  static const QString LOGOUT;

  bool isShowing();
  bool isLoggedIn();
  bool isLoginEnabled();
  void showLogin(bool showLogin);
  void setCustomLoginDialog(AbstractLoginDialog *loginDlg);
  bool hasCustomLoginDialog();
  void setSimplePassword(const QString &password);
  void addUser(const QString &username, const QString &password);
  void removeUser(const QString &username);
  void clearUsers();
  AbstractLoginDialog::LoginType loginType() const;
  void setLoginType(const AbstractLoginDialog::LoginType &loginType);
  void loginWasSuccessful(const QString &username);
  void loginHasFailed(AbstractLoginDialog::LoginFailureTypes types);
  void setLoginText(const QString &loginText);
  void setLogoutText(const QString &logoutText);
  void setKey(quint64 key);
  int minUsernameLength() const;
  void setMinUsernameLength(int length);
  int minPasswordLength() const;
  void setMinPasswordLength(int length);
private:
  QString m_loginText,m_logoutText;
  AbstractLoginDialog::LoginType  m_loginType;
  bool m_loggedIn,m_showLogin;
  int m_textLength;
  quint64 m_key;
  AbstractLoginDialog *m_loginDlg, *m_customLoginDlg;
  void loginBtnClicked();
};

#endif // LOGINWIDGET_H
