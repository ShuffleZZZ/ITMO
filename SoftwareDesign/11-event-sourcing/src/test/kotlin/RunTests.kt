import exceptions.*
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test
import services.ManagerService
import services.ReportService
import services.TourniquetService
import storage.Account
import storage.EventStorage
import java.time.LocalDateTime
import java.util.AbstractMap.SimpleEntry

class RunTests {
    private var now: LocalDateTime
    private var clock: TestClock
    private var eventStorage: EventStorage
    private var manager: ManagerService

    init {
        now = LocalDateTime.now()
        clock = TestClock(now)
        eventStorage = EventStorage()
        manager = ManagerService(eventStorage, clock)
    }

    @BeforeEach
    fun init() {
        now = LocalDateTime.now()
        clock = TestClock(now)
        eventStorage = EventStorage()
        manager = ManagerService(eventStorage, clock)
    }

    @Test
    @Throws(
        CreationException::class,
        ExtensionException::class,
        CollectionException::class
    )
    fun managerServiceTest() {
        manager.createAccount(1, "User")
        manager.extendAccount(1, 30)
        clock.plusHours(25)

        val account: Account = manager.collectInfo(1)

        assertEquals("User", account.name)
        assertEquals(now.toLocalDate(), account.created)
        assertEquals(now.toLocalDate().plusDays(30), account.expiration)
    }

    @Test
    @Throws(
        CreationException::class,
        ExtensionException::class,
        CollectionException::class,
        EntryException::class,
        ExitException::class
    )
    fun reportServiceTest() {
        val tourniquet = TourniquetService(eventStorage, clock)
        val report = ReportService()

        manager.createAccount(1, "User")
        manager.extendAccount(1, 30)
        tourniquet.enter(1)
        clock.plusHours(2)
        tourniquet.leave(1)
        clock.plusHours(23)
        tourniquet.enter(1)
        clock.plusHours(1)
        tourniquet.leave(1)

        eventStorage.subscribe(report)
        assertEquals(1.5, report.meanDuration(), 1e-8)
        assertEquals(1.0, report.meanFrequency(), 1e-8)

        val daily = report.dailyStatistics()
        assertTrue(daily.containsKey(now.toLocalDate()))
        assertTrue(daily.containsKey(now.plusDays(1).toLocalDate()))
        assertEquals(daily[now.toLocalDate()], SimpleEntry(1, 2L))
    }

    @Test
    @Throws(
        CreationException::class,
        CollectionException::class,
        EntryException::class,
        ExtensionException::class,
        ExitException::class
    )
    fun tourniquetServiceTest() {
        val tourniquet = TourniquetService(eventStorage, clock)

        manager.createAccount(1, "User")
        manager.extendAccount(1, 2)
        tourniquet.enter(1)
        clock.plusHours(25)
        tourniquet.leave(1)

        val account = manager.collectInfo(1)
        assertEquals(now, account.lastVisit)
    }
}
