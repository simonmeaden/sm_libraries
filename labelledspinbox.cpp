/*
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
#include "labelledspinbox.h"

/*!
   \brief Constructs a labelled spin box with a babel of text and 0 as minimum
   value and 99 as maximum value, a step value of 1.
   The value is initially set to 0. It is parented to parent.
*/
LabelledSpinBox::LabelledSpinBox(const QString& text, QWidget* parent)
  : AbstractLabelledSpinBox(text, parent)
{
  initGui();
}

void LabelledSpinBox::initGui(const QString& /*text*/)
{
  m_widget = new QSpinBox(this);
  m_layout->addWidget(m_widget, 0, 1);
  connect(qobject_cast<QSpinBox*>(m_widget),
          qOverload<int>(&QSpinBox::valueChanged),
          this,
          &AbstractLabelledSpinBox::valueChanged);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
  connect(reinterpret_cast<QSpinBox*>(m_widget),
          qOverload<const QString&>(&QSpinBox::textChanged),
          this,
          &AbstractLabelledSpinBox::textChanged);
#else
  connect(reinterpret_cast<QSpinBox*>(m_widget),
          qOverload<const QString&>(&QSpinBox::valueChanged),
          this,
          &AbstractLabelledSpinBox::textChanged);
#endif
}
