package database.dao

import database.User

interface UserDAO {

    fun getUser(id: Long): User

    fun addUser(id: Long, name: String)

    fun increaseBalance(id: Long, amount: Long)

    fun decreaseBalance(id: Long, amount: Long)

    fun addStocks(id: Long, companyName: String, amount: Long)

    fun removeStocks(id: Long, companyName: String, amount: Long)

}
