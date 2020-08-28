#ifndef EXTENDEDTABWIDGETPRIVATE_H
#define EXTENDEDTABWIDGETPRIVATE_H

#include <QDateTime>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFont>
#include <QGridLayout>
#include <QGuiApplication>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QObject>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QPushButton>
#include <QStyleOption>
#include <QTabBar>
#include <QTimer>
#include <QRegularExpression>

/// \cond DO_NOT_DOCUMENT

#include "sm_widgets/loginwidget.h"

class ExTabWidget;

class ClockWidget : public QFrame
{
public:
  explicit ClockWidget(QWidget* parent = nullptr);

  bool isShowing();
  void showClock(bool showClock);
  void setClockFrame(QFrame::Shape style);

  bool showSeconds() const;
  void setShowSeconds(bool value);

  void paintEvent(QPaintEvent* evt) override;
  int calculateRequiredWidth(int w);

  QSize sizeHint() const override;
  void setSizeHint(const QSize& size);
//  QString setStyleSheet(const QString &stylesheet)
//  {
//    QFrame::setStyleSheet(stylesheet);
//    update();
//  }

protected:
  void nextSecond();

private:
  QTimer* m_clockTimer;
  QRect m_rect;
  bool m_showSeconds, m_showClock;
  QString m_nowString;
  QSize m_size;
  //   QString m_stylesheet;

  static const QString WITHSECONDS;
  static const QString NOSECONDS;
  const static int CLOCK_TIME = 1000;
};

class MessageWidget : public QFrame
{
public:
  explicit MessageWidget(QWidget* parent = nullptr);

  void showMessages(bool show);
  bool isShowing();
  void setMessage(const QString& message, quint32 timeout = 0);
  void setMessageFrame(QFrame::Shape style);
  void clearMessage();

  bool isMarqueeEnabled();
  void enableMarquee(bool enable);
  void setMarqueeSpeed(qreal charPerSecond);

  void paintEvent(QPaintEvent* evt) override;
  void setSizeHint(QSize size);
  QSize sizeHint() const override;

  const static qreal DEF_MARQUEE_TIME;

protected:
private:
  int m_marqueeTime;
  quint32 m_timeout;
  bool m_showMessages, m_marqueeEnabled;
  QTimer* m_marqueeTimer, *m_timeoutTimer;
  QString m_messageText;
  int m_marqueePos;
  QSize m_size;

  void updateMarquee();
  void timedout();

  //   void resetMessageData(const QString& message);
  void startMarqueeIfRequired();

  //   void startTimeoutTimer();
  void stopMarqueeIfRequired();
  void startTimeoutIfRequired(uint timeout);
  QString cleanMessage(const QString &message);
  void stopTimeoutIfRequired();
};

class WrapperWidget : public QFrame
{
   Q_OBJECT
public:
   explicit WrapperWidget(QWidget* parent = nullptr, quint64 key = 0);

   // login methods
   void setLoginText(const QString& text);
   void setLogoutText(const QString& text);

   //! Returns true if the user is logged in, otherwise false.
   bool isLoggedIn();
   bool isLoginEnabled();
   bool isShowLogin();
   AbstractLoginDialog::LoginType loginType() const;
   void setLoginType(const AbstractLoginDialog::LoginType& loginType);
   void showLogin(bool show);
   void setLoginStyleSheet(const QString& stylesheet);
   QString loginStyleSheet();
   void setCustomLoginDialog(AbstractLoginDialog* loginDlg);
   bool hasCustomLoginDialog();
   void setSimplePassword(QString password);
   void addUser(QString username, QString password);
   void removeUser(const QString& username);
   void clearUsers();
   void loginIsCorrect(QString username);
   void loginIsIncorrect();
   void setKey(quint64 key);

   // clock methods
   bool isShowClock();
   void showClock(bool show);
   void setClockFrame(QFrame::Shape style);
   void setShowSeconds(bool show);
   void setClockStyleSheet(const QString& stylesheet);
   QString clockStyleSheet();

   // message methods.
   void setMessageStyleSheet(const QString& stylesheet);
   QString messageStyleSheet();
   void showMessages(bool show);
   bool isShowMessages();
   bool isMarqueeEnabled();
   void clearMessageText();
   void enableMarquee(bool enable);
   void setMessageFrame(QFrame::Shape style);
   void setMessageText(const QString& message, quint32 timeout = 0);
   void setMarqueeSpeed(qreal charPerSecond);

   // general methods.
   void calculateWidgetSizes(int w, int h);
   void removeWidgetsFromLayout();
   void addWidgetsToLayout();

signals:
   void loginSucceeded(const QString& username);
   void loginFailed(AbstractLoginDialog::LoginFailureTypes types);
   void loggedOut();

private:
   QWidget* m_parent;
   QGridLayout* m_layout;
   ClockWidget* m_clockWidget;
   LoginWidget* m_loginWidget;
   MessageWidget* m_messageWidget;
   QFrame* m_filler;
   qreal m_marqueeSpeed;
   quint64 m_key;

   // stores clock/login/message values to restore when reshown.
   // the clock, login and message wisgets are destroyed when not required
   // so we need to store these until needed again.
   QString m_stylesheet, m_clockStylesheet, m_loginStylesheet, m_messageStylesheet, m_simplePassword;
   QMap<QString, QString> m_passwords;
   bool m_ignoreCase, m_showSeconds;
   QFrame::Shape m_clockFrame;

   void rebuildPasswords();
};

class ExTabWidgetPrivate
{

   Q_DECLARE_PUBLIC(ExTabWidget)
public:
   ExTabWidgetPrivate(ExTabWidget* parent, AbstractLoginDialog* customDlg, quint64 key);
   ~ExTabWidgetPrivate();

   ExTabWidget* q_ptr;
   WrapperWidget* m_wrapper;

   int m_frameHeight, m_frameWidth;
   QString m_stylesheet;

   // clock stuff.
   void showClock(bool showClock);
   bool isShowClock();
   void showSeconds(bool showSeconds);
   void setClockFrame(QFrame::Shape style);

   // Login stuff
   void showLogin(bool showLogin);
   void setLoginType(AbstractLoginDialog::LoginType type);
   AbstractLoginDialog::LoginType loginType();
   void setLoginText(const QString& text);
   void setLogoutText(const QString& text);
   bool isLoggedIn();
   bool isLoginEnabled();
   void setPassword(QString password);
   void addUser(QString username, QString password);
   void removeUser(const QString& username);
   void clearUsers();
   void setLargeTextForLoginDialog(bool);
   bool hasCustomLoginDialog();
   void setCustomLoginDialog(AbstractLoginDialog* loginDlg);
   void setKey(quint64 key);

   // message stuff.
   void showMessages(bool show);
   bool isShowMessages();
   void setMessageFrame(QFrame::Shape style);
   bool isMarqueeEnabled();
   void setMarqueeSpeed(qreal charPerSecond);
   void clearMessage();
   void setMessage(const QString& message, uint messageTimeout = 0);
   void enableMarquee(bool enable);
   void messageTimeout();

   // general stuff.
   void tabwidgetStatusChanged();
   QString styleSheet() const;
   QString clockStyleSheet() const;
   QString loginStyleSheet() const;
   QString messageStyleSheet() const;
   QString setStyleSheet(const QString &stylesheet);
   void setClockStyleSheet(const QString& styleSheet);
   void setLoginStyleSheet(const QString& styleSheet);
   void setMessageStyleSheet(const QString& styleSheet);
};

/// \endcond DO_NOT_DOCUMENT

#endif // EXTENDEDTABWIDGETPRIVATE_H
