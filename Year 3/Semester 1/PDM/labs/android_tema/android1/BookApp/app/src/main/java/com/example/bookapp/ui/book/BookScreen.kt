package com.example.bookapp.ui.book

import android.util.Log
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.LinearProgressIndicator
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.bookapp.core.Result

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun BookScreen(bookId: String?, onClose: () -> Unit) {
    val bookViewModel = viewModel<BookViewModel>(factory = BookViewModel.Factory(bookId))
    val bookUiState = bookViewModel.uiState
    var title by rememberSaveable { mutableStateOf(bookUiState.book.title) }
    var writer by rememberSaveable { mutableStateOf(bookUiState.book.writer) }
    Log.d("BookScreen", "recompose, title = $title, writer = $writer")

    LaunchedEffect(bookUiState.submitResult) {
        Log.d("BookScreen", "Submit = ${bookUiState.submitResult}");
        if (bookUiState.submitResult is Result.Success) {
            Log.d("BookScreen", "Closing screen");
            onClose();
        }
    }

    Scaffold(
        topBar = {
            TopAppBar(
                title = { Text(text = "Book") },
                actions = {
                    Button(onClick = {
                        Log.d("BookScreen", "save book title = $title, writer = $writer");
                        bookViewModel.saveOrUpdateBook(title, writer)
                    }) { Text("Save") }
                }
            )
        }
    ) {
        Column(
            modifier = Modifier
                .padding(it)
                .fillMaxSize()
        ) {
            if (bookUiState.submitResult is Result.Loading) {
                Column(
                    modifier = Modifier.fillMaxWidth(),
                    horizontalAlignment = Alignment.CenterHorizontally
                ) { LinearProgressIndicator() }
            }
            Column {
                TextField(
                    value = title,
                    onValueChange = { title = it }, label = { Text("Title") },
                    modifier = Modifier.fillMaxWidth(),
                )
                TextField(
                    value = writer,
                    onValueChange = { writer = it }, label = { Text("Writer") },
                    modifier = Modifier.fillMaxWidth(),
                )
            }
            if (bookUiState.submitResult is Result.Error) {
                Text(
                    text = "Failed to submit book - ${(bookUiState.submitResult as Result.Error).exception?.message}",
                    modifier = Modifier.fillMaxWidth(),
                )
            }
        }
    }
}


@Preview
@Composable
fun PreviewBookScreen() {
    BookScreen(bookId = "0", onClose = {})
}