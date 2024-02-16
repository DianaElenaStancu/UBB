// import React, {useCallback, useContext, useEffect, useReducer} from 'react';
// import PropTypes from 'prop-types';
// import {getLogger} from '../core';
// import {ItemProps} from './ItemProps';
// import {createItem, getItems, newWebSocket, updateItem} from './itemApi';
// import {AuthContext} from '../auth';
// import {useNetwork} from "./useNetwork";
// import {Preferences} from "@capacitor/preferences";
// import {useIonAlert} from "@ionic/react";
//
// const log = getLogger('ItemProvider');
//
// type SaveItemFn = (item: ItemProps) => Promise<any>;
// type PaginationFunction = (item: ItemProps) => void;
//
// export interface ItemsState {
//     items?: ItemProps[],
//     fetching: boolean,
//     fetchingError?: Error | null,
//     saving: boolean,
//     savingError?: Error | null,
//     saveItem?: SaveItemFn,
//     paginationFunction?: PaginationFunction,
//     reviews:  string[]}
//
// interface ActionProps {
//     type: string,
//     payload?: any,
// }
//
// export const initialStateItems: ItemsState = {
//     fetching: false,
//     saving: false,
//     reviews: ['1'],
// };
//
// export const ItemContext = React.createContext<ItemsState>(initialStateItems);
//
// const FETCH_ITEMS_STARTED = 'FETCH_ITEMS_STARTED';
// const FETCH_ITEMS_SUCCEEDED = 'FETCH_ITEMS_SUCCEEDED';
// const FETCH_ITEMS_FAILED = 'FETCH_ITEMS_FAILED';
// const SAVE_ITEM_STARTED = 'SAVE_ITEM_STARTED';
// const SAVE_ITEM_SUCCEEDED = 'SAVE_ITEM_SUCCEEDED';
// const SAVE_ITEM_FAILED = 'SAVE_ITEM_FAILED';
// const FETCH_REVIEWS_SUCCEEDED = 'SAVE_REVIEWS_SUCCEEDED';
// const FETCH_REVIEWS_FAILED = 'FETCH_REVIEWS_FAILED';
//
// const reducer: (state: ItemsState, action: ActionProps) => ItemsState =
//     (state, { type, payload }) => {
//         switch(type) {
//             case FETCH_ITEMS_STARTED:
//                 return { ...state, fetching: true, fetchingError: null };
//             case FETCH_ITEMS_SUCCEEDED:
//                 return { ...state, items: payload.items, fetching: false };
//             case FETCH_ITEMS_FAILED:
//                 return { ...state, fetchingError: payload.error, fetching: false };
//             case SAVE_ITEM_STARTED:
//                 return { ...state, savingError: null, saving: true };
//             case SAVE_ITEM_SUCCEEDED:
//                 const items = [...(state.items || [])];
//                 const item = payload.item;
//                 const index = items.findIndex(it => it._id === item._id);
//                 if (index === -1) {
//                     items.splice(0, 0, item);
//                 } else {
//                     items[index] = item;
//                 }
//                 return { ...state, items, saving: false };
//             case SAVE_ITEM_FAILED:
//                 return { ...state, savingError: payload.error, saving: false };
//             case FETCH_REVIEWS_SUCCEEDED:
//                 return { ...state, reviews: payload.reviews, fetching: false };
//             case FETCH_REVIEWS_FAILED:
//                 return { ...state, fetching: false, fetchingError: payload.error };
//             default:
//                 return state;
//         }
//     };
//
// interface ItemProviderProps {
//     children: PropTypes.ReactNodeLike,
// }
//
// export const ItemProvider: React.FC<ItemProviderProps> = ({ children }) => {
//     const { token } = useContext(AuthContext);
//     const [state, dispatch] = useReducer(reducer, initialStateItems);
//     const [presentAlert] = useIonAlert();
//     const { networkStatus } = useNetwork();
//     const { items, fetching, fetchingError, saving, savingError, reviews } = state;
//     useEffect(getItemsEffect, [token, networkStatus]);
//     useEffect(wsEffect, [token]);
//     useEffect(resendData, [token, networkStatus]);
//     useEffect(getAllReviews, [token]);
//     const saveItem = useCallback<SaveItemFn>(saveItemCallback, [token, networkStatus]);
//     const paginationFunction = useCallback<PaginationFunction>(paginationCallBack, [token, items]);
//     const value = { items, fetching, fetchingError, saving, savingError, saveItem, paginationFunction, reviews };
//     log('returns');
//     return (
//         <ItemContext.Provider value={value}>
//             {children}
//         </ItemContext.Provider>
//     );
//     function getAllReviews()
//     {
//         let canceled = false;
//         if (token) {
//             fetchReviews();
//         }
//         return () => {
//             canceled = true;
//         }
//         async function fetchReviews()
//         {
//             try {
//                 const allItems:ItemProps[] = await getItems(token);
//                 let allReviews: string[] = [];
//                 for(let i = 0; i < allItems.length; i++)
//                 {
//                     if(allReviews.indexOf(String(allItems[i].review)) < 0)
//                     {
//                         allReviews.push(String(allItems[i].review));
//                     }
//                 }
//                 allReviews.push("");
//                 allReviews.sort((a, b) => Number(a) -Number(b));
//                 dispatch({type: FETCH_REVIEWS_SUCCEEDED, payload: {reviews: allReviews}})
//
//             }
//             catch (error) {
//                 log('fetchItemsConnected failed', error);
//                 dispatch({ type: FETCH_REVIEWS_FAILED, payload: { error } });
//             }
//            }
//     }
//     async function paginationCallBack(item: ItemProps) {
//         let canceled = false;
//         if(items)
//         {
//             await fetchPaginationData();
//         }
//         return () => {
//             canceled = true;
//         }
//         async function fetchPaginationData()
//         {
//             try {
//                 log('pagination started');
//                 const itemsAux: ItemProps[]  = await getItems(token);
//                 let index = 0;
//                 for(let i = 0; i < itemsAux.length; i++)
//                 {
//                     if(itemsAux[i]._id === item._id)
//                     {
//                         index = i;
//                         break;
//                     }
//                 }
//                 let itemsFinal:ItemProps[] = [];
//                 for(let i = 0; i < index + 5 && i < itemsAux.length; i++)
//                 {
//                     itemsFinal.push(itemsAux[i]);
//                 }
//                 dispatch({type: FETCH_ITEMS_SUCCEEDED, payload: {items: itemsFinal}})
//
//             } catch (error) {
//                 log('saveItem failed');
//                 dispatch({type: SAVE_ITEM_FAILED, payload: {error}});
//             }
//
//         }
//     }
//     function getItemsEffect() {
//         let canceled = false;
//         if (token && networkStatus.connected) {
//             fetchItemsConnected();
//         }
//         if (token && !networkStatus.connected) {
//             fetchItemsNotConnected();
//         }
//         return () => {
//             canceled = true;
//         }
//         async function fetchItemsNotConnected() {
//             try {
//                 log('fetchItemsNotConnected started');
//                 dispatch({ type: FETCH_ITEMS_STARTED });
//                 const allResources = await Preferences.get({ key: 'resourceAll' });
//                 if(allResources.value)
//                 {
//                     log('fetchItemsNotConnected succeeded');
//                     if (!canceled) {
//                         const itemsNotConnected: ItemProps[] = JSON.parse(allResources.value).items;
//                         dispatch({ type: FETCH_ITEMS_SUCCEEDED, payload: { items: itemsNotConnected } });
//                     }
//                 }
//             } catch (error) {
//                 log('fetchItemsNotConnected failed', error);
//                 dispatch({ type: FETCH_ITEMS_FAILED, payload: { error } });
//             }
//         }
//
//         async function fetchItemsConnected() {
//             try {
//                 log('fetchItemsConnected started');
//                 dispatch({ type: FETCH_ITEMS_STARTED });
//                 const itemsAux: ItemProps[]  = await getItems(token);
//                 Preferences.set({
//                     key: 'resourceAll',
//                     value: JSON.stringify({
//                         items: itemsAux
//                     })
//                 });
//                 log('fetchItemsConnected succeeded');
//                 if (!canceled) {
//                     let index:number = 0;
//                     if(items)
//                     {
//                         for(let i = 0; i < itemsAux.length; i++)
//                         {
//                             if(itemsAux[i]._id === items[items.length-1]._id)
//                             {
//                                 index = i;
//                                 break;
//                             }
//                         }
//                     }
//                     let itemsFinal:ItemProps[] = [];
//                     for(let i = 0; i < Math.max(index, 5) && i<itemsAux.length; i++)
//                     {
//                         itemsFinal.push(itemsAux[i]);
//                     }
//                     dispatch({ type: FETCH_ITEMS_SUCCEEDED, payload: { items: itemsFinal}});
//                 }
//             } catch (error) {
//                 log('fetchItemsConnected failed', error);
//                 dispatch({ type: FETCH_ITEMS_FAILED, payload: { error } });
//             }
//         }
//     }
//     function resendData() {
//         let canceled = false;
//         if (networkStatus.connected) {
//             resendDataConnected();
//         }
//         return () => {
//             canceled = true;
//         }
//         async function resendDataConnected() {
//             try {
//                 log('fetchItemsNotConnected started');
//                 const alreadyExisting = await Preferences.get({key: 'toAdd'});
//                 let itemsToAdd: ItemProps[] = [];
//                 if (alreadyExisting.value) {
//                     dispatch({ type: SAVE_ITEM_STARTED });
//                     itemsToAdd = JSON.parse(alreadyExisting.value).itemsToAdd;
//                     for(let i = 0; i < itemsToAdd.length; i++)
//                     {
//                         const savedItem = await (itemsToAdd[i]._id ? updateItem(token, itemsToAdd[i]) : createItem(token, itemsToAdd[i]));
//                         log('saveItem succeeded');
//                         dispatch({type: SAVE_ITEM_SUCCEEDED, payload: {item: savedItem}});
//                     }
//                     Preferences.remove({ key: 'toAdd' });
//                     return (
//                         presentAlert({
//                             header: 'Alert',
//                             subHeader: 'Important message',
//                             message: 'Datele s-au retrimis la server!',
//                             buttons: ['OK'],
//                         })
//                     );
//                 }
//             } catch (error) {
//                 log('fetchItemsNotConnected failed', error);
//                 dispatch({ type: FETCH_ITEMS_FAILED, payload: { error } });
//             }
//         }
//     }
//     async function saveItemCallback(item: ItemProps) {
//         if(networkStatus.connected) {
//             try {
//                 log('saveItem started');
//                 dispatch({type: SAVE_ITEM_STARTED});
//                 const savedItem = await (item._id ? updateItem(token, item) : createItem(token, item));
//                 log('saveItem succeeded');
//                 dispatch({type: SAVE_ITEM_SUCCEEDED, payload: {item: savedItem}});
//                 const itemsAuxiliar: ItemProps[] = [...(state.items) || []];
//                 itemsAuxiliar.map(aux => {
//                     if(aux._id === JSON.parse(JSON.stringify(savedItem))._id)
//                     {
//                         aux.date = JSON.parse(JSON.stringify(savedItem)).date;
//                         aux.review = JSON.parse(JSON.stringify(savedItem)).review;
//                         aux.watched = JSON.parse(JSON.stringify(savedItem)).watched;
//                         aux.title = JSON.parse(JSON.stringify(savedItem)).title;
//                     }
//                 })
//                 await Preferences.set({
//                     key: 'resourceAll',
//                     value: JSON.stringify({
//                         items: itemsAuxiliar
//                     })
//                 });
//
//             } catch (error) {
//                 log('saveItem failed');
//                 dispatch({type: SAVE_ITEM_FAILED, payload: {error}});
//             }
//         }
//         else
//         {
//             const alreadyExisting = await Preferences.get({key: 'toAdd'});
//             let itemsToAdd: ItemProps[] = [];
//             if (alreadyExisting.value) {
//                 itemsToAdd = JSON.parse(alreadyExisting.value).itemsToAdd;
//             }
//             itemsToAdd.push(JSON.parse(JSON.stringify(item)) || {title: 'movie 978', date: new Date(), review: 1, watched: false, _id: ''});
//             await Preferences.set({
//                 key: 'toAdd',
//                 value: JSON.stringify({
//                     itemsToAdd
//                 })
//             });
//             return (
//                 presentAlert({
//                     header: 'Alert',
//                     subHeader: 'Important message',
//                     message: 'Nu se pot trimite date la server!',
//                     buttons: ['OK'],
//                 })
//             );
//         }
//     }
//     function wsEffect() {
//         let canceled = false;
//         log('wsEffect - connecting');
//         let closeWebSocket: () => void;
//         if (token?.trim()) {
//             closeWebSocket = newWebSocket(token, message => {
//                 if (canceled) {
//                     return;
//                 }
//                 const { type, payload: item } = message;
//                 log(`ws message, item ${type}`);
//                 if (type === 'created' || type === 'updated') {
//                     dispatch({ type: SAVE_ITEM_SUCCEEDED, payload: { item } });
//                 }
//             });
//         }
//         return () => {
//             log('wsEffect - disconnecting');
//             canceled = true;
//             closeWebSocket?.();
//         }
//     }
// };
