package com.example.bookapp.auth.data

import android.util.Log
import com.example.bookapp.auth.data.remote.AuthDataSource
import com.example.bookapp.auth.data.remote.TokenHolder
import com.example.bookapp.auth.data.remote.User
import com.example.bookapp.core.data.remote.Api
import com.example.bookapp.core.TAG


class AuthRepository(private val authDataSource: AuthDataSource) {
    init {
        Log.d(TAG, "init")
    }

    fun clearToken() {
        Api.tokenInterceptor.token = null
    }

    suspend fun login(username: String, password: String): Result<TokenHolder> {
        val user = User(username, password)
        val result = authDataSource.login(user)
        if (result.isSuccess) {
            Api.tokenInterceptor.token = result.getOrNull()?.token
        }
        return result
    }
}
