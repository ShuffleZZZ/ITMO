package storage

abstract class Event {
    protected var description = HashMap<String, Any>()

    operator fun get(key: String): Any? {
        return description[key]
    }

    companion object {
        const val DATE = "date"
        const val TIME = "time"
        const val NAME = "name"
        const val PERIOD = "days"
    }
}
