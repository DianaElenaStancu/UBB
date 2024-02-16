import React, { useContext, useEffect, useState } from 'react';
import { RouteComponentProps } from 'react-router';
import BookComponent from './BookComponent';
import { getLogger } from '../core';
import { BookContext } from './BookProvider';
import { IonContent, 
         IonHeader, 
         IonList, 
         IonLoading, 
         IonPage, 
         IonTitle, 
         IonToolbar,
         IonToast, 
         IonFab,
         IonFabButton,
         IonIcon,
         IonButton, 
         IonButtons,
         IonInfiniteScroll,
         IonInfiniteScrollContent,
         IonSearchbar,
         IonSelect, IonSelectOption } from '@ionic/react';

import { add } from 'ionicons/icons';
import { AuthContext } from '../auth';
import { NetworkState } from '../pages/NetworkState';
import { BookProps } from './BookProps';
import styles from "./styles.module.css";

const log = getLogger('BooksList');
const booksPerPage = 3;
const filterValues = ["IsRead", "IsClosedSource"];

export const BooksList: React.FC<RouteComponentProps> = ({ history }) => {
  const { books, fetching, fetchingError, successMessage, closeShowSuccess } = useContext(BookContext);
  const { logout } = useContext(AuthContext);
  const [isOpen, setIsOpen]= useState(false);
  const [index, setIndex] = useState<number>(0);
  const [booksAux, setBooksAux] = useState<BookProps[] | undefined>([]);
  const [more, setHasMore] = useState(true);
  const [searchText, setSearchText] = useState('');
  const [filter, setFilter] = useState<string | undefined>(undefined);
  //const [hasFetched, setHasFetched] = useState(false);

  useEffect(()=>{
    if(fetching) setIsOpen(true);
    else setIsOpen(false);
  }, [fetching]);

  log('render');
  console.log(books);

  function handleLogout(){
    logout?.();
    history.push('/login');
  }

  //pagination
  useEffect(()=>{
    fetchData();
  }, [books]);

  // searching
  useEffect(()=>{
    if (searchText === "") {
      setBooksAux(books);
    }
    if (books && searchText !== "") {
      setBooksAux(books.filter(book => book.authors!.some((a)=>a.toLowerCase().includes(searchText.toLowerCase()))));
    }
  }, [searchText]);

   // filtering
   useEffect(() => {
    if (books && filter) {
        setBooksAux(books.filter(book => {
            if (filter === "IsRead")
                return book.isRead === true;
            else
                return book.isRead === false;
        }));
    }
}, [filter]);

  function fetchData() {
    if(books){
      const newIndex = Math.min(index + booksPerPage, books.length);
      if( newIndex >= books.length){
          setHasMore(false);
      }
      else{
          setHasMore(true);
      }
      setBooksAux(books.slice(0, newIndex));
      setIndex(newIndex);
    }
  }

  async function searchNext($event: CustomEvent<void>){
    await fetchData();
    await ($event.target as HTMLIonInfiniteScrollElement).complete();
  }

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonTitle>Bookshelf</IonTitle>
          <IonSelect 
            className={styles.selectBar} 
            slot="end" 
            value={filter} 
            placeholder="Filter" 
            onIonChange={(e) => setFilter(e.detail.value)}>
                        {filterValues.map((each) => (
                            <IonSelectOption key={each} value={each}>
                                {each}
                            </IonSelectOption>
                        ))}
          </IonSelect>
          <NetworkState />
          <IonSearchbar className={styles.customSearchBar} placeholder="Search by author" value={searchText} debounce={200} onIonInput={(e) => {
                        setSearchText(e.detail.value!);
                    }} slot="secondary">
          </IonSearchbar>
          <IonButtons slot='end'>
             <IonButton onClick={handleLogout}>Logout</IonButton>
          </IonButtons>
        </IonToolbar>
      </IonHeader>
      <IonContent fullscreen>
        <IonLoading isOpen={isOpen} message="Fetching books..." />
        {booksAux && (
          <IonList>
            {booksAux.map(book => 
              <BookComponent 
                key={book._id} 
                _id={book._id} 
                title={book.title} 
                onEdit={id => history.push(`/book/${id}`)}
                launchDate={book.launchDate} 
                publisher={book.publisher} 
                lastVersion={book.lastVersion} 
                url={book.url} 
                isRead={book.isRead}
                isNotSaved={book.isNotSaved}
                webViewPath={book.webViewPath}
                authors = {book.authors} totalReleases={book.totalReleases}/>           
            )}
          </IonList>
        )}
        <IonInfiniteScroll threshold="100px" disabled={!more} onIonInfinite={(e:CustomEvent<void>) => searchNext(e)} >
          <IonInfiniteScrollContent loadingText="Loading more books..." >
          </IonInfiniteScrollContent>
        </IonInfiniteScroll>
        {fetchingError && (
          <div>{fetchingError.message || 'Failed to fetch books'}</div>
        )}
        <IonFab vertical="bottom" horizontal="end" slot="fixed">
          <IonFabButton onClick={() => history.push('/book')}>
            <IonIcon icon={add} />
          </IonFabButton>
        </IonFab>
        <IonToast
          isOpen={!!successMessage}
          message={successMessage}
          position='bottom'
          buttons={[
            {
              text: 'Dismiss',
              role: 'cancel',
              handler: () => {
                console.log('More Info clicked');
              },
            }]}
          onDidDismiss={closeShowSuccess}
          duration={5000}
          />
      </IonContent>
    </IonPage>
  );
};