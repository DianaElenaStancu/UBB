import React, { useContext } from 'react';
import { RouteComponentProps } from 'react-router';
import {
    IonContent,
    IonFab,
    IonFabButton,
    IonHeader,
    IonIcon, IonLabel,
    IonList, IonListHeader, IonLoading,
    IonPage,
    IonTitle,
    IonToolbar
} from '@ionic/react';
import { add } from 'ionicons/icons';
import Book from './Book';
import { getLogger } from '../core';
import { BookContext } from './BookProvider';

const log = getLogger('BookList');

const BookList: React.FC<RouteComponentProps> = ({ history }) => {
    const { books, fetching, fetchingError } = useContext(BookContext);
    log('render');
    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>My bookshelf</IonTitle>
                </IonToolbar>
            </IonHeader>
            <IonContent>
                <IonLoading isOpen={fetching} message="Fetching items" />
                {books && (
                    <IonList>
                        {books.map(({ id, name, pageCount, dateAdded, alreadyRead}) =>
                            <Book key={id} id={id}
                                  name={name}
                                  pageCount={pageCount}
                                  dateAdded={dateAdded}
                                  alreadyRead={alreadyRead}
                                  onEdit={id => history.push(`/book/${id}`)}
                            />
                        )}
                    </IonList>
                )}
                {fetchingError && (
                    <div>{fetchingError.message || 'Failed to fetch books'}</div>
                )}
                <IonFab vertical="bottom" horizontal="end" slot="fixed">
                    <IonFabButton onClick={() => history.push('/book')}>
                        <IonIcon icon={add} />
                    </IonFabButton>
                </IonFab>
            </IonContent>
        </IonPage>
    );
};

export default BookList;
