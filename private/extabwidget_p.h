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

/// \cond DO_NOT_DOCUMENT

#include "loginwidget.h"
#include "clockwidget.h"

class ExTabWidget;



class MessageWidget : public QFrame
{
public:
   explicit MessageWidget(QWidget* parent = nullptr)
      : QFrame(parent)
      , m_marqueeSpeed(MARQUEE_TIME)
   {}

   void paintEvent(QPaintEvent* evt) {
      QFrame::paintEvent(evt);
   }

   int calculateRequiredWidth(int x, int y, int w, int h) {
      //      int w = 0;

      return 0;
   }

protected:
private:
   int m_marqueeSpeed;

   const static int MARQUEE_TIME = 100;
};

class WrapperWidget : public QFrame
{
   Q_OBJECT
public:
   explicit WrapperWidget(QWidget* parent = nullptr);

   // login methods
   QString loginText() const;
   void setLoginText(const QString& text);
   QString logoutText() const;
   void setLogoutText(const QString& text);

   //! Returns true if the user is logged in, otherwise false.
   bool isLoggedIn();
   bool isLoginEnabled();
   bool isShowLogin();
   QString username();
   AbstractLoginDialog::LoginType loginType() const;
   void setLoginType(const AbstractLoginDialog::LoginType& loginType);
   void showLogin(bool show);
   void setLoginStyleSheet(const QString& stylesheet);
   QString loginStyleSheet();
   void setCustomLoginDialog(AbstractLoginDialog* loginDlg);
   bool hasCustomLoginDialog();
   void checkPassword(QString password);
   void checkPassword(QString username, QString password);
   void setPassword(QString password);
   void addPassword(QString id, QString password);
   void clearPasswords();
   void loginIsCorrect(QString username);
   void loginIsIncorrect();

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
   void showMessages(bool show) {
      //     f->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
   }

   // general methods.
   void calculateWidgetSizes(int x, int y, int w, int h);
   void removeWidgetsFromLayout();
   void addWidgetsToLayout();

signals:
   void loggedOut();
   void loggedIn();
   void passwordBad();
   void usernameBad();
   void loginBad();

private:
   QWidget* m_parent;
   //   QSize m_size;
   QGridLayout* m_layout;
   ClockWidget* m_clockWidget;
   LoginWidget* m_loginWidget;
   MessageWidget* m_messageWidget;
   QFrame* m_filler;

   // stores clock/login/message values to restore when reshown.
   // the clock, login and message wisgets are destroyed when not required
   // so we need to store these until needed again.
   QString m_clockStylesheet, m_loginStylesheet, m_messageStylesheet;
   bool m_ignoreCase, m_showSeconds;
   QFrame::Shape m_clockFrame;

   void loginClicked(bool /*clicked*/) {
      if (m_loginWidget) {
         if (isLoggedIn()) { // if it's logged in already then log out.
            m_loginWidget->logOut();
            emit loggedOut();

         } else {
            AbstractLoginDialog* abstractDlg = m_loginWidget->loginDialog();
            abstractDlg->setAttribute(Qt::WA_DeleteOnClose, true);
            abstractDlg->exec();

            if (isLoggedIn()) {
               m_loginWidget->displayLogoutText();
            }
         }
      }

      update();
   }
};

class ExTabWidgetPrivate
{

   Q_DECLARE_PUBLIC(ExTabWidget)
public:
   ExTabWidgetPrivate(ExTabWidget* parent, AbstractLoginDialog* customDlg);
   ~ExTabWidgetPrivate();

//   bool isInLoginFrame(int x, int y);

   ExTabWidget* q_ptr;
   WrapperWidget* m_wrapper;

   bool m_showMessages;
   QPalette m_palette;
   QRect* m_messageRect, *m_messageClip;
   int m_stringAdvance, m_frameHeight, m_frameWidth, m_frameX, m_frameY,
       m_messageWidth;

   // Clock stuff.
   QString m_nowString;
   uint m_now;
   bool m_showFrame;
   bool m_isInframe/*, m_loginPressed*//*, m_ignoreCase*/;

   // clock stuff.
   void showClock(bool showClock);
   bool isShowClock();
   void showSeconds(bool showSeconds);
   void setClockFrame(QFrame::Shape style);

   // Login stuff
   void showLogin(bool showLogin);
   void setLoginType(AbstractLoginDialog::LoginType type);
   AbstractLoginDialog::LoginType loginType();
   QString loginText() const;
   void setLoginText(const QString& text);
   QString logoutText() const;
   void setLogoutText(const QString& text);
   bool isLoggedIn();
   bool isLoginEnabled();
   void setPassword(QString password);
   void addPassword(QString username, QString);
   void clearPasswords();
   void setLargeTextForLoginDialog(bool);
   bool hasCustomLoginDialog();
   void setCustomLoginDialog(AbstractLoginDialog* loginDlg);
   void checkPassword(QString value);
   void checkPassword(QString username, QString value);
   QString username();

   // message stuff.
   void showMessages(bool);
   void showMessageFrame(bool showFrame, QFrame::Shape style);
   void setMarqueeSpeed(qreal charPerSecond);
   uint m_timeout;
   void clearMessage();
   void setMessage(uint);
   void setMessageColor(QColor color);
   void setMessageBackground(QColor);
   void setMessageBackground(QBrush);
   void setMessage(const QString& message, uint messageTimeout = 0);
   void setMessage(QColor, QString message, uint messageTimeout = 0);
   void setMessage(QColor, QColor, QString message, uint messageTimeout = 0);
   void setMessage(QColor, QBrush, QString message, uint messageTimeout = 0);
   void setMarquee(bool marquee);
   void startMarqueeTimerIfRequired();
   void stopMarqueeTimer();
   void updateMarquee();
   QBrush messageBackgroundBrush();
   QColor messageTextColor();
   void messageTimeout();

   // general stuff.
   //   bool mousePressEvent(QMouseEvent* event);
   //   bool mouseReleaseEvent(QMouseEvent* event);
//   void paintLogin(QPainter* painter, int w, int h);
   void paintMessages(QPainter* painter, int w, int h);
//   void paintBorder(QPainter* painter,
//                    int x,
//                    int y,
//                    int w,
//                    int h,
//                    bool darkFirst);
//   void paintUpperBorder(QPainter* painter, int x, int y, int w, int h);
//   void paintLowerBorder(QPainter* painter, int x, int y, int w, int h);
   void tabwidgetStatusChanged();
   QString m_stylesheet;
   QString clockStyleSheet() const;
   QString loginStyleSheet() const;
   QString messageStyleSheet() const;
   void setClockStyleSheet(const QString& styleSheet);
   void setLoginStyleSheet(const QString& styleSheet);
   void setMessageStyleSheet(const QString& styleSheet);

   // message stuff
   QString m_messageText;
   QString m_username;
   QColor m_textColor, m_tempColor;
   QBrush m_background, m_tempBackground;
   bool m_marquee, m_useTempColor, m_useTempBack;
   int m_marqueePos /*, m_marqueeSpeed*/;
   //   AbstractLoginDialog::LoginType m_loginType;


private:
   void resetMessageData(const QString& message, bool tempColor);
};

/// \endcond

#endif // EXTENDEDTABWIDGETPRIVATE_H
