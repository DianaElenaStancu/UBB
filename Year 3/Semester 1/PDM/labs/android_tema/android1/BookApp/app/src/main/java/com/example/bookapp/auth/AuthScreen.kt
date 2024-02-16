//package com.example.bookapp.auth
//
//import android.util.Log
//import androidx.compose.foundation.layout.Column
//import androidx.compose.foundation.layout.fillMaxSize
//import androidx.compose.foundation.layout.fillMaxWidth
//import androidx.compose.foundation.layout.padding
//import androidx.compose.material3.Button
//import androidx.compose.material3.ExperimentalMaterial3Api
//import androidx.compose.material3.LinearProgressIndicator
//import androidx.compose.material3.Scaffold
//import androidx.compose.material3.Text
//import androidx.compose.material3.TextField
//import androidx.compose.material3.TopAppBar
//import androidx.compose.runtime.Composable
//import androidx.compose.runtime.LaunchedEffect
//import androidx.compose.runtime.getValue
//import androidx.compose.runtime.mutableStateOf
//import androidx.compose.runtime.saveable.rememberSaveable
//import androidx.compose.runtime.setValue
//import androidx.compose.ui.Alignment
//import androidx.compose.ui.Modifier
//import androidx.compose.ui.tooling.preview.Preview
//import androidx.lifecycle.viewmodel.compose.viewModel
//import com.example.bookapp.core.Result
//
//@OptIn(ExperimentalMaterial3Api::class)
//@Composable
//fun AuthScreen(onClose: () -> Unit) {
//    val authViewModel = viewModel<AuthViewModel>(factory = AuthViewModel.Factory())
//    val authUiState = authViewModel.uiState
//
//    var username by rememberSaveable { mutableStateOf(authUiState.userCredentials.username) }
//    var password by rememberSaveable { mutableStateOf(authUiState.userCredentials.password) }
//    Log.d("AuthScreen", "recompose, username = $username, password = $password")
//
//    LaunchedEffect(authUiState.submitResult) {
//        Log.d("AuthScreen", "Submit = ${authUiState.submitResult}");
//        if (authUiState.submitResult is Result.Success) {
//            Log.d("AuthScreen", "Closing screen");
//            onClose();
//        }
//    }
//
//    Scaffold(
//        topBar = {
//            TopAppBar(
//                title = { Text(text = "Authentication") }
//            )
//        }
//    ) {
//        Column(
//            modifier = Modifier
//                .padding(it)
//                .fillMaxSize()
//        ) {
//            if (authUiState.submitResult is Result.Loading) {
//                Column(
//                    modifier = Modifier.fillMaxWidth(),
//                    horizontalAlignment = Alignment.CenterHorizontally
//                ) { LinearProgressIndicator() }
//            }
//            TextField(
//                value = username,
//                onValueChange = { username = it }, label = { Text("Username") },
//                modifier = Modifier.fillMaxWidth(),
//            )
//            TextField(
//                value = password,
//                onValueChange = { password = it }, label = { Text("Password") },
//                modifier = Modifier.fillMaxWidth(),
//            )
//            Button(
//                onClick = {
//                    Log.d("Authentication", "log in with username = $username, password = $password");
//                    authViewModel.login(username, password)
//                })
//            { Text("Log in") }
//            if (authUiState.submitResult is Result.Error) {
//                Text(
//                    text = "Failed to log in - ${(authUiState.submitResult as Result.Error).exception?.message}",
//                    modifier = Modifier.fillMaxWidth(),
//                )
//            }
//        }
//    }
//}
//
//
//@Preview
//@Composable
//fun PreviewBookScreen() {
//    BookScreen(bookId = "0", onClose = {})
//}