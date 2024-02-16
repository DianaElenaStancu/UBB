import React from 'react';
import { IonItem, IonLabel } from '@ionic/react';
import { getLogger } from '../core';
import { ItemProps } from './ItemProps';

const log = getLogger('Item');

interface ItemPropsExt extends ItemProps {
    onEdit: (_id?: string) => void;
}

const Item: React.FC<ItemPropsExt> = ({ _id, name, pageCount, dateAdded, alreadyRead, onEdit }) => {
    return (
        <IonItem onClick={() => onEdit(_id)}>
            <IonLabel>{name}</IonLabel>
            <IonLabel>{dateAdded.toString().substring(0,10)}</IonLabel>
            <IonLabel>{pageCount}</IonLabel>
            <IonLabel>{alreadyRead.toString()}</IonLabel>
        </IonItem>
    );
};

export default Item;
