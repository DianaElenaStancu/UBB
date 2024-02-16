package com.example.bookapp.todo.data

import android.util.Log
import com.example.bookapp.core.TAG
import com.example.bookapp.core.data.remote.Api
import com.example.bookapp.todo.data.remote.BookService

class BookRepository(private val bookService: BookService) {
    private var cachedBooks: MutableList<Book> = listOf<Book>().toMutableList()

    init {
        Log.d(TAG, "init")
    }

    private fun getBearerToken() = "Bearer ${Api.tokenInterceptor.token}"


    suspend fun loadAll(): List<Book> {
        Log.d(TAG, "loadAll")
        val books = bookService.find(authorization = getBearerToken());
        Log.d(TAG, books.toString())
        Log.d(TAG, "loadAll succeeded ${books.size}")
        cachedBooks = books.toMutableList()
        return cachedBooks as List<Book>
    }

    suspend fun load(bookId: String?): Book {
        Log.d(TAG, "load $bookId")
        return bookService.read(authorization = getBearerToken(), bookId)
    }

    suspend fun update(book: Book): Book {
        Log.d(TAG, "update $book")
        val updatedBook = bookService.update(authorization = getBearerToken(), book._id, book)
        val index = cachedBooks.indexOfFirst { it._id == book._id }
        if (index != -1) {
            cachedBooks.set(index, updatedBook)
        }
        return updatedBook
    }

    suspend fun save(book: Book): Book {
        Log.d(TAG, "save $book")
        val createdBook = bookService.create(authorization = getBearerToken(), book)
        cachedBooks.add(0, createdBook);
        return createdBook
    }

    fun getBook(bookId: String?): Book? = cachedBooks.find { it._id == bookId }
}