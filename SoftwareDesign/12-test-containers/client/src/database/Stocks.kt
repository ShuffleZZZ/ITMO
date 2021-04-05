package database

data class Stocks(
    val companyName: String,
    val amount: Long,
    val price: Long? = null
)
