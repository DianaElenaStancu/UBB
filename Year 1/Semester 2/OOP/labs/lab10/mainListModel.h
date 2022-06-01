//
// Created by Diana-Elena Stancu on 01/06/2022.
//

#ifndef LAB10_MAINLISTMODEL_H
#define LAB10_MAINLISTMODEL_H
#include <qabstractitemview.h>
#include <vector>
#include "domain.h"
#include <qobject.h>

using std::vector;

class MainListModel : public QAbstractListModel {
private:
    vector<Activitate> activitati;
public:
    MainListModel(const vector<Activitate>& activitati);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void setActivitati(const vector<Activitate>& activitati);
};

#endif //LAB10_MAINLISTMODEL_H
