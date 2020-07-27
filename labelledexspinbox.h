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
#ifndef LABELLEDEXSPINBOX_H
#define LABELLEDEXSPINBOX_H

#include "abstractlabelledspinbox.h"
#include "sm_widgets_global.h"
#include "exspinbox.h"

/*!
   \file labelledexspinbox.h labelledexspinbox.cpp
   \class LabelledExSpinBox labelledexspinbox.h
   \brief The LabelledExSpinBox is a wrapper for QLabel and ExSpinBox that
          provides a labelled extended spin box.
   \since 5.7.0
   \license The MIT License
   \copyright © 2019 - 2020 Simon Meaden. All rights reserved.

   All properties of the QSpinBox are copied across to this widget.

   By default the ExSpinBox type is ExSpinBox::Hexadecimal.
*/
class SM_WIDGETS_SHARED_EXPORT LabelledExSpinBox : public AbstractLabelledSpinBox
{
   /*!
      \property LabelledExSpinBox::displayDigits

      \brief This property holds the number of displayable digits of the spin box.

      This is not necessarily the number of digits displayed unless showLeadingZeroes
      is true.


      @accessor %displayDigits()
   */
   Q_PROPERTY(int displayDigits READ displayDigits)

   /*!
      \property LabelledExSpinBox::displayType

      \brief This property holds the type for the spin box to display.
      By default ExSpinBox::Hexadecimal.

      @accessor %displayType(void), %setDisplayType()
      @notifier displayTypeChanged()
   */
   Q_PROPERTY(ExSpinBox::DisplayType displayType
              READ displayType
              WRITE setDisplayType
              NOTIFY displayTypeChanged(ExSpinBox::DisplayType))

   /*!
      \property LabelledExSpinBox::showLeadingZeroes

      \brief This property holds whether the spin box shows leading zeroes.

      If true leading zeroes are added until numberOfDigits characters are reached.

      @accessor %showLeadingZeroes(void), %setShowLeadingZeroes()
   */
   Q_PROPERTY(bool showLeadingZeroes READ showLeadingZeroes WRITE setShowLeadingZeroes)

   /*!
      \property AbstractLabelledSpinBox::stepType

   \brief This property holds the step type.

     @reimplements QSpinBox::stepType
     @accessor %stepType(), %setStepType(QSpinBox::StepType)
       */
       Q_PROPERTY(QSpinBox::StepType stepType READ stepType WRITE setStepType)


       Q_OBJECT

protected:
   struct WidgetFactory : AbstractLabelledWidget::WidgetFactory
   {
      virtual QWidget* newWidget(QWidget* parent) const {
         return new ExSpinBox(parent);
      }
   };

public:
   explicit LabelledExSpinBox(const QString& labelText = QString(),
                              QWidget* parent = nullptr,
                              WidgetFactory const& factory = WidgetFactory());

   /*!
      \brief Returns the number of displayable digits in the text string. By default 2.
   */
   quint8 displayDigits() const;

   /*!
      \brief Returns the type of the display, by default ExSpinBox Hexadecimal.
   */
   ExSpinBox::DisplayType displayType() const;

   //! @reimplements QSpinBox::singleStep() const.
   int singleStep() const;

   //! @reimplements QSpinBox::setSingleStep().
   void setSingleStep(int step);

   /*!
      \brief Sets the type of the display, by default ExSpinBox Hexadecimal.
   */
   void setDisplayType(ExSpinBox::DisplayType type);

   /*!
      \brief returns whether leading zeroes are displayed.
   */
   bool showLeadingZeroes() const;

   /*!
      \brief Sets whether leading zeroes are displayed.
   */
   void setShowLeadingZeroes(bool showLeadingZeroes);

   //! @reimplements QSpinBox::value() const.
   int value() const;

   //! @reimplements QSpinBox::setValue().
   void setValue(int v);

   //! @reimplements QSpinBox::maximum() const.
   int maximum() const;

   //! @reimplements QSpinBox::setMaximum().
   void setMaximum(int max);

   //! @reimplements QSpinBox::minimum() const.
   int minimum() const;

   //! @reimplements QSpinBox::setMinimum().
   void setMinimum(int min);

   //! @reimplements QSpinBox::setRange().
   void setRange(int min, int max);

   //! @reimplements QSpinBox::prefix().
   QString  prefix() const;

   //! @reimplements QSpinBox::suffix().
   QString  suffix() const;


signals:
   /*!
       \fn LabelledExSpinBox::displayTypeChanged(ExSpinBox::DisplayType)

      This signal is sent when the user changes the display type of the spin box.
   */
   void displayTypeChanged(ExSpinBox::DisplayType);

   /*!
      \fn LabelledExSpinBox::valueChanged(int value)

      @from QSpinBox::value.
      @notprop value.
   */
   void valueChanged(int);

private:
   void initGui(const QString& text = QString());
};

#endif // LABELLEDEXSPINBOX_H
