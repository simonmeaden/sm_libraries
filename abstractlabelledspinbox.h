/*
   Copyright 2020 Simon Meaden

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/
#ifndef ABSTRACTLABELLEDSPINBOX_H
#define ABSTRACTLABELLEDSPINBOX_H

#include "abstractlabelledwidget.h"
#include <QSpinBox>

/*!
   \file abstractlabelledspinbox.h abstractlabelledspinbox.cpp
   \class AbstractLabelledSpinBox abstractlabelledspinbox.h
   \brief The LabelledSpinWidget abstract base class.
   \since 5.7.0
   \license The MIT License
   \copyright © 2019 - 2020 Simon Meaden. All rights reserved.

   Extends AbstractLabelledWidget to supply common capability to the
    various labelled spin boxes.

   All properties of the QSpinBox  are copied across to this widget.
*/
class AbstractLabelledSpinBox : public AbstractAlignableLabelledWidget
{
   /*!
      \property AbstractLabelledSpinBox::value

      \brief This property holds the value of the spin box.

      @reimplements QSpinBox::value
      @accessor %value(), %setValue()
      @notifier valueChanged(int)
   */
   Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged USER true)

   /*!
      \property AbstractLabelledSpinBox::maximum

      \brief This property holds the maximum value of the spin box.

      @reimplements QSpinBox::maximum
      @accessor %maximum(void), %setMaximum()
   */
   Q_PROPERTY(int maximum READ maximum WRITE setMaximum)

   /*!
      \property AbstractLabelledSpinBox::minimum

      \brief This property holds the minimum value of the spin box.

      @reimplements QSpinBox::minimum
      @accessor %minimum(), %setMinimum()
   */
   Q_PROPERTY(int minimum READ minimum WRITE setMinimum)

   /*!
      \property AbstractLabelledSpinBox::displayIntegerBase

      \brief This property holds the base used to display the value of the spin
      box

      @reimplements QSpinBox::displayIntegerBase
      @accessor %displayIntegerBase(), %setDisplayIntegerBase()
   */
   Q_PROPERTY(
      int displayIntegerBase READ displayIntegerBase WRITE setDisplayIntegerBase)

   /*!
      \property AbstractLabelledSpinBox::suffix

      \brief This property holds the suffix of the spin box

      @reimplements QSpinBox::suffix
       @accessor %suffix(), %setSuffix()
   */
   Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)

   /*!
      \property AbstractLabelledSpinBox::prefix

      \brief This property holds the spin box's prefix

      @reimplements QSpinBox::prefix
      @accessor %prefix(), %setPrefix()
   */
   Q_PROPERTY(QString prefix READ prefix WRITE setPrefix)

   /*!
      \property AbstractLabelledSpinBox::singleStep

      \brief This property holds the step value

      @reimplements QSpinBox::singleStep
      @accessor %singleStep(), %setSingleStep()
   */
   Q_PROPERTY(int singleStep READ singleStep WRITE setSingleStep)

   /*!
      \property AbstractLabelledSpinBox::stepType

      \brief This property holds the step type.

      @reimplements QSpinBox::stepType
      @accessor %stepType(), %setStepType(QSpinBox::StepType)
   */
   Q_PROPERTY(QSpinBox::StepType stepType READ stepType WRITE setStepType)

   Q_OBJECT

public:
   //! Constructs a lineedit with the given parent, and supplied label.
   explicit AbstractLabelledSpinBox(const QString& labelText = QString(),
                                    QWidget* parent = nullptr,
                                   WidgetFactory const& factory = WidgetFactory());

   //! @reimplements QComboBox::value() const.
   int value() const;

   //! @reimplements QSpinBox::setValue().
   void setValue(int v);

   //! @reimplements QComboBox::maximum() const.
   int maximum() const;

   //! @reimplements QSpinBox::setMaximum().
   void setMaximum(int max);

   //! @reimplements QComboBox::minimum() const.
   int minimum() const;

   //! @reimplements QSpinBox::setMinimum().
   void setMinimum(int min);

   //! @reimplements QComboBox::displayIntegerBase() const.
   int displayIntegerBase() const;

   //! @reimplements QSpinBox::setDisplayIntegerBase().
   void setDisplayIntegerBase(int base);

   //! @reimplements QComboBox::prefix() const.
   QString prefix();

   //! @reimplements QSpinBox::setPrefix().
   void setPrefix(const QString& labelText);

   //! @reimplements QComboBox::suffix() const.
   QString suffix();

   //! @reimplements QSpinBox::setSuffix().
   void setSuffix(const QString& labelText);

   //! @reimplements QSpinBox::setRange().
   void setRange(int min, int max);

   //! @reimplements QComboBox::singleStep() const.
   int singleStep() const;

   //! @reimplements QSpinBox::setSingleStep().
   void setSingleStep(int step);

   //! @reimplements QComboBox::stepType() const.
   QAbstractSpinBox::StepType stepType() const;

   //! @reimplements QSpinBox::setStepType().
   void setStepType(QAbstractSpinBox::StepType type);

   //! @reimplements QSpinBox::cleanText().
   QString  cleanText() const;

   //! @reimplements QSpinBox::prefix().
   QString  prefix() const;

   //! @reimplements QSpinBox::suffix().
   QString  suffix() const;

   //! @reimplements QSpinBox::setAlignment() const.
   void setWidgetAlignment(const Qt::Alignment& widgetAlignment);

   //! @reimplements QSpinBox::alignment() const.
   Qt::Alignment widgetAlignment() const;


signals:
   /*!
      \fn AbstractLabelledSpinBox::textChanged(const QString& text)

      @from QSpinBox::textChanged.
      @notprop value.
   */
   void textChanged(const QString& labelText);

   /*!
      \fn AbstractLabelledSpinBox::valueChanged(int value)

      @from QSpinBox::value.
      @notprop value.
   */
   void valueChanged(int);
};
#endif // ABSTRACTLABELLEDSPINBOX_H
