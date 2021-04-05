package storage

import java.time.LocalDateTime

class Entry(time: LocalDateTime?) : Event() {
    init {
        description[TIME] = time as Any
    }
}
