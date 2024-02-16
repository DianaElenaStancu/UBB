import { useCallback, useEffect, useReducer } from 'react';
import { getLogger } from '../core';
import { BookProps } from './BookProps';
import { getBooks } from './bookApi';

const log = getLogger('useBooks');

export interface BooksState {
    books?: BookProps[],
    fetching: boolean,
    fetchingError?: Error,
}

export interface BooksProps extends BooksState {
    addBook: () => void,
}

interface ActionProps {
    type: string,
    payload?: any,
}

const initialState: BooksState = {
    books: undefined,
    fetching: false,
    fetchingError: undefined,
};

const FETCH_BOOKS_STARTED = 'FETCH_BOOKS_STARTED';
const FETCH_BOOKS_SUCCEEDED = 'FETCH_BOOKS_SUCCEEDED';
const FETCH_BOOKS_FAILED = 'FETCH_BOOKS_FAILED';

const reducer: (state: BooksState, action: ActionProps) => BooksState =
    (state, { type, payload }) => {
        switch(type) {
            case FETCH_BOOKS_STARTED:
                return { ...state, fetching: true };
            case FETCH_BOOKS_SUCCEEDED:
                return { ...state, books: payload.books, fetching: false };
            case FETCH_BOOKS_FAILED:
                return { ...state, fetchingError: payload.error, fetching: false };
            default:
                return state;
        }
    };

export const useBooks: () => BooksProps = () => {
    const [state, dispatch] = useReducer(reducer, initialState);
    const { books, fetching, fetchingError } = state;
    const addBook = useCallback(() => {
        log('addBook - TODO');
    }, []);
    useEffect(getBooksEffect, [dispatch]);
    log(`returns - fetching = ${fetching}, books = ${JSON.stringify(books)}`);
    return {
        books,
        fetching,
        fetchingError,
        addBook,
    };

    function getBooksEffect() {
        let canceled = false;
        fetchBooks();
        return () => {
            canceled = true;
        }

        async function fetchBooks() {
            try {
                log('fetchBooks started');
                dispatch({ type: FETCH_BOOKS_STARTED });
                const books = await getBooks();
                log('fetchBooks succeeded');
                if (!canceled) {
                    dispatch({ type: FETCH_BOOKS_SUCCEEDED, payload: { books } });
                }
            } catch (error) {
                log('fetchBooks failed');
                if (!canceled) {
                    dispatch({ type: FETCH_BOOKS_FAILED, payload: { error } });
                }
            }
        }
    }
};
