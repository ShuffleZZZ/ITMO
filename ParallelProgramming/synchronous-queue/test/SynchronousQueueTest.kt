import org.jetbrains.kotlinx.lincheck.LinChecker
import org.jetbrains.kotlinx.lincheck.LoggingLevel
import org.jetbrains.kotlinx.lincheck.LoggingLevel.DEBUG
import org.jetbrains.kotlinx.lincheck.annotations.LogLevel
import org.jetbrains.kotlinx.lincheck.annotations.Operation
import org.jetbrains.kotlinx.lincheck.strategy.stress.StressCTest
import org.jetbrains.kotlinx.lincheck.verifier.VerifierState
import org.junit.Test
import kotlin.coroutines.Continuation
import kotlin.coroutines.resume
import kotlin.coroutines.suspendCoroutine

@LogLevel(DEBUG)
@StressCTest(actorsBefore = 0, threads = 2, actorsPerThread = 3, invocationsPerIteration = 20_000,
             sequentialSpecification = SynchronousQueueSequential::class)
class SynchronousQueueTest : SynchronousQueue<Int> {
    val q = SynchronousQueueMS<Int>()

    @Operation
    override suspend fun send(element: Int) { q.send(element) }

    @Operation
    override suspend fun receive(): Int = q.receive()

    @Test
    fun runTest() = LinChecker.check(this::class.java)
}

class SynchronousQueueSequential : SynchronousQueue<Int>, VerifierState() {
    private val senders = ArrayList<Pair<Continuation<Unit>, Int>>() // pair = continuation + element
    private val receivers = ArrayList<Continuation<Int>>()

    override suspend fun send(element: Int) {
        if (receivers.isNotEmpty()) {
            val r = receivers.removeAt(0)
            r.resume(element)
        } else {
            suspendCoroutine<Unit> { cont ->
                senders.add(cont to element)
            }
        }
    }

    override suspend fun receive(): Int {
        if (senders.isNotEmpty()) {
            val (s, elem) = senders.removeAt(0)
            s.resume(Unit)
            return elem
        } else {
            return suspendCoroutine { cont ->
                receivers.add(cont)
            }
        }
    }

    override fun extractState() = Unit
}