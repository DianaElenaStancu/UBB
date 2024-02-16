import React, { useCallback, useContext, useEffect, useState } from 'react';
import {
  IonButton,
  IonButtons,
  IonContent,
  IonHeader,
  IonInput,
  IonLoading,
  IonPage,
  IonTitle,
  IonToolbar,
  IonBackButton,
  IonLabel,
  IonDatetime,
  IonSelect,
  IonSelectOption,
  IonCheckbox
} from '@ionic/react';
import { getLogger } from '../core';
import { RouteComponentProps } from 'react-router';
import { BookContext } from './BookProvider';
import { BookProps } from './BookProps';
import styles from './styles.module.css';

const log = getLogger('SaveLogger');

interface BookEditProps extends RouteComponentProps<{
  id?: string;
}> {}

export const BookAdd: React.FC<BookEditProps> = ({ history, match }) => {
  log("book add here");
  const { books, updating, updateError, addBook } = useContext(BookContext);
  const [title, setTitle] = useState('');
  const [launchDate, setLaunchDate] = useState(new Date());
  const [publisher, setPublisher] = useState('');
  const [lastVersion, setLastVersion] = useState("");
  const [url, setUrl] = useState("");
  const [authors, setAuthors] = useState<string[]>([]);
  const [totalReleases, setTotalReleases] = useState(0);
  const [isRead, setIsRead] = useState(false);

  
  const [bookToUpdate, setBookToUpdate] = useState<BookProps>();

  const handleAdd = useCallback(() => {
    const editedBook ={ ...bookToUpdate, title, launchDate, publisher, lastVersion, url, authors, totalReleases, isRead };
    //console.log(duration);
    //console.log(editedBook);
    log(editedBook);
    console.log(updateError);
    addBook && addBook(editedBook).then(() => history.goBack());
  }, [bookToUpdate, addBook, title, launchDate, publisher, lastVersion, url, authors, totalReleases, isRead , history]);  

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
        <IonButtons slot="start">
            <IonBackButton></IonBackButton>
          </IonButtons>
          <IonTitle>Edit</IonTitle>
          <IonButtons slot="end">
            <IonButton onClick={handleAdd}>
              Add
            </IonButton>
          </IonButtons>
        </IonToolbar>
      </IonHeader>
      {/*<IonContent>
        <IonInput label="Title:" className={styles.customInput} placeholder="New Title" value={title} onIonInput={e => setTitle(prev => e.detail.value || '')} />
        <IonInput label="Artist:" className={styles.customInput} placeholder="New Artist" value={artist} onIonInput={e => setArtist(prev => e.detail.value || '')} />
        <IonInput label="Duration:" className={styles.customInput} placeholder="New duration" value={duration} onIonInput={e => e.detail.value ? setDuration(prev => e.detail.value!) : setDuration('') }/>
        <IonInput label="DateOfRelease:" className={styles.customInput} placeholder="Choose date" value={new Date(date).toDateString()} />
        <IonDatetime
                onIonChange={(e) => dateChanged(e.detail.value)}>
        </IonDatetime>
        <IonInput label="Featured Artists:" className={styles.customInput} placeholder="True/False" value={option==true ? 'True' : 'False'} />
        <IonSelect value={option} onIonChange={e => setOption(e.detail.value)}>
          <IonSelectOption value={true}>
            {'True'}
          </IonSelectOption>
          <IonSelectOption value={false}>
            {'False'}
          </IonSelectOption>
        </IonSelect>
        <IonLoading isOpen={updating} />
        {updateError && (
          <div className={styles.errorMessage}>{updateError.message || 'Failed to save item'}</div>
        )}
        </IonContent>*/}
        <IonContent>        
        <br/>
        <IonLabel><b>Title</b></IonLabel>
        <IonInput value={title} onIonChange={e => setTitle(e.detail.value || '')} />
        <br/>
        <IonLabel><b>Authors</b> (separated by ",")</IonLabel>
        <IonInput value={authors.join(",")} onIonChange={e => setAuthors((e.detail.value || '').split(",").filter(x=>x!=""))} />
        <br/>
        <IonLabel><b>Launch Date</b></IonLabel>
        <IonDatetime presentation="date" value={launchDate.toString()} onIonChange={e=>{ setLaunchDate(new Date(Date.parse(e.detail.value?.toString() || new Date(Date.now()).toString())))}}/>
        <br/>
        <IonLabel><b>Publisher</b></IonLabel>
        <IonSelect value={publisher} onIonChange={e => setPublisher(e.detail.value || '')}>
          <IonSelectOption>Editura 1</IonSelectOption>          
          <IonSelectOption>Editura 2</IonSelectOption>
          <IonSelectOption>Editura 3</IonSelectOption>
          <IonSelectOption>Editura 4</IonSelectOption>
          <IonSelectOption>Editura 5</IonSelectOption>
        </IonSelect> 
        <br/>
        <IonLabel><b>Last Version</b></IonLabel>
        <IonInput value={lastVersion} onIonChange={e => setLastVersion(e.detail.value || '')} />

        <br/>
        <IonLabel><b>Read</b></IonLabel>
        <IonCheckbox checked={isRead} onIonChange={e =>{ setIsRead(e.detail.checked) } } />        

        <br/>
        <IonLabel><b>Total Releases</b></IonLabel>
        <IonInput type="number" value={totalReleases} onIonChange={e => setTotalReleases(Number.parseInt(e.detail.value || "0"))} />

        <br/>
        <IonLabel><b>External link</b></IonLabel>
        <IonInput value={url} onIonChange={e => setUrl(e.detail.value || '')} />              

        <IonLoading isOpen={updating} />
        {updateError && (
          <div className={styles.errorMessage}>{updateError.message || 'Failed to update item'}</div>
        )}
      </IonContent>
    </IonPage>
  );
}
