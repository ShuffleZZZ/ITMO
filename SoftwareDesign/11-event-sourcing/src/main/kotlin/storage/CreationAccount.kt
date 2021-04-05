package storage

import java.time.LocalDate

class CreationAccount(date: LocalDate?, name: String?) : Event() {
    init {
        description[DATE] = date as Any
        description[NAME] = name as Any
    }
}
