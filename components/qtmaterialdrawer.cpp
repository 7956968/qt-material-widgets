#include "qtmaterialdrawer.h"
#include "qtmaterialdrawer_p.h"
#include <QPainter>
#include <QEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLayout>
#include <QLinearGradient>
#include <QtWidgets/QVBoxLayout>
#include "qtmaterialdrawer_internal.h"

QtMaterialDrawerPrivate::QtMaterialDrawerPrivate(QtMaterialDrawer *q)
    : q_ptr(q),
      stateMachine(new QtMaterialDrawerStateMachine(q)),
      window(new QWidget),
      width(250)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(window);

    q->setLayout(layout);
    q->setFixedWidth(width+16);

    stateMachine->start();

    QCoreApplication::processEvents();
}

QtMaterialDrawer::QtMaterialDrawer(QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      d_ptr(new QtMaterialDrawerPrivate(this))
{
}

QtMaterialDrawer::~QtMaterialDrawer()
{
}

void QtMaterialDrawer::setDrawerWidth(int width)
{
    Q_D(QtMaterialDrawer);

    d->width = width;
    d->stateMachine->updatePropertyAssignments();
    setFixedWidth(width+16);
}

int QtMaterialDrawer::drawerWidth() const
{
    Q_D(const QtMaterialDrawer);

    return d->width;
}

void QtMaterialDrawer::setDrawerLayout(QLayout *layout)
{
    Q_D(QtMaterialDrawer);

    d->window->setLayout(layout);
}

QLayout *QtMaterialDrawer::drawerLayout() const
{
    Q_D(const QtMaterialDrawer);

    return d->window->layout();
}

void QtMaterialDrawer::openDrawer()
{
    Q_D(QtMaterialDrawer);

    emit d->stateMachine->enterOpenedState();
}

void QtMaterialDrawer::closeDrawer()
{
    Q_D(QtMaterialDrawer);

    emit d->stateMachine->enterClosedState();
}

bool QtMaterialDrawer::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type) {
        QLayout *t = layout();
        if (t && 16 != t->contentsMargins().right()) {
            t->setContentsMargins(0, 0, 16, 0);
        }
    }
    return QtMaterialOverlayWidget::eventFilter(obj, event);
}

void QtMaterialDrawer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.drawRect(rect().adjusted(0, 0, -16, 0));

    QLinearGradient gradient(QPointF(width()-16, 0), QPointF(width(), 0));
    gradient.setColorAt(0, QColor(0, 0, 0, 80));
    gradient.setColorAt(0.5, QColor(0, 0, 0, 20));
    gradient.setColorAt(1, QColor(0, 0, 0, 0));
    painter.setBrush(QBrush(gradient));

    painter.drawRect(width()-16, 0, 16, height());
}

QRect QtMaterialDrawer::overlayGeometry() const
{
    Q_D(const QtMaterialDrawer);

    return QtMaterialOverlayWidget::overlayGeometry().translated(d->stateMachine->offset(), 0);
}
