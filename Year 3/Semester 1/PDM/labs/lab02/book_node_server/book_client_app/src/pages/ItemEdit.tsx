import React, { useContext, useEffect, useState } from 'react';
import {
    IonButton,
    IonButtons, IonCheckbox,
    IonContent, IonDatetime,
    IonHeader,
    IonInput,
    IonLoading,
    IonPage,
    IonTitle,
    IonToolbar
} from '@ionic/react';
import { getLogger } from '../core';
import { ItemContext } from './ItemProvider';
import { RouteComponentProps } from 'react-router';
import { ItemProps } from './ItemProps';

const log = getLogger('ItemEdit');

interface ItemEditProps extends RouteComponentProps<{
    id?: string;
}> {}

const ItemEdit: React.FC<ItemEditProps> = ({ history, match }) => {
    const { items, saving, savingError, saveItem } = useContext(ItemContext);
    const [name, setName] = useState('');
    const [pageCount, setPageCount] = useState('');
    const [dateAdded, setDateAdded] = useState(Date.now().toString());
    const [alreadyRead, setAlreadyRead] = useState<Boolean>(false);
    const [item, setItem] = useState<ItemProps>();

    useEffect(() => {
        log('useEffect');
        const routeId = match.params.id || '';
        const item = items?.find(it => it._id === routeId);
        setItem(item);
        if (item) {
            setName(item.name);
            setPageCount(item.pageCount.toString());
            setDateAdded(item.dateAdded.toString());
            setAlreadyRead(item.alreadyRead);
        }
    }, [match.params.id, items]);
    const handleSave = () => {
        const editedItem = item ? { ...item, name, pageCount: Number.parseInt(pageCount), dateAdded: new Date(dateAdded), alreadyRead: Boolean(alreadyRead) } : { name, pageCount: Number.parseInt(pageCount), dateAdded: new Date(dateAdded), alreadyRead: Boolean(alreadyRead) };
        saveItem && saveItem(editedItem).then(() => history.goBack());
    };
    log('render');
    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Edit</IonTitle>
                    <IonButtons slot="end">
                        <IonButton onClick={handleSave}>
                            Save
                        </IonButton>
                    </IonButtons>
                </IonToolbar>
            </IonHeader>
            <IonContent>
                <IonInput label={"Name"} value={name} onIonChange={e => {setName(e.detail.value || '')}} />
                <IonInput label={"Page count"} value={pageCount} onIonChange={e => {
                    if(Number.parseInt(e.detail.value || '').toString()!='NaN' && Number.parseInt(e.detail.value || '').toString().length==(e.detail.value || '').length){
                        setPageCount(Number.parseInt(e.detail.value || '').toString() || '')
                    }}}/>
                <IonCheckbox title={"Already read"} checked={alreadyRead == true} value={alreadyRead} onIonChange={e => setAlreadyRead(e.detail.checked == true)}>Watched</IonCheckbox>
                <IonDatetime size={"cover"}  presentation="date" value={dateAdded} onIonChange={e => setDateAdded(e.detail.value || '')}><span slot={"title"}>Select the date</span></IonDatetime>
                <IonLoading isOpen={saving} />
                {savingError && (
                    <div>{savingError.message || 'Failed to save item'}</div>
                )}
            </IonContent>
        </IonPage>
    );
};

export default ItemEdit;
