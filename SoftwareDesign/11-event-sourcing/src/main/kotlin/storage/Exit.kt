package storage

import java.time.LocalDateTime

class Exit(time: LocalDateTime?) : Event() {
    init {
        description[TIME] = time as Any
    }
}
