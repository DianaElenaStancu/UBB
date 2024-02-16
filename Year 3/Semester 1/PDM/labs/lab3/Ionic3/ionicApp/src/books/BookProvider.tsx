import React, { useCallback, useEffect, useReducer, useContext } from 'react';
import PropTypes from 'prop-types';
import { getLogger } from '../core';
import { getAllBooks, updateBookAPI, createBookAPI, newWebSocket, deleteBookAPI } from './BookApi';
import { BookProps } from './BookProps';
import { AuthContext } from '../auth';
import { useNetwork } from '../pages/useNetwork';
import {useIonToast} from "@ionic/react";
import { Preferences } from '@capacitor/preferences';

const log = getLogger('BookProvider');

type UpdateBookFn = (book: BookProps) => Promise<any>;
type DeleteBookFn = (id: string) => Promise<any>;

interface BooksState {
    books?: BookProps[];
    fetching: boolean;
    fetchingError?: Error | null;
    updating: boolean,
    updateError?: Error | null,
    updateBook?: UpdateBookFn,
    addBook?: UpdateBookFn,
    deleteBook?: DeleteBookFn;
    successMessage?: string;
    closeShowSuccess?: () => void;
}

interface ActionProps {
    type: string,
    payload?: any,
}

const initialState: BooksState = {
    fetching: false,
    updating: false,
};

const FETCH_BOOKS_STARTED = 'FETCH_BOOKS_STARTED';
const FETCH_BOOKS_SUCCEEDED = 'FETCH_BOOKS_SUCCEEDED';
const FETCH_BOOKS_FAILED = 'FETCH_BOOKS_FAILED';
const UPDATE_BOOK_STARTED = 'UPDATE_BOOK_STARTED';
const UPDATE_BOOK_SUCCEDED = 'UPDATE_BOOK_SUCCEDED';
const UPDATE_BOOK_FAILED = 'UPDATE_BOOK_FAILED';
const SHOW_SUCCESS_MESSSAGE = 'SHOW_SUCCESS_MESSAGE';
const HIDE_SUCCESS_MESSSAGE = 'HIDE_SUCCESS_MESSAGE';
const CREATE_BOOK_STARTED = 'CREATE_BOOK_STARTED';
const CREATE_BOOK_SUCCEDED = 'CREATE_BOOK_SUCCEDED';
const CREATE_BOOK_FAILED = 'CREATE_BOOK_FAILED';
const DELETE_BOOK_STARTED = 'DELETE_BOOK_STARTED';
const DELETE_BOOK_SUCCEDED = 'DELETE_BOOK_SUCCEDED';
const DELETE_BOOK_FAILED = 'DELETE_BOOK_FAILED';

const reducer: (state: BooksState, action: ActionProps) => BooksState 
    = (state, { type, payload }) => {
    switch(type){
        case FETCH_BOOKS_STARTED:
            return { ...state, fetching: true, fetchingError: null };
        case FETCH_BOOKS_SUCCEEDED:
            return {...state, books: payload.books, fetching: false };
        case FETCH_BOOKS_FAILED:
            return { ...state, fetchingError: payload.error, fetching: false };
        case UPDATE_BOOK_STARTED:
            return { ...state, updateError: null, updating: true };
        case UPDATE_BOOK_FAILED:
            return { ...state, updateError: payload.error, updating: false };
        case UPDATE_BOOK_SUCCEDED:
            const books = [...(state.books || [])];
            const book = payload.book;
            const index = books.findIndex(it => it._id === book._id);
            books[index] = book;
            return { ...state,  books, updating: false };
        case CREATE_BOOK_FAILED:
            console.log(payload.error);
          return { ...state, updateError: payload.error, updating: false };
        case CREATE_BOOK_STARTED:
          return { ...state, updateError: null, updating: true };
        case CREATE_BOOK_SUCCEDED:
            const beforeBooks = [...(state.books || [])];
            const createdBook = payload.book;
            console.log(createdBook);
            if (createdBook && createdBook._id){
              const indexOfAdded = beforeBooks.findIndex(it => it._id === createdBook?._id || it.title === createdBook?.title);
              console.log("index: ", indexOfAdded);
              if (indexOfAdded === -1) {
                   beforeBooks.splice(0, 0, createdBook);
               } else {
                  beforeBooks[indexOfAdded] = createdBook;
               }
            }
            
            console.log(beforeBooks);
            console.log(payload);
            return { ...state,  books: beforeBooks, updating: false, updateError: null };
            case DELETE_BOOK_FAILED:
              console.log(payload.error);
              return { ...state, updateError: payload.error, updating: false };
            case DELETE_BOOK_STARTED:
              return { ...state, updateError: null, updating: true };
            case DELETE_BOOK_SUCCEDED:
                const originalBooks = [...(state.books || [])];
                const deletedBook = payload.book;
                const indexOfDeleted = originalBooks.findIndex(it => it._id === deletedBook._id);
                if (indexOfDeleted > -1) {
                  originalBooks.splice(indexOfDeleted, 1);
                }
                console.log(originalBooks);
                console.log(payload);
                return { ...state,  books: originalBooks, updating: false };
        case SHOW_SUCCESS_MESSSAGE:
            const allBooks = [...(state.books || [])];
            const updatedBook = payload.updatedBook;
            const indexOfBook = allBooks.findIndex(it => it._id === updatedBook?._id);
            allBooks[indexOfBook] = updatedBook;
            console.log(payload);
            return {...state, books: allBooks, successMessage: payload.successMessage }
        case HIDE_SUCCESS_MESSSAGE:
            return {...state, successMessage: payload }
        
        default:
            return state;
    }
};

export const BookContext = React.createContext(initialState);

interface BookProviderProps {
    children: PropTypes.ReactNodeLike,
}

export const BookProvider: React.FC<BookProviderProps> = ({ children }) => {
    const [state, dispatch] = useReducer(reducer, initialState);
    const { books, fetching, fetchingError, updating, updateError, successMessage } = state;
    const { token } = useContext(AuthContext);
    const { networkStatus } = useNetwork();
    const [toast] = useIonToast();

    useEffect(getItemsEffect, [token]);
    useEffect(wsEffect, [token]);
    useEffect(executePendingOperations, [networkStatus.connected, token, toast]);

    const updateBook = useCallback<UpdateBookFn>(updateBookCallback, [token]);
    const addBook = useCallback<UpdateBookFn>(addBookCallback, [token]);
    const deleteBook = useCallback<DeleteBookFn>(deleteBookCallback, [token]);

    log('returns');

    function getItemsEffect() {
        let canceled = false;
        fetchItems();
        return () => {
            canceled = true;
        }

        async function fetchItems() {
          if(!token?.trim()){
            return;
          }

            try{
                log('fetchBooks started');
                dispatch({ type: FETCH_BOOKS_STARTED });
                const books = await getAllBooks(token);
                log('fetchItems succeeded');
                if (!canceled) {
                dispatch({ type: FETCH_BOOKS_SUCCEEDED, payload: { books } });
                }
            } catch (error) {
                log('fetchItems failed');
                if (!canceled) {
                    dispatch({ type: FETCH_BOOKS_FAILED, payload: { error } });
                }
            }
        }
    }

    async function updateBookCallback(book: BookProps) {
        try {
          log('updateBook started');
          dispatch({ type: UPDATE_BOOK_STARTED });
          const updatedBook = await updateBookAPI(token, book);
          log('saveBook succeeded');
          dispatch({ type: UPDATE_BOOK_SUCCEDED, payload: { book: updatedBook } });
        } catch (error: any) {
          log('updateBook failed');
          // save item to storage
          console.log('Updating book locally...');

          book.isNotSaved = true;
          await Preferences.set({
            key: `upd-${book.title}`,
            value: JSON.stringify({token, book })
          });
          console.log(book);
          dispatch({ type: UPDATE_BOOK_SUCCEDED, payload: { book: book } });
          toast("You are offline... Updating book locally!", 3000);
    
          if(error.toJSON().message === 'Network Error')
            dispatch({ type: UPDATE_BOOK_FAILED, payload: { error: new Error(error.response) } });
        }
    }

    async function addBookCallback(book: BookProps){
        try{
          log('addBook started');
          dispatch({ type: CREATE_BOOK_STARTED });
          console.log(token);
          const addedBook = await createBookAPI(token, book);
          console.log(addedBook);
          log('saveBook succeeded');
          dispatch({ type: CREATE_BOOK_SUCCEDED, payload: { book: addedBook } });
        }catch(error: any){
          log('addBook failed');
          console.log(error.response);
          // save item to storage
          console.log('Saving book locally...');
          const { keys } = await Preferences.keys();
          const matchingKeys = keys.filter(key => key.startsWith('sav-'));
          const numberOfItems = matchingKeys.length + 1;
          console.log(numberOfItems);

          book._id = numberOfItems.toString(); // ii adaug si id...
          book.isNotSaved = true;
          await Preferences.set({
            key: `sav-${book.title}`,
            value: JSON.stringify({token, book })
          });
          dispatch({ type: CREATE_BOOK_SUCCEDED, payload: { book: book } });
          toast("You are offline... Saving book locally!", 3000);
    
          if(error.toJSON().message === 'Network Error')
            dispatch({ type: CREATE_BOOK_FAILED, payload: { error: new Error(error.response || 'Network error') } });
        }
    }

    async function deleteBookCallback(id: string){
        try{
          log('deleteBook started');
          dispatch({ type: DELETE_BOOK_STARTED });
          const deletedBook = await deleteBookAPI(token, id);
          console.log('deleted book: '+ deletedBook);
          log('deleteBook succeeded');
          dispatch({ type: DELETE_BOOK_SUCCEDED, payload: { book: deletedBook } });
        }catch(error: any){
          log('addBook failed');
          console.log(error.response.data.message);
          dispatch({ type: DELETE_BOOK_FAILED, payload: { error: new Error(error.response.data.message) } });
        }
    }

    function executePendingOperations(){
      async function helperMethod(){
          if(networkStatus.connected && token?.trim()){
              log('executing pending operations')
              const { keys } = await Preferences.keys();
              for(const key of keys) {
                  if(key.startsWith("sav-")){
                      const res = await Preferences.get({key: key});
                      console.log("Result", res);
                      if (typeof res.value === "string") {
                          const value = JSON.parse(res.value);
                          value.book._id=undefined;  // ca sa imi puna serverul id nou!!
                          log('creating item from pending', value);
                          await addBookCallback(value.book);
                          await Preferences.remove({key: key});
                      }
                  }
              }
              for(const key of keys) {
                if(key.startsWith("upd-")){
                    const res = await Preferences.get({key: key});
                    console.log("Result", res);
                    if (typeof res.value === "string") {
                        const value = JSON.parse(res.value);
                        log('updating item from pending', value);
                        await updateBookCallback(value.book);
                        await Preferences.remove({key: key});
                    }
                }
            }
          }
      }
      helperMethod();
  }

    function wsEffect() {
        let canceled = false;
        log('wsEffect - connecting');
        let closeWebSocket: () => void;
        if(token?.trim()){
          closeWebSocket = newWebSocket(token, message => {
            if (canceled) {
              return;
            }
            const { event, payload } = message;
            console.log('Provider message: ', message);

            log(`ws message, item ${event}`);
            if (event === 'updated') {
              console.log('aici');

              console.log(payload);
              dispatch({ type: SHOW_SUCCESS_MESSSAGE, payload: {successMessage: payload.successMessage, updatedBook: payload.updatedBook } });
            }
            else if(event == 'created'){
              console.log(payload);
              dispatch({ type: CREATE_BOOK_SUCCEDED, payload: { book: payload.updatedBook } });
            }
            else if(event === 'deleted'){
              console.log(payload);
              dispatch({ type: DELETE_BOOK_SUCCEDED, payload: { book: payload.updatedBook } });
            }
          });
        }
        return () => {
          log('wsEffect - disconnecting');
          canceled = true;
          closeWebSocket?.();
        }
    }

    function closeShowSuccess(){
        dispatch({ type: HIDE_SUCCESS_MESSSAGE, payload: null });
    }

    const value = { books, fetching, fetchingError, updating, updateError, updateBook, addBook, deleteBook, successMessage, closeShowSuccess };

    return (
        <BookContext.Provider value={value}>
            {children}
        </BookContext.Provider>
    );
};

