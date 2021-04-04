import server.StubServer
import org.junit.jupiter.api.Assertions.*
import org.junit.jupiter.api.Test
import request.Request
import request.Site
import scala.concurrent.duration.Duration
import java.util.concurrent.TimeUnit

class RequestTest {
    @Test
    fun testSingleServer() {
        StubServer(PORT1, NO_TIMEOUT).use {
            val request = Request()
            request.add(Site("localhost", PORT1))
            val res = request.search("google", DEFAULT_TIMEOUT)

            assertEquals(res.size, 1)
            assertTrue(res.containsKey("localhost:$PORT1"))
            assertNotNull(res["localhost:$PORT1"])
        }
    }

    @Test
    fun testMultipleServers() {
        StubServer(PORT1, NO_TIMEOUT).use {
            StubServer(PORT2, NO_TIMEOUT).use {
                StubServer(PORT3, NO_TIMEOUT).use {
                    val request = Request()
                    request.add(Site("localhost", PORT1))
                    request.add(Site("localhost", PORT2))
                    request.add(Site("localhost", PORT3))
                    val res = request.search("google", DEFAULT_TIMEOUT)

                    assertEquals(res.size, 3)
                    assertTrue(res.containsKey("localhost:$PORT1"))
                    assertTrue(res.containsKey("localhost:$PORT2"))
                    assertTrue(res.containsKey("localhost:$PORT3"))
                }
            }
        }
    }

    @Test
    fun testSingleServerWithTimeOut() {
        StubServer(PORT1, DEFAULT_TIMEOUT).use {
            val request = Request()
            request.add(Site("localhost", PORT1))
            val res = request.search("google", NO_TIMEOUT)

            assertEquals(res.size, 0)
        }
    }

    companion object {
        private val NO_TIMEOUT: Duration = Duration.create(0, TimeUnit.MILLISECONDS)
        private val DEFAULT_TIMEOUT: Duration = Duration.create(1000, TimeUnit.MILLISECONDS)
        private const val PORT1 = 33333
        private const val PORT2 = 44444
        private const val PORT3 = 55555
    }
}
