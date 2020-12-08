import com.natpryce.konfig.ConfigurationProperties
import com.natpryce.konfig.Key
import com.natpryce.konfig.stringType
import twitter4j.TwitterFactory
import twitter4j.conf.ConfigurationBuilder

fun main() {
    val tweetWalker = TweetWalker(TwitterFactory(createConfig().build()).instance)

    val hoursArray = tweetWalker.getHoursArray("нюдсочетверг", 24)

    println(hoursArray.contentToString())
}

fun createConfig(): ConfigurationBuilder {
    val configuration = ConfigurationProperties.fromResource("twitterj4.properties")

    val cb = ConfigurationBuilder()
    cb.setOAuthConsumerKey(configuration[Key("consumer-key", stringType)])
    cb.setOAuthConsumerSecret(configuration[Key("consumer-secret", stringType)])
    cb.setOAuthAccessToken(configuration[Key("access-token", stringType)])
    cb.setOAuthAccessTokenSecret(configuration[Key("access-secret", stringType)])

    return cb;
}
