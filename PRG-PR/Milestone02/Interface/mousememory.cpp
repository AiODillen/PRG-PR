#include "mousememory.h"
#include <vector>
#include <tuple>

using namespace std;

mousememory::mousememory(QObject *parent) : QObject(parent)
{

}

void mousememory::test()
{
    qDebug() << "hello World";
}

void mousememory::add(int x, int y)
{
    QPoint p(x, y);
    qDebug() << "adding" << p;
    v.push_back(make_tuple(x, y));
}

void mousememory::print()
{
    for (int i = 0; i < v.size(); i++)
            qDebug() << get<0>(v[i]) << " "
                 << get<1>(v[i]) << "\n";
}
