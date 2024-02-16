package com.example.bookapp

import android.content.Context
import android.util.Log
import androidx.datastore.preferences.preferencesDataStore
import com.example.bookapp.auth.data.AuthRepository
import com.example.bookapp.auth.data.remote.AuthDataSource
import com.example.bookapp.core.data.remote.Api
import com.example.bookapp.core.TAG
import com.example.bookapp.core.data.UserPreferencesRepository
import com.example.bookapp.todo.data.BookRepository
import com.example.bookapp.todo.data.remote.BookService

val Context.userPreferencesDataStore by preferencesDataStore(
    name = "user_preferences"
)

class AppContainer(val context: Context) {
    init {
        Log.d(TAG, "init")
    }

    val bookService: BookService = Api.retrofit.create(BookService::class.java)

    private val authDataSource: AuthDataSource = AuthDataSource()

    val bookRepository: BookRepository by lazy {
        BookRepository(bookService)
    }
    val authRepository: AuthRepository by lazy {
        AuthRepository(authDataSource)
    }

    val userPreferencesRepository: UserPreferencesRepository by lazy {
        UserPreferencesRepository(context.userPreferencesDataStore)
    }
}
