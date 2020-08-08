#ifndef _H
#define _H

#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGuiApplication>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QTabWidget>
#include <QTimer>
#include <QWidget>

#include "private/extabwidget_p.h"
#include "sm_widgets_global.h"

/*!
   \class ExTabWidget
   \file extabwidget.h extabwidget.cpp
   \class ExTabWidget extabwidget.h

   \brief An extension of QTabWidget with the ability to add various things in
   the unused space to the right of the tabs.

   \since 5.7.0
   \license The MIT License
   \copyright © 2019 - 2020 Simon Meaden. All rights reserved.

   There are three things that can be added :
   -# A login button
   -# A digital clock
   -# A single line message box.

   More than one of the options can be added at the same time with the order
   from right to left being the login button, the clock and finally the message
   box, with the message box taking all available free space.

   The login button is displayed/hidden using the ExTabWidget::showLogin(bool)
   method, with true displaying the button.

   //   There are two varieties of login, a fairly standard login dialog with
   both username and a
   //   password
   //   edit boxes and a 'simple' login which has only a password edit box. Use
   the ExTabWidget::setLogin(bool) or
   //   ExTabWidget::setSimpleLogin(bool) methods, with a value of true, to set
   the login method.

   //   If the login username/password is valid the button will change to
   display "Log Out" and a
   //   ExTabWidget::loggedIn() signal is sent, otherwise either a
   ExTabWidget::usernameBad()
   //   signal  or a ExTabWidget::passwordBad() signal will be sent, depending
   on the fault. The
   //   ExTabWidget::isLoggedIn() method can be used to check whether a user is
   logged in, and the
   //   ExTabWidget::username() method can be used to recover the username of
   the logged in user. If
   //   the simple login dialog is used or the ExTabWidget::usernameBad() signal
   was sent then
   //   ExTabWidget::username() will return an empty QString.

   Clicking on the button when "Log Out" is displayed will cause a
   ExTabWidget::loggedOut() signal to be sent. ExTabWidget::loggedIn() returns
   false and ExTabWidget::username() returns an empty string at this point.

   The simple login method requires that a password is set, only one allowed,
   using the ExTabWidget::setPassword(QString) method. The standard login
   requires that one or more username/password pairs be set up using the
   ExTabWidget::insertPassword(QString username, QString password) method, once
   for each user. User names must be unique, adding a second entry with the same
   username will overwrite the first entry.

   Setting the value of the ignore case flag to true using the
   ExTabWidget::setIgnoreCase(bool) method will cause the character case of the
   password and username to be ignored. If false the case of the username and
   password are checked, ie UsErNaMe does not equal username.

   ExTabWidget::clearPasswords() will remove all passwords from the list.
   Passwords and usernames for the simple and standard login dialogs are kept
   separately so it is possible to switch between the two methods if required.

   The clock is displayed when the ExTabWidget::enableClock(bool) is called with
   the value of true. By default the digital clock is displayed without seconds.
   The display seconds use the ExTabWidget::showseconds(bool) method.

   The message box can be displayed using the ExTabWidget::enableMessages(bool)
   method with a value of true. Messages are sent using the
   ExTabWidget::setMessage(QString, uint) method with the optional uint value
   indicating a timeout in seconds before the message is erased. Text colour can
   be modified by using the alternative ExTabWidget::setMessage(QColor, QString,
   uint) method, alternatively use the ExTabWidget::setMessageColor(QColor
   color) to permanently change the text colour.

   If messages are too long for the available space you can use the marquee
   option which causes the message to rotate along message box. To enable this
   use the ExTabWidget::enableMarquee(bool) with a value of true, adjusting the
   speed if necessary with the setMarqueeSpeed(qreal) method.

   Each can be drawn with or without a frame, using the
   ExTabWidget::showFrame(bool) method. By default a frame is shown.

   \since 5.0
*/
class SM_WIDGETS_SHARED_EXPORT ExTabWidget : public QTabWidget
{

   Q_OBJECT

   /*!
      \property ExTabWidget::clock

      \brief This property describes whether the clock is displayed.

      By default, this property is false, and the clock is not displayed.

      @accessor showClock(), isClockEnabled()
   */ Q_PROPERTY(bool clock READ isClockEnabled WRITE showClock DESIGNABLE true)

   /*!
      \property ::messages

      \brief This property describes whether the message box is displayed.

      By default, this property is false, and messages are not displayed.

                               @accessor showMessages(), isMessagesEnabled()
   */
   Q_PROPERTY(
      bool messages READ isMessagesEnabled WRITE showMessages DESIGNABLE true)

   /*!
      \property ExTabWidget::login

      \brief This property describes whether the login button is displayed.

      By default, this property is false, and the login button is not displayed.

      @accessor isLoginEnabled()
   */
   Q_PROPERTY(bool login READ isLoginEnabled)

   /*!
      \property ::loginType

      \brief This property sets the login dialog type.

      By default this is None, and no login button is diaplayed.

      @accessor loginType(), setLoginType()
   */
   Q_PROPERTY(AbstractLoginDialog::LoginType loginType READ loginType WRITE setLoginType)

   /*!
      \property ignoreCase

      \brief This property defines whether character case is ignored for
      usernames and passwords.

      By default, this property is false and case is not ignored.

      @accessor setIgnoreCase(), isIgnoreCase()
   */
   Q_PROPERTY(
      bool ignoreCase READ isIgnoreCase WRITE setIgnoreCase DESIGNABLE true)
   /*!
      \property ::marquee

      \brief  This property describes whether the marquee is enabled.

      @accessor setMarquee(bool), isMarqueeEnabled()
   */
   Q_PROPERTY(
      bool marquee READ isMarqueeEnabled WRITE setMarquee DESIGNABLE true)

   /*!
      \property ::messageColor

      \brief  This property describes whether the marquee is enabled.

      @accessor messageColor(), setMessageColor(QColor)
   */
   Q_PROPERTY(
      QColor messageColor READ messageColor WRITE setMessageColor DESIGNABLE true)
   /*!
      \property ::messageBackground

      \brief  This property describes whether the marquee is enabled.

      @accessor messageBackground(), setMessageColor(QColor)
   */
   Q_PROPERTY(QBrush messageBackground READ messageBackground WRITE
              setMessageBackground DESIGNABLE true)

   Q_DECLARE_PRIVATE(ExTabWidget)

public:

   /*!
      \brief Constructs an ExTabWidget with parent parent with an optional custom
      login dialog.
   */
   explicit ExTabWidget(QWidget* parent = nullptr,
                        AbstractLoginDialog::LoginType type = AbstractLoginDialog::None,
                        AbstractLoginDialog* customDlg = nullptr);

   /*!
      \brief Destroys the tabbed widget.
   */
   ~ExTabWidget() {}

   // ReImplemented from QTabWidget.
   int addTab(QWidget* page, const QString& label);
   int addTab(QWidget* page, const QIcon& icon, const QString& label);
   void clear();
   int insertTab(int index, QWidget* page, const QString& label);
   int insertTab(int index,
                 QWidget* page,
                 const QIcon& icon,
                 const QString& label);
   void removeTab(int index);
   void setIconSize(const QSize& size);
   void setTabIcon(int index, const QIcon& icon);
   void setTabShape(QTabWidget::TabShape s);
   void setTabText(int index, const QString& label);
   void setTabVisible(int index, bool visible);

   //! Returns true if the clock is enabled, otherwise false.
   bool isClockEnabled();
   //! Enables/disables the display of the digital clock
   //!
   //! Shows the clock if true, otherwise hides it.
   void showClock(bool showClock);
   //! Shows a frame around the displayed items if true.
   //!
   //! The show frame flag operates on all of the extensions, so either they all
   //!  have frames or none of them have frames.
   void setClockFrameStyle(QFrame::Shape style = QFrame::NoFrame);
   //! Set the show seconds flag.
   //!
   //! Show the optional show seconds flag. Displays seconds when true, otherwise
   //! the seconds are not displayed.
   void showSeconds(bool showSeconds);
   //! Returns the stylesheet for the clock widget.
   QString clockStyleSheet() const;
   //! Sets the stylesheet for the clock widget alone.
   void setClockStyleSheet(const QString& styleSheet);


   QString loginText() const;
   void setLoginText(const QString &text);
   QString logoutText() const;
   void setLogoutText(const QString &text);

   /*!
      \brief Returns true if the user is logged in, otherwise false.
   */
   bool isLoggedIn();

   /*!
      \brief Returns the username if logged in with the standard login,
      otherwise an empty string is returned.
   */
   QString username();


   /*!
      \brief Returns true if the login is enabled, otherwise false.
   */
   bool isLoginEnabled();

   /*!
      \brief Returns true if the message box is enabled, otherwise false.
   */
   bool isMessagesEnabled();

   /*!
      \brief Returns the value of the ignore case flag.

      True if the character case of usernames and passwords are to be ignored.
   */
   bool isIgnoreCase();

   /*!
      \brief Sets the message text scrolling.

      Sets the text message to scrolling if the text is longer than the available
      space. If the text will fit inside the available space then this is
      ignored.
   */
   bool isMarqueeEnabled();

   /*!
      \brief The permanent background brush.

      This QBrush object defines the standard background for messages.

      \sa setMessageBackground(QBrush)
   */
   QBrush messageBackground();

   /*!
      \brief The permanent background brush.

      This QColor defines the standard text color for messages.

      \sa setMessageColor(QColor)
   */
   QColor messageColor();

   /*!
      \brief Enables/disables the display of the login button

      Shows the login button if showLogin is true, otherwise hides it.
   */
   void showLogin(bool showLogin);
   /*!
      \brief Sets the login type to one of ExTabWidget::LoginType values.

      This is one of the LoginType values. By default it is ExTabWidget::None,
      however it can be set to ExTabWidget::Simple or ExTabWidget::Standard for
      one of the internal types or ExTabWidget::Custom if the user supplies a
      custom login dialog.

      \sa loginType(), ExTabWidget::LoginType
   */
   void setLoginType(AbstractLoginDialog::LoginType type);

   /*!
      \brief Returns the login type.

      This is one of the LoginType values. By default it is ExTabWidget::None,
      however it can be set to ExTabWidget::Simple or ExTabWidget::Standard for
      one of the internal types or ExTabWidget::Custom if the user supplies a
      custom login dialog.

      \sa setLoginType(), ExTabWidget::LoginType
   */
   AbstractLoginDialog::LoginType loginType();

   /*!
      \brief Sets a custom logging dialog.

      Note: This only stores the custom dialog object, it does not ensure tha it
      is used. To use the custom dialog you also need to call
      setLoginType(LoginType) method to ExTabWidget::Custom.
   */
   void setCustomLoginDialog(AbstractLoginDialog* loginDlg);

   /*!
      \brief Enables/disables the message box if the value is true.
   */
   void showMessages(bool showMessages);

   void showMessageFrame(bool showFrame, QFrame::Shape style = QFrame::NoFrame);

   /*!
      \brief Sets the password for the simple login dialog.
   */
   void setPassword(QString password);
   /*!
      \brief Adds a username/password pair for the standard login dialog.

      Usernames must be unique, inserting a repeat username will overwrite the
      earlier version.
   */
   void addPassword(QString id, QString password);
   /*!
      \brief Clears all password/usernames.
   */
   void clearPasswords();

   /*!
      \brief Sets the value of the ignore case flag. If set to true all
      password/username checks ignore the character case.
   */
   void setIgnoreCase(bool ignoreCase);


   /*!
      \brief Sets the text colour the message is drawn in.

      This can temporarily be overridden by using the setMessage() method
      with the text color and background color methods.

      \sa messageBackground(), setMessageBackground(QBrush),
      setMessageBackground(QColor)

   */
   void setMessageColor(QColor color);
   /*!
      \brief Sets the background brush colour the message is drawn on.

      This can temporarily be overridden by using the setMessage() method
      with the text color and background color methods.

      \sa messageBackgroundBrush(), setMessageBackground(QBrush),
      setMessageColor(QColor)
   */
   void setMessageBackground(QColor color);
   /*!
      \brief Sets the background brush the message is drawn on.

      This can temporarily be overridden by using the setMessage() method
      with the text color and background color methods.

      \sa messageBackgroundBrush(), setMessageBackground(QColor),
      setMessageColor(QColor)
   */
   void setMessageBackground(QBrush brush);

   /*!
      \brief Sets the message text, with an optional timeout in seconds.

      Sets the text message for the tab bar. This is only a single line message
      so "\n" characters are removed. There really is not enough room for a multi
      line MessageTabWidget within the tab bar.
   */
   void setMessage(QString message, uint timeout = 0);

   //   /*!
   //      \brief Sets the message text and text colour, with an optional timeout
   //      in seconds.

   //      Sets the text message and colour for the tab bar. The optional timeout
   //      will cause the message to  disappear after timeout seconds.

   //      This is only a single line message so "\n" characters are removed.
   //      There really is not enough room for a multi line MessageTabWidget
   //      within the tab bar.

   //      This is the equivalent of
   //      \code
   //      tab->setMessageColor(color);
   //      tab->setMessage(message, timeout);
   //      \endcode

   //   */
   //   void setMessage(QColor color, QString message, uint timeout = 0);
   //   /*!
   //      \brief Sets the message text and text colour and background colour,
   //      with an optional timeout in seconds.

   //      Sets the text message and colour for the tab bar. The optional timeout
   //      will cause the message to  disappear after timeout seconds.

   //      This is only a single line message so "\n" characters are removed.
   //      There really is not enough room for a multi line MessageTabWidget
   //      within the tab bar.

   //      This is the equivalent of
   //      \code
   //      tab->setMessageColor(color);
   //      tab->setMessage(message, timeout);
   //      \endcode

   //   */
   //   void setMessage(QColor color, QColor back, QString message, uint timeout
   //   = 0);

   //   /*!
   //      \brief Sets the message text and text colour and background brush,
   //      with an optional timeout in seconds.

   //      Sets the text message and colour for the tab bar. The optional timeout
   //      will cause the message to  disappear after timeout seconds.

   //      This is only a single line message so "\n" characters are removed.
   //      There really is not enough room for a multi line MessageTabWidget
   //      within the tab bar.

   //      This is the equivalent of
   //      \code
   //      tab->setMessageColor(color);
   //      tab->setMessage(message, timeout);
   //      \endcode

   //   */
   //   void setMessage(QColor color, QBrush back, QString message, uint timeout
   //   = 0);
   /*!
      \brief Sets the message text scrolling.

      Sets the text message to scrolling if the text is longer than the available
      space. If the text will fit inside the available space then this is
      ignored.
   */
   void setMarquee(bool marquee);
   /*!
      \brief Sets the marquee speed in characters a second.

      The default is 10 characters a second. To slow it down enter a lower
       number of characters a second and to speed it up a higher number.
   */
   void setMarqueeSpeed(qreal charPerSecond);

   /*!
      \brief Removes the message from the display.
   */
   void clearMessage();

   QString styleSheet() const;
   QString loginStyleSheet() const;
   QString messageStyleSheet() const;
   //   void setStyleSheet(const QString &styleSheet);
   void setLoginStyleSheet(const QString& styleSheet);
   void setMessageStyleSheet(const QString& styleSheet);

signals:
   /*!
      \fn ExTabWidget::loggedOut()

      \brief This signal is emitted when either the simple or the standard login
      dialog indicate that the user has successfully logged out.
   */
   void loggedOut();

   /*!
      \fn ExTabWidget::loggedIn()

      \brief This signal is emitted when either the simple or the standard login
      dialog indicate that the user has successfully logged in.
   */
   void loggedIn();

   /*!
      \fn ExTabWidget::passwordBad()

      \brief This signal is emitted when either the simple or the standard login
      dialog indicate that the password was bad for the username.
   */

   void passwordBad();
   /*!
      \fn ExTabWidget::usernameBad()

      \brief This signal is emitted when either the simple or the standard login
      dialog indicate that the username was not one of the supplied values
   */
   void usernameBad();

   /*!
      \fn ExTabWidget::loginBad()

      \brief This signal is emitted when a custom login dialog sends a
      loginIsIncorrect signal.
   */
   void loginBad();

signals:
   //! This signal is inended for internal use and informes the ExTabWidget whenever
   //! a tab is added, removed or modified.
   void statusChanged();

private:

   void statusHasChanged();

   //   /*!
   //       \brief Reimplements: QTabWidget::paintEvent()
   //   */
   //   virtual void paintEvent(QPaintEvent* evt);
   //   /*!
   //      \brief Reimplements: QTabWidget::mousePressEvent()
   //   */
   //   virtual void mousePressEvent(QMouseEvent* event);
   //   /*!
   //      \brief Reimplements: QTabWidget::mouseReleaseEvent()
   //   */
   //   virtual void mouseReleaseEvent(QMouseEvent* event);
   /*!
      \brief Reimplements: QTabWidget::resizeEvent()
   */
   virtual void resizeEvent(QResizeEvent* evt);

private:
   ExTabWidgetPrivate* d_ptr;

   /*
      Checks the password for a simple login dialog.
   */
   void checkPassword(QString password);
   /*
      Checks the username/password for a standard login dialog.
   */
   void checkPassword(QString id, QString password);

   void updateMarquee();

   void timeout();


};

#endif // _H
