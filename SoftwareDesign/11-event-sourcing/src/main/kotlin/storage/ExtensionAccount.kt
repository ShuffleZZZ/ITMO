package storage

import java.time.LocalDate

class ExtensionAccount(date: LocalDate?, days: Long) : Event() {
    init {
        description[DATE] = date as Any
        description[PERIOD] = days
    }
}
