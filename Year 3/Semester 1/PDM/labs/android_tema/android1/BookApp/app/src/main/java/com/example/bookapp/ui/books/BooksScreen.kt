package com.example.bookapp.ui.books

import android.util.Log
import androidx.compose.foundation.layout.padding
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.rounded.Add
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.FloatingActionButton
import androidx.compose.material3.Icon
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.bookapp.core.Result

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun BooksScreen(onItemClick: (id: String?) -> Unit, onAddItem: () -> Unit) {
    Log.d("BooksScreen", "recompose")
    val booksViewModel = viewModel<BooksViewModel>(factory = BooksViewModel.Factory)
    val booksUiState = booksViewModel.uiState
    Scaffold(
        topBar = {
            TopAppBar(title = { Text(text = "Books") })
        },
        floatingActionButton = {
            FloatingActionButton(
                onClick = {
                    Log.d("BooksScreen", "add")
                    onAddItem()
                },
            ) { Icon(Icons.Rounded.Add, "Add") }
        }
    ) {
        when (booksUiState) {
            is Result.Success ->
                BookList(
                    bookList = booksUiState.data,
                    onItemClick = onItemClick,
                    modifier = Modifier.padding(it)
                )

            is Result.Loading -> CircularProgressIndicator(modifier = Modifier.padding(it))
            is Result.Error -> Text(
                text = "Failed to load books - ${booksUiState.exception?.message}",
            )

            else -> {}
        }
    }
}

@Preview
@Composable
fun PreviewItemsScreen() {
    BooksScreen(onItemClick = {}, onAddItem = {})
}
