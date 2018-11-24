#ifndef MOUSEMEMORY_H
#define MOUSEMEMORY_H

#include <QObject>
#include <QDebug>
#include <QPoint>
#include <tuple>
#include <vector>

class mousememory : public QObject
{
    Q_OBJECT
    std::vector<std::tuple<int, int> > v;
public:
    explicit mousememory(QObject *parent = nullptr);

    Q_INVOKABLE void test();
    Q_INVOKABLE void add(int x, int y);
    Q_INVOKABLE void print();

signals:

public slots:
};

#endif // MOUSEMEMORY_H
