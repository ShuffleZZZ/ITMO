package database

data class User(
    val id: Long,
    val name: String,
    val balance: Long,
    val stocks: List<Stocks>
)
