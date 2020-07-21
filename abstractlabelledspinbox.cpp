/**
  Copyright 2020 Simon Meaden

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#include "abstractlabelledspinbox.h"

/*!
   \brief Constructs an abstract labelled spinbox with the given label text and
          parent with default wrapping, and alignment properties.
*/
AbstractLabelledSpinBox::AbstractLabelledSpinBox(const QString& text,
    QWidget* parent)
  : AbstractLabelledWidget(text, parent)
{}

int AbstractLabelledSpinBox::value() const
{
  return qobject_cast<QSpinBox*>(m_widget)->value();
}

void AbstractLabelledSpinBox::setValue(int val)
{
  qobject_cast<QSpinBox*>(m_widget)->setValue(val);
}

int AbstractLabelledSpinBox::maximum() const
{
  return qobject_cast<QSpinBox*>(m_widget)->maximum();
}

void AbstractLabelledSpinBox::setMaximum(int max)

{
  qobject_cast<QSpinBox*>(m_widget)->setMaximum(max);
}

int AbstractLabelledSpinBox::minimum() const
{
  return qobject_cast<QSpinBox*>(m_widget)->minimum();
}

void AbstractLabelledSpinBox::setMinimum(int min)
{
  qobject_cast<QSpinBox*>(m_widget)->setMinimum(min);
}

int AbstractLabelledSpinBox::displayIntegerBase() const
{
  return qobject_cast<QSpinBox*>(m_widget)->displayIntegerBase();
}

void AbstractLabelledSpinBox::setDisplayIntegerBase(int base)
{
  qobject_cast<QSpinBox*>(m_widget)->setDisplayIntegerBase(base);
}

QString AbstractLabelledSpinBox::prefix()
{
  return qobject_cast<QSpinBox*>(m_widget)->prefix();
}

void AbstractLabelledSpinBox::setPrefix(const QString& text)
{
  qobject_cast<QSpinBox*>(m_widget)->setPrefix(text);
}

QString AbstractLabelledSpinBox::suffix()
{
  return qobject_cast<QSpinBox*>(m_widget)->suffix();
}

void AbstractLabelledSpinBox::setSuffix(const QString& text)
{
  qobject_cast<QSpinBox*>(m_widget)->setSuffix(text);
}

/*!
   \brief Convenience function to set the minimum, and maximum values with a
  single function call.

  \code
  sb->setRange(minimum, maximum);
  \endcode

  is equivalent to:

  \code
  sb->setMinimum(minimum);
  sb->setMaximum(maximum);
  \endcode

  \sa minimum() and maximum().
*/
void AbstractLabelledSpinBox::setRange(int min, int max)
{
  qobject_cast<QSpinBox*>(m_widget)->setRange(min, max);
}

int AbstractLabelledSpinBox::singleStep() const
{
  return qobject_cast<QSpinBox*>(m_widget)->singleStep();
}

void AbstractLabelledSpinBox::setSingleStep(int step)
{
  qobject_cast<QSpinBox*>(m_widget)->setSingleStep(step);
}

QAbstractSpinBox::StepType AbstractLabelledSpinBox::stepType() const
{
  return qobject_cast<QSpinBox*>(m_widget)->stepType();
}

void AbstractLabelledSpinBox::setStepType(QAbstractSpinBox::StepType type)
{
  qobject_cast<QSpinBox*>(m_widget)->setStepType(type);
}
