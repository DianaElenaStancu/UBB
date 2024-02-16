import axios from "axios";
import { getLogger, authConfig, baseUrl, withLogs } from "../core";
import { BookProps } from "./BookProps";
import { Preferences } from "@capacitor/preferences";

const log = getLogger('bookLogger');

const booksUrl = `http://${baseUrl}/api/book`;

export const getAllBooks: (token: string) => Promise<BookProps[]> = (token) => {
    return withLogs(axios.get(booksUrl, authConfig(token)), 'getAllBooks');
}

export const updateBookAPI: (token: string, book: BookProps) => Promise<BookProps[]> = (token, book) => {
    return withLogs(axios.put(`${booksUrl}/${book._id}`, book, authConfig(token)), 'updateBook');
}

export const createBookAPI: (token: string, book: BookProps) => Promise<BookProps[]> = (token, book) => {
  return withLogs(axios.post(`${booksUrl}`, book, authConfig(token)), 'createBook');
}

export const deleteBookAPI: (token: string, id: string) => Promise<BookProps[]> = (token, id) => {
  return withLogs(axios.delete(`${booksUrl}/${id}`, authConfig(token)), 'deleteBook');
}

interface MessageData {
    event: string;
    payload: {
      successMessage: string,
      updatedBook: BookProps[]
    };
}

export const newWebSocket = (token: string, onMessage: (data: MessageData) => void) => {
    const ws = new WebSocket(`ws://${baseUrl}`)
    ws.onopen = () => {
      log('web socket onopen');
      ws.send(JSON.stringify({type: 'authorization', payload :{token}}));
    };
    ws.onclose = () => {
      log('web socket onclose');
    };
    ws.onerror = error => {
      log('web socket onerror', error);
    };
    ws.onmessage = messageEvent => {
      log('web socket onmessage');
      console.log(messageEvent.data);
      onMessage(JSON.parse(messageEvent.data));
    };
    return () => {
      ws.close();
    }
}

  