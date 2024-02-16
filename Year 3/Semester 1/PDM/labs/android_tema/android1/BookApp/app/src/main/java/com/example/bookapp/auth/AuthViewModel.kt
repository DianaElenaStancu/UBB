//package com.example.bookapp.auth
//
//import android.util.Log
//import androidx.compose.runtime.getValue
//import androidx.compose.runtime.mutableStateOf
//import androidx.compose.runtime.setValue
//import androidx.lifecycle.ViewModel
//import androidx.lifecycle.ViewModelProvider
//import androidx.lifecycle.viewModelScope
//import androidx.lifecycle.viewmodel.initializer
//import androidx.lifecycle.viewmodel.viewModelFactory
//import com.example.bookapp.MyApplication
//import com.example.bookapp.core.TAG
//import kotlinx.coroutines.launch
//import com.example.bookapp.core.Result
//import com.example.bookapp.todo.data.UserCredentials
//
//data class AuthUiState(
//    val userId: String? = null,
//    val userCredentials: UserCredentials,
//    var submitResult: Result<UserCredentials>? = null,
//)
//
//class AuthViewModel(private val authRepository: AuthRepository) :
//    ViewModel() {
//    init {
//        Log.d(TAG, "init")
//    }
//
//    var uiState: AuthUiState by mutableStateOf(
//        AuthUiState(userCredentials = UserCredentials())
//    )
//        private set
//
//
//    fun login(username: String, password: String) {
//        viewModelScope.launch {
//            Log.d(TAG, "login...");
//            try {
//                uiState = uiState.copy(submitResult = Result.Loading)
//                val userCredentials = uiState.userCredentials.copy(username = username, password = password)
//                val savedUserCredentials = authRepository.login(userCredentials)
//
//                Log.d(TAG, "login succeeeded");
//                uiState = uiState.copy(submitResult = Result.Success(savedUserCredentials))
//            } catch (e: Exception) {
//                Log.d(TAG, "login failed");
//                uiState = uiState.copy(submitResult = Result.Error(e))
//            }
//        }
//    }
//
//    companion object {
//        fun Factory(itemId: String?): ViewModelProvider.Factory = viewModelFactory {
//            initializer {
//                val app =
//                    (this[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as MyApplication)
//                AuthViewModel(app.container.authRepository)
//            }
//        }
//    }
//}