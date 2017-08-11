#ifndef STYLESHEETBLOCKWIDGET_H
#define STYLESHEETBLOCKWIDGET_H

#include <QWidget>

class CssBlock;
class QLineEdit;

namespace Ui {
class StyleSheetBlockWidget;
}

class StyleSheetBlockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StyleSheetBlockWidget(QWidget *parent = 0);
    void setBlockName(const QString& name);
    QString getBlockName() const;
    ~StyleSheetBlockWidget();

signals:
    void styleSheetChanged(QWidget* self, const QString& styleSheet);

public slots:
    void onUpdateStyleSheet();

private:
    void getDataFromUi();
    void notify();

    void getFromUiBorderColor();
    void getFromUiBorderStyle();
    void getFromUiBorderWidth();
    void getFromUiBorderRadius();
    void getFromUiTextPadding();
    void getFromUiTextAlign();
    void getFromUiTextColor();
    void getFromUiBgColor();
    void getFromUiMinSize();
    void getFromUiMaxSize();
    void initHexLineEditor(QLineEdit *edit);

private:
    Ui::StyleSheetBlockWidget *ui;

    CssBlock* mCssBlock;
};

#endif // STYLESHEETBLOCKWIDGET_H
