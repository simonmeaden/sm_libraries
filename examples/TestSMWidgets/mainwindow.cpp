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

   m_tabs->setCurrentIndex(1);
}

MainWindow::~MainWindow() {}

void MainWindow::chooseWidget(const QString& text)
{

   if (text == tr("LineEdit")) {
      if (m_currentWidget != m_lineEdit) {
         m_currentWidget = m_lineEdit;
         m_labelText->setText(m_lineEdit->labelText());
         m_widgetText->setText(m_lineEdit->text());
         m_spinStack->setEnabled(false);
         m_exBox->setEnabled(false);
         m_exNegBeforePrefixBox->setEnabled(false);
         m_exPrefixEdit->setEnabled(false);
         m_setSpinBtn->setEnabled(false);
      }

   } else if (text == tr("Text Field")) {
      if (m_currentWidget != m_textField) {
         m_currentWidget = m_textField;
         m_labelText->setText(m_textField->labelText());
         m_widgetText->setText(m_textField->text());
         m_spinStack->setEnabled(false);
         m_exBox->setEnabled(false);
         m_exNegBeforePrefixBox->setEnabled(false);
         m_exPrefixEdit->setEnabled(false);
         m_setSpinBtn->setEnabled(false);
      }

   } else if (text == tr("Combo Box")) {
      if (m_currentWidget != m_comboBox) {
         m_currentWidget = m_comboBox;
         m_labelText->setText(m_comboBox->labelText());
         m_widgetText->setText(m_comboBox->currentText());
         m_spinStack->setEnabled(false);
         m_exBox->setEnabled(false);
         m_exNegBeforePrefixBox->setEnabled(false);
         m_exPrefixEdit->setEnabled(false);
         m_setSpinBtn->setEnabled(false);
      }

   } else if (text == tr("Spin Box")) {
      if (m_currentWidget != m_spinBox) {
         m_currentWidget = m_spinBox;
         m_labelText->setText(m_spinBox->labelText());
         m_widgetText->setText(QString::number(m_spinBox->value()));
         m_spinStack->setEnabled(true);
         m_spinStack->setCurrentIndex(m_spinIntStack);
         m_exBox->setEnabled(false);
         m_exNegBeforePrefixBox->setEnabled(false);
         m_exPrefixEdit->setEnabled(false);
         m_setSpinBtn->setEnabled(true);
      }

   } else if (text == tr("Double Spin Box")) {
      if (m_currentWidget != m_doubleSpinBox) {
         m_currentWidget = m_doubleSpinBox;
         m_labelText->setText(m_doubleSpinBox->labelText());
         m_widgetText->setText(QString::number(m_doubleSpinBox->value(), 'f', m_doubleSpinBox->decimals()));
         m_spinStack->setEnabled(true);
         m_spinStack->setCurrentIndex(m_spinDblStack);
         m_exBox->setEnabled(false);
         m_exNegBeforePrefixBox->setEnabled(false);
         m_exPrefixEdit->setEnabled(false);
         m_setSpinBtn->setEnabled(true);
      }

   } else if (text == tr("ExSpinBox")) {
      if (m_currentWidget != m_exSpinBox) {
         m_currentWidget = m_exSpinBox;
         m_labelText->setText(m_exSpinBox->labelText());
         m_widgetText->setText(QString::number(m_exSpinBox->value()));
         m_spinStack->setEnabled(true);
         m_spinStack->setCurrentIndex(m_spinIntStack);
         m_exBox->setEnabled(true);
         m_exNegBeforePrefixBox->setEnabled(true);
         m_exPrefixEdit->setEnabled(true);
         m_setSpinBtn->setEnabled(true);
      }

   } else if (text == tr("None")) {
      m_currentWidget = nullptr;
      m_labelText->setText(tr("No Widget Selected!"));
      m_widgetText->setText("");
      m_spinStack->setEnabled(false);
      m_exBox->setEnabled(false);
      m_exNegBeforePrefixBox->setEnabled(false);
      m_exPrefixEdit->setEnabled(false);
      m_setSpinBtn->setEnabled(false);
   }

   setAlignmentStatus();
   setStylesheetStatus();
   setLabelPositionStatus();
   setLayoutStatus();
   setSpinBoxStatus();
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

   } else if (m_currentWidget == m_doubleSpinBox) {
      qobject_cast<LabelledDoubleSpinBox*>(m_currentWidget)->setValue(text.toDouble());

   } else if (m_currentWidget == m_exSpinBox) {
      qobject_cast<LabelledExSpinBox*>(m_currentWidget)->setValue(text.toInt());
   }
}

void MainWindow::labelSizePolicyHasChanged(const QString&)
{
   if (!m_currentWidget) {
      return;
   }

   QSizePolicy::Policy hPolicy = m_labelHPoliciesBox->currentData(Qt::UserRole).value<QSizePolicy::Policy>();
   QSizePolicy::Policy vPolicy = m_labelVPoliciesBox->currentData(Qt::UserRole).value<QSizePolicy::Policy>();
   m_currentWidget->setLabelSizePolicy(hPolicy, vPolicy);
}

void MainWindow::widgetSizePolicyHasChanged(const QString&)
{
   if (!m_currentWidget) {
      return;
   }

   QSizePolicy::Policy hPolicy = m_widgetHPoliciesBox->currentData(Qt::UserRole).value<QSizePolicy::Policy>();
   QSizePolicy::Policy vPolicy = m_widgetVPoliciesBox->currentData(Qt::UserRole).value<QSizePolicy::Policy>();
   m_currentWidget->setWidgetSizePolicy(hPolicy, vPolicy);
}

void MainWindow::spinWidgetChanged()
{
   if (!m_currentWidget) {
      return;
   }

   if (m_currentWidget == m_spinBox) {
      m_spinBox->setMinimum(m_minIntSpin->value());
      m_spinBox->setMaximum(m_maxIntSpin->value());
      m_spinBox->setSingleStep(m_stepIntSpin->value());

   } else if (m_currentWidget == m_exSpinBox) {
      m_exSpinBox->setMinimum(m_minIntSpin->value());
      m_exSpinBox->setMaximum(m_maxIntSpin->value());
      m_exSpinBox->setSingleStep(m_stepIntSpin->value());
      m_exSpinBox->setNegBeforePrefix(m_exNegBeforePrefixBox->isChecked());
      m_exSpinBox->setPrefix(m_exPrefixEdit->text());

   } else if (m_currentWidget == m_doubleSpinBox) {
      m_doubleSpinBox->setMinimum(m_minDblSpin->value());
      m_doubleSpinBox->setMaximum(m_maxDblSpin->value());
      m_doubleSpinBox->setSingleStep(m_stepDblSpin->value());
   }
}

void MainWindow::setAlignmentStatus()
{
   AlignableWidgetInterface* awi = dynamic_cast<AlignableWidgetInterface*>(m_currentWidget);

   if (!awi) {
      m_widgetVerticalBox->setEnabled(false);
      m_widgetHorizontalBox->setEnabled(false);
      return;

   } else {

      m_widgetVerticalBox->setEnabled(true);
      m_widgetHorizontalBox->setEnabled(true);
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

      if (awi) {
         m_widgetVerticalBox->setEnabled(true);
         m_widgetHorizontalBox->setEnabled(true);
         widgetAlignment = awi->widgetAlignment();

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
}

void MainWindow::setStylesheetStatus()
{
   if (!m_currentWidget) {
      return;
   }

   QString labelStylesheet = m_currentWidget->labelStyleSheet();
   m_labelStylesheet->setPlainText(labelStylesheet);

   QString widgetStylesheet = m_currentWidget->widgetStyleSheet();
   m_widgetStylesheet->setPlainText(widgetStylesheet);

   QString overallStylesheet = m_currentWidget->styleSheet();
   m_overallStylesheet->setPlainText(overallStylesheet);
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

      } else if (m_currentWidget == m_doubleSpinBox) {
         m_widgetText->setEnabled(enable);
         m_widgetText->setValidator(new QDoubleValidator(this));
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
   if (!m_currentWidget) {
      return;
   }

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

QString MainWindow::sizePolicyToString(QSizePolicy::Policy policy)
{
   if (policy == QSizePolicy::Fixed) {
      return "Fixed";

   } else if (policy == QSizePolicy::Minimum) {
      return "Minimum";

   } else if (policy == QSizePolicy::Maximum) {
      return "Maximum";

   } else if (policy == QSizePolicy::Preferred) {
      return "Preferred";

   } else if (policy == QSizePolicy::Expanding) {
      return "Expanding";

   } else if (policy == QSizePolicy::MinimumExpanding) {
      return "MinimumExpanding";

   } else if (policy == QSizePolicy::Ignored) {
      return "Ignored";
   }

   return QString();
}

void MainWindow::showClock(bool enable)
{
   m_exTabWidget->showClock(enable);
   m_showSecondsBox->setEnabled(enable);
   m_showClockFrame->setEnabled(true);
   m_clockFrameStyleBox->setEnabled(true);

   if (enable) {
      m_showClockBox->setText(tr("Hide Clock"));

   } else {
      m_showClockBox->setText(tr("Show Clock"));
   }
}

void MainWindow::showSeconds(bool enable)
{
   m_exTabWidget->showSeconds(enable);

   if (enable) {
      m_showSecondsBox->setText(tr("Hide Seconds"));

   } else {
      m_showSecondsBox->setText(tr("Show Seconds"));
   }
}

void MainWindow::showClockFrame()
{
   // TODO might still need this.
   //   if (m_showClockFrame->isChecked()) {
   //      m_exTabWidget->showClockFrame(true, m_clockFrameStyleBox->currentData(Qt::UserRole).value<QFrame::Shape>());
   //   }else {
   //     m_exTabWidget->showClockFrame(false);
   //   }
}

void MainWindow::clockFrameStyleChanged(int /*index*/)
{
   showClockFrame();
}

void MainWindow::showMessages(bool enable)
{
   m_exTabWidget->showMessages(enable);

   if (enable) {
      m_showMessageBox->setText(tr("Hide Messages"));

   } else {
      m_showMessageBox->setText(tr("Show Messages"));
   }
}

void MainWindow::setMarqueeMoving(bool enable)
{
   m_exTabWidget->setMarquee(enable);

   if (enable) {
      m_enableMarqueeBox->setText(tr("Stop marquee"));

   } else {
      m_enableMarqueeBox->setText(tr("Start marquee"));
   }
}

void MainWindow::setMarqueeSpeed(qreal charPerSec)
{
   m_exTabWidget->setMarqueeSpeed(charPerSec);
}

void MainWindow::setSizePolicyStatus()
{
   if (!m_currentWidget) {
      return;
   }

   QSizePolicy policy = m_currentWidget->sizePolicy();
   m_labelHPoliciesBox->setCurrentText(sizePolicyToString(policy.horizontalPolicy()));
   m_labelVPoliciesBox->setCurrentText(sizePolicyToString(policy.verticalPolicy()));
}

void MainWindow::setSpinBoxStatus()
{
   if (!m_currentWidget) {
      return;
   }

   if (m_currentWidget == m_spinBox) {
      int min = m_spinBox->minimum();
      int max = m_spinBox->maximum();
      int step = m_spinBox->singleStep();

      if (min != m_minIntSpin->value()) {
         m_minIntSpin->setValue(min);
      }

      if (max != m_maxIntSpin->value()) {
         m_maxIntSpin->setValue(max);
      }

      if (step != m_stepIntSpin->value()) {
         m_stepIntSpin->setValue(step);
      }

   } else if (m_currentWidget == m_doubleSpinBox) {
      double min = m_doubleSpinBox->minimum();
      double max = m_doubleSpinBox->maximum();
      double step = m_doubleSpinBox->singleStep();

      if (min != m_minDblSpin->value()) {
         m_minDblSpin->setValue(min);
      }

      if (max != m_maxDblSpin->value()) {
         m_maxDblSpin->setValue(max);
      }

      if (step != m_stepDblSpin->value()) {
         m_stepDblSpin->setValue(step);
      }

   } else if (m_currentWidget == m_exSpinBox) {
      int min = m_exSpinBox->minimum();
      int max = m_exSpinBox->maximum();
      int step = m_exSpinBox->singleStep();

      if (min != m_minIntSpin->value()) {
         m_minIntSpin->setValue(min);
      }

      if (max != m_maxIntSpin->value()) {
         m_maxIntSpin->setValue(max);
      }

      if (step != m_stepIntSpin->value()) {
         m_stepIntSpin->setValue(step);
      }

      switch (m_exSpinBox->displayType()) {
      case ExSpinBox::Hexadecimal:
         m_exBox->setCurrentIndex(0);
         break;

      case ExSpinBox::Decimal:
         m_exBox->setCurrentIndex(1);
         break;

      case ExSpinBox::Octal:
         m_exBox->setCurrentIndex(2);
         break;

      case ExSpinBox::Binary:
         m_exBox->setCurrentIndex(3);
         break;
      }

      m_exNegBeforePrefixBox->setChecked(m_exSpinBox->negBeforePrefix());

      m_exPrefixEdit->setText(m_exSpinBox->prefix());
   }
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

void MainWindow::doubleSpinBoxChanged(double value)
{
   if (m_currentWidget == m_doubleSpinBox) {
      m_widgetText->setText(QString::number(value, 'f', m_doubleSpinBox->decimals()));
   }
}

void MainWindow::exSpinBoxChanged(int value)
{
   if (m_currentWidget == m_exSpinBox) {
      m_widgetText->setText(QString::number(value));
   }
}

void MainWindow::setCurrentWidgetAlignment()
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

   AlignableWidgetInterface* awi =
      dynamic_cast<AlignableWidgetInterface*>(m_currentWidget);

   switch (alignment) {
   case Qt::AlignLeft:
   case Qt::AlignRight:
   case Qt::AlignHCenter:
   case Qt::AlignJustify:
      if (awi && type == "Widget") {
         existing = awi->widgetAlignment();
         existing &= Qt::AlignVertical_Mask;
         existing |= alignment;
         awi->setWidgetAlignment(existing);

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
      if (awi && type == "Widget") {
         existing = awi->widgetAlignment();
         existing &= Qt::AlignHorizontal_Mask;
         existing |= alignment;
         awi->setWidgetAlignment(existing);

      } else if (type == "Label") {
         existing = m_currentWidget->labelAlignment();
         existing &= Qt::AlignHorizontal_Mask;
         existing |= alignment;
         m_currentWidget->setLabelAlignment(existing);
      }

      break;
   }
}

void MainWindow::exBoxTypeChanged(int /*index*/)
{
   if (m_exBox->currentIndex() == 0) {
      m_exSpinBox->setDisplayType(ExSpinBox::Hexadecimal);

   } else if (m_exBox->currentIndex() == 1) {
      m_exSpinBox->setDisplayType(ExSpinBox::Decimal);

   } else if (m_exBox->currentIndex() == 2) {
      m_exSpinBox->setDisplayType(ExSpinBox::Octal);

   } else if (m_exBox->currentIndex() == 3) {
      m_exSpinBox->setDisplayType(ExSpinBox::Binary);
   }
}

void MainWindow::setMessage()
{
   m_exTabWidget->setMessage(m_messageEdit->text());
}

void MainWindow::setTempMessage()
{
   //  m_exTabWidget->setMessage();
}

QWidget* MainWindow::initLabelledWidgets()
{
   QGroupBox* box = new QGroupBox(tr("Labelled Widgets :"), this);
   QVBoxLayout* l = new QVBoxLayout;
   box->setLayout(l);

   m_lineEdit = new LabelledLineEdit(tr("QLineEdit :"), this);
   // I chose textEdited because it ignores programatically changed text
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

   m_doubleSpinBox = new LabelledDoubleSpinBox(tr("QDoubleSpinBox :"), this);
   connect(m_doubleSpinBox,
           &LabelledDoubleSpinBox::valueChanged,
           this,
           &MainWindow::doubleSpinBoxChanged);
   l->addWidget(m_doubleSpinBox);

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
           << tr("Spin Box") << tr("Double Spin Box") << tr("ExSpinBox");
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
   m_left->setMinimum(-5);
   connect(m_left, &LabelledSpinBox::valueChanged, this, &MainWindow::setLeft);
   layoutLayout->addWidget(m_left, 1, 0);
   m_right = new LabelledSpinBox(tr("Right"), this);
   m_right->setMinimum(-5);
   connect(m_right, &LabelledSpinBox::valueChanged, this, &MainWindow::setRight);
   layoutLayout->addWidget(m_right, 1, 2);
   m_top = new LabelledSpinBox(tr("Top"), this);
   m_top->setMinimum(-5);
   connect(m_top, &LabelledSpinBox::valueChanged, this, &MainWindow::setTop);
   layoutLayout->addWidget(m_top, 0, 1);
   m_bottom = new LabelledSpinBox(tr("Bottom"), this);
   m_bottom->setMinimum(-5);
   connect(m_bottom, &LabelledSpinBox::valueChanged, this, &MainWindow::setBottom);
   layoutLayout->addWidget(m_bottom, 2, 1);
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

   // label is always enabled, but widget only if it implements AlignableWidgetInterface.
   m_widgetHorizontalBox->setEnabled(false);
   m_widgetVerticalBox->setEnabled(false);

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

   connect(topBtn, &QRadioButton::clicked, this, &MainWindow::setCurrentWidgetAlignment);
   connect(bottomBtn, &QRadioButton::clicked, this, &MainWindow::setCurrentWidgetAlignment);
   connect(centreBtn, &QRadioButton::clicked, this, &MainWindow::setCurrentWidgetAlignment);
   connect(baselineBtn, &QRadioButton::clicked, this, &MainWindow::setCurrentWidgetAlignment);

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

   connect(leftBtn, &QRadioButton::clicked, this, &MainWindow::setCurrentWidgetAlignment);
   connect(rightBtn, &QRadioButton::clicked, this, &MainWindow::setCurrentWidgetAlignment);
   connect(centreBtn, &QRadioButton::clicked, this, &MainWindow::setCurrentWidgetAlignment);
   connect(justifyBtn, &QRadioButton::clicked, this, &MainWindow::setCurrentWidgetAlignment);

   return box;
}

QWidget* MainWindow::initStylesheetBox()
{
   QGroupBox* box = new QGroupBox(tr("Stylesheets :"), this);
   QVBoxLayout* l = new QVBoxLayout;
   box->setLayout(l);

   QString tempShit = "color:yellow;background:red;";

   QGroupBox* labelBox = new QGroupBox(tr("Label"), this);
   QGridLayout* labelLayout = new QGridLayout;
   labelBox->setLayout(labelLayout);
   m_labelStylesheet = new QPlainTextEdit(this);
   m_labelStylesheet->setPlainText(tempShit);
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
   m_widgetStylesheet->setPlainText(tempShit);
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
   overallLayout->addWidget(overallBtn, 1, 0);
   l->addWidget(overallBox);

   return box;
}

QWidget* MainWindow::initSpinBoxRangeBox()
{
   QFrame* f = new QFrame(this);
   QGridLayout* l = new QGridLayout;
   f->setLayout(l);

   m_spinStack = new QStackedWidget(this);
   l->addWidget(m_spinStack, 0, 0);

   QGroupBox* intBox = new QGroupBox(tr("Int Spin Box Control"), this);
   QVBoxLayout* intLayout = new QVBoxLayout;
   intBox->setLayout(intLayout);
   m_spinIntStack = m_spinStack->addWidget(intBox);

   m_minIntSpin = new LabelledSpinBox(tr("Minimum Spin"), this);
   m_minIntSpin->setRange(-100, 100);
   intLayout->addWidget(m_minIntSpin);

   m_maxIntSpin = new LabelledSpinBox(tr("Maximum Spin"), this);
   m_maxIntSpin->setRange(-100, 100);
   intLayout->addWidget(m_maxIntSpin);

   m_stepIntSpin = new LabelledSpinBox(tr("Single Step"), this);
   m_stepIntSpin->setRange(-5, 5);
   intLayout->addWidget(m_stepIntSpin);

   QStringList extypes;
   extypes << "Hexadecimal" << "Decimal" << "Octal" << "Binary";
   m_exBox = new LabelledComboBox(tr("Choose ExSpinBox Display Type"), this);
   m_exBox->addItems(extypes);
   m_exBox->setEnabled(false);
   connect(m_exBox, &LabelledComboBox::currentIndexChanged, this, &MainWindow::exBoxTypeChanged);
   intLayout->addWidget(m_exBox);

   m_exNegBeforePrefixBox = new QCheckBox(tr("ExSpinBox Negative Before Prefix"), this);
   m_exNegBeforePrefixBox->setEnabled(false);
   intLayout->addWidget(m_exNegBeforePrefixBox);

   m_exPrefixEdit = new LabelledLineEdit(tr("ExSpinBox prefix"), this);
   m_exPrefixEdit->setEnabled(false);
   intLayout->addWidget(m_exPrefixEdit);

   QGroupBox* dblBox = new QGroupBox(tr("Double Spin Box Control"), this);
   QVBoxLayout* dblLayout = new QVBoxLayout;
   dblBox->setLayout(dblLayout);
   m_spinDblStack = m_spinStack->addWidget(dblBox);

   m_minDblSpin = new LabelledDoubleSpinBox(tr("Maximum Spin"), this);
   m_minDblSpin->setRange(-100.0, 100.0);
   dblLayout->addWidget(m_minDblSpin);

   m_maxDblSpin = new LabelledDoubleSpinBox(tr("Minimum Spin"), this);
   m_maxDblSpin->setRange(-100.0, 100.0);
   dblLayout->addWidget(m_maxDblSpin);

   m_stepDblSpin = new LabelledDoubleSpinBox(tr("Single Step"), this);
   m_stepDblSpin->setRange(-5.0, 5.0);
   m_stepDblSpin->setSingleStep(0.1);
   dblLayout->addWidget(m_stepDblSpin);

   m_setSpinBtn = new QPushButton(tr("Set Message"), this);
   m_setSpinBtn->setEnabled(false);
   connect(m_setSpinBtn, &QPushButton::clicked, this, &MainWindow::setMessage);
   l->addWidget(m_setSpinBtn, 1, 0);

   QFrame* dummy = new QFrame(this);
   dummy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   l->addWidget(dummy);

   m_spinStack->setCurrentIndex(m_spinIntStack);

   return f;
}

QWidget* MainWindow::initPolicyBox()
{
   QGroupBox* box = new QGroupBox(this);
   QVBoxLayout* l = new QVBoxLayout;
   box->setLayout(l);

   QGroupBox* labelBox = new QGroupBox(tr("Label SizePolicy:"), this);
   QVBoxLayout* labelLayout = new QVBoxLayout;
   labelBox->setLayout(labelLayout);

   QStringList sizePolicies;
   sizePolicies << "Fixed" << "Minimum" << "Maximum" << "Preferred" << "Expanding"
                << "MinimumExpanding" << "Ignored";
   m_labelHPoliciesBox = new LabelledComboBox(tr("Horizontal"), this);
   m_labelHPoliciesBox->addItems(sizePolicies);
   m_labelHPoliciesBox->setItemData(0, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Fixed));
   m_labelHPoliciesBox->setItemData(1, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Minimum));
   m_labelHPoliciesBox->setItemData(2, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Maximum));
   m_labelHPoliciesBox->setItemData(3, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Preferred));
   m_labelHPoliciesBox->setItemData(4, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Expanding));
   m_labelHPoliciesBox->setItemData(5, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::MinimumExpanding));
   m_labelHPoliciesBox->setItemData(6, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Ignored));
   labelLayout->addWidget(m_labelHPoliciesBox);

   m_labelVPoliciesBox = new LabelledComboBox(tr("Vertical"), this);
   m_labelVPoliciesBox->addItems(sizePolicies);
   m_labelVPoliciesBox->setItemData(0, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Fixed));
   m_labelVPoliciesBox->setItemData(1, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Minimum));
   m_labelVPoliciesBox->setItemData(2, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Maximum));
   m_labelVPoliciesBox->setItemData(3, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Preferred));
   m_labelVPoliciesBox->setItemData(4, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Expanding));
   m_labelVPoliciesBox->setItemData(5, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::MinimumExpanding));
   m_labelVPoliciesBox->setItemData(6, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Ignored));
   labelLayout->addWidget(m_labelVPoliciesBox);

   l->addWidget(labelBox);

   QGroupBox* widgetBox = new QGroupBox(tr("Widget SizePolicy :"), this);
   QVBoxLayout* widgetLayout = new QVBoxLayout;
   widgetBox->setLayout(widgetLayout);

   m_widgetHPoliciesBox = new LabelledComboBox(tr("Horizontal"), this);
   m_widgetHPoliciesBox->addItems(sizePolicies);
   m_widgetHPoliciesBox->setItemData(0, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Fixed));
   m_widgetHPoliciesBox->setItemData(1, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Minimum));
   m_widgetHPoliciesBox->setItemData(2, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Maximum));
   m_widgetHPoliciesBox->setItemData(3, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Preferred));
   m_widgetHPoliciesBox->setItemData(4, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Expanding));
   m_widgetHPoliciesBox->setItemData(5, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::MinimumExpanding));
   m_widgetHPoliciesBox->setItemData(6, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Ignored));
   widgetLayout->addWidget(m_widgetHPoliciesBox);

   m_widgetVPoliciesBox = new LabelledComboBox(tr("Vertical"), this);
   m_widgetVPoliciesBox->addItems(sizePolicies);
   m_widgetVPoliciesBox->setItemData(0, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Fixed));
   m_widgetVPoliciesBox->setItemData(1, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Minimum));
   m_widgetVPoliciesBox->setItemData(2, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Maximum));
   m_widgetVPoliciesBox->setItemData(3, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Preferred));
   m_widgetVPoliciesBox->setItemData(4, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Expanding));
   m_widgetVPoliciesBox->setItemData(5, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::MinimumExpanding));
   m_widgetVPoliciesBox->setItemData(6, QVariant::fromValue<QSizePolicy::Policy>(QSizePolicy::Ignored));
   widgetLayout->addWidget(m_widgetVPoliciesBox);

   l->addWidget(widgetBox);

   connect(m_labelHPoliciesBox, &LabelledComboBox::currentTextChanged, this, &MainWindow::labelSizePolicyHasChanged);
   connect(m_labelVPoliciesBox, &LabelledComboBox::currentTextChanged, this, &MainWindow::labelSizePolicyHasChanged);
   connect(m_widgetHPoliciesBox, &LabelledComboBox::currentTextChanged, this, &MainWindow::widgetSizePolicyHasChanged);
   connect(m_widgetVPoliciesBox, &LabelledComboBox::currentTextChanged, this, &MainWindow::widgetSizePolicyHasChanged);

   return box;
}

QWidget* MainWindow::initLabelledWidgetFrame()
{
   QWidget* f = new QFrame(this);
   QGridLayout* l = new QGridLayout;
   f->setLayout(l);

   l->addWidget(initLabelledWidgets(), 0, 0);
   l->addWidget(initChooseWidgetBox(), 0, 1);
   l->addWidget(initPolicyBox(), 0, 2);

   l->addWidget(initStylesheetBox(), 1, 0);
   l->addWidget(initAlignmentBox(), 1, 1);
   l->addWidget(initSpinBoxRangeBox(), 1, 2);

   chooseWidget(tr("None"));
   enableWidgets(false);
   setAlignmentStatus();

   return f;
}

QWidget* MainWindow::initExTabWidget()
{
   m_exTabWidget = new ExTabWidget(this);
   QFrame* f1 = new QFrame(this);
   QGridLayout* l1 = new QGridLayout;
   f1->setLayout(l1);

   QGroupBox* enableBox = new QGroupBox(tr("Enable Components"), this);
   QVBoxLayout* enableLayout = new QVBoxLayout;
   enableBox->setLayout(enableLayout);

   m_showClockBox = new QCheckBox(tr("Enable Clock"), this);
   connect(m_showClockBox, &QCheckBox::clicked, this, &MainWindow::showClock);
   enableLayout->addWidget(m_showClockBox);

   m_showSecondsBox = new QCheckBox(tr("Show Seconds"), this);
   m_showSecondsBox->setEnabled(false);
   connect(m_showSecondsBox, &QCheckBox::clicked, this, &MainWindow::showSeconds);
   enableLayout->addWidget(m_showSecondsBox);

   m_showClockFrame = new QCheckBox(tr("Show Clock Frame"), this);
   m_showClockFrame->setEnabled(false);
   connect(m_showClockFrame, &QCheckBox::clicked, this, &MainWindow::showClockFrame);
   enableLayout->addWidget(m_showClockFrame);

   QStringList frameStyles;
   frameStyles << "QFrame::NoFrame" << "QFrame::Box" << "QFrame::Panel"
               << "QFrame::StyledPanel" << "QFrame::HLine"
               << "QFrame::VLine" << "QFrame::WinPanel";
   m_clockFrameStyleBox = new LabelledComboBox(tr("Clock Frame Style"), this);
   m_clockFrameStyleBox->setEnabled(false);
   connect(m_clockFrameStyleBox, &LabelledComboBox::currentIndexChanged, this,
           &MainWindow::clockFrameStyleChanged);
   m_clockFrameStyleBox->addItems(frameStyles);
   m_clockFrameStyleBox->setItemData(0, QVariant::fromValue<QFrame::Shape>(QFrame::NoFrame));
   m_clockFrameStyleBox->setItemData(1, QVariant::fromValue<QFrame::Shape>(QFrame::Box));
   m_clockFrameStyleBox->setItemData(2, QVariant::fromValue<QFrame::Shape>(QFrame::Panel));
   m_clockFrameStyleBox->setItemData(3, QVariant::fromValue<QFrame::Shape>(QFrame::StyledPanel));
   m_clockFrameStyleBox->setItemData(4, QVariant::fromValue<QFrame::Shape>(QFrame::HLine));
   m_clockFrameStyleBox->setItemData(5, QVariant::fromValue<QFrame::Shape>(QFrame::VLine));
   m_clockFrameStyleBox->setItemData(6, QVariant::fromValue<QFrame::Shape>(QFrame::WinPanel));
   enableLayout->addWidget(m_clockFrameStyleBox);

   m_showMessageBox = new QCheckBox(tr("Show Messages"), this);
   connect(m_showMessageBox, &QCheckBox::clicked, this, &MainWindow::showMessages);
   enableLayout->addWidget(m_showMessageBox);

   m_enableMarqueeBox = new QCheckBox(tr("Start marquee"), this);
   connect(m_enableMarqueeBox, &QCheckBox::clicked, this, &MainWindow::setMarqueeMoving);
   enableLayout->addWidget(m_enableMarqueeBox);

   m_messageEdit = new LabelledLineEdit(tr("Enter message :"), this);
   m_messageEdit->setText(
      tr("This is a very, very, very, very, very, very, very, very, very, very, very, very, very, very, very, very, very, very, very, very long message"));
   enableLayout->addWidget(m_messageEdit);

   m_messageBtn = new QPushButton(tr("Set Message"), this);
   connect(m_messageBtn, &QPushButton::clicked, this,
           &MainWindow::setMessage);
   enableLayout->addWidget(m_messageBtn);

   m_tempMessageEdit = new LabelledLineEdit(tr("Enter message :"), this);
   m_tempMessageEdit->setText(tr("Temporary message"));
   enableLayout->addWidget(m_tempMessageEdit);

   m_timeoutBox = new LabelledDoubleSpinBox(tr("Temp Message Timeout (Seconds)"), this);
   m_timeoutBox->setRange(0, 10);
   enableLayout->addWidget(m_timeoutBox);

   //   QFrame *colorBtnFrame = new QFrame(this);
   QVBoxLayout* clMain = new QVBoxLayout;
   QHBoxLayout* cl1 = new QHBoxLayout, *cl2 = new QHBoxLayout;
   clMain->addLayout(cl1);
   clMain->addLayout(cl2);
   //   colorBtnFrame->setLayout(clMain);

   m_textColorBtn = new QPushButton(tr("Set Color"), this);
   cl1->addWidget(m_textColorBtn);
   m_backColorBtn = new QPushButton(tr("Set Background"), this);
   cl1->addWidget(m_backColorBtn);
   m_textColorBtn = new QPushButton(tr("Set Temporary Color"), this);
   cl2->addWidget(m_textColorBtn);
   m_backColorBtn = new QPushButton(tr("Set Temporary Background"), this);
   cl2->addWidget(m_backColorBtn);
   // TODO set colors.

   enableLayout->addLayout(clMain);

   m_tempMessageBtn = new QPushButton(tr("Set Temporary Message"), this);
   connect(m_tempMessageBtn, &QPushButton::clicked, this,
           &MainWindow::setTempMessage);
   enableLayout->addWidget(m_tempMessageBtn);

   l1->addWidget(enableBox, 0, 0);

   QFrame* dummy = new QFrame(this);
   dummy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   l1->addWidget(dummy, 7, 0);

   QFrame* f2 = new QFrame(this);
   m_exTabWidget->addTab(f1, tr("Tab 1"));
   m_exTabWidget->addTab(f2, tr("Tab 2"));

   return m_exTabWidget;
}

void MainWindow::initGui()
{
   m_tabs = new QTabWidget(this);
   setCentralWidget(m_tabs);


   m_tabs->addTab(initLabelledWidgetFrame(), tr("Labelled Widgets"));
   m_tabs->addTab(initExTabWidget(), tr("Extended TabWidget"));

   //   initLabelledWidgetFrame();
}
