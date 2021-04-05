import com.fasterxml.jackson.databind.SerializationFeature
import io.ktor.application.*
import io.ktor.features.*
import io.ktor.http.*
import io.ktor.jackson.*
import io.ktor.response.*
import io.ktor.routing.*
import database.dao.StocksDAO
import database.dao.UserDAO
import database.dao.StocksHttpDAO
import database.dao.UserInMemoryDAO

fun main(args: Array<String>): Unit = io.ktor.server.netty.EngineMain.main(args)


@kotlin.jvm.JvmOverloads
fun Application.module(@Suppress("UNUSED_PARAMETER") testing: Boolean = false) {
    install(ContentNegotiation) {
        jackson {
            enable(SerializationFeature.INDENT_OUTPUT)
        }
    }

    val userDAO: UserDAO = UserInMemoryDAO
    val stocksDAO: StocksDAO = StocksHttpDAO(
        "http://localhost:49152",
        userDAO
    )

    routing {
        get("/register") {
            try {
                val id = call.requireParameter<Long>("user-id")
                val name = call.requireParameter<String>("name")

                userDAO.addUser(id, name)

                call.respond("SUCCESS")
            } catch (e: Exception) {
                call.respondText("Error: ${e.message}", status = HttpStatusCode.BadRequest)
            }
        }

        get("/profile") {
            try {
                val id = call.requireParameter<Long>("user-id")

                call.respond(userDAO.getUser(id))
            } catch (e: Exception) {
                call.respondText("Error: ${e.message}", status = HttpStatusCode.BadRequest)
            }
        }

        get("/increase") {
            try {
                val id = call.requireParameter<Long>("user-id")
                val amount = call.requireParameter<Long>("amount")

                userDAO.increaseBalance(id, amount)

                call.respond("SUCCESS")
            } catch (e: Exception) {
                call.respondText("Error: ${e.message}", status = HttpStatusCode.BadRequest)
            }
        }

        get("/totals") {
            try {
                val id = call.requireParameter<Long>("user-id")
                val newStocks = stocksDAO.getTotalWorth(userDAO.getUser(id).stocks)

                call.respond(
                    mapOf(
                        "details" to newStocks,
                        "total" to newStocks.map { it.amount * it.price!! }.sum()
                    )
                )
            } catch (e: Exception) {
                call.respondText("Error: ${e.message}", status = HttpStatusCode.BadRequest)
            }
        }

        get("/buy") {
            try {
                val id = call.requireParameter<Long>("user-id")
                val companyName = call.requireParameter<String>("company-name")
                val amount = call.requireParameter<Long>("amount")

                stocksDAO.buy(id, companyName, amount)

                call.respond("SUCCESS")
            } catch (e: Exception) {
                call.respondText("Error: ${e.message}", status = HttpStatusCode.BadRequest)
            }
        }

        get("/sell") {
            try {
                val id = call.requireParameter<Long>("user-id")
                val companyName = call.requireParameter<String>("company-name")
                val amount = call.requireParameter<Long>("amount")

                stocksDAO.sell(id, companyName, amount)

                call.respond("SUCCESS")
            } catch (e: Exception) {
                call.respondText("Error: ${e.message}", status = HttpStatusCode.BadRequest)
            }
        }
    }
}

