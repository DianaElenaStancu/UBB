import React, { useCallback, useContext, useEffect, useState, useRef  } from 'react';
import {
  IonButton, IonButtons, IonContent, IonHeader, IonInput, IonLoading, IonPage,
  IonTitle, IonToolbar, IonBackButton, IonLabel, IonDatetime, IonSelect,
  IonSelectOption, IonCheckbox, IonFab, IonFabButton,
  IonIcon, IonGrid, IonRow, IonCol, IonImg, IonActionSheet, IonItem,
  createAnimation,
  IonModal,  
} from '@ionic/react';
import { getLogger } from '../core';
import { RouteComponentProps } from 'react-router';
import { BookContext } from './BookProvider';
import { BookProps } from './BookProps';
import styles from './styles.module.css';

import {Photo, usePhotoGallery} from "../pages/usePhotoGallery";
import {useMyLocation} from "../pages/useMyLocation";
import {MyMap} from "../pages/MyMap";
import {camera, trash} from "ionicons/icons";

const log = getLogger('EditLogger');

interface BookEditProps extends RouteComponentProps<{
  id?: string;
}> {}

export const BookEdit: React.FC<BookEditProps> = ({ history, match }) => {      
  log("book edit here");
  const { books, updating, updateError, updateBook, deleteBook } = useContext(BookContext);
  const [title, setTitle] = useState('');
  const [launchDate, setLaunchDate] = useState<Date>(new Date(Date.now()));
  const [publisher, setPublisher] = useState('');
  const [lastVersion, setLastVersion] = useState("");
  const [url, setUrl] = useState("");
  const [authors, setAuthors] = useState<string[]>([]);
  const [totalReleases, setTotalReleases] = useState(0);
  const [isRead, setIsRead] = useState(false);
  const [bookToUpdate, setBookToUpdate] = useState<BookProps>();

  const {photos, takePhoto, deletePhoto} = usePhotoGallery();

  const [showStoredPictures, setShowStoredPictures] = useState<boolean>(false);
  const [webViewPath, setWebViewPath] = useState('');  
  const [photoToDelete, setPhotoToDelete] = useState<Photo>();

  const [currentLatitude, setCurrentLatitude] = useState<number | undefined>(undefined);
  const [currentLongitude, setCurrentLongitude] = useState<number | undefined>(undefined);  

  const photoStyle = { width: '30%', margin: "0 0 0 35%" };

  useEffect(() => {
    const routeId = match.params.id || '';
    console.log("BookEdit use effect");
    console.log(routeId);
    //const idNumber = parseInt(routeId);
    const book = books?.find(it => it._id === routeId);
    setBookToUpdate(book);
    if(book){
      setTitle(book.title);   
      setAuthors(book.authors);
      setLaunchDate(book.launchDate);
      setIsRead(book.isRead);
      setLastVersion(book.lastVersion);
      setPublisher(book.publisher);
      setWebViewPath(book.webViewPath || "");
      log("LOADED!!!")
      log(book);
      setCurrentLatitude(book.latitude || 0);
      setCurrentLongitude(book.longitude || 0);
      setUrl(book.url);   
    }
  }, [match.params.id, books]);

  const handleUpdate = useCallback(() => {
    log(`ULL ${currentLatitude} ${currentLongitude}`);
    const editedBook ={ ...bookToUpdate, title, launchDate, publisher, lastVersion, url, authors, totalReleases, isRead, 
      webViewPath, 
      latitude:currentLatitude, longitude:currentLongitude };
    
    log(editedBook);
    console.log(updateBook);
    updateBook && updateBook(editedBook).then(() => history.goBack());
  }, [bookToUpdate, updateBook, title, launchDate, publisher, lastVersion, url, authors, totalReleases, isRead, history,
    webViewPath, currentLatitude, currentLongitude
  ]);


  async function handlePhotoChange() {
    const image = await takePhoto();
    //log(`vw ===== ${image}`);
    if (!image) {
        setWebViewPath('');
    } else {
        setWebViewPath(image);
    }
  } 

  useEffect(simpleAnimation, []);


  const modalEl = useRef<HTMLIonModalElement>(null);
  const closeModal = () => {
    modalEl.current?.dismiss();
  };


  const enterAnimation = (baseEl: HTMLElement) => {
    const root = baseEl.shadowRoot!;

    const backdropAnimation = createAnimation()
      .addElement(root.querySelector('ion-backdrop')!)
      .fromTo('opacity', '0.01', 'var(--backdrop-opacity)');

    const wrapperAnimation = createAnimation()
      .addElement(root.querySelector('.modal-wrapper')!)
      .duration(2000)
      .keyframes([
        { offset: 0, opacity: '0', transform: 'scale(0)' },
        { offset: 0.9, opacity: '0.7', transform: 'scale(1.3)' },
        { offset: 1, opacity: '0.99', transform: 'scale(1)' },
      ]);

    return createAnimation()
      .addElement(baseEl)
      .easing('ease-out')
      .duration(500)
      .addAnimation([backdropAnimation, wrapperAnimation]);
  };
  const leaveAnimation = (baseEl: HTMLElement) => {
    return enterAnimation(baseEl).direction('reverse');
  };   

  log("render BookEdit")
  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
        <IonButtons slot="start">
            <IonBackButton></IonBackButton>
          </IonButtons>
          <IonTitle>Edit</IonTitle>
          <IonButtons slot="end">
            <IonButton onClick={handleUpdate}>
              Update
            </IonButton>            
          </IonButtons>
        </IonToolbar>
      </IonHeader>            
      <IonContent>
          <br/>
          <br/>

          <IonButton id="modal-trigger">Present Modal</IonButton>
          <IonModal trigger="modal-trigger" ref={modalEl} enterAnimation={enterAnimation} leaveAnimation={leaveAnimation}>
            <IonHeader>
              <IonToolbar>
                <IonTitle>Modal</IonTitle>
                <IonButtons slot="end">
                  <IonButton onClick={closeModal}>Close</IonButton>
                </IonButtons>
              </IonToolbar>
            </IonHeader>
            <IonContent className="ion-padding">Modal Content</IonContent>
          </IonModal>

        <br/>
        <IonLabel><b>Title</b></IonLabel>        

        <IonInput className="square-a" value={title} onIonChange={e => setTitle(e.detail.value || '')} />
        <br/>
        <IonLabel><b>Authors</b> (separated by ",")</IonLabel>
        <IonInput value={authors.join(",")} onIonChange={e => setAuthors((e.detail.value || '').split(",").filter(x=>x!=""))} />
        <br/>
        <IonLabel><b>Launch Date</b></IonLabel>
        <IonDatetime presentation="date" value={new Date(launchDate).toISOString()} onIonChange={e=>{ setLaunchDate(new Date(Date.parse(e.detail.value?.toString() || new Date(Date.now()).toString())))}}/>
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


        {showStoredPictures &&
        <div>
            <IonGrid>
                <IonRow>
                    {photos.map((photo, index) => (
                        <IonCol size="6" key={index}>
                            <IonImg onClick={() => setPhotoToDelete(photo)}
                                    src={photo.webviewPath}/>
                        </IonCol>
                    ))}
                </IonRow>
            </IonGrid>
            <IonActionSheet
                isOpen={!!photoToDelete}
                buttons={[{
                    text: 'Delete',
                    role: 'destructive',
                    icon: trash,
                    handler: () => {
                        if (photoToDelete) {
                            deletePhoto(photoToDelete);
                            setPhotoToDelete(undefined);
                        }
                    }
                }, {
                    text: 'Cancel',
                    icon: 'close',
                    role: 'cancel'
                }]}
                onDidDismiss={() => setPhotoToDelete(undefined)}
            />
        </div>}

        {webViewPath && (<img style={photoStyle} onClick={handlePhotoChange} src={webViewPath} width={'200px'} height={'200px'}/>)}
        {!webViewPath && (
                    <IonFab vertical="bottom" horizontal="center" slot="fixed">
                        <IonFabButton onClick={handlePhotoChange}>
                            <IonIcon icon={camera}/>
                        </IonFabButton>
        </IonFab>)}
          <div>                                
            <MyMap
                lat={currentLatitude}
                lng={currentLongitude}
                onCoordsChanged={(elat, elng)=>{
                  log(`HAHA ${elat} ${elng}`)
                  setCurrentLatitude(elat);
                  setCurrentLongitude(elng);
                }}                      
            />            
          </div>

        </IonContent>
    </IonPage>
  );

  function simpleAnimation() {
    const el = document.querySelector('.square-a');
    if (el) {
        const animation = createAnimation()
            .addElement(el)
            .duration(1000)
            .direction('alternate')
            .iterations(Infinity)
            .keyframes([
                { offset: 0, marginLeft:"0px", background: 'pink'},
                { offset: 0.5, marginLeft:"20px", background: 'yellow'},
                { offset: 1, marginLeft:"0px", background: 'lime'}
            ]);
        animation.play();
    }        
}

}
