package com.example.bookapp

import android.util.Log
import androidx.compose.runtime.Composable
import androidx.navigation.NavType
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.rememberNavController
import androidx.navigation.compose.composable
import androidx.navigation.navArgument
import com.example.bookapp.auth.LoginScreen
import com.example.bookapp.ui.book.BookScreen
import com.example.bookapp.ui.books.BooksScreen

val booksRoute = "books"
val authRoute = "auth"

@Composable
fun NavHost() {
    val navController = rememberNavController()
    val onCloseItem = {
        Log.d("NavHost", "navigate back to list")
        navController.popBackStack()
    }
    NavHost(
        navController = navController,
        startDestination = authRoute
    ) {
        composable(booksRoute) {
            BooksScreen(
                onItemClick = { bookId ->
                    Log.d("NavHost", "navigate to item $bookId")
                    navController.navigate("$booksRoute/$bookId")
                },
                onAddItem = {
                    Log.d("NavHost", "navigate to new book")
                    navController.navigate("$booksRoute-new")
                }
            )
        }
        composable(
            route = "$booksRoute/{id}",
            arguments = listOf(navArgument("id") { type = NavType.StringType })
        )
        {
            BookScreen(
                bookId = it.arguments?.getString("id"),
                onClose = { onCloseItem() }
            )
        }
        composable(route = "$booksRoute-new")
        {
            BookScreen(
                bookId = null,
                onClose = { onCloseItem() }
            )
        }
        composable(route = authRoute) {
            LoginScreen(onClose = {
                Log.d("NavHost", "navigate to list")
                navController.navigate(booksRoute)
            })
        }
    }
}
