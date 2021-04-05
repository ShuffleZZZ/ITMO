package services

import java.time.LocalDate
import java.util.HashMap
import java.time.LocalDateTime
import kotlin.Throws
import exceptions.CollectionException
import java.util.AbstractMap.SimpleEntry
import java.time.temporal.ChronoUnit
import storage.*

class ReportService {
    private val daily = HashMap<LocalDate, Map.Entry<Int, Long>>()
    private val visit = HashMap<Int, LocalDateTime>()

    private var visits = 0.0
    private var duration = 0L

    @Throws(CollectionException::class)
    fun handle(pair: Map.Entry<Int, Event>) {
        val (id, event) = pair.toPair()

        if (event is Entry) {
            val time = event[Event.TIME] as LocalDateTime
            visit[id] = time
        } else if (event is Exit) {
            val time = event[Event.TIME] as LocalDateTime
            val date = time.toLocalDate()

            val p = daily.getOrDefault(date, SimpleEntry(0, 0L))
            val d = p.value + ChronoUnit.HOURS.between(visit[id], time)

            daily[date] = SimpleEntry(p.key + 1, d)
            visits++
            duration += d
        }
    }

    fun meanFrequency(): Double {
        val days = daily.keys.size.toDouble()
        var res = 0.0

        for (d in daily.keys) {
            res += daily[d]!!.key
        }

        return res / days
    }

    fun meanDuration() = duration / visits

    fun dailyStatistics() = daily
}
