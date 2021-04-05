package storage

import exceptions.CollectionException
import services.ReportService
import java.util.*
import java.util.AbstractMap.SimpleEntry
import java.util.function.Consumer

class EventStorage {
    private val events = HashMap<Int, MutableList<Event>>()
    private val subscribers = ArrayList<ReportService>()

    fun isExist(id: Int) = events.containsKey(id)

    fun addEvent(id: Int, event: Event) {
        events.computeIfAbsent(id) { ArrayList() }
        events[id]!!.add(event)

        subscribers.forEach(Consumer { s ->
            try {
                s.handle(SimpleEntry(id, event))
            } catch (e: CollectionException) {
                e.printStackTrace()
            }
        })
    }

    fun getEvents(id: Int) = events[id]

    fun subscribe(subscriber: ReportService) {
        events.forEach { (key, value) ->
            value.forEach(Consumer { v ->
                try {
                    subscriber.handle(SimpleEntry(key, v))
                } catch (e: CollectionException) {
                    e.printStackTrace()
                }
            })
        }

        subscribers.add(subscriber)
    }
}
