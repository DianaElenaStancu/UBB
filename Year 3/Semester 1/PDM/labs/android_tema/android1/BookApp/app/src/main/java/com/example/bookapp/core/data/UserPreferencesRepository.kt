package com.example.bookapp.core.data

import android.content.Context
import android.util.Log
import androidx.datastore.core.DataStore
import androidx.datastore.preferences.core.Preferences
import androidx.datastore.preferences.core.edit
import androidx.datastore.preferences.core.stringPreferencesKey
import androidx.preference.PreferenceManager
import com.example.bookapp.core.TAG
import com.example.bookapp.todo.data.UserCredentials

//suspend fun login(userCredentials: UserCredentials): UserCredentials {
//    Log.d(TAG, "login with username ${userCredentials.username} and password ${userCredentials.password}")
//
//    val sharedPreferences = activity?.getSharedPreferences(getString(R.string.preference_file_key), Context.MODE_PRIVATE)
//
//
//    PreferenceManager.getDefaultSharedPreferences()
//    val sharedPreferences = PreferenceManager.getSharedPreferences("Auth", Context.MODE_PRIVATE)
//
//    val returnedCredentials = authService.login(userCredentials)
//    return userCredentials
//}
class UserPreferencesRepository(private val dataStore: DataStore<Preferences>) {
    private object PreferencesKeys {
        val username = stringPreferencesKey("username")
        val token = stringPreferencesKey("token")
    }

    init {
        Log.d(TAG, "init")
    }

    suspend fun save(userPreferences: UserPreferences) {
        dataStore.edit { preferences ->
            preferences[PreferencesKeys.username] = userPreferences.username
            preferences[PreferencesKeys.token] = userPreferences.token
        }
    }

    private fun load(preferences: Preferences) =
        UserPreferences(
            username = preferences[PreferencesKeys.username]  ?: "",
            token = preferences[PreferencesKeys.token]  ?: ""
        )
}