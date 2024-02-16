//package com.example.bookapp.core.ui
//
//import android.util.Log
//import androidx.compose.runtime.getValue
//import androidx.compose.runtime.mutableStateOf
//import androidx.lifecycle.ViewModel
//import androidx.lifecycle.ViewModelProvider
//import androidx.lifecycle.viewModelScope
//import androidx.lifecycle.viewmodel.initializer
//import androidx.lifecycle.viewmodel.viewModelFactory
//import com.example.bookapp.MyApplication
//import com.example.bookapp.core.TAG
//import com.example.bookapp.core.data.UserPreferences
//import com.example.bookapp.core.data.UserPreferencesRepository
//import kotlinx.coroutines.flow.Flow
//import kotlinx.coroutines.launch
//import com.example.bookapp.core.Result
//
//class UserPreferencesViewModel(private val userPreferencesRepository: UserPreferencesRepository) : ViewModel() {
//    var uiState: Result<UserPreferences> by mutableStateOf(Result.Loading)
//        private set
//
//    init {
//        Log.d(TAG, "init")
//        loadUserPreferences()
//    }
//
//    private fun loadUserPreferences() {
//        Log.d(TAG, "loadUserPreferences")
//        viewModelScope.launch {
//            uiState = Result.Loading
//            uiState = try {
//                Result.Success(userPreferencesRepository.load())
//            } catch (e: Exception) {
//                Result.Error(e)
//            }
//        }
//    }
//
//    fun save(userPreferences: UserPreferences) {
//        viewModelScope.launch {
//            Log.d(TAG, "saveUserPreferences...");
//            userPreferencesRepository.save(userPreferences)
//        }
//    }
//
//    companion object {
//        val Factory: ViewModelProvider.Factory = viewModelFactory {
//            initializer {
//                val app =
//                    (this[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as MyApplication)
//                UserPreferencesViewModel(app.container.userPreferencesRepository)
//            }
//        }
//    }
//}
//
