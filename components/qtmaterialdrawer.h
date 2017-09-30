#ifndef QTMATERIALDRAWER_H
#define QTMATERIALDRAWER_H

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialDrawerPrivate;
class QtMaterialDrawerStateMachine;

class QtMaterialDrawer : public QtMaterialOverlayWidget
{
    Q_OBJECT

public:
    explicit QtMaterialDrawer(QWidget *parent = 0);
    ~QtMaterialDrawer();

    void setDrawerWidth(int width);
    int drawerWidth() const;

    void setDrawerLayout(QLayout *layout);
    QLayout *drawerLayout() const;

protected slots:
    void openDrawer();
    void closeDrawer();

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    QRect overlayGeometry() const Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialDrawerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialDrawer)
    Q_DECLARE_PRIVATE(QtMaterialDrawer)
};

#endif // QTMATERIALDRAWER_H
