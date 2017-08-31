#ifndef LOCKMONTHFIELD_H
#define LOCKMONTHFIELD_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QDoubleSpinBox;
QT_END_NAMESPACE

/** Widget for entering Mokacoin fee.
  */
class LockMonthField: public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int value READ value WRITE setValue NOTIFY textChanged USER true)

public:
    explicit LockMonthField(QWidget *parent = 0);

    int value(bool *valid=0) const;
    void setValue(int value);

    /** Mark current value as invalid in UI. */
    void setValid(bool valid);
    /** Perform input validation, mark field as invalid if entered value is not valid. */
    bool validate();

    /** Make field empty and ready for new input. */
    void clear();

    /** Qt messes up the tab chain by default in some cases (issue https://bugreports.qt-project.org/browse/QTBUG-10907),
        in these cases we have to set it up manually.
    */
    QWidget *setupTabChain(QWidget *prev);

signals:
    void textChanged();

protected:
    /** Intercept focus-in event and ',' key presses */
    bool eventFilter(QObject *object, QEvent *event);

private:
    QDoubleSpinBox *amount;

    void setText(const QString &text);
    QString text() const;
};

#endif // LOCKMONTHFIELD_H
