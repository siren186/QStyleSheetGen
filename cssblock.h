#ifndef CSSBLOCK_H
#define CSSBLOCK_H

#include <QString>
#include <QMap>

class CssBlock
{
public:
    CssBlock(const QString& name)
    {
        setName(name);
    }

    QString getName() const
    {
        return mBlockName;
    }

    void setName(const QString& name)
    {
        mBlockName = name;
    }

    void addParam(const QString& key, const QString& value)
    {
        mParams[key] = value;
    }

    void addParam(const QString& key, const quint32& value)
    {
        mParams[key] = QString::number(value);
    }

    void addParam(const QString& key, const quint32& value, const QString& sufix)
    {
        mParams[key] = QString::number(value) + sufix;
    }

    void delParam(const QString& key)
    {
        QMap<QString, QString>::iterator it = mParams.find(key);
        if (it != mParams.end())
        {
            mParams.erase(it);
        }
    }

    bool isEmpty() const
    {
        return mParams.isEmpty();
    }

    QString toString() const
    {
        QString str = mBlockName + " {\n";

        for (QMap<QString, QString>::const_iterator it = mParams.constBegin(); it != mParams.constEnd(); ++it)
        {
            str = str + it.key() + ":" + it.value() + ";\n";
        }

        str += "}\n";

        return str;
    }

    void clearParams()
    {
        mParams.clear();
    }

private:
    QString mBlockName;
    QMap<QString, QString> mParams;
};

#endif // CSSBLOCK_H
