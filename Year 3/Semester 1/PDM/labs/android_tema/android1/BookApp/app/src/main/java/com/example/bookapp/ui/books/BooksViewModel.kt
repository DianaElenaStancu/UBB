package com.example.bookapp.ui.books

import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import com.example.bookapp.MainActivity
import com.example.bookapp.MyApplication
import com.example.bookapp.core.TAG
import com.example.bookapp.todo.data.Book
import com.example.bookapp.todo.data.BookRepository
import kotlinx.coroutines.launch
import com.example.bookapp.core.Result

class BooksViewModel(private val bookRepository: BookRepository) : ViewModel() {
    var uiState: Result<List<Book>> by mutableStateOf(Result.Loading)
        private set

    init {
        Log.d(TAG, "init")
        loadItems()
    }

    fun loadItems() {
        Log.d(TAG, "loadBooks")
        viewModelScope.launch {
            uiState = Result.Loading
            uiState = try {
                Result.Success(bookRepository.loadAll())
            } catch (e: Exception) {
                Result.Error(e)
            }
        }
    }

    companion object {
        val Factory: ViewModelProvider.Factory = viewModelFactory {
            initializer {
                val app =
                    (this[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as MyApplication)
                BooksViewModel(app.container.bookRepository)
            }
        }
    }
}