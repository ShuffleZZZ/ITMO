import com.fasterxml.jackson.databind.SerializationFeature
import io.ktor.application.*
import io.ktor.features.*
import io.ktor.http.*
import io.ktor.jackson.*
import io.ktor.response.*
import io.ktor.routing.*
import database.dao.StocksDAO
import database.dao.StocksInMemoryDAO

fun main(args: Array<String>): Unit = io.ktor.server.netty.EngineMain.main(args)

@kotlin.jvm.JvmOverloads
fun Application.module(@Suppress("UNUSED_PARAMETER") testing: Boolean = false) {
    install(ContentNegotiation) {
        jackson {
            enable(SerializationFeature.INDENT_OUTPUT)
        }
    }

    val dao: StocksDAO = StocksInMemoryDAO()

    routing {
        get("/") {
            try {
                val companyName = call.getParameter<String>("company-name")

                if (companyName == null) {
                    call.respond(dao.getStocks())
                } else {
                    call.respond(dao.getStocks(companyName))
                }
            } catch (e: Exception) {
                call.respondText("Error: ${e.message}", status = HttpStatusCode.BadRequest)
            }
        }

        get("/admin/register") {
            try {
                val companyName = call.requireParameter<String>("company-name")
                val price = call.requireParameter<Long>("price")
                val amount = call.getParameter<Long>("amount")

                dao.addStocks(companyName, price)
                if (amount != null) {
                    dao.increaseStocks(companyName, amount)
                }

                call.respond("SUCCESS")
            } catch (e: Exception) {
                call.respondText("Error: ${e.message}", status = HttpStatusCode.BadRequest)
            }
        }

        get("/sell") {
            try {
                val companyName = call.requireParameter<String>("company-name")
                val amount = call.requireParameter<Long>("amount")

                call.respond(dao.increaseStocks(companyName, amount))
            } catch (e: Exception) {
                call.respondText("Error: ${e.message}", status = HttpStatusCode.BadRequest)
            }
        }

        get("/buy") {
            try {
                val companyName = call.requireParameter<String>("company-name")
                val amount = call.requireParameter<Long>("amount")

                call.respond(dao.decreaseStocks(companyName, amount))
            } catch (e: Exception) {
                call.respondText("Error: ${e.message}", status = HttpStatusCode.BadRequest)
            }
        }

        get("/admin/change") {
            try {
                val companyName = call.requireParameter<String>("company-name")
                val newPrice = call.requireParameter<Long>("new-price")

                dao.changePrice(companyName, newPrice)

                call.respond("SUCCESS")
            } catch (e: Exception) {
                call.respondText("Error: ${e.message}", status = HttpStatusCode.BadRequest)
            }
        }
    }
}

