#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum { INDEX_NORMAL = 0, INDEX_HOVER, INDEX_PRESSED, INDEX_FOCUS, INDEX_CHECKED, INDEX_DISABLED };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onSetStackWidgetToQPushBtn();
    void onSetStackWidgetToQToolBtn();
    void onClickedOpenImg();
    void updateStyleSheet(QWidget *w, const QString &styleSheet);
    void updateStyleSheetNormal(const QString &styleSheet);
    void updateStyleSheetHover(const QString &styleSheet);
    void updateStyleSheetPressed(const QString &styleSheet);
    void updateStyleSheetFocus(const QString &styleSheet);
    void updateStyleSheetChecked(const QString &styleSheet);
    void updateStyleSheetDisabled(const QString &styleSheet);

private:
    Ui::MainWindow *ui;

    QVector<QString> mCssBlocks;
};

#endif // MAINWINDOW_H
