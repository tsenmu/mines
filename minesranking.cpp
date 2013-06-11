#include "minesranking.h"
#include "minesrankingitem.h"
#include <QFile>
#include <QDomDocument>
#include <QDebug>

MinesRanking::MinesRanking(QObject *parent) :
    QObject(parent)
{

}

void MinesRanking::addRankingItem(const MinesRankingItem& item)
{
    vector.push_back(item);
    qSort(vector.begin(), vector.end());
    while(vector.count() > 10)
    {
        vector.pop_back();
    }
}

void MinesRanking::clear()
{
    vector.clear();
}

int MinesRanking::count() const
{
    return vector.count();
}

const MinesRankingItem& MinesRanking::operator[] (int index) const
{
    return vector[index];
}

MinesRankingItem& MinesRanking::operator[](int index)
{
    return vector[index];
}
void MinesRanking::readRanking(const QString& fileName)
{
    QDomDocument doc("MINESRANKING");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList list = root.childNodes();
    clear();
    for(int i = 0; i < list.count(); ++i)
    {
        QDomNamedNodeMap atts = list.at(i).attributes();
        MinesRankingItem item;
        item.player = atts.namedItem("player").toAttr().value();
        item.score = atts.namedItem("score").toAttr().value().toInt();
        item.nRows = atts.namedItem("nRows").toAttr().value().toInt();
        item.nCols = atts.namedItem("nCols").toAttr().value().toInt();
        item.time = atts.namedItem("time").toAttr().value().toInt();
        item.mines = atts.namedItem("mines").toAttr().value().toInt();
        addRankingItem(item);
    }
}

void MinesRanking::writeRanking(const QString& fileName)
{
    QDomDocument doc("MINESRANKING");
    QDomElement root = doc.createElement("ranking");
    doc.appendChild(root);
    for(int i = 0; i < count(); ++i)
    {
        MinesRankingItem item = vector.at(i);
        QDomElement element = doc.createElement("entry");
        element.setAttribute("player", item.player);
        element.setAttribute("score", item.score);
        element.setAttribute("nRows", item.nRows);
        element.setAttribute("nCols", item.nCols);
        element.setAttribute("time", item.time);
        element.setAttribute("mines", item.mines);
        root.appendChild(element);
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }
    QTextStream stream(&file);
    doc.save(stream, 4);
    file.close();
}
