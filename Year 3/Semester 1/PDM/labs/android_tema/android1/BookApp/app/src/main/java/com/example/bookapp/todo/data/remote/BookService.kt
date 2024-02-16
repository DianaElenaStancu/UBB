package com.example.bookapp.todo.data.remote

import com.example.bookapp.todo.data.Book
import retrofit2.http.Body
import retrofit2.http.GET
import retrofit2.http.Header
import retrofit2.http.Headers
import retrofit2.http.POST
import retrofit2.http.PUT
import retrofit2.http.Path

interface BookService {
    @GET("/book")
    suspend fun find(@Header("Authorization") authorization: String): List<Book>

    @GET("/book/{id}")
    suspend fun read(
        @Header("Authorization") authorization: String,
        @Path("id") bookId: String?): Book

    @Headers("Content-Type: application/json")
    @POST("/book")
    suspend fun create(
        @Header("Authorization") authorization: String,
        @Body book: Book): Book

    @Headers("Content-Type: application/json")
    @PUT("/book/{id}")
    suspend fun update(
        @Header("Authorization") authorization: String,
        @Path("id") bookId: String?, @Body book: Book): Book
}