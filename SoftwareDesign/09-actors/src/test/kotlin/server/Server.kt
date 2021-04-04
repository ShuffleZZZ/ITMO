package server

import org.mockserver.integration.ClientAndServer
import org.mockserver.model.HttpRequest
import org.mockserver.model.HttpResponse
import org.mockserver.model.HttpStatusCode
import scala.concurrent.duration.Duration
import java.lang.Exception

class StubServer(port: Int, duration: Duration) : AutoCloseable {
    private val stubServer = ClientAndServer.startClientAndServer(port)

    @Throws(Exception::class)
    override fun close() {
        stubServer.close()
    }

    init {
        stubServer.`when`(HttpRequest.request().withMethod("GET")).respond { httpRequest: HttpRequest ->
            Thread.sleep(duration.toMillis())
            val name = httpRequest.getFirstQueryStringParameter("q")
            HttpResponse.response().withStatusCode(HttpStatusCode.OK_200.code())
                .withBody(
                    """
                        ${name}1
                        ${name}2
                        ${name}3
                        ${name}4
                        ${name}5
                        """.trimIndent()
                )
        }
    }
}
