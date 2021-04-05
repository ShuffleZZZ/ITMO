package database.dao

import database.Stocks
import java.util.concurrent.ConcurrentHashMap

class StocksInMemoryDAO : StocksDAO {

    private val stocks: MutableMap<String, Stocks> = ConcurrentHashMap()

    private fun mapPrice(stocks: Stocks): Stocks = stocks

    override fun getStocks(): List<Stocks> {
        return stocks.values.toList().map(this::mapPrice)
    }

    override fun getStocks(companyName: String): Stocks {
        return mapPrice(
            stocks[companyName] ?: throw IllegalArgumentException("No stocks registered for '$companyName'")
        )
    }

    override fun addStocks(companyName: String, price: Long) {
        check(price > 0) { "Stocks can't cost non-positive amount" }
        check(companyName !in stocks.keys) { "Company '$companyName' already registered" }

        stocks[companyName] = Stocks(companyName, 0, price)
    }

    override fun increaseStocks(companyName: String, amount: Long): Long {
        check(amount > 0) { "Can't increase by non-positive amount" }

        val oldValue = stocks[companyName] ?: throw IllegalArgumentException("Company '$companyName' is not registered")
        stocks[companyName] = oldValue.copy(amount = oldValue.amount + amount)

        return oldValue.price * amount
    }

    override fun decreaseStocks(companyName: String, amount: Long): Long {
        check(amount > 0) { "Can't decrease by non-positive amount" }

        val oldValue = stocks[companyName] ?: throw IllegalArgumentException("Company '$companyName' is not registered")

        check(oldValue.amount >= amount) { "Can't decrease into negative amount" }

        stocks[companyName] = oldValue.copy(amount = oldValue.amount - amount)

        return oldValue.price * amount
    }

    override fun changePrice(companyName: String, newPrice: Long) {
        check(newPrice > 0) { "Stocks can't const non-positive amount" }

        val oldValue = stocks[companyName] ?: throw IllegalArgumentException("Company '$companyName' is not registered")

        stocks[companyName] = oldValue.copy(price = newPrice)
    }
}
