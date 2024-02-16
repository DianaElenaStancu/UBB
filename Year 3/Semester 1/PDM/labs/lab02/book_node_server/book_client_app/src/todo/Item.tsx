import React, { memo } from 'react';
import { IonItem, IonLabel } from '@ionic/react';
import { getLogger } from '../core';
import { ItemProps } from './ItemProps';

const log = getLogger('Item');

interface ItemPropsExt extends ItemProps {
  onEdit: (id?: string) => void;
}

const Item: React.FC<ItemPropsExt> = ({ id, text, onEdit }) => {
  return (
    <IonItem onClick={() => onEdit(id)}>
      <IonLabel>{text}</IonLabel>
    </IonItem>
  );
};

export default memo(Item);
