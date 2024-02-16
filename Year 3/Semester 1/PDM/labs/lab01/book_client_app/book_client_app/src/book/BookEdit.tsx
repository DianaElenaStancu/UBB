import React, {useCallback, useContext, useEffect, useState} from 'react';
import {
    IonButton,
    IonButtons, IonCheckbox,
    IonContent, IonDatetime,
    IonHeader,
    IonInput, IonLabel,
    IonLoading,
    IonPage, IonRow,
    IonTitle,
    IonToolbar
} from '@ionic/react';
import {getLogger} from '../core';
import {BookContext} from './BookProvider';
import {RouteComponentProps} from 'react-router';
import {BookProps} from './BookProps';

const log = getLogger('BookEdit');

interface BookEditProps extends RouteComponentProps<{
    id?: string;
}> {
}

const BookEdit: React.FC<BookEditProps> = ({history, match}) => {
    const {books, saving, fetching, savingError, saveBook} = useContext(BookContext);
    const [name, setName] = useState('');
    const [pageCount, setPageCount] = useState(0);
    const [dateAdded, setDateAdded] = useState(new Date());
    const [alreadyRead, setAlreadyRead] = useState(false);
    const [book, setBook] = useState<BookProps>();

    useEffect(() => {
        log('useEffect');
        const routeId = match.params.id || '';
        const book = books?.find(b => b.id === routeId);

        setBook(book);

        if (book) {
            setName(book.name);
            setPageCount(book.pageCount);
            setDateAdded(book.dateAdded);
            setAlreadyRead(book.alreadyRead);
        }
    }, [match.params.id, books]);

    const handleSave = useCallback(() => {
        const editedBook = book ? {...book, name, pageCount, dateAdded, alreadyRead} : {
            name,
            pageCount,
            dateAdded,
            alreadyRead
        };
        console.log(editedBook);
        saveBook && saveBook(editedBook).then(() => history.goBack());
    }, [book, saveBook, name, pageCount, alreadyRead, history]);

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
                <IonLoading isOpen={fetching} message="Fetching items" />
                <IonInput label="Book name: " type="text" value={name} onIonChange={e => setName(e.detail.value)}/>
                <IonInput label="Page count: " value={pageCount} type="number"
                          onIonChange={e => setPageCount(e.detail.value)}/>
                <IonInput label="Date added: " value={dateAdded} readonly/>
                {/*<IonDatetime presentation="date" preferWheel={true} value = {dateAdded} readonly></IonDatetime>*/}
                <IonCheckbox labelPlacement="start" checked={alreadyRead}
                             onIonChange={e => setAlreadyRead(e.detail.checked)}>Book already read:</IonCheckbox>
                <IonLoading isOpen={saving}/>
                {savingError && (
                    <div>{savingError.message || 'Failed to save book'}</div>
                )}
            </IonContent>
        </IonPage>
    );
};

export default BookEdit;
