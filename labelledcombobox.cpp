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
#include "labelledcombobox.h"

/*!
   \brief Constructs a combobox with the given label text and parent,
   using the default model QStandardItemModel.
*/
LabelledComboBox::LabelledComboBox(const QString& text, QWidget* parent)
  : AbstractLabelledWidget(text, parent)
{
  initGui();
}

/*!
  \brief  Adds an item to the combobox with the given text, and containing the
  specified userData (stored in the Qt::UserRole). The item is appended to the
  list of existing items.
*/
void LabelledComboBox::addItem(const QString& text, const QVariant& userdata)
{
  qobject_cast<QComboBox*>(m_widget)->addItem(text, userdata);
}

/*!
  \brief  Adds an item to the combobox with the given icon and text, and
  containing the specified userData (stored in the Qt::UserRole). The item is
  appended to the list of existing items.
*/
void LabelledComboBox::addItem(const QIcon& icon,
                               const QString& text,
                               const QVariant& userdata)
{
  qobject_cast<QComboBox*>(m_widget)->addItem(icon, text, userdata);
}

/*!
   \brief Adds each of the strings in the given texts to the combobox.
  Each item is appended to the list of existing items in turn.
*/
void LabelledComboBox::addItems(const QStringList& items)
{
  qobject_cast<QComboBox*>(m_widget)->addItems(items);
}

/*!
   \brief Returns the completer that is used to auto complete text input for the
   combobox.

   \since 4.2
*/
QCompleter* LabelledComboBox::completer()
{
  return qobject_cast<QComboBox*>(m_widget)->completer();
}

/*!
   \brief Sets the completer to use instead of the current completer.
  If completer is nullptr, auto completion is disabled.

  By default, for an editable combo box, a QCompleter that performs case
  insensitive inline completion is automatically created.

  Note: The completer is removed when the editable property becomes false.
  Setting a completer on a QComboBox that is not editable will be ignored.
*/
void LabelledComboBox::setCompleter(QCompleter* completer)
{
  qobject_cast<QComboBox*>(m_widget)->setCompleter(completer);
}

int LabelledComboBox::count()
{
  return qobject_cast<QComboBox*>(m_widget)->count();
}

int LabelledComboBox::maxCount()
{
  return qobject_cast<QComboBox*>(m_widget)->maxCount();
}

void LabelledComboBox::setMaxCount(int max)
{
  qobject_cast<QComboBox*>(m_widget)->setMaxCount(max);
}

QVariant LabelledComboBox::currentData(int role) const
{
  return qobject_cast<QComboBox*>(m_widget)->currentData(role);
}

int LabelledComboBox::currentIndex() const
{
  return qobject_cast<QComboBox*>(m_widget)->currentIndex();
}

QString LabelledComboBox::currentText() const
{
  return qobject_cast<QComboBox*>(m_widget)->currentText();
}

void LabelledComboBox::setCurrentIndex(int index)
{
  qobject_cast<QComboBox*>(m_widget)->setCurrentIndex(index);
}

void LabelledComboBox::setCurrentText(const QString& text)
{
  qobject_cast<QComboBox*>(m_widget)->setCurrentText(text);
}

/*!
   \brief Returns whether the user can enter duplicate items into the combobox

   Note that it is always possible to programmatically insert duplicate items
   into the combobox.

   By default, this property is false (duplicates are not allowed).
*/
bool LabelledComboBox::duplicatesEnabled()
{
  return qobject_cast<QComboBox*>(m_widget)->duplicatesEnabled();
}

/*!
   \brief Sets whether the user can enter duplicate items into the combobox

  Note that it is always possible to programmatically insert duplicate items
  into the combobox.

  By default, this property is false (duplicates are not allowed).
*/
void LabelledComboBox::setDuplicatesEnabled(bool enable)
{
  qobject_cast<QComboBox*>(m_widget)->setDuplicatesEnabled(enable);
}

/*!
   \brief Returns the index of the item containing the given data for the given
   role; otherwise returns -1.

   The flags specify how the items in the combobox are searched.
*/
int LabelledComboBox::findData(const QVariant& data,
                               int role,
                               Qt::MatchFlags flags) const
{
  return qobject_cast<QComboBox*>(m_widget)->findData(data, role, flags);
}

/*!
   \brief Returns the index of the item containing the given text; otherwise
  returns -1.

  The flags specify how the items in the combobox are searched.
*/
int LabelledComboBox::findText(const QString& text, Qt::MatchFlags flags) const
{
  return qobject_cast<QComboBox*>(m_widget)->findText(text, flags);
}

QSize LabelledComboBox::iconSize()
{
  return qobject_cast<QComboBox*>(m_widget)->iconSize();
}

/*!
   \brief Hides the list of items in the combobox if it is currently visible and
  resets the internal state, so that if the custom pop-up was shown inside the
  reimplemented showPopup(), then you also need to reimplement the hidePopup()
  function to hide your custom pop-up and call the base class implementation to
  reset the internal state whenever your custom pop-up widget is hidden.

  \sa showPopup()
*/
void LabelledComboBox::hidePopup()
{
  qobject_cast<QComboBox*>(m_widget)->hidePopup();
}

/*!
   \brief Inserts the text and userData (stored in the Qt::UserRole) into the
  combobox at the given index.

  If the index is equal to or higher than the total number of items, the new
  item is appended to the list of existing items. If the index is zero or
  negative, the new item is prepended to the list of existing items.
*/
void LabelledComboBox::insertItem(int index,
                                  const QString& text,
                                  const QVariant& userData)
{
  qobject_cast<QComboBox*>(m_widget)->insertItem(index, text, userData);
}

/*!
   \brief Inserts the icon, text and userData (stored in the Qt::UserRole) into
  the combobox at the given index.

  If the index is equal to or higher than the total number of items, the
  new item is appended to the list of existing items. If the index is zero
  or negative, the new item is prepended to the list of existing items.
*/
void LabelledComboBox::insertItem(int index,
                                  const QIcon& icon,
                                  const QString& text,
                                  const QVariant& userData)
{
  qobject_cast<QComboBox*>(m_widget)->insertItem(index, icon, text, userData);
}

/*!
   \brief Inserts the strings from the list into the combobox as separate items,
  starting at the index specified.

  If the index is equal to or higher than the total number of items, the new
  items are appended to the list of existing items. If the index is zero or
  negative, the new items are prepended to the list of existing items.
*/
void LabelledComboBox::insertItems(int index, const QStringList& list)
{
  qobject_cast<QComboBox*>(m_widget)->insertItems(index, list);
}

QComboBox::InsertPolicy LabelledComboBox::insertPolicy() const
{
  return qobject_cast<QComboBox*>(m_widget)->insertPolicy();
}

/*!
   \brief Inserts a separator item into the combobox at the given index.

  If the index is equal to or higher than the total number of items, the
  new item is appended to the list of existing items. If the index is zero
  or negative, the new item is prepended to the list of existing items.

  \since 4.4
*/
void LabelledComboBox::insertSeparator(int index)
{
  qobject_cast<QComboBox*>(m_widget)->insertSeparator(index);
}

bool LabelledComboBox::isEditable() const
{
  return qobject_cast<QComboBox*>(m_widget)->isEditable();
}

/*!
   \brief Returns the data for the given role in the given index in the combobox,
  or QVariant::Invalid if there is no data for this role.
*/
QVariant LabelledComboBox::itemData(int index, int role) const
{
  return qobject_cast<QComboBox*>(m_widget)->itemData(index, role);
}

/*!
   \brief Returns the item delegate used by the popup list view.
*/
QAbstractItemDelegate* LabelledComboBox::itemDelegate() const
{
  return qobject_cast<QComboBox*>(m_widget)->itemDelegate();
}

/*!
   \brief Returns the icon for the item on the given index in the combobox.
*/
QIcon LabelledComboBox::itemIcon(int index) const
{
  return qobject_cast<QComboBox*>(m_widget)->itemIcon(index);
}

/*!
   \brief Returns the text for the item on the given index in the combobox.
*/
QString LabelledComboBox::itemText(int index) const
{
  return qobject_cast<QComboBox*>(m_widget)->itemText(index);
}

/*!
   \brief Returns the line edit used to edit items in the combobox,
  or nullptr if there is no line edit.

  Only editable combo boxes have a line edit.
*/
QLineEdit* LabelledComboBox::lineEdit() const
{
  return qobject_cast<QComboBox*>(m_widget)->lineEdit();
}

int LabelledComboBox::maxVisibleItems() const
{
  return qobject_cast<QComboBox*>(m_widget)->maxVisibleItems();
}

int LabelledComboBox::minimumContentsLength() const
{
  return qobject_cast<QComboBox*>(m_widget)->minimumContentsLength();
}

/*!
   \brief Returns the model used by the combobox.
*/
QAbstractItemModel* LabelledComboBox::model() const
{
  return qobject_cast<QComboBox*>(m_widget)->model();
}

/*!
   \brief Sets the column in the model that is visible.

  If set prior to populating the combo box, the pop-up view will not be
  affected and will show the first column (using this property's default value).

  By default, this property has a value of 0.
*/
int LabelledComboBox::modelColumn() const
{
  return qobject_cast<QComboBox*>(m_widget)->modelColumn();
}

#if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
// these are only available in 15.0.0 and greater.
QString LabelledComboBox::placeholderText() const
{
  return qobject_cast<QComboBox*>(m_widget)->placeholderText();
}

void LabelledComboBox::setPlaceholderText(const QString& placeholderText)
{
  qobject_cast<QComboBox*>(m_widget)->setPlaceholderText(placeholderText);
}
#endif

/*!
   \brief Removes the item at the given index from the combobox. This will update
  the current index if the index is removed.

  This function does nothing if index is out of range.
*/
void LabelledComboBox::removeItem(int index)
{
  qobject_cast<QComboBox*>(m_widget)->removeItem(index);
}

/*!
   \brief Returns the root model item index for the items in the combobox.
*/
QModelIndex LabelledComboBox::rootModelIndex() const
{
  return qobject_cast<QComboBox*>(m_widget)->rootModelIndex();
}

void LabelledComboBox::setEditable(bool editable)
{
  qobject_cast<QComboBox*>(m_widget)->setEditable(editable);
}

void LabelledComboBox::setIconSize(const QSize& size)
{
  qobject_cast<QComboBox*>(m_widget)->setIconSize(size);
}

void LabelledComboBox::setInsertPolicy(QComboBox::InsertPolicy policy)
{
  qobject_cast<QComboBox*>(m_widget)->setInsertPolicy(policy);
}

/*!
   \brief Sets the data role for the item on the given index in the combobox to the specified value.
*/
void LabelledComboBox::setItemData(int index, const QVariant& value, int role)
{
  qobject_cast<QComboBox*>(m_widget)->setItemData(index, value, role);
}

/*!
   \brief Sets the item delegate for the popup list view. The combobox takes
  ownership of the delegate.

  Warning: You should not share the same instance of a delegate between comboboxes,
  widget mappers or views. Doing so can cause incorrect or unintuitive editing behavior
  since each view connected to a given delegate may receive the closeEditor() signal,
  and attempt to access, modify or close an editor that has already been closed.
*/
void LabelledComboBox::setItemDelegate(QAbstractItemDelegate* delegate)
{
  qobject_cast<QComboBox*>(m_widget)->setItemDelegate(delegate);
}

/*!
   \brief Sets the icon for the item on the given index in the combobox.
*/
void LabelledComboBox::setItemIcon(int index, const QIcon& icon)
{
  qobject_cast<QComboBox*>(m_widget)->setItemIcon(index, icon);
}

/*!
   \brief Sets the text for the item on the given index in the combobox.
*/
void LabelledComboBox::setItemText(int index, const QString& text)
{
  qobject_cast<QComboBox*>(m_widget)->setItemText(index, text);
}

/*!
   \brief Sets the line edit to use instead of the current line edit widget.

  The combo box takes ownership of the line edit.
*/
void LabelledComboBox::setLineEdit(QLineEdit* edit)
{
  qobject_cast<QComboBox*>(m_widget)->setLineEdit(edit);
}

void LabelledComboBox::setMaxVisibleItems(int maxItems)
{
  qobject_cast<QComboBox*>(m_widget)->setMaxVisibleItems(maxItems);
}

void LabelledComboBox::setMinimumContentsLength(int characters)
{
  qobject_cast<QComboBox*>(m_widget)->setMinimumContentsLength(characters);
}

/*!
   \brief Sets the model to be model. model must not be nullptr. If you
  want to clear the contents of a model, call clear().
*/
void LabelledComboBox::setModel(QAbstractItemModel* model)
{
  qobject_cast<QComboBox*>(m_widget)->setModel(model);
}

/*!
   \brief Sets the column in the model that is visible.

  If set prior to populating the combo box, the pop-up view will
  not be affected and will show the first column (using this property's default value).

  By default, this property has a value of 0.
*/
void LabelledComboBox::setModelColumn(int visibleColumn)
{
  qobject_cast<QComboBox*>(m_widget)->setModelColumn(visibleColumn);
}

/*!
   \brief Sets the root model item index for the items in the combobox.
*/
void LabelledComboBox::setRootModelIndex(const QModelIndex& index)
{
  qobject_cast<QComboBox*>(m_widget)->setRootModelIndex(index);
}

void LabelledComboBox::setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy policy)
{
  qobject_cast<QComboBox*>(m_widget)->setSizeAdjustPolicy(policy);
}

/*!
   \brief Sets the validator to use instead of the current validator.

  Note: The validator is removed when the editable property becomes false.
*/
void LabelledComboBox::setValidator(const QValidator* validator)
{
  qobject_cast<QComboBox*>(m_widget)->setValidator(validator);
}

/*!
   \brief Sets the view to be used in the combobox popup to the given itemView.
  The combobox takes ownership of the view.

  Note: If you want to use the convenience views (like QListWidget, QTableWidget or
  QTreeWidget), make sure to call setModel()
  on the combobox with the convenience widgets model before calling this function.
*/
void LabelledComboBox::setView(QAbstractItemView* itemView)
{
  qobject_cast<QComboBox*>(m_widget)->setView(itemView);
}

/*!
   \brief Displays the list of items in the combobox.
  If the list is empty then no items will be shown.

  If you reimplement this function to show a
  custom pop-up, make sure you call hidePopup() to reset the internal state.
*/
void LabelledComboBox::showPopup()
{
  qobject_cast<QComboBox*>(m_widget)->showPopup();
}

QComboBox::SizeAdjustPolicy LabelledComboBox::sizeAdjustPolicy() const
{
  return qobject_cast<QComboBox*>(m_widget)->sizeAdjustPolicy();
}

/*!
   \brief Returns the current validator.

  Note: The validator is removed when the editable property becomes false.
*/
const QValidator* LabelledComboBox::validator() const
{
  return qobject_cast<QComboBox*>(m_widget)->validator();
}

/*!
   \brief Returns the list view used for the combobox popup.
*/
QAbstractItemView* LabelledComboBox::view() const
{
  return qobject_cast<QComboBox*>(m_widget)->view();
}

void LabelledComboBox::initGui()
{
  m_widget = new QComboBox(this);
  m_layout->addWidget(m_widget, 0, 1);
  connect(qobject_cast<QComboBox*>(m_widget),
          qOverload<int>(&QComboBox::activated),
          this,
          &LabelledComboBox::activated);
  connect(qobject_cast<QComboBox*>(m_widget),
          qOverload<int>(&QComboBox::currentIndexChanged),
          this,
          &LabelledComboBox::currentIndexChanged);
  connect(qobject_cast<QComboBox*>(m_widget),
          qOverload<const QString&>(&QComboBox::currentTextChanged),
          this,
          &LabelledComboBox::currentTextChanged);
  connect(qobject_cast<QComboBox*>(m_widget),
          qOverload<const QString&>(&QComboBox::editTextChanged),
          this,
          &LabelledComboBox::editTextChanged);
  connect(qobject_cast<QComboBox*>(m_widget),
          qOverload<int>(&QComboBox::highlighted),
          this,
          &LabelledComboBox::highlighted);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
  connect(qobject_cast<QComboBox*>(m_widget),
          qOverload<const QString&>(&QComboBox::textActivated),
          this,
          &LabelledComboBox::textActivated);
#else
  connect(reinterpret_cast<QComboBox*>(m_widget),
          qOverload<const QString&>(&QComboBox::activated),
          this,
          &LabelledComboBox::textActivated);
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
  connect(qobject_cast<QComboBox*>(m_widget),
          qOverload<const QString&>(&QComboBox::textHighlighted),
          this,
          &LabelledComboBox::textHighlighted);
#else
  connect(reinterpret_cast<QComboBox*>(m_widget),
          qOverload<const QString&>(&QComboBox::highlighted),
          this,
          &LabelledComboBox::textHighlighted);
#endif
}

/*====================================================================*/
