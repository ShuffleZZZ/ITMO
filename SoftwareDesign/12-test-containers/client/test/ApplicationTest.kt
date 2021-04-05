import io.ktor.client.*
import io.ktor.client.engine.apache.*
import io.ktor.client.features.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import io.ktor.server.testing.*
import kotlinx.coroutines.runBlocking
import org.junit.Assert.assertEquals
import org.junit.Assert.assertTrue
import org.junit.jupiter.api.AfterEach
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test
import container.MarketContainer
import kotlin.random.Random

class ApplicationTest {

    private val container = MarketContainer("market:latest")
        .withFixedExposedPort(49152, 8080)
        .withExposedPorts(8080)

    private val client = HttpClient(Apache) {
        install(HttpTimeout) {
            requestTimeoutMillis = 5000
        }
        expectSuccess = false
    }

    private var baseURL: String? = null

    @BeforeEach
    fun setUp() {
        container.start()
        baseURL = "http://${container.host}:49152"

        runBlocking {
            client.get<HttpResponse>("$baseURL/admin/register?company-name=x&amount=200&price=100")
            client.get<HttpResponse>("$baseURL/admin/register?company-name=y&amount=1000&price=1")
        }
    }

    @AfterEach
    fun terminate() {
        container.stop()
    }

    private fun TestApplicationEngine.registerUser() {
        handleRequest(HttpMethod.Get, "/register?user-id=1&name=user1")
    }

    private fun TestApplicationEngine.buyDefault(ratio: Double, code: HttpStatusCode) {
        handleRequest(HttpMethod.Get, "/buy?user-id=1&company-name=x&amount=${(200 * ratio).toInt()}")
            .apply {
                assertEquals(code, response.status())
            }

        handleRequest(HttpMethod.Get, "/buy?user-id=1&company-name=y&amount=${(1000 * ratio).toInt()}")
            .apply {
                assertEquals(code, response.status())
            }
    }

    @Test
    fun testCanBuy() {
        withTestApplication({ module(testing = true) }) {
            registerUser()
            handleRequest(HttpMethod.Get, "/increase?user-id=1&amount=100000000")
                .apply {
                    assertEquals(HttpStatusCode.OK, response.status())
                }

            buyDefault(1.0, HttpStatusCode.OK)
        }
    }

    @Test
    fun testCanSell() {
        withTestApplication({ module(testing = true) }) {
            registerUser()
            handleRequest(HttpMethod.Get, "/increase?user-id=1&amount=100000000")
                .apply {
                    assertEquals(HttpStatusCode.OK, response.status())
                }

            buyDefault(0.5, HttpStatusCode.OK)
            handleRequest(HttpMethod.Get, "/sell?user-id=1&company-name=x&amount=1")
                .apply {
                    assertEquals(HttpStatusCode.OK, response.status())
                }

            handleRequest(HttpMethod.Get, "/buy?user-id=1&company-name=y&amount=1")
                .apply {
                    assertEquals(HttpStatusCode.OK, response.status())
                }
        }
    }

    @Test
    fun testCantBuyExceedingLimit() {
        withTestApplication({ module(testing = true) }) {
            registerUser()
            handleRequest(HttpMethod.Get, "/increase?user-id=1&amount=10000000")
                .apply {
                    assertEquals(HttpStatusCode.OK, response.status())
                }

            buyDefault(1.1, HttpStatusCode.BadRequest)
        }
    }

    @Test
    fun testCantBuyExceedingBalance() {
        withTestApplication({ module(testing = true) }) {
            registerUser()

            handleRequest(HttpMethod.Get, "/increase?user-id=1&amount=1050")
                .apply {
                    assertEquals(HttpStatusCode.OK, response.status())
                }

            buyDefault(0.051, HttpStatusCode.BadRequest)
            buyDefault(0.05, HttpStatusCode.OK)
        }
    }

    @Test
    fun testCantSellExceeding() {
        withTestApplication({ module(testing = true) }) {
            registerUser()

            handleRequest(HttpMethod.Get, "/increase?user-id=1&amount=100000000")
                .apply {
                    assertEquals(HttpStatusCode.OK, response.status())
                }

            buyDefault(0.5, HttpStatusCode.OK)
            handleRequest(HttpMethod.Get, "/sell?user-id=1&company-name=x&amount=101")
                .apply {
                    assertEquals(HttpStatusCode.BadRequest, response.status())
                }
        }
    }

    @Test
    fun testStatIsCorrect() {
        withTestApplication({ module(testing = true) }) {
            runBlocking {
                registerUser()

                handleRequest(HttpMethod.Get, "/increase?user-id=1&amount=100000000")
                    .apply {
                        assertEquals(HttpStatusCode.OK, response.status())
                    }

                buyDefault(0.5, HttpStatusCode.OK)
                client.get<HttpResponse>("$baseURL/admin/change?company-name=y&new-price=7")

                handleRequest(HttpMethod.Get, "/totals?user-id=1")
                    .apply {
                        assertEquals(HttpStatusCode.OK, response.status())
                        assertTrue(response.content!!.contains("13500"))
                    }
            }
        }
    }

}
