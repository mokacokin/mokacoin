#include "lockmonthfield.h"

#include "guiconstants.h"

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QDoubleSpinBox>
#include <QApplication>
#include <qmath.h> // for qPow()

LockMonthField::LockMonthField(QWidget *parent):
        QWidget(parent), amount(0)
{
    amount = new QDoubleSpinBox(this);
    amount->setLocale(QLocale::c());
    amount->setDecimals(0);
    amount->installEventFilter(this);
    amount->setMaximumWidth(170);
    amount->setMaximum(1200);
    amount->setMinimum(1);
    amount->setSingleStep(1);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(amount);
    layout->addStretch(1);
    layout->setContentsMargins(0,0,0,0);

    setLayout(layout);

    setFocusPolicy(Qt::TabFocus);
    setFocusProxy(amount);

    // If one if the widgets changes, the combined content changes as well
    connect(amount, SIGNAL(valueChanged(QString)), this, SIGNAL(textChanged()));
}

void LockMonthField::setText(const QString &text)
{
    if (text.isEmpty())
        amount->clear();
    else
        amount->setValue(text.toDouble());
}

void LockMonthField::clear()
{
    amount->clear();
}

bool LockMonthField::validate()
{
    bool valid = true;
    if (amount->value() <= 0 || amount->value() > 1200)
        valid = false;

    setValid(valid);

    return valid;
}

void LockMonthField::setValid(bool valid)
{
    if (valid)
        amount->setStyleSheet("");
    else
        amount->setStyleSheet(STYLE_INVALID);
}

QString LockMonthField::text() const
{
    if (amount->text().isEmpty())
        return QString();
    else
        return amount->text();
}

bool LockMonthField::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusIn)
    {
        // Clear invalid flag on focus
        setValid(true);
    }
    else if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Comma)
        {
            // Translate a comma into a period
            QKeyEvent periodKeyEvent(event->type(), Qt::Key_Period, keyEvent->modifiers(), ".", keyEvent->isAutoRepeat(), keyEvent->count());
            qApp->sendEvent(object, &periodKeyEvent);
            return true;
        }
    }
    return QWidget::eventFilter(object, event);
}

QWidget *LockMonthField::setupTabChain(QWidget *prev)
{
    QWidget::setTabOrder(prev, amount);
    return amount;
}

int LockMonthField::value(bool *valid_out) const
{
    int val_out = text().toInt();
    if(valid_out)
    {
        *valid_out = true;
    }
    return val_out;
}

void LockMonthField::setValue(int value)
{
    setText(QString::number(value));
}
