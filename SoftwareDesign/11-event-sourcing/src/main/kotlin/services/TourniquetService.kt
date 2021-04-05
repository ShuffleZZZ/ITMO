package services

import exceptions.CollectionException
import exceptions.EntryException
import exceptions.ExitException
import storage.*
import utils.Utils
import java.time.Clock
import java.time.LocalDate
import java.util.AbstractMap.SimpleEntry

class TourniquetService(
    private val storage: EventStorage,
    private val clock: Clock
) {

    @Throws(EntryException::class, CollectionException::class)
    fun enter(id: Int) {
        if (!hasAccess(id)) {
            throw EntryException("Account $id has no right to enter the facility")
        }

        storage.addEvent(id, Entry(Utils.localDateTime(clock)))
    }

    @Throws(ExitException::class, CollectionException::class)
    fun leave(id: Int) {
        if (!canLeave(id)) {
            throw ExitException("Account $id can't leave as he didn't enter the facility")
        }

        storage.addEvent(id, Exit(Utils.localDateTime(clock)))
    }

    @Throws(CollectionException::class)
    private fun hasAccess(id: Int): Boolean {
        val p = getExpirationAndInside(id)

        return !p.value && p.key.isAfter(Utils.localDate(clock))
    }

    @Throws(CollectionException::class)
    private fun canLeave(id: Int) = getExpirationAndInside(id).value

    @Throws(CollectionException::class)
    private fun getExpirationAndInside(id: Int): Map.Entry<LocalDate, Boolean> {
        val events = storage.getEvents(id)

        val event0 = events?.get(0) as? CreationAccount
            ?: throw CollectionException("Account with id $id doesn't exist")

        var expiration = event0[Event.DATE] as LocalDate
        var inside = false

        for (i in 1 until events.size) {
            when (val event = events[i]) {
                is ExtensionAccount -> {
                    val date: LocalDate = event[Event.DATE] as LocalDate
                    val period = event[Event.PERIOD] as Long
                    expiration = date.plusDays(period)
                }
                is Entry -> inside = true
                is Exit -> inside = false
            }
        }

        return SimpleEntry(expiration, inside)
    }
}
