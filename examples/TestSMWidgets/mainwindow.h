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

//#include "sm_libraries/qyamlcpp.h"
#include "sm_libraries/labelledwidgets.h"

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget* parent = nullptr);
   ~MainWindow();

   void enableWidgets(bool enable);

private:
   QTabWidget* m_tabs;

   //   Qt::Alignment m_alignment;
   QGroupBox* m_labelVerticalBox, *m_labelHorizontalBox, *m_widgetVerticalBox, *m_widgetHorizontalBox;
   QButtonGroup* m_labelVerticalGrp, *m_labelHorizontalGrp, *m_widgetVerticalGrp, *m_widgetHorizontalGrp;

   LabelledComboBox* m_comboBox;
   LabelledSpinBox* m_spinBox;
   LabelledExSpinBox* m_exSpinBox;
   LabelledTextField* m_textField;
   LabelledLineEdit* m_lineEdit;

   LabelledComboBox* m_widgetChoiceBox;
   LabelledLineEdit* m_labelText, *m_widgetText;
   AbstractLabelledWidget* m_currentWidget;
   QPlainTextEdit* m_labelStylesheet, *m_widgetStylesheet, *m_overallStylesheet;
   QPushButton* m_setLabelStylesheet, *m_setWidgetStylesheet;
   LabelledComboBox* m_positionBox;
   LabelledComboBox* m_labelTextFormatBox, *m_widgetTextFormatBox;
   LabelledComboBox* m_labelHPoliciesBox, *m_labelVPoliciesBox;
   LabelledComboBox* m_widgetHPoliciesBox, *m_widgetVPoliciesBox;
   LabelledSpinBox* m_left, *m_right, *m_top, *m_bottom, *m_spacing;
   QStringList m_textFormats;
   LabelledLineEdit *m_textFormatDisplay;

   void setLabelStylesheet();
   void setWidgetStylesheet();
   void setStylesheet();

   void setLabelPosition(const QString& pos);
   void setLeft();
   void setRight();
   void setTop();
   void setBottom();
   void setSpacing();

   void lineEditChanged(const QString& text);
   void comboBoxChanged(const QString& text);
   void spinBoxChanged(int value);
   void exSpinBoxChanged(int value);
   void setCurrentWidgetAlignment();

   void chooseWidget(const QString& text);
   void labelTextHasChanged(const QString& text);
   void widgetTextHasChanged(const QString& text);
   void labelSizePolicyHasChanged(const QString&);
   void widgetSizePolicyHasChanged(const QString&);
   void labelTextFormatHasChanged(const QString&);
   void widgetTextFormatHasChanged(const QString&);

   void setAlignmentStatus();
   void setStylesheetStatus();
   void setLabelPositionStatus();
   void setLayoutStatus();
   void setSizePolicyStatus();
   void setTextFormatStatus();

   void initGui();
   QWidget* initLabelledWidgets();
   QWidget* initChooseWidgetBox();
   QWidget* initAlignmentBox();
   QWidget* initVAlignBox(const QString& type, QGroupBox* box, QButtonGroup* grp);
   QWidget* initHAlignBox(const QString& direction, QGroupBox* box, QButtonGroup* grp);
   QWidget* initStylesheetBox();
   QWidget* initPolicyBox();
   QWidget* initFormatBox();
   QString sizePolicyToString(QSizePolicy::Policy policy);
   void setFormattedText(Qt::TextFormat format);
};

#endif // MAINWINDOW_H
