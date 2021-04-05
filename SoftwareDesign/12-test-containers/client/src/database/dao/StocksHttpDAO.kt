package database.dao

import io.ktor.client.*
import io.ktor.client.engine.apache.*
import io.ktor.client.features.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import database.Stocks

class StocksHttpDAO(
    private val baseURL: String,
    private val userDAO: UserDAO
) : StocksDAO {

    private val client: HttpClient = HttpClient(Apache) {
        install(HttpTimeout) {
            requestTimeoutMillis = 5000
        }
        expectSuccess = false
    }

    override suspend fun buy(userId: Long, companyName: String, amount: Long) {
        val stocks = client.get<Stocks>("$baseURL?company-name=$companyName")

        userDAO.decreaseBalance(userId, stocks.price!! * amount)
        client.get<HttpResponse>("$baseURL/buy?company-name=$companyName&amount=$amount")
        userDAO.addStocks(userId, companyName, amount)
    }

    override suspend fun sell(userId: Long, companyName: String, amount: Long) {
        val stocks = client.get<Stocks>("$baseURL?company-name=$companyName")

        userDAO.removeStocks(userId, companyName, amount)
        client.get<HttpResponse>("$baseURL/sell?company-name=$companyName&amount=$amount")
        userDAO.increaseBalance(userId, stocks.price!! * amount)
    }

    override suspend fun getTotalWorth(stocks: List<Stocks>): List<Stocks> =
        stocks.map { client.get("$baseURL?company-name=${it.companyName}") }

}
