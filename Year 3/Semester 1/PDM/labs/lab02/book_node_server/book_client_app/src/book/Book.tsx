import React, { memo } from 'react';
import {IonCheckbox, IonItem, IonLabel} from '@ionic/react';
import { getLogger } from '../core';
import { BookProps } from './BookProps';

const log = getLogger('Item');

interface BookPropsExt extends BookProps {
    onEdit: (id?: string) => void;
}

const Book: React.FC<BookPropsExt> = ({id, name, pageCount, dateAdded, alreadyRead, onEdit}) => {
    const formattedDate = new Date(dateAdded).toLocaleDateString();

    return (
        <IonItem onClick={() => onEdit(id)}>
            <IonLabel>{name}</IonLabel>
        </IonItem>
    );
};

export default memo(Book);
