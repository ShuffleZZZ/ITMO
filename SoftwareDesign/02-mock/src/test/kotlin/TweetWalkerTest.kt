import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test
import org.mockito.Mockito.*
import twitter4j.QueryResult
import twitter4j.Status
import twitter4j.Twitter
import java.time.LocalDateTime
import java.time.ZoneId
import java.time.format.DateTimeFormatter
import java.util.*


internal class TweetWalkerTest {

    private val someLocalDateTime = LocalDateTime.now()
    private lateinit var tweetWalker: TweetProvider

    private val expectedList = listOf(1, 0, 2, 0, 1)

    @BeforeEach
    fun setUp() {
        val tweets = mock(Status::class.java).also {
            val date = Date.from(
                someLocalDateTime.atZone(ZoneId.systemDefault()).toInstant()
            )
            `when`(it.createdAt).thenReturn(date)
        }

        val twitterResponse: List<Status> = arrayListOf(tweets)

        val queryResult = mock(QueryResult::class.java).also {
            `when`(it.tweets).thenReturn(twitterResponse)

            `when`(it.nextQuery()).thenReturn(null)
        }

        val twitter = mock(Twitter::class.java).also {
            `when`(it.search(any()))
                .thenReturn(queryResult)
                .thenReturn(null)
        }

        tweetWalker = TweetWalker(twitter)
    }

    @Test
    fun getTweetsByHashtag() {
        val tweets = tweetWalker.getTweetsByHashtag("any")
        val format = DateTimeFormatter.ofPattern("uuuu-MM-dd'T'HH:mm:ss.SSS")

        assertEquals(1, tweets.size)
        assertEquals(someLocalDateTime.format(format), tweets[0].getDate().format(format))
    }

    @Test
    fun listTest() {
        assertEquals(expectedList, tweetWalker.makeHoursArray(listOf(0, 2, 2, 4), 5).asList())
    }

    @Test
    fun emptyListTest() {
        assertEquals(listOf(0, 0, 0, 0, 0), tweetWalker.makeHoursArray(listOf(), 5).asList())
    }

    @Test
    fun valueRangeListTest() {
        assertEquals(
            expectedList,
            tweetWalker.makeHoursArray(listOf(-1, 2, 0, 2, 4, 5), 5).asList())
    }
}
