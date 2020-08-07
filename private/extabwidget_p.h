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
   SimpleLoginDialogPrivate* d_ptr;
   QLineEdit* m_passEdit;

   void initGui(bool largeText);
   void acceptLogin();
};

class ClockWidget : public QFrame
{
public:
   explicit ClockWidget(QWidget* parent = nullptr);

   bool isShowing();
   void showClock(bool showClock);
   void showClockFrame(bool showFrame, QFrame::Shape style);

   bool showSeconds() const;
   void setShowSeconds(bool value);

   void paintEvent(QPaintEvent* evt);
   int calculateRequiredWidth(int x, int y, int w, int h);

   QSize sizeHint() const override;
   void setSizeHint(const QSize& size);

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

class LoginWidget : public QPushButton
{
public:
   explicit LoginWidget(QWidget* parent = nullptr)
      : QPushButton(parent)
      , m_loginText(LOGIN)
   {}

   bool isShowing() {
      return m_showLogin;
   }
   void showLogin(bool showLogin) {
      if (showLogin != m_showLogin) {
         m_showLogin = showLogin;

         if (showLogin) {
//            if (m_clockTimer && m_clockTimer->isActive()) {
//               return;

//            } else {
//               if (!m_clockTimer) {
//                  m_clockTimer = new QTimer(this);
//                  connect(m_clockTimer, &QTimer::timeout,
//                          this, &ClockWidget::nextSecond,
//                          Qt::UniqueConnection);
//               }

//               m_clockTimer->start(CLOCK_TIME);
//            }

//         } else {
//            if (m_clockTimer) {
//               if (m_clockTimer->isActive()) {
//                  m_clockTimer->stop();
//               }

//               m_clockTimer->deleteLater();
//               m_clockTimer = nullptr;
//            }
         }
      }
   }

   int calculateRequiredWidth() {
      if (isVisible()) {
         QFontMetrics fm = fontMetrics();
         // always use LOGOUT as it is the longer. Dont want width to change.
         return fm.horizontalAdvance(LOGOUT) + 20;

      } else {
         return 0;
      }
   }

   int calculateRequiredWidth(int x, int y, int w, int h) {
      //      int w = 0;

      return 0;
   }

   void paintEvent(QPaintEvent* evt) {
      QPushButton::paintEvent(evt);
   }

private:
   QString m_loginText;
   bool m_showLogin;

   static const QString LOGIN;
   static const QString LOGOUT;
};

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
public:
   explicit WrapperWidget(QWidget* parent = nullptr)
      : QFrame(parent)
      , m_parent(parent)
      , m_layout(new QGridLayout)
      , m_showLogin(false)
      , m_showClock(false)
      , m_showMessages(false)
      , m_clockWidget(nullptr)
      , m_loginWidget(nullptr)
      , m_messageWidget(nullptr)
      , m_filler(nullptr) {
      setStyleSheet("background: lightgreen;");
      setContentsMargins(0, 0, 3, 0);
      m_layout->setContentsMargins(0, 0, 0, 0);
      setLayout(m_layout);
   }

   bool isShowLogin() {
      return false;
   }

   void showLogin(bool show) {}

   //   void setLoginType(ExTabWidget::LoginType type) {

   //   }

   void removeWidgetsFromLayout() {
      for (int i = m_layout->count(); i > 0; --i) {
         m_layout->takeAt(i - 1);
      }
   }

   void addWidgetsToLayout() {
      // must be reloaded in reverse order.
      if (m_messageWidget) {
         m_layout->addWidget(m_messageWidget, 0, 0);

         if (m_filler) {
            // filler not needed if messages exists.
            m_filler->deleteLater();
            m_filler = nullptr;
         }

      } else {
         if (!m_filler) {
            m_filler = new QFrame(this);
            m_filler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            m_filler->setStyleSheet("background: lightblue");
         }

         m_layout->addWidget(m_filler, 0, 0);
      }

      if (m_clockWidget) {
         m_layout->addWidget(m_clockWidget, 0, 1);
      }

      if (m_loginWidget) {
         m_layout->addWidget(m_loginWidget, 0, 2);
      }

      updateGeometry();
   }

   bool isShowClock();

   void showClock(bool show) {
      // we need to remove the widgets from the layout then after creating
      // or destroying the clock widget reload them in the right order.
      removeWidgetsFromLayout();

      if (m_showLogin) {
         // TODO login
      }

      if (show) {
         if (!m_clockWidget) {
            m_clockWidget = new ClockWidget(m_parent);
            m_clockWidget->setSizePolicy(QSizePolicy::Preferred,
                                         QSizePolicy::Fixed);
            m_clockWidget->showClock(true);

            if (!m_clockStylesheet.isEmpty()) {
               m_clockWidget->setStyleSheet(m_clockStylesheet);
            }
         }

      } else {

         m_clockWidget->deleteLater();
         m_clockWidget = nullptr;
      }

      if (m_showMessages) {
         // TODO messages
      }

      addWidgetsToLayout();
   }

   void showClockFrame(bool showFrame, QFrame::Shape style) {
      if (m_clockWidget) {
         m_clockWidget->showClockFrame(showFrame, style);
      }
   }

   void setShowSeconds(bool show) {
      if (m_clockWidget) {
         m_clockWidget->setShowSeconds(show);
      }
   }

   void setClockStyleSheet(const QString& stylesheet) {
      if (m_clockWidget) {
         m_clockWidget->setStyleSheet(stylesheet);
      }

      m_clockStylesheet = stylesheet;
   }

   void setLoginStyleSheet(const QString& stylesheet) {
      if (m_loginWidget) {
         m_loginWidget->setStyleSheet(stylesheet);
      }

      m_loginStylesheet = stylesheet;
   }

   void setMessageStyleSheet(const QString& stylesheet) {
      if (m_messageWidget) {
         m_messageWidget->setStyleSheet(stylesheet);
      }

      m_messageStylesheet = stylesheet;
   }

   void showMessages(bool show) {
      //     f->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
   }

   void calculateWidgetSizes(int x, int y, int w, int h) {
      int availableWidth = w;

      if (m_loginWidget) {
         int reqWidth =
            m_loginWidget->calculateRequiredWidth(x, y, availableWidth, h);
         availableWidth -= reqWidth;
      }

      if (m_clockWidget) {
         int reqWidth =
            m_clockWidget->calculateRequiredWidth(x, y, availableWidth, h);

         if (reqWidth < 0) {
            return;
         }

         QSize size = QSize(reqWidth, h);
         m_clockWidget->setSizeHint(size);
         availableWidth -= reqWidth;
      }

      if (m_messageWidget) {
         m_messageWidget->calculateRequiredWidth(x, y, availableWidth, h);
      }
   }

private:
   QWidget* m_parent;
   //   QSize m_size;
   QGridLayout* m_layout;
   bool m_showLogin, m_showClock, m_showMessages;
   ClockWidget* m_clockWidget;
   LoginWidget* m_loginWidget;
   MessageWidget* m_messageWidget;
   QFrame* m_filler;
   QString m_clockStylesheet, m_loginStylesheet, m_messageStylesheet;
};

class ExTabWidgetPrivate
{

   Q_DECLARE_PUBLIC(ExTabWidget)
public:
   ExTabWidgetPrivate(ExTabWidget* parent, AbstractLoginDialog* customDlg);
   ~ExTabWidgetPrivate();

   bool isInLoginFrame(int x, int y);
   bool isShowClock() {
      return m_wrapper->isShowClock();
   }

   ExTabWidget* q_ptr;
   WrapperWidget* m_wrapper;

   QMap<QString, QString> m_passwords;
   QString m_password;
   bool m_loggedIn, m_showLogin, /*m_login,*/ /*m_simplelogin,*/ /*m_showClock,*/
        m_showMessages;
   AbstractLoginDialog* m_loginDlg, *m_customLoginDlg;
   QPalette m_palette;
   QRect* m_loginRect, /**m_clockRect,*/ *m_messageRect, *m_messageClip;
   int m_stringAdvance, m_frameHeight, m_frameWidth, m_frameX, m_frameY,
       m_messageWidth;

   // Clock stuff.
   QString m_nowString;
   uint m_now;
   bool /*m_showSeconds,*/ m_showFrame;
   bool m_isInframe, m_loginPressed, m_ignoreCase;

   //   void showFrame(bool frame, QFrame::Shape style);
   void showClockFrame(bool showFrame, QFrame::Shape style);
   void showMessageFrame(bool showFrame, QFrame::Shape style);

   //   QTimer* m_clockTimer;
   QTimer* m_marqueeTimer;
   QTimer* m_timeoutTimer;

   void showLogin(bool showLogin);
   void setLoginType();
   //  void setSimpleLogin(bool);
   void setCustomLoginDialog(AbstractLoginDialog* loginDlg);
   void showMessages(bool);

   // clock stuff.
   void showClock(bool showClock);
   //   void nextSecond();
   void showSeconds(bool showSeconds);

   // Login stuff
   QString m_loginText;
   void displayLoginText();
   void displayLogoutText();
   void checkPassword(QString value);
   void checkPassword(QString username, QString value);
   void loginIsCorrect(QString username = QString());
   void loginIsIncorrect();
   void setIgnoreCase(bool);
   bool isLoggedIn();
   void addPassword(QString password);
   void addPassword(QString, QString);
   void setLargeTextForLoginDialog(bool);
   bool hasCustomLoginDialog();

   // message stuff.
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
   bool mousePressEvent(QMouseEvent* event);
   bool mouseReleaseEvent(QMouseEvent* event);
   void paintLogin(QPainter* painter, int w, int h);
   void paintMessages(QPainter* painter, int w, int h);
   void paintBorder(QPainter* painter,
                    int x,
                    int y,
                    int w,
                    int h,
                    bool darkFirst);
   void paintUpperBorder(QPainter* painter, int x, int y, int w, int h);
   void paintLowerBorder(QPainter* painter, int x, int y, int w, int h);
   void tabwidgetStatusChanged();
   QString m_stylesheet;
   QString styleSheet() const;
   QString clockStyleSheet() const;
   QString loginStyleSheet() const;
   QString messageStyleSheet() const;
   void setClockStyleSheet(const QString& styleSheet);
   void setLoginStyleSheet(const QString& styleSheet);
   void setMessageStyleSheet(const QString& styleSheet);

   void clearFrames();

   // message stuff
   QString m_messageText;
   QString m_username;
   QColor m_textColor, m_tempColor;
   QBrush m_background, m_tempBackground;
   bool m_marquee, m_useTempColor, m_useTempBack;
   int m_marqueePos /*, m_marqueeSpeed*/;

private:
   void resetMessageData(const QString& message, bool tempColor);
};

/// \endcond

#endif // EXTENDEDTABWIDGETPRIVATE_H
