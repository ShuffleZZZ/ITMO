import java.time.Clock
import java.time.Instant
import java.time.LocalDateTime
import java.time.ZoneId

class TestClock(time: LocalDateTime?) : Clock() {
    private var now: Instant

    override fun getZone(): ZoneId = ZoneId.systemDefault()

    override fun withZone(zone: ZoneId): Clock {
        throw UnsupportedOperationException()
    }

    override fun instant() = now

    fun plusHours(hours: Long) {
        now = now.plusSeconds(hours * 3600L)
    }

    init {
        now = time!!.atZone(ZoneId.systemDefault()).toInstant()
    }
}
