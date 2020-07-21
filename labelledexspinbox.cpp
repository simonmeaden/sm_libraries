/**
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
#include "labelledexspinbox.h"

/*!
   \file labelledexspinbox.h labelledexspinbox.cpp
   \class LabelledExSpinBox labelledexspinbox.h
   \brief The LabelledExSpinBox is a wrapper for QLabel and QSpinBox that
          provides a labelled extended spin box.

   Extends AbstractLabelledSpinBox to supply a spin box with hexadecimal, octal and
   binary display of interger values.

*/

LabelledExSpinBox::LabelledExSpinBox(const QString& text, QWidget* parent)
  : AbstractLabelledSpinBox(text, parent)
{
  initGui();
}

/*!
   \brief Gets the number of digits allowed in the text string. By default 2.

  \return the number of digits.
*/
quint8 LabelledExSpinBox::numberOfDigits() const
{
  return reinterpret_cast<ExSpinBox*>(m_widget)->displayDigits();
}

ExSpinBox::DisplayType LabelledExSpinBox::displayType() const
{
  return reinterpret_cast<ExSpinBox*>(m_widget)->displayType();
}

void LabelledExSpinBox::setDisplayType(ExSpinBox::DisplayType type)
{
  reinterpret_cast<ExSpinBox*>(m_widget)->setDisplayType(type);
}

bool LabelledExSpinBox::showLeadingZeroes() const
{
  return reinterpret_cast<ExSpinBox*>(m_widget)->showLeadingZeroes();
}

void LabelledExSpinBox::setShowLeadingZeroes(bool showLeadingZeroes)
{
  reinterpret_cast<ExSpinBox*>(m_widget)->setShowLeadingZeroes(
    showLeadingZeroes);
}

void LabelledExSpinBox::initGui()
{
  m_widget = new ExSpinBox(this);
  m_layout->addWidget(m_widget, 0, 1);
  connect(reinterpret_cast<ExSpinBox*>(m_widget),
          qOverload<int>(&QSpinBox::valueChanged),
          this,
          &LabelledExSpinBox::valueChanged);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
  connect(reinterpret_cast<ExSpinBox*>(m_widget),
          qOverload<const QString&>(&QSpinBox::textChanged),
          this,
          &LabelledExSpinBox::textChanged);
#else
  connect(reinterpret_cast<ExSpinBox*>(m_widget),
          qOverload<const QString&>(&QSpinBox::valueChanged),
          this,
          &LabelledExSpinBox::textChanged);
#endif
  connect(reinterpret_cast<ExSpinBox*>(m_widget),
          &ExSpinBox::displayTypeChanged,
          this,
          &LabelledExSpinBox::displayTypeChanged);
  connect(reinterpret_cast<ExSpinBox*>(m_widget),
          &ExSpinBox::displayDigitsChanged,
          this,
          &LabelledExSpinBox::displayDigitsChanged);
}

