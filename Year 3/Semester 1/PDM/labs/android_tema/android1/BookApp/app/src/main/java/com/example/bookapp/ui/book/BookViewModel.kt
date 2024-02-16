package com.example.bookapp.ui.book

import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import com.example.bookapp.MyApplication
import com.example.bookapp.core.TAG
import com.example.bookapp.todo.data.Book
import com.example.bookapp.todo.data.BookRepository
import kotlinx.coroutines.launch
import com.example.bookapp.core.Result

data class BookUiState(
    val bookId: String? = null,
    val book: Book = Book(),
    var submitResult: Result<Book>? = null,
)

class BookViewModel(private val bookId: String?, private val bookRepository: BookRepository) :
    ViewModel() {
    init {
        Log.d(TAG, "init")
    }

    var uiState: BookUiState by mutableStateOf(
        BookUiState(book = bookRepository.getBook(bookId)?.copy() ?: Book())
    )
        private set

    fun saveOrUpdateBook(title: String, writer: String) {
        viewModelScope.launch {
            Log.d(TAG, "saveOrUpdateBook...");
            try {
                uiState = uiState.copy(submitResult = Result.Loading)
                val book = uiState.book.copy(title = title, writer = writer)
                val savedBook: Book;
                if (bookId == null) {
                    savedBook = bookRepository.save(book)
                } else {
                    savedBook = bookRepository.update(book)
                }
                Log.d(TAG, "saveOrUpdateBook succeeeded");
                uiState = uiState.copy(submitResult = Result.Success(savedBook))
            } catch (e: Exception) {
                Log.d(TAG, "saveOrUpdateBook failed");
                uiState = uiState.copy(submitResult = Result.Error(e))
            }
        }
    }

    companion object {
        fun Factory(itemId: String?): ViewModelProvider.Factory = viewModelFactory {
            initializer {
                val app =
                    (this[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as MyApplication)
                BookViewModel(itemId, app.container.bookRepository)
            }
        }
    }
}
