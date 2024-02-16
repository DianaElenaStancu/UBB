import React, {useCallback, useContext, useEffect, useState} from 'react';
import { RouteComponentProps } from 'react-router';
import {
    IonContent,
    IonFab,
    IonFabButton,
    IonHeader,
    IonIcon,
    IonItem,
    IonLabel,
    IonList,
    IonLoading,
    IonPage,
    IonSelectOption,
    IonSelect,
    IonTitle,
    IonToolbar,
    IonSearchbar,
    IonAlert,
    IonRefresher,
    IonRefresherContent,
    IonInfiniteScroll,
    IonInfiniteScrollContent,
    IonCard
} from '@ionic/react';
import {add, logOut} from 'ionicons/icons';
import Item from './Item';
import {authConfig, getLogger} from '../core';
import {initialStateItems, ItemContext, ItemsState} from './ItemProvider';
import { useAppState } from './useAppState';
import { useNetwork } from './useNetwork';
import {Preferences} from "@capacitor/preferences";
import {AuthContext, AuthState, initialState} from "../auth";
import item from "./Item";
import {getItems} from "./itemApi";
import {ItemProps} from "./ItemProps";
import axios from "axios";
const log = getLogger('ItemList');

const ItemList: React.FC<RouteComponentProps> = ({ history }) => {
    const { items, fetching, fetchingError, paginationFunction, readStates} = useContext(ItemContext);
    const [disableInfiniteScroll, setDisableInfiniteScroll] = useState<boolean>(false)
    const [searchBook, setSearchBook] = useState<string>('');
    const [filter, setFilter] = useState<string>('');
    const { appState } = useAppState();
    const { networkStatus } = useNetwork();
    log('render', fetching);
    function fetchData() {
        let canceled = false;
        if(items)
        {
            const lengthInitial = items.length;
            paginationFunction?.(items[items.length-1]);
            if (items && lengthInitial != items.length)
            {
                setDisableInfiniteScroll(items.length < lengthInitial + 5);
            }
            else
            {
                setDisableInfiniteScroll(true);
            }
        }
        return () => {
            canceled = true;
        }
    }
    async function searchNext($event: CustomEvent<void>) {
        fetchData();
        await ($event.target as HTMLIonInfiniteScrollElement).complete();
    }

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Bookshelf</IonTitle>
                </IonToolbar>
                <IonItem>
                    <IonFab>
                        <IonFabButton onClick={() => {
                            Preferences.clear();
                            window.location.reload();
                        }}>
                            <IonIcon icon={logOut}/>
                        </IonFabButton>
                    </IonFab>
                </IonItem>
                <IonToolbar>
                    <IonItem>
                        <IonLabel>App state is {JSON.stringify(appState)}</IonLabel>
                        <IonLabel>Network status is {JSON.stringify(networkStatus)}</IonLabel>
                    </IonItem>
                </IonToolbar>
            </IonHeader>
            <IonContent>
                {/*<IonLoading isOpen={fetching} message="Fetching items"/>*/}
                <IonSearchbar
                    value={searchBook}
                    debounce={1000}
                    onIonInput={e => setSearchBook(e.detail.value!)}>
                </IonSearchbar>
                <IonSelect value={filter} placeholder="Select read state" onIonChange={e => setFilter((e.detail.value))}>
                    {
                        readStates.map(readState => <IonSelectOption key={readState} value={readState}>{readState}</IonSelectOption>)
                    }
                </IonSelect>
                {items && (
                    <IonList>
                        {items
                            .filter(item => item.name.toString().includes(searchBook) && (filter!== "" ? item.alreadyRead.toString() === filter: true))
                            .map(({ _id, name, pageCount, dateAdded, alreadyRead}) =>
                            <Item key={_id} _id={_id} name={name} pageCount={pageCount}  dateAdded={dateAdded} alreadyRead={alreadyRead} onEdit={_id => history.push(`/item/${_id}`)} />)}
                    </IonList>
                )}
                <IonInfiniteScroll threshold="100px" disabled={disableInfiniteScroll}
                                   onIonInfinite={(e: CustomEvent<void>) => searchNext(e)}>
                    <IonInfiniteScrollContent loadingText="Loading more books..."></IonInfiniteScrollContent>
                </IonInfiniteScroll>
            {fetchingError && (
                    <div>{fetchingError.message || 'Failed to fetch items'}</div>
                )}
                <IonFab vertical="bottom" horizontal="end" slot="fixed">
                    <IonFabButton onClick={() => history.push('/item')}>
                        <IonIcon icon={add}/>
                    </IonFabButton>
                </IonFab>
            </IonContent>
        </IonPage>
    );
};

export default ItemList;
