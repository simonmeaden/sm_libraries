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
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
   QApplication a(argc, argv);
   MainWindow w;
   w.show();
   return a.exec();
}

MainWindow::MainWindow(QWidget* parent)
   : QMainWindow(parent)
{
   initGui();
}

MainWindow::~MainWindow()
{
}

void MainWindow::chooseWidget(const QString& text)
{
   if (text == tr("LineEdit")) {
      m_currentWidget = m_lineEdit;
      m_labelText->setLabelText(m_lineEdit->labelText());
      m_widgetText->setEnabled(true);
      m_widgetText->setText(m_lineEdit->text());

   } else if (text == tr("Text Field")) {
      m_currentWidget = m_textField;
      m_labelText->setLabelText(m_textField->labelText());
      m_widgetText->setEnabled(true);
      m_widgetText->setText(m_textField->text());

   } else if (text == tr("Combo Box")) {
      m_currentWidget = m_comboBox;
      m_labelText->setLabelText(m_comboBox->labelText());
      m_widgetText->setEnabled(true);
      m_widgetText->setText(m_comboBox->currentText());

   } else if (text == tr("Spin Box")) {
      m_currentWidget = m_spinBox;
      m_labelText->setLabelText(m_comboBox->labelText());
      m_widgetText->setEnabled(false);
      m_widgetText->setText(QString::number(m_spinBox->value()));

   } else if (text == tr("ExSpinBox")) {
      m_currentWidget = m_exSpinBox;
      m_labelText->setLabelText(m_exSpinBox->labelText());
      m_widgetText->setEnabled(false);
      m_widgetText->setText(QString::number(m_exSpinBox->value()));
   }
}

void MainWindow::labelTextHasChanged(const QString& text)
{
   m_currentWidget->setLabelText(text);
}

QWidget* MainWindow::initLabelledWidgets()
{
   QGroupBox* box = new QGroupBox(tr("Labelled Widgets :"), this);
   QVBoxLayout* l = new QVBoxLayout;
   box->setLayout(l);

   m_lineEdit = new LabelledLineEdit(tr("QLineEdit :"), this);
   m_currentWidget = m_lineEdit;
   l->addWidget(m_lineEdit);

   m_textField = new LabelledTextField(tr("QLabel :"), tr("A TextField."), this);
   l->addWidget(m_textField);

   QStringList choices;
   choices << tr("First") << tr("Second") << tr("Third") << tr("Fourth") << tr("Fifth");
   m_comboBox = new LabelledComboBox(tr("QComboBox :"), this);
   m_comboBox->addItems(choices);
   l->addWidget(m_comboBox);

   m_spinBox = new LabelledSpinBox(tr("QSpinBox :"), this);
   l->addWidget(m_spinBox);

   m_exSpinBox = new LabelledExSpinBox(tr("ExSpinBox :"), this);
   l->addWidget(m_exSpinBox);

   return box;
}

void MainWindow::initGui()
{
   m_tabs = new QTabWidget(this);
   setCentralWidget(m_tabs);

   QWidget* f = new QFrame(this);
   QGridLayout* l = new QGridLayout;
   f->setLayout(l);

   m_tabs->addTab(f, tr("Labelled Widgets"));

   int row = 0;
   l->addWidget(initLabelledWidgets(), row, 0);

   row++;

   QStringList choices;
   choices << tr("LineEdit") << tr("Text Field") << tr("Combo Box") << tr("Spin Box") << tr("ExSpinBox");
   m_widgetChoiceBox = new LabelledComboBox(tr("Choose Widget to modify :"), this);
   m_widgetChoiceBox->addItems(choices);
   connect(m_widgetChoiceBox, &LabelledComboBox::currentTextChanged, this, &MainWindow::chooseWidget);
   l->addWidget(m_widgetChoiceBox, row, 0);

   row++;

   // initially defaults to LabelledLineEdit
   m_labelText = new LabelledLineEdit(tr("Edit label text :"), m_lineEdit->labelText(), this);
   connect(m_labelText, &LabelledLineEdit::textChanged, this, &MainWindow::labelTextHasChanged);
   l->addWidget(m_labelText, row, 0);
   row++;

   m_widgetText = new LabelledLineEdit(tr("Edit widget text :"), m_lineEdit->text(), this);
   connect(m_widgetText, &LabelledLineEdit::textChanged, this, &MainWindow::labelTextHasChanged);
   l->addWidget(m_widgetText, row, 0);

   row++;
}

