package utils

import java.time.Clock
import java.time.LocalDate
import java.time.LocalDateTime

object Utils {
    fun localDate(clock: Clock): LocalDate = LocalDate.ofInstant(clock.instant(), clock.zone)

    fun localDateTime(clock: Clock): LocalDateTime = LocalDateTime.ofInstant(clock.instant(), clock.zone)
}
