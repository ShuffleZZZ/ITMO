import org.apache.logging.log4j.Level
import org.apache.logging.log4j.LogManager
import twitter4j.Query
import twitter4j.QueryResult
import twitter4j.Twitter
import java.time.LocalDateTime
import java.time.ZoneId
import java.time.temporal.ChronoUnit
import java.util.*

class TweetWalker(private val twitter: Twitter) : TweetProvider {

    companion object {
        private val logger = LogManager
            .getLogger(TweetWalker::class.simpleName)
    }

    private class TweetTimed(val localDateTime: LocalDateTime)
        : Tweet {

        constructor(date: Date) : this(LocalDateTime.ofInstant(
            date.toInstant(),
            ZoneId.systemDefault()))

        override fun getDate(): LocalDateTime = localDateTime
    }

    override fun getTweetsByHashtag(hashtag: String): List<Tweet> {
        var query = Query("#$hashtag")
        query.resultType = Query.ResultType.recent
        query.count = 100

        var queryResult: QueryResult
        var tweetCount = 0
        val tweets = ArrayList<Tweet>()

        while (true) {
            queryResult = twitter.search(query)
            tweetCount += queryResult.tweets.size
            for (tweet in queryResult.tweets) {
                tweets.add(TweetTimed(tweet.createdAt))
            }
            logger.log(Level.TRACE, "read $tweetCount tweets")

            query = queryResult.nextQuery() ?: break
        }

        return tweets
    }

    override fun getHoursArray(hashtag: String, hours: Int): Array<Int> {
        val tweets = this.getTweetsByHashtag(hashtag)

        val now = LocalDateTime.now()
        val tweetsByHours = tweets.map { it.getDate().until(now, ChronoUnit.HOURS).toInt() }

        return this.makeHoursArray(tweetsByHours, hours)
    }

    override fun makeHoursArray(hours: List<Int>, forHours: Int): Array<Int> {
        val diagram = Array(forHours) { 0 }
        for (hour in hours) {
            if (hour in 0 until forHours) {
                ++diagram[hour]
            }
        }

        return diagram
    }
}
