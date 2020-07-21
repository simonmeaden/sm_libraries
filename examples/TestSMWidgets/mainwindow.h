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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

//#include "sm_widgets/qyamlcpp.h"
#include "sm_widgets/labelledwidgets.h"

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget* parent = nullptr);
   ~MainWindow();

private:
   QTabWidget* m_tabs;

   LabelledComboBox* m_comboBox;
   LabelledSpinBox* m_spinBox;
   LabelledExSpinBox* m_exSpinBox;
   LabelledTextField* m_textField;
   LabelledLineEdit* m_lineEdit;

   LabelledComboBox* m_widgetChoiceBox;
   LabelledLineEdit* m_labelText, *m_widgetText;
   AbstractLabelledWidget* m_currentWidget;

   void chooseWidget(const QString& text);
   void labelTextHasChanged(const QString& text);


   void initGui();
   QWidget* initLabelledWidgets();

};

#endif // MAINWINDOW_H
