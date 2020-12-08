import java.time.LocalDateTime

interface Tweet {
    fun getDate(): LocalDateTime
}

interface TweetProvider {
    fun getTweetsByHashtag(hashtag: String): List<Tweet>
    fun getHoursArray(hashtag: String, hours: Int): Array<Int>
    fun makeHoursArray(hours: List<Int>, forHours: Int): Array<Int>
}
