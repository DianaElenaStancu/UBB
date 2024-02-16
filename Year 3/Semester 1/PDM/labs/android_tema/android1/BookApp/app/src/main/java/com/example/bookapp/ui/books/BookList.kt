package com.example.bookapp.ui.books

import android.util.Log
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.text.ClickableText
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.AnnotatedString
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.bookapp.todo.data.Book

typealias OnItemFn = (id: String?) -> Unit

@Composable
fun BookList(bookList: List<Book>, onItemClick: OnItemFn, modifier: Modifier) {
    Log.d("BookList", "recompose")
    LazyColumn(
        modifier = modifier
            .fillMaxSize()
            .padding(12.dp)
    ) {
        items(bookList) { book ->
            BookDetail(book, onItemClick)
        }
    }
}

@Composable
fun BookDetail(book: Book, onItemClick: OnItemFn) {
    Log.d("BookDetail", "recompose id = ${book._id}")
    Row {
        ClickableText(
            text = AnnotatedString("title:" + book.title + " "),
            style = TextStyle(fontSize = 24.sp),
            onClick = { onItemClick(book._id) }
        )
        ClickableText(
            text = AnnotatedString("writer:" + book.writer + " "),
            style = TextStyle(fontSize = 24.sp),
            onClick = { onItemClick(book._id) }
        )
    }
}