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

#include "logindialog.h"

LoginDialog::LoginDialog(QWidget* parent)
   : AbstractLoginDialog(parent)
{
   initGui(false);
}

LoginDialog::~LoginDialog() {}

void LoginDialog::clearText()
{
   m_userEdit->clear();
   m_passEdit->clear();
}

void LoginDialog::acceptLogin()
{
   emit loginData(m_userEdit->text(), m_passEdit->text());
}

void LoginDialog::initGui(bool largeText)
{
   QFont f = font();

   if (largeText) {
      f.setPointSize(20);
      f.setWeight(QFont::Bold);
      setFont(f);
   }

   QLabel* lbl1 = new QLabel("User name :", this);
   lbl1->setFont(f);
   m_userEdit = new QLineEdit(this);
   QLabel* lbl2 = new QLabel("Password :", this);
   lbl2->setFont(f);
   m_passEdit = new QLineEdit(this);
   m_passEdit->setEchoMode(QLineEdit::Password);

   QGridLayout* layout = new QGridLayout(this);
   setLayout(layout);

   layout->addWidget(lbl1, 0, 0);
   layout->addWidget(m_userEdit, 0, 1);
   layout->addWidget(lbl2, 1, 0);
   layout->addWidget(m_passEdit, 1, 1);

   QDialogButtonBox* buttons = new QDialogButtonBox(this);
   buttons->addButton(QDialogButtonBox::Ok);
   buttons->addButton(QDialogButtonBox::Cancel);
   buttons->button(QDialogButtonBox::Ok)->setText(tr("Login"));
   buttons->button(QDialogButtonBox::Ok)->setFont(f);
   buttons->button(QDialogButtonBox::Cancel)->setText(tr("Abort"));
   buttons->button(QDialogButtonBox::Cancel)->setFont(f);
   layout->addWidget(buttons, 2, 0, 1, 2);

   // close on abort
   connect(buttons->button(QDialogButtonBox::Cancel),
           &QPushButton::clicked,
           this,
           &LoginDialog::close);

   // acceptLogin and abort on accept.
   // should acceptLogin first.
   connect(buttons->button(QDialogButtonBox::Ok),
           &QPushButton::clicked,
           this,
           &LoginDialog::acceptLogin);
   connect(buttons->button(QDialogButtonBox::Ok),
           &QPushButton::clicked,
           this,
           &LoginDialog::close);
}

SimpleLoginDialog::SimpleLoginDialog(QWidget* parent)
   : AbstractLoginDialog(parent)
{
   initGui(false);
}

SimpleLoginDialog::~SimpleLoginDialog() {}

void SimpleLoginDialog::clearText()
{
   m_passEdit->clear();
}

void SimpleLoginDialog::initGui(bool largeText)
{
   QFont f = font();

   if (largeText) {
      f.setPointSize(20);
      f.setWeight(QFont::Bold);
      setFont(f);
   }

   QLabel* lbl1 = new QLabel("Password :", this);
   lbl1->setFont(f);

   m_passEdit = new QLineEdit(this);
   m_passEdit->setFont(f);
   m_passEdit->setEchoMode(QLineEdit::Password);

   QGridLayout* layout = new QGridLayout(this);
   setLayout(layout);

   layout->addWidget(lbl1, 0, 0);
   layout->addWidget(m_passEdit, 0, 1);

   QDialogButtonBox* buttons = new QDialogButtonBox(this);
   buttons->addButton(QDialogButtonBox::Ok);
   buttons->addButton(QDialogButtonBox::Cancel);
   buttons->button(QDialogButtonBox::Ok)->setText(tr("Login"));
   buttons->button(QDialogButtonBox::Ok)->setFont(f);
   buttons->button(QDialogButtonBox::Cancel)->setText(tr("Abort"));
   buttons->button(QDialogButtonBox::Cancel)->setFont(f);
   layout->addWidget(buttons, 1, 0, 1, 2);

   // close on abort
   connect(buttons->button(QDialogButtonBox::Cancel),
           &QPushButton::clicked,
           this,
           &SimpleLoginDialog::close);

   // acceptLogin and abort on accept.
   // should acceptLogin first.
   connect(buttons->button(QDialogButtonBox::Ok),
           &QPushButton::clicked,
           this,
           &SimpleLoginDialog::acceptLogin);
   connect(buttons->button(QDialogButtonBox::Ok),
           &QPushButton::clicked,
           this,
           &SimpleLoginDialog::close);
}

void SimpleLoginDialog::acceptLogin()
{
   emit loginData(m_passEdit->text());
}
