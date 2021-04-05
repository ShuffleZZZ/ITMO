package database.dao

import database.Stocks

interface StocksDAO {

    fun getStocks(): List<Stocks>

    fun getStocks(companyName: String): Stocks

    fun addStocks(companyName: String, price: Long)

    fun increaseStocks(companyName: String, amount: Long): Long

    fun decreaseStocks(companyName: String, amount: Long): Long

    fun changePrice(companyName: String, newPrice: Long)

}
