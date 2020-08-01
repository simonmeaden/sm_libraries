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
#include <QObject>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QPushButton>
#include <QTabBar>
#include <QStyleOption>

/// \cond DO_NOT_DOCUMENT

#include "abstractlogindialog.h"

class ExTabWidget;
class LoginDialogPrivate;
class SimpleLoginDialogPrivate;

class LoginDialog : public AbstractLoginDialog
{
  Q_OBJECT
public:
  explicit LoginDialog(QWidget* parent);
  ~LoginDialog();

  // AbstractLoginDialog interface
  void clearText() override;

private:
  QLineEdit *m_userEdit, *m_passEdit;

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
  SimpleLoginDialogPrivate* d_ptr;
  QLineEdit* m_passEdit;

  void initGui(bool largeText);
  void acceptLogin();

};

class ExTabWidgetPrivate
{

  class ClockWidget : public QWidget {
  public:
    explicit ClockWidget(QWidget *parent=nullptr);

  };

  Q_DECLARE_PUBLIC(ExTabWidget)
public:
  ExTabWidgetPrivate(ExTabWidget* parent, AbstractLoginDialog *customDlg);
  ~ExTabWidgetPrivate();

  bool isInLoginFrame(int x, int y);

  ExTabWidget* q_ptr;

  QMap<QString, QString> m_passwords;
  QString m_password;
  bool m_loggedIn, m_showLogin, /*m_login,*/ /*m_simplelogin,*/ m_showClock,
    m_showMessages;
  AbstractLoginDialog *m_loginDlg, *m_customLoginDlg;
  QPalette m_palette;
  QRect *m_loginRect, *m_clockRect, *m_messageRect, *m_messageClip;
  int m_stringAdvance, m_frameHeight, m_messageWidth;

  // Clock stuff.
  QString m_nowString;
  uint m_now;
  bool m_showSeconds, m_showFrame;
  bool m_isInframe, m_loginPressed, m_ignoreCase;

  void showFrame(bool frame);

  QTimer* m_clockTimer;
  QTimer* m_marqueeTimer;
  QTimer* m_timeoutTimer;

  void showLogin(bool showLogin);
  void setLoginType();
  //  void setSimpleLogin(bool);
  void setCustomLoginDialog(AbstractLoginDialog* loginDlg);
  void showClock(bool showClock);
  void showMessages(bool);

  void nextSecond();
  void showSeconds(bool showSeconds);

  // Login stuff
  QString m_loginText;

  static const QString LOGIN;
  static const QString LOGOUT;
  static const QString WITHSECONDS;
  static const QString NOSECONDS;
  const static int CLOCK_TIME = 1000;
  const static int MARQUEE_TIME = 100;

  bool mousePressEvent(QMouseEvent* event);
  bool mouseReleaseEvent(QMouseEvent* event);
  void paint(QPainter* painter, int width, QStyle *style);
  void paintLogin(QPainter *painter, int w, int h);
  void paintClock(QPainter *painter, int w, int h);
  void paintMessages(QPainter *painter, int w, int h);
  void paintBorder(QPainter *painter, int x, int y, int w, int h, bool darkFirst);
  void paintUpperBorder(QPainter *painter, int x, int y, int w, int h);
  void paintLowerBorder(QPainter *painter, int x, int y, int w, int h);
  void resize();

  void displayLoginText();
  void displayLogoutText();
  void checkPassword(QString value);
  void checkPassword(QString username, QString value);
  void loginIsCorrect(QString username=QString());
  void loginIsIncorrect();
  void setIgnoreCase(bool);
  void setLargeTextForLoginDialog(bool);
  bool isLoggedIn();
  void addPassword(QString password);
  void addPassword(QString, QString);
  void setMarqueeSpeed(qreal charPerSecond);
  void timeout();
  void clearFrames();
  bool hasCustomLoginDialog();

  // message stuff
  QString m_messageText;
  QString m_username;
  QColor m_textColor, m_tempColor;
  QBrush m_background, m_tempBackground;
  bool m_marquee, m_useTempColor, m_useTempBack;
  int m_marqueePos, m_marqueeSpeed;

  uint m_timeout;
  void clearMessage();
  void setMessage(uint);
  void setMessageColor(QColor color);
  void setMessageBackground(QColor);
  void setMessageBackground(QBrush);
  void setMessage(const QString &message, uint timeout = 0);
  void setMessage(QColor, QString message, uint timeout = 0);
  void setMessage(QColor, QColor, QString message, uint timeout = 0);
  void setMessage(QColor, QBrush, QString message, uint timeout = 0);

  void setMarquee(bool marquee);
  void startMarqueeTimerIfRequired();
  void stopMarqueeTimer();
  void updateMarquee();
  QBrush messageBackgroundBrush();
  QColor messageTextColor();

private:
  void resetMessageData(const QString &message, bool tempColor);
};

/// \endcond

#endif // EXTENDEDTABWIDGETPRIVATE_H
