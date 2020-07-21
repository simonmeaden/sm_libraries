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
#ifndef LABELLEDSPINBOX_H
#define LABELLEDSPINBOX_H

#include "abstractlabelledspinbox.h"
#include "sm_widgets_global.h"

/*!
   \file labelledspinbox.h labelledspinbox.cpp
   \class LabelledSpinBox labelledspinbox.h
   \brief The LabelledSpinBox is a wrapper for QLabel and QSpinBox that
          provides a labelled spin box.
   \since 5.7.0
   \license The MIT License
   \copyright © 2019 - 2020 Simon Meaden. All rights reserved.

   All properties of the QSpinBox  are copied across to this widget.
*/
class SM_WIDGETS_SHARED_EXPORT LabelledSpinBox : public AbstractLabelledSpinBox
{
   Q_OBJECT

protected:
  struct WidgetFactory : AbstractLabelledWidget::WidgetFactory
   {
      QWidget* newWidget(QWidget* parent) const {
         return new QSpinBox(parent);
      }
   };

public:
   explicit LabelledSpinBox(const QString& labelText = QString(),
                            QWidget* parent = nullptr,
                           WidgetFactory const& factory = WidgetFactory());

private:
   void initGui(const QString& text = QString());
};


#endif // LABELLEDSPINBOX_H
