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
#include "mainwindow.h"

#include <QApplication>
#include <Qt>

int main(int argc, char* argv[])
{
   qRegisterMetaType<Qt::Alignment>("Qt::Alignment");

   QApplication a(argc, argv);
   MainWindow w;
   w.show();
   return a.exec();
}

MainWindow::MainWindow(QWidget* parent)
   : QMainWindow(parent)
   , m_currentWidget(nullptr)
{
   initGui();
}

MainWindow::~MainWindow() {}

void MainWindow::chooseWidget(const QString& text)
{
   if (text == tr("LineEdit")) {
      if (m_currentWidget != m_lineEdit) {
         m_currentWidget = m_lineEdit;
         m_labelText->setText(m_lineEdit->labelText());
         m_widgetText->setText(m_lineEdit->text());
      }

   } else if (text == tr("Text Field")) {
      if (m_currentWidget != m_textField) {
         m_currentWidget = m_textField;
         m_labelText->setText(m_textField->labelText());
         m_widgetText->setText(m_textField->text());
      }

   } else if (text == tr("Combo Box")) {
      if (m_currentWidget != m_comboBox) {
         m_currentWidget = m_comboBox;
         m_labelText->setText(m_comboBox->labelText());
         m_widgetText->setText(m_comboBox->currentText());
      }

   } else if (text == tr("Spin Box")) {
      if (m_currentWidget != m_spinBox) {
         m_currentWidget = m_spinBox;
         m_labelText->setText(m_spinBox->labelText());
         m_widgetText->setText(QString::number(m_spinBox->value()));
      }

   } else if (text == tr("ExSpinBox")) {
      if (m_currentWidget != m_exSpinBox) {
         m_currentWidget = m_exSpinBox;
         m_labelText->setText(m_exSpinBox->labelText());
         m_widgetText->setText(QString::number(m_exSpinBox->value()));
      }

   } else if (text == tr("None")) {
      m_currentWidget = nullptr;
      m_labelText->setText(tr("No Widget Selected!"));
      m_widgetText->setText("");
   }

   setAlignmentStatus();
   setStylesheetStatus();
   setLabelPositionStatus();
   setLayoutStatus();
   enableWidgets(true);
}

void MainWindow::labelTextHasChanged(const QString& text)
{
   if (m_currentWidget) {
      m_currentWidget->setLabelText(text);
   }
}

void MainWindow::widgetTextHasChanged(const QString& text)
{
   if (m_currentWidget == m_lineEdit) {
      qobject_cast<LabelledLineEdit*>(m_currentWidget)->setText(text);

   } else if (m_currentWidget == m_textField) {
      qobject_cast<LabelledTextField*>(m_currentWidget)->setText(text);

   } else if (m_currentWidget == m_comboBox) {
      qobject_cast<LabelledComboBox*>(m_currentWidget)->setCurrentText(text);

   } else if (m_currentWidget == m_spinBox) {
      qobject_cast<LabelledSpinBox*>(m_currentWidget)->setValue(text.toInt());

   } else if (m_currentWidget == m_exSpinBox) {
      qobject_cast<LabelledExSpinBox*>(m_currentWidget)->setValue(text.toInt());
   }
}

void MainWindow::setAlignmentStatus()
{
   if (!m_currentWidget) {
      m_labelVerticalBox->setEnabled(false);
      m_labelHorizontalBox->setEnabled(false);
      m_widgetVerticalBox->setEnabled(false);
      m_widgetHorizontalBox->setEnabled(false);
      return;
   }

   m_labelVerticalBox->setEnabled(true);
   m_labelHorizontalBox->setEnabled(true);
   Qt::Alignment labelAlighnment = m_currentWidget->labelAlignment();

   if (labelAlighnment.testFlag(Qt::AlignLeft)) {
      m_labelHorizontalGrp->buttons().at(0)->setChecked(true);

   }

   if (labelAlighnment.testFlag(Qt::AlignRight)) {
      m_labelHorizontalGrp->buttons().at(1)->setChecked(true);

   }

   if (labelAlighnment.testFlag(Qt::AlignHCenter)) {
      m_labelHorizontalGrp->buttons().at(2)->setChecked(true);

   }

   if (labelAlighnment.testFlag(Qt::AlignJustify)) {
      m_labelHorizontalGrp->buttons().at(3)->setChecked(true);

   }

   if (labelAlighnment.testFlag(Qt::AlignTop)) {
      m_labelVerticalGrp->buttons().at(0)->setChecked(true);

   }

   if (labelAlighnment.testFlag(Qt::AlignBottom)) {
      m_labelVerticalGrp->buttons().at(1)->setChecked(true);

   }

   if (labelAlighnment.testFlag(Qt::AlignVCenter)) {
      m_labelVerticalGrp->buttons().at(2)->setChecked(true);

   }

   if (labelAlighnment.testFlag(Qt::AlignBaseline)) {
      m_labelVerticalGrp->buttons().at(3)->setChecked(true);
   }

   Qt::Alignment widgetAlignment;
   AbstractAlignableLabelledWidget* alw =
      dynamic_cast<AbstractAlignableLabelledWidget*>(m_currentWidget);

   if (alw) {
      m_widgetVerticalBox->setEnabled(true);
      m_widgetHorizontalBox->setEnabled(true);
      widgetAlignment = alw->widgetAlignment();

      if (widgetAlignment.testFlag(Qt::AlignLeft)) {
         m_widgetHorizontalGrp->buttons().at(0)->setChecked(true);

      }

      if (widgetAlignment.testFlag(Qt::AlignRight)) {
         m_widgetHorizontalGrp->buttons().at(1)->setChecked(true);

      }

      if (widgetAlignment.testFlag(Qt::AlignHCenter)) {
         m_widgetHorizontalGrp->buttons().at(2)->setChecked(true);

      }

      if (widgetAlignment.testFlag(Qt::AlignJustify)) {
         m_widgetHorizontalGrp->buttons().at(3)->setChecked(true);

      }

      if (widgetAlignment.testFlag(Qt::AlignTop)) {
         m_widgetVerticalGrp->buttons().at(0)->setChecked(true);

      }

      if (widgetAlignment.testFlag(Qt::AlignBottom)) {
         m_widgetVerticalGrp->buttons().at(1)->setChecked(true);

      }

      if (widgetAlignment.testFlag(Qt::AlignVCenter)) {
         m_widgetVerticalGrp->buttons().at(2)->setChecked(true);

      }

      if (widgetAlignment.testFlag(Qt::AlignBaseline)) {
         m_widgetVerticalGrp->buttons().at(3)->setChecked(true);
      }

   } else {
      m_widgetVerticalBox->setEnabled(false);
      m_widgetHorizontalBox->setEnabled(false);
   }
}

void MainWindow::setStylesheetStatus()
{
   if (!m_currentWidget) {
      return;
   }

   QString labelStylesheet = m_currentWidget->labelStyleSheet();
   m_labelStylesheet->setStyleSheet(labelStylesheet);

   QString widgetStylesheet = m_currentWidget->widgetStyleSheet();
   m_widgetStylesheet->setStyleSheet(widgetStylesheet);

   QString overallStylesheet = m_currentWidget->styleSheet();
   m_overallStylesheet->setStyleSheet(overallStylesheet);
}

void MainWindow::setLabelPositionStatus()
{
   if (!m_currentWidget) {
      return;
   }

   AbstractLabelledWidget::LabelPosition pos = m_currentWidget->labelPosition();

   switch (pos) {
   case AbstractLabelledWidget::Left:
      m_positionBox->setCurrentText(tr("Left"));
      break;

   case AbstractLabelledWidget::Right:
      m_positionBox->setCurrentText(tr("Right"));
      break;

   case AbstractLabelledWidget::Above:
      m_positionBox->setCurrentText(tr("Above"));
      break;

   case AbstractLabelledWidget::Below:
      m_positionBox->setCurrentText(tr("Below"));
      break;

   }
}

void MainWindow::enableWidgets(bool enable)
{
   if (m_currentWidget) {
      if (m_currentWidget == m_lineEdit || m_currentWidget == m_textField ||
            m_currentWidget == m_comboBox) {
         m_widgetText->setEnabled(enable);
         m_widgetText->setValidator(0);

      } else if (m_currentWidget == m_spinBox || m_currentWidget == m_exSpinBox) {
         m_widgetText->setEnabled(enable);
         m_widgetText->setValidator(new QIntValidator(this));
      }

      m_labelText->setEnabled(true);

   } else {
      m_labelText->setEnabled(false);
      m_widgetText->setEnabled(false);
   }
}

void MainWindow::setLabelStylesheet()
{
   if (!m_currentWidget) {
      return;
   }

   QString stylesheet = m_labelStylesheet->toPlainText();
   m_currentWidget->setLabelStyleSheet(stylesheet);
}

void MainWindow::setWidgetStylesheet()
{
  if (!m_currentWidget) {
    return;
  }

  QString stylesheet = m_widgetStylesheet->toPlainText();
  m_currentWidget->setWidgetStyleSheet(stylesheet);
}

void MainWindow::setStylesheet()
{
  QString stylesheet = m_overallStylesheet->toPlainText();
  m_currentWidget->setStyleSheet(stylesheet);
}

void MainWindow::setLabelPosition(const QString& pos)
{
   if (!m_currentWidget) {
      return;
   }

   if (pos == tr("Left")) {
      m_currentWidget->setLabelPosition(AbstractLabelledWidget::Left);

   } else if (pos == tr("Right")) {
      m_currentWidget->setLabelPosition(AbstractLabelledWidget::Right);

   } else if (pos == tr("Above")) {
      m_currentWidget->setLabelPosition(AbstractLabelledWidget::Above);

   } else if (pos == tr("Below")) {
      m_currentWidget->setLabelPosition(AbstractLabelledWidget::Below);
   }
}

void MainWindow::setLeft()
{
   if (!m_currentWidget) {
      return;
   }

   QMargins margins = m_currentWidget->contentsMargins();
   margins.setLeft(m_left->value());
   m_currentWidget->setContentsMargins(margins);
}

void MainWindow::setRight()
{
   if (!m_currentWidget) {
      return;
   }

   QMargins margins = m_currentWidget->contentsMargins();
   margins.setRight(m_right->value());
   m_currentWidget->setContentsMargins(margins);
}

void MainWindow::setTop()
{
   if (!m_currentWidget) {
      return;
   }

   QMargins margins = m_currentWidget->contentsMargins();
   margins.setTop(m_top->value());
   m_currentWidget->setContentsMargins(margins);
}

void MainWindow::setBottom()
{
   if (!m_currentWidget) {
      return;
   }

   QMargins margins = m_currentWidget->contentsMargins();
   margins.setBottom(m_bottom->value());
   m_currentWidget->setContentsMargins(margins);
}

void MainWindow::setSpacing()
{
   if (!m_currentWidget) {
      return;
   }

   m_currentWidget->setSpacing(m_spacing->value());
}

void MainWindow::setLayoutStatus()
{
   if (!m_currentWidget) {
      return;
   }

   QMargins margins = m_currentWidget->contentsMargins();
   m_left->setValue(margins.left());
   m_right->setValue(margins.right());
   m_top->setValue(margins.top());
   m_bottom->setValue(margins.bottom());

   m_spacing->setValue(m_currentWidget->spacing());
}

void MainWindow::lineEditChanged(const QString& text)
{
   if (m_currentWidget == m_lineEdit) {
      m_widgetText->setText(text);
   }
}

void MainWindow::comboBoxChanged(const QString& text)
{
   if (m_currentWidget == m_comboBox) {
      m_widgetText->setText(text);
   }
}

void MainWindow::spinBoxChanged(int value)
{
   if (m_currentWidget == m_spinBox) {
      m_widgetText->setText(QString::number(value));
   }
}

void MainWindow::exSpinBoxChanged(int value)
{
   if (m_currentWidget == m_exSpinBox) {
      m_widgetText->setText(QString::number(value));
   }
}

void MainWindow::setAlign()
{
   if (!m_currentWidget) {
      return;
   }

   QRadioButton* btn = qobject_cast<QRadioButton*>(sender());
   // alignment flag from button
   Qt::Alignment alignment = static_cast<Qt::Alignment>(btn->property("alignment").value<Qt::Alignment::Int>());
   // alignment flag from widget - loaded later.
   Qt::Alignment existing;
   QString type = btn->property("widget").toString();

   AbstractAlignableLabelledWidget* alw =
      dynamic_cast<AbstractAlignableLabelledWidget*>(m_currentWidget);

   switch (alignment) {
   case Qt::AlignLeft:
   case Qt::AlignRight:
   case Qt::AlignHCenter:
   case Qt::AlignJustify:
      if (alw && type == "Widget") {
         existing = alw->widgetAlignment();
         existing &= Qt::AlignVertical_Mask;
         existing |= alignment;
         alw->setWidgetAlignment(existing);

      } else if (type == "Label") {
         existing = m_currentWidget->labelAlignment();
         existing &= Qt::AlignVertical_Mask;
         existing |= alignment;
         m_currentWidget->setLabelAlignment(existing);
      }

      //      m_alignment = existing;
      break;

   case Qt::AlignTop:
   case Qt::AlignBottom:
   case Qt::AlignVCenter:
   case Qt::AlignBaseline:
      if (alw && type == "Widget") {
         existing = alw->widgetAlignment();
         existing &= Qt::AlignHorizontal_Mask;
         existing |= alignment;
         alw->setWidgetAlignment(existing);

      } else if (type == "Label") {
         existing = m_currentWidget->labelAlignment();
         existing &= Qt::AlignHorizontal_Mask;
         existing |= alignment;
         m_currentWidget->setLabelAlignment(existing);
      }

      //      m_alignment = existing;
      break;
   }
}

QWidget* MainWindow::initLabelledWidgets()
{
   QGroupBox* box = new QGroupBox(tr("Labelled Widgets :"), this);
   QVBoxLayout* l = new QVBoxLayout;
   box->setLayout(l);

   m_lineEdit = new LabelledLineEdit(tr("QLineEdit :"), this);
   //   connect(m_lineEdit, &LabelledLineEdit::textChanged,
   //           this, &MainWindow::lineEditChanged);
   connect(m_lineEdit,
           &LabelledLineEdit::textEdited,
           this,
           &MainWindow::lineEditChanged);
   l->addWidget(m_lineEdit);

   m_textField = new LabelledTextField(tr("QLabel :"), tr("A TextField."), this);
   l->addWidget(m_textField);

   QStringList choices;
   choices << tr("First") << tr("Second") << tr("Third") << tr("Fourth")
           << tr("Fifth");
   m_comboBox = new LabelledComboBox(tr("QComboBox :"), this);
   connect(m_comboBox,
           &LabelledComboBox::currentTextChanged,
           this,
           &MainWindow::comboBoxChanged);
   m_comboBox->addItems(choices);
   l->addWidget(m_comboBox);

   m_spinBox = new LabelledSpinBox(tr("QSpinBox :"), this);
   connect(m_spinBox,
           &LabelledSpinBox::valueChanged,
           this,
           &MainWindow::spinBoxChanged);
   l->addWidget(m_spinBox);

   m_exSpinBox = new LabelledExSpinBox(tr("ExSpinBox :"), this);
   connect(m_exSpinBox,
           &LabelledExSpinBox::valueChanged,
           this,
           &MainWindow::exSpinBoxChanged);
   l->addWidget(m_exSpinBox);

   return box;
}

QWidget* MainWindow::initChooseWidgetBox()
{
   QGroupBox* box = new QGroupBox(this);
   QVBoxLayout* l = new QVBoxLayout;
   box->setLayout(l);

   QStringList choices;
   choices << tr("None") << tr("LineEdit") << tr("Text Field") << tr("Combo Box")
           << tr("Spin Box") << tr("ExSpinBox");
   m_widgetChoiceBox =
      new LabelledComboBox(tr("Choose Widget to modify :"), this);
   m_widgetChoiceBox->addItems(choices);
   connect(m_widgetChoiceBox,
           &LabelledComboBox::currentTextChanged,
           this,
           &MainWindow::chooseWidget);
   l->addWidget(m_widgetChoiceBox);

   // initially defaults to LabelledLineEdit
   m_labelText = new LabelledLineEdit(
      tr("Edit label text :"), m_lineEdit->labelText(), this);
   m_labelText->setEnabled(false);
   connect(m_labelText,
           &LabelledLineEdit::textChanged,
           this,
           &MainWindow::labelTextHasChanged);
   l->addWidget(m_labelText);

   m_widgetText =
      new LabelledLineEdit(tr("Edit widget text :"), m_lineEdit->text(), this);
   m_widgetText->setEnabled(false);
   connect(m_widgetText,
           &LabelledLineEdit::textChanged,
           this,
           &MainWindow::widgetTextHasChanged);
   l->addWidget(m_widgetText);

   QStringList positions;
   positions << tr("Left") << tr("Right") << tr("Above") << tr("Below");
   m_positionBox = new LabelledComboBox(tr("Label Position :"), this);
   m_positionBox->addItems(positions);
   connect(m_positionBox, &LabelledComboBox::currentTextChanged, this, &MainWindow::setLabelPosition);
   l->addWidget(m_positionBox);

   QFrame* layoutFrame = new QFrame(this);
   QGridLayout* layoutLayout = new QGridLayout;
   layoutFrame->setLayout(layoutLayout);

   m_left = new LabelledSpinBox(tr("Left"), this);
   connect(m_left, &LabelledSpinBox::valueChanged, this, &MainWindow::setLeft);
   layoutLayout->addWidget(m_left, 0, 1);
   m_right = new LabelledSpinBox(tr("Right"), this);
   connect(m_right, &LabelledSpinBox::valueChanged, this, &MainWindow::setRight);
   layoutLayout->addWidget(m_right, 1, 0);
   m_top = new LabelledSpinBox(tr("Top"), this);
   connect(m_top, &LabelledSpinBox::valueChanged, this, &MainWindow::setTop);
   layoutLayout->addWidget(m_top, 2, 1);
   m_bottom = new LabelledSpinBox(tr("Bottom"), this);
   connect(m_bottom, &LabelledSpinBox::valueChanged, this, &MainWindow::setBottom);
   layoutLayout->addWidget(m_bottom, 1, 2);
   m_spacing = new LabelledSpinBox(tr("Spacing"), this);
   connect(m_spacing, &LabelledSpinBox::valueChanged, this, &MainWindow::setSpacing);
   layoutLayout->addWidget(m_spacing, 1, 1);

   l->addWidget(layoutFrame);

   return box;
}

QWidget* MainWindow::initAlignmentBox()
{
   QGroupBox* box = new QGroupBox(tr("Alignment"), this);
   QGridLayout* l = new QGridLayout;
   box->setLayout(l);

   int row = 0;

   m_labelVerticalBox = new QGroupBox(tr("Vertical Label"), this);
   m_labelHorizontalBox = new QGroupBox(tr("Horizontal Label"), this);
   m_widgetVerticalBox = new QGroupBox(tr("Vertical Widget"), this);
   m_widgetHorizontalBox = new QGroupBox(tr("Horizontal Widget"), this);
   m_labelVerticalGrp = new QButtonGroup(this);
   m_labelHorizontalGrp = new QButtonGroup(this);
   m_widgetVerticalGrp = new QButtonGroup(this);
   m_widgetHorizontalGrp = new QButtonGroup(this);

   l->addWidget(
      initHAlignBox("Label", m_labelHorizontalBox, m_labelHorizontalGrp), 0, 0);
   l->addWidget(
      initVAlignBox("Label", m_labelVerticalBox, m_labelVerticalGrp), 0, 1);
   l->addWidget(
      initHAlignBox("Widget", m_widgetHorizontalBox, m_widgetHorizontalGrp), 1, 0);
   l->addWidget(
      initVAlignBox("Widget", m_widgetVerticalBox, m_widgetVerticalGrp), 1, 1);

   return box;
}

QWidget* MainWindow::initVAlignBox(const QString& type,
                                   QGroupBox* box,
                                   QButtonGroup* grp)
{
   QVBoxLayout* l = new QVBoxLayout;
   box->setLayout(l);

   QRadioButton* topBtn = new QRadioButton(tr("Top"), this);
   grp->addButton(topBtn);
   topBtn->setProperty("alignment", static_cast<Qt::Alignment::Int>(Qt::AlignTop));
   topBtn->setProperty("widget", type);
   l->addWidget(topBtn);
   QRadioButton* bottomBtn = new QRadioButton(tr("Bottom"), this);
   grp->addButton(bottomBtn);
   bottomBtn->setProperty("alignment", static_cast<Qt::Alignment::Int>(Qt::AlignBottom));
   bottomBtn->setProperty("widget", type);
   l->addWidget(bottomBtn);
   QRadioButton* centreBtn = new QRadioButton(tr("Vertical Centre"), this);
   grp->addButton(centreBtn);
   centreBtn->setProperty("alignment", static_cast<Qt::Alignment::Int>(Qt::AlignVCenter));
   centreBtn->setProperty("widget", type);
   l->addWidget(centreBtn);
   QRadioButton* baselineBtn = new QRadioButton(tr("Baseline"), this);
   grp->addButton(baselineBtn);
   baselineBtn->setProperty("alignment", static_cast<Qt::Alignment::Int>(Qt::AlignBaseline));
   baselineBtn->setProperty("widget", type);
   l->addWidget(baselineBtn);

   connect(topBtn, &QRadioButton::clicked, this, &MainWindow::setAlign);
   connect(bottomBtn, &QRadioButton::clicked, this, &MainWindow::setAlign);
   connect(centreBtn, &QRadioButton::clicked, this, &MainWindow::setAlign);
   connect(baselineBtn, &QRadioButton::clicked, this, &MainWindow::setAlign);

   return box;
}

QWidget* MainWindow::initHAlignBox(const QString& type,
                                   QGroupBox* box,
                                   QButtonGroup* grp)
{
   QVBoxLayout* l = new QVBoxLayout;
   box->setLayout(l);

   QRadioButton* leftBtn = new QRadioButton(tr("Left"), this);
   grp->addButton(leftBtn);
   leftBtn->setProperty("alignment", static_cast<Qt::Alignment::Int>(Qt::AlignLeft));
   leftBtn->setProperty("widget", type);
   l->addWidget(leftBtn);
   QRadioButton* rightBtn = new QRadioButton(tr("Right"), this);
   grp->addButton(rightBtn);
   rightBtn->setProperty("alignment", static_cast<Qt::Alignment::Int>(Qt::AlignRight));
   rightBtn->setProperty("widget", type);
   l->addWidget(rightBtn);
   QRadioButton* centreBtn = new QRadioButton(tr("Horizontal Centre"), this);
   grp->addButton(centreBtn);
   centreBtn->setProperty("alignment", static_cast<Qt::Alignment::Int>(Qt::AlignHCenter));
   centreBtn->setProperty("widget", type);
   l->addWidget(centreBtn);
   QRadioButton* justifyBtn = new QRadioButton(tr("Justify"), this);
   grp->addButton(justifyBtn);
   justifyBtn->setProperty("alignment", static_cast<Qt::Alignment::Int>(Qt::AlignJustify));
   justifyBtn->setProperty("widget", type);
   l->addWidget(justifyBtn);

   connect(leftBtn, &QRadioButton::clicked, this, &MainWindow::setAlign);
   connect(rightBtn, &QRadioButton::clicked, this, &MainWindow::setAlign);
   connect(centreBtn, &QRadioButton::clicked, this, &MainWindow::setAlign);
   connect(justifyBtn, &QRadioButton::clicked, this, &MainWindow::setAlign);

   return box;
}

QWidget* MainWindow::initStylesheetBox()
{
   QGroupBox* box = new QGroupBox(tr("Stylesheets :"), this);
   QVBoxLayout* l = new QVBoxLayout;
   box->setLayout(l);

   QGroupBox* labelBox = new QGroupBox(tr("Label"), this);
   QGridLayout* labelLayout = new QGridLayout;
   labelBox->setLayout(labelLayout);
   m_labelStylesheet = new QPlainTextEdit(this);
   labelLayout->addWidget(m_labelStylesheet, 0, 0);
   QPushButton* labelBtn  = new QPushButton(tr("Set"), this);
   labelBox->setAlignment(Qt::AlignCenter);
   connect(labelBtn, &QPushButton::clicked, this, &MainWindow::setLabelStylesheet);
   labelLayout->addWidget(labelBtn, 1, 0);
   l->addWidget(labelBox);

   QGroupBox* widgetBox = new QGroupBox(tr("Widget"), this);
   QGridLayout* widgetLayout = new QGridLayout;
   widgetBox->setLayout(widgetLayout);
   m_widgetStylesheet = new QPlainTextEdit(this);
   widgetLayout->addWidget(m_widgetStylesheet, 0, 0);
   QPushButton* widgetBtn  = new QPushButton(tr("Set"), this);
   widgetBox->setAlignment(Qt::AlignCenter);
   connect(widgetBtn, &QPushButton::clicked, this, &MainWindow::setWidgetStylesheet);
   widgetLayout->addWidget(widgetBtn, 1, 0);
   l->addWidget(widgetBox);

   QGroupBox* overallBox = new QGroupBox(tr("Entire Widget"), this);
   QGridLayout* overallLayout = new QGridLayout;
   overallBox->setLayout(overallLayout);
   m_overallStylesheet = new QPlainTextEdit(this);
   overallLayout->addWidget(m_overallStylesheet, 0, 0);
   QPushButton* overallBtn  = new QPushButton(tr("Set"), this);
   overallBox->setAlignment(Qt::AlignCenter);
   connect(overallBtn, &QPushButton::clicked, this, &MainWindow::setStylesheet);
   overallLayout->addWidget(widgetBtn, 1, 0);
   l->addWidget(widgetBox);

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

   l->addWidget(initLabelledWidgets(), 0, 0);
   l->addWidget(initChooseWidgetBox(), 0, 1);
   l->addWidget(initStylesheetBox(), 1, 0);
   l->addWidget(initAlignmentBox(), 1, 1);

   chooseWidget(tr("None"));
   enableWidgets(false);
   setAlignmentStatus();
}
