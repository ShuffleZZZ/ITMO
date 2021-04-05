package storage

import java.time.LocalDate
import java.time.LocalDateTime

@Suppress("unused")
class Account(
    private val id: Int,
    var name: String,
    val created: LocalDate
) {
    var expiration = created
    var lastVisit: LocalDateTime? = null
}
