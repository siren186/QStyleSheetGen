#include <QDebug>
#include "stylesheetblockwidget.h"
#include "ui_stylesheetblockwidget.h"
#include "cssblock.h"

StyleSheetBlockWidget::StyleSheetBlockWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StyleSheetBlockWidget)
{
    ui->setupUi(this);
    mCssBlock = new CssBlock("QPushButton");

    initHexLineEditor(ui->borderColor);
    initHexLineEditor(ui->borderColorUp);
    initHexLineEditor(ui->borderColorDown);
    initHexLineEditor(ui->borderColorLeft);
    initHexLineEditor(ui->borderColorRight);
    initHexLineEditor(ui->textColor);
    initHexLineEditor(ui->bgColor);

    connect(ui->borderColorCtrl, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderStyleCtrl, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderWidthCtrl, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderRadiusCtrl, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->textPaddingCtrl, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->textAlignCtrl, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->textColorCtrl, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->bgColorCtrl, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->minSizeCtrl, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->maxSizeCtrl, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));

    connect(ui->simpleBorderStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderStyleUp, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderStyleDown, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderStyleLeft, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderStyleRight, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateStyleSheet()));

    connect(ui->simpleBorderWidth, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderWidthUp, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderWidthDown, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderWidthLeft, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderWidthRight, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));

    connect(ui->borderColor, SIGNAL(textChanged(QString)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderColorUp, SIGNAL(textChanged(QString)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderColorDown, SIGNAL(textChanged(QString)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderColorLeft, SIGNAL(textChanged(QString)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderColorRight, SIGNAL(textChanged(QString)), this, SLOT(onUpdateStyleSheet()));

    connect(ui->simpleBorderRadius, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderRadiusTopLeft, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderRadiusTopRight, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderRadiusBottomLeft, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->borderRadiusBottomRight, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));

    connect(ui->simpleTextPadding, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->textPaddingUp, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->textPaddingDown, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->textPaddingLeft, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->textPaddingRight, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));

    connect(ui->textColor, SIGNAL(textChanged(QString)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->bgColor, SIGNAL(textChanged(QString)), this, SLOT(onUpdateStyleSheet()));

    connect(ui->minWidth, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->minHeight, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->maxWidth, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
    connect(ui->maxHeight, SIGNAL(valueChanged(int)), this, SLOT(onUpdateStyleSheet()));
}

void StyleSheetBlockWidget::setBlockName(const QString &name)
{
    mCssBlock->setName(name);
}

QString StyleSheetBlockWidget::getBlockName() const
{
    return mCssBlock->getName();
}

StyleSheetBlockWidget::~StyleSheetBlockWidget()
{
    delete ui;
}

void StyleSheetBlockWidget::onUpdateStyleSheet()
{
    getDataFromUi();
    notify();
}

void StyleSheetBlockWidget::getDataFromUi()
{
    getFromUiBorderColor();
    getFromUiBorderStyle();
    getFromUiBorderWidth();
    getFromUiBorderRadius();
    getFromUiTextPadding();
    getFromUiTextAlign();
    getFromUiTextColor();
    getFromUiBgColor();
    getFromUiMinSize();
    getFromUiMaxSize();
}

void StyleSheetBlockWidget::notify()
{
    if (mCssBlock->isEmpty())
    {
        emit styleSheetChanged(this, "");
    }
    else
    {
        emit styleSheetChanged(this, mCssBlock->toString());
    }
}

void StyleSheetBlockWidget::getFromUiBorderColor()
{
    if (0 == ui->borderColorCtrl->currentText().compare("简单"))
    {
        uint color = ui->borderColor->text().toUInt(0, 16);
        mCssBlock->delParam("border-top-color");
        mCssBlock->delParam("border-bottom-color");
        mCssBlock->delParam("border-left-color");
        mCssBlock->delParam("border-right-color");
        mCssBlock->addParam("border-color", QString().sprintf("#%06x", color));
    }
    else if (0 == ui->borderColorCtrl->currentText().compare("复杂"))
    {
        uint up = ui->borderColorUp->text().toUInt(0, 16);
        uint down = ui->borderColorDown->text().toUInt(0, 16);
        uint left = ui->borderColorLeft->text().toUInt(0, 16);
        uint right = ui->borderColorRight->text().toUInt(0, 16);
        mCssBlock->delParam("border-color");
        mCssBlock->addParam("border-top-color", QString().sprintf("#%06x", up));
        mCssBlock->addParam("border-bottom-color", QString().sprintf("#%06x", down));
        mCssBlock->addParam("border-left-color", QString().sprintf("#%06x", left));
        mCssBlock->addParam("border-right-color", QString().sprintf("#%06x", right));
    }
    else
    {
        mCssBlock->delParam("border-color");
        mCssBlock->delParam("border-top-color");
        mCssBlock->delParam("border-bottom-color");
        mCssBlock->delParam("border-left-color");
        mCssBlock->delParam("border-right-color");
    }
}

void StyleSheetBlockWidget::getFromUiBorderStyle()
{
    QString text = ui->borderStyleCtrl->currentText();

    if (0 == text.compare("简单"))
    {
        mCssBlock->addParam("border-style", ui->simpleBorderStyle->currentText());
    }
    else if (0 == text.compare("复杂"))
    {
        mCssBlock->addParam("border-style"
                            , ui->borderStyleUp->currentText()
                            + " "
                            + ui->borderStyleRight->currentText()
                            + " "
                            + ui->borderStyleDown->currentText()
                            + " "
                            + ui->borderStyleLeft->currentText()
                            );
    }
    else
    {
        mCssBlock->delParam("border-style");
    }
}

void StyleSheetBlockWidget::getFromUiBorderWidth()
{
    QString text = ui->borderWidthCtrl->currentText();
    if (0 == text.compare("简单"))
    {
        mCssBlock->addParam("border-width", ui->simpleBorderWidth->value());
    }
    else if (0 == text.compare("复杂"))
    {
        mCssBlock->addParam("border-width", QString("%1px %2px %3px %4px")
                            .arg(ui->borderWidthUp->value())
                            .arg(ui->borderWidthRight->value())
                            .arg(ui->borderWidthDown->value())
                            .arg(ui->borderWidthLeft->value())
                            );
    }
    else
    {
        mCssBlock->delParam("border-width");
    }
}

void StyleSheetBlockWidget::getFromUiBorderRadius()
{
    QString text = ui->borderRadiusCtrl->currentText();
    if (0 == text.compare("简单"))
    {
        mCssBlock->delParam("border-top-left-radius");
        mCssBlock->delParam("border-top-right-radius");
        mCssBlock->delParam("border-bottom-left-radius");
        mCssBlock->delParam("border-bottom-right-radius");
        mCssBlock->addParam("border-radius", ui->simpleBorderRadius->value(), "px");
    }
    else if (0 == text.compare("复杂"))
    {
        mCssBlock->delParam("border-radius");
        mCssBlock->addParam("border-top-left-radius", ui->borderRadiusTopLeft->value(), "px");
        mCssBlock->addParam("border-top-right-radius", ui->borderRadiusTopRight->value(), "px");
        mCssBlock->addParam("border-bottom-left-radius", ui->borderRadiusBottomLeft->value(), "px");
        mCssBlock->addParam("border-bottom-right-radius", ui->borderRadiusBottomRight->value(), "px");
    }
    else
    {
        mCssBlock->delParam("border-radius");
        mCssBlock->delParam("border-top-left-radius");
        mCssBlock->delParam("border-top-right-radius");
        mCssBlock->delParam("border-bottom-left-radius");
        mCssBlock->delParam("border-bottom-right-radius");
    }
}

void StyleSheetBlockWidget::getFromUiTextPadding()
{
    QString text = ui->textPaddingCtrl->currentText();
    if (0 == text.compare("简单"))
    {
        mCssBlock->addParam("padding", ui->simpleTextPadding->value(), "px");
    }
    else if (0 == text.compare("复杂"))
    {
        mCssBlock->addParam("padding", QString("%1px %2px %3px %4px")
                            .arg(ui->textPaddingUp->value())
                            .arg(ui->textPaddingRight->value())
                            .arg(ui->textPaddingDown->value())
                            .arg(ui->textPaddingLeft->value())
                            );
    }
    else
    {
        mCssBlock->delParam("padding");
    }
}

void StyleSheetBlockWidget::getFromUiTextAlign()
{
    QString text = ui->textAlignCtrl->currentText();
    if (0 == text.compare("左对齐"))
    {
        mCssBlock->addParam("text-align", "left");
    }
    else if (0 == text.compare("右对齐"))
    {
        mCssBlock->addParam("text-align", "right");
    }
    else if (0 == text.compare("居中"))
    {
        mCssBlock->addParam("text-align", "center");
    }
    else
    {
        mCssBlock->delParam("text-align");
    }
}

void StyleSheetBlockWidget::getFromUiTextColor()
{
    if (0 == ui->textColorCtrl->currentText().compare("设置"))
    {
        uint color = ui->textColor->text().toUInt(0, 16);
        mCssBlock->addParam("color", QString().sprintf("#%06x", color));
    }
    else
    {
        mCssBlock->delParam("color");
    }
}

void StyleSheetBlockWidget::getFromUiBgColor()
{
    if (0 == ui->bgColorCtrl->currentText().compare("设置"))
    {
        uint color = ui->bgColor->text().toUInt(0, 16);
        mCssBlock->addParam("background", QString().sprintf("#%06x", color));
    }
    else
    {
        mCssBlock->delParam("background");
    }
}

void StyleSheetBlockWidget::getFromUiMinSize()
{
    if (0 == ui->minSizeCtrl->currentText().compare("设置"))
    {
        int width = ui->minWidth->value();
        int height = ui->minHeight->value();
        if (0 != width)
        {
            mCssBlock->addParam("min-width", width, "px");
        }
        else
        {
            mCssBlock->delParam("min-width");
        }

        if (0 != height)
        {
            mCssBlock->addParam("min-height", height, "px");
        }
        else
        {
            mCssBlock->delParam("min-height");
        }
    }
    else
    {
        mCssBlock->delParam("min-width");
        mCssBlock->delParam("min-height");
    }
}

void StyleSheetBlockWidget::getFromUiMaxSize()
{
    if (0 == ui->maxSizeCtrl->currentText().compare("设置"))
    {
        int width = ui->maxWidth->value();
        int height = ui->maxHeight->value();
        if (0 != width)
        {
            mCssBlock->addParam("max-width", width, "px");
        }
        else
        {
            mCssBlock->delParam("max-width");
        }

        if (0 != height)
        {
            mCssBlock->addParam("max-height", height, "px");
        }
        else
        {
            mCssBlock->delParam("max-height");
        }
    }
    else
    {
        mCssBlock->delParam("max-width");
        mCssBlock->delParam("max-height");
    }
}

void StyleSheetBlockWidget::initHexLineEditor(QLineEdit* edit)
{
    QRegExpValidator* validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,6}"), this);
    edit->setValidator(validator);
    edit->setText("000000");
}
