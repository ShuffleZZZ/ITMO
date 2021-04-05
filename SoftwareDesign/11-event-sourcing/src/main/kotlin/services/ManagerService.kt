package services

import exceptions.CollectionException
import exceptions.CreationException
import exceptions.ExtensionException
import storage.*
import utils.Utils
import java.time.Clock
import java.time.LocalDate
import java.time.LocalDateTime

class ManagerService(
    private val storage: EventStorage,
    private val clock: Clock
) {

    @Throws(ExtensionException::class)
    fun extendAccount(id: Int, days: Long) {
        if (!storage.isExist(id)) {
            throw ExtensionException("Account with id $id doesn't exist. Try to create account instead")
        }

        storage.addEvent(id, ExtensionAccount(Utils.localDate(clock), days))
    }

    @Throws(CreationException::class)
    fun createAccount(id: Int, name: String?) {
        if (storage.isExist(id)) {
            throw CreationException("Account with id $id already exists. You may extend it or choose another id")
        }

        storage.addEvent(id, CreationAccount(Utils.localDate(clock), name))
    }

    @Throws(CollectionException::class)
    fun collectInfo(id: Int): Account {
        val events = storage.getEvents(id)

        if (events.isNullOrEmpty() ||  events[0] !is CreationAccount) {
            throw CollectionException("Account with id $id doesn't exist")
        }

        val created = events[0][Event.DATE] as LocalDate
        val name = events[0][Event.NAME] as String
        val account = Account(id, name, created)

        for (i in 1 until events.size) {
            val event = events[i]

            if (event is ExtensionAccount) {
                val date = event[Event.DATE] as LocalDate
                val period = event[Event.PERIOD] as Long
                val expiration = date.plusDays(period)

                account.expiration = expiration
            } else if (event is Entry) {
                val time = event[Event.TIME] as LocalDateTime

                account.lastVisit = time
            }
        }

        return account
    }
}
