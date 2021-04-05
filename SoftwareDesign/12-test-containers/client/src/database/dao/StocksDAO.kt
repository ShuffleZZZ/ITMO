package database.dao

import database.Stocks

interface StocksDAO {

    suspend fun buy(userId: Long, companyName: String, amount: Long)

    suspend fun sell(userId: Long, companyName: String, amount: Long)

    suspend fun getTotalWorth(stocks: List<Stocks>): List<Stocks>

}
