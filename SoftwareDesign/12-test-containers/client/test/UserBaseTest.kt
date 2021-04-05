import io.ktor.http.*
import io.ktor.server.testing.*
import org.junit.Assert.assertEquals
import org.junit.Assert.assertTrue
import org.junit.Test

class UserBaseTest {
    @Test
    fun testRegisterAndProfile() {
        withTestApplication({ module(testing = true) }) {
            handleRequest(HttpMethod.Get, "/register?user-id=1&name=user1")
                .apply {
                    assertEquals(HttpStatusCode.OK, response.status())
                }

            handleRequest(HttpMethod.Get, "/profile?user-id=1")
                .apply {
                    assertEquals(HttpStatusCode.OK, response.status())
                    assertTrue(response.content!!.contains("user1"))
                }
        }
    }
}
