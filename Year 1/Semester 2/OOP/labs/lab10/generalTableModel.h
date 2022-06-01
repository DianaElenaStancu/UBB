//
// Created by Diana-Elena Stancu on 01/06/2022.
//

#ifndef LAB10_GENERALTABLEMODEL_H
#define LAB10_GENERALTABLEMODEL_H

#include <vector>
#include <qabstractitemview.h>
#include "domain.h"

using std::vector;

class GeneralTableModel : public QAbstractTableModel {
private:
    vector<Activitate> activitati;
public:

    GeneralTableModel(const vector <Activitate>& activitati);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    QVariant data(const QModelIndex& parent, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setActivitati(const vector<Activitate>& activitati);
};


#endif //LAB10_GENERALTABLEMODEL_H
