#ifndef ABSTRACTLABELLEDWIDGET_H
#define ABSTRACTLABELLEDWIDGET_H

#include <QWidget>
#include <Qt>
#include <QtGlobal>
#include <QGridLayout>
#include <QLabel>

/*!
   \file abstractlabelledwidget.h abstractlabelledwidget.cpp
   \class AbstractLabelledWidget abstractlabelledwidget.h
   \brief The LabelledWidget abstract base class.
   \since 5.7.0
   \license The MIT License
   \copyright © 2019 - 2020 Simon Meaden. All rights reserved.

   The class is designed as a common super class for widgets like LabelledSpinBox
   and LabelledComboBox.

   The label can be on either side of the combo box, above it or below, with the position
   being set using the LabelledComboBox::setPosition() method.

   The label's value can be set/recovered using the text() and setText methods, and their
   format can be modified using textFormat() and setTextFormat().

   The label has full alignment capability using LabelledComboBox::setLabelAlignment().
   Use the LabelledComboBox::value() method to access.

   Stylesheets can be set for the individual components using either setLabelStyleSheet()
   or setWrapperStyleSheet(). Alternatively you can set a combined stypesheet using
   setStyleSheet() of the wrapping QWidget, however stylesheets set for individual
   components will override those set for the wrapper.

   QSizeSizePolicy can be set for either component using setLabelSizePolicy() or
   setWidgetSizePolicy().


*/
class AbstractLabelledWidget : public QWidget
{
   /*!
      \property AbstractLabelledWidget::labelText

      \brief This property holds the text of the label.

      @accessor %labelText(), %setLabelText()
   */
   Q_PROPERTY(QString labelText READ labelText WRITE setLabelText)

   /*!
      \property AbstractLabelledWidget::labelTextFormat
      \brief This property holds the label's text format

      See the Qt::TextFormat enum for an explanation of the possible options.

      The default format is Qt::AutoText.

      @accessor %labelTextFormat(), %setTextFormat(Qt::TextFormat)
   */
   Q_PROPERTY(Qt::TextFormat labelTextFormat READ labelTextFormat WRITE setLabelTextFormat)

   /*!
      \property AbstractLabelledWidget::labelAlignment

      \brief This property holds the alignment of the label.

      @accessor %labelAlignment(), %setLabelAlignment()
   */
   Q_PROPERTY(Qt::Alignment labelAlignment READ labelAlignment WRITE setLabelAlignment)

   /*!
      \property AbstractLabelledWidget::labelPosition

      \brief This property holds the position of the label. Possible values
      are AbstractLabelledWidget::Left, the default and AbstractLabelledWidget::Right.

      @accessor %position(), %setPosition()
   */
   Q_PROPERTY(AbstractLabelledWidget::LabelPosition labelPosition READ labelPosition WRITE setLabelPosition)

   enum Widget
   {
      Widget = 0,
      Label,
   };

public:
   /*!
      \brief An enum defining the label position.
   */
   enum LabelPosition
   {
      Left = 0, //!< The label is positioned to the left of the widget.
      Right,    //!< The label is positioned to the right of the widget.
      Above,    //!< The label is positioned above the widget.
      Below,    //!< The label is positioned below the widget.
   };

   //! Constructs an abstract spinbox with the given parent with default parent,
   //! and label text property.
   explicit AbstractLabelledWidget(QString labelText = QString(),
                                   QWidget* parent = nullptr);
   //! Called when the AbstractLabelledWidget is destroyed.
   virtual ~AbstractLabelledWidget();

   //! Sets the label text.
   void setLabelText(const QString& labelText);
   //! Returns the label text
   QString labelText() const;

   //! Returns the label position.
   LabelPosition labelPosition() const;
   //! Sets the label position.
   void setLabelPosition(const LabelPosition& labelPosition);

   //! Returns the label alignment.
   Qt::Alignment labelAlignment() const;
   //! Sets the label alignment.
   void setLabelAlignment(const Qt::Alignment& widgetAlignment);

   //! Returns the widget alignment.
   //! This returns 0, indicating that the widget doesn't support text alignment.
   virtual Qt::Alignment widgetAlignment() const {
      return QFlags<Qt::Alignment>();
   }
   //! Sets the widget alignment.
   //! This doesn't do anything and should be overridden in derived classes.
   virtual void setWidgetAlignment(const Qt::Alignment&) {}

   //! returns the label text format.
   Qt::TextFormat labelTextFormat() const;
   //! Sets the label text format.
   void setLabelTextFormat(Qt::TextFormat format);

   //!  @reimplements QWidget::sizeHint() const.
   QSize sizeHint() const override;
   //!  @reimplements QWidget::minimumSizeHint.
   QSize minimumSizeHint() const override;

   //! Sets the size policy for the label.
   //! \see QWidget::setSizePolicy(QSizePolicy)
   void setLabelSizePolicy(QSizePolicy policy);
   //! Sets the size policy for the label.
   //! \see QWidget::setSizePolicy(QSizePolicy::Policy, QSizePolicy::Policy)
   void setLabelSizePolicy(QSizePolicy::Policy horizontal, QSizePolicy::Policy vertical);
   //! Sets the size policy for the widget.
   //! \see QWidget::setSizePolicy(QSizePolicy)
   void setWidgetSizePolicy(QSizePolicy policy);
   //! Sets the size policy for the widget.
   //! \see QWidget::setSizePolicy(QSizePolicy::Policy, QSizePolicy::Policy)
   void setWidgetSizePolicy(QSizePolicy::Policy horizontal, QSizePolicy::Policy vertical);
   //! Returns the size policy for the widget.
   //! \see QLabel::sesizePolicy(QSizePolicy::Policy, QSizePolicy::Policy)
   QSizePolicy labelSizePolicy();
   //! Returns the size policy for the widget.
   //! \see QWidget::sizePolicy()
   QSizePolicy widgetSizePolicy();

   //! Sets the stylesheet for the label.
   //! For the entire widget use QWidget::setStyleSheet()
   void setLabelStyleSheet(const QString& styleSheet);
   //! Sets the stylesheet for the widget.
   //! For the entire widget use QWidget::setStyleSheet()
   void setWidgetStyleSheet(const QString& styleSheet);

   //! Clears the label's text.
   //! @reimplements QLabel::clear().
   void clearLabel();

protected:
   QLabel* m_label;            //!< pointer to the Label.
   QWidget* m_widget;        //!< pointer to the widget.
   QGridLayout* m_layout;    //!< widget layout
   LabelPosition m_position; //!< the label position
   void positionLabel();

private:
   //! you should override this for extensions to the abstract class.
   virtual void initGui(const QString& text = QString());
};

#endif // ABSTRACTLABELLEDWIDGET_H
