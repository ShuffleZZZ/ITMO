import java.util.concurrent.atomic.AtomicReference
import kotlin.coroutines.Continuation
import kotlin.coroutines.resume
import kotlin.coroutines.suspendCoroutine

const val RETRY = "RETRY"

class SynchronousQueueMS<E> : SynchronousQueue<E> {
    private val head : AtomicReference<Node>
    private val tail : AtomicReference<Node>

    init {
        val dummy = Node()
        head = AtomicReference(dummy)
        tail = AtomicReference(dummy)
    }

    override suspend fun send(element: E) {
        while (true) {
            val curTail = tail.get()
            if (curTail == head.get() || curTail is Sender<*>) {
                val res = suspendCoroutine<Any> sc@ {cont ->
                    val newTail = Sender(element, cont)
                    val oldTail = tail.get()
                    if (((oldTail == head.get()) || oldTail is Sender<*>) && oldTail.next.compareAndSet(null, newTail)) {
                        tail.compareAndSet(oldTail, newTail)
                    } else {
                        cont.resume(RETRY)
                        return@sc
                    }
                }
                if (res != RETRY) return
            } else {
                val curHead = head.get()
                if (curHead == tail.get() || curHead.next.get() == null) continue
                val headNext = curHead.next.get()
                if (headNext is Receiver<*> && head.compareAndSet(curHead, headNext)) {
                    (headNext.action as Continuation<E>).resume(element)
                    return
                }
            }
        }
    }

    override suspend fun receive(): E {
        while (true) {
            val curTail = tail.get()
            if (curTail == head.get() || curTail is Receiver<*>) {
                val res = suspendCoroutine<E?> sc@ {cont ->
                    val newTail = Receiver(cont)
                    val oldTail = tail.get()
                    if ((oldTail == head.get() || oldTail is Receiver<*>) && oldTail.next.compareAndSet(null, newTail)) {
                        tail.compareAndSet(oldTail, newTail)
                    } else {
                        cont.resume(null)
                        return@sc
                    }
                }
                if (res != null) return res
            } else {
                val curHead = head.get()
                if (curHead == tail.get() || curHead.next.get() == null) continue
                val headNext = curHead.next.get()
                if (curHead != tail.get() && headNext is Sender<*> && head.compareAndSet(curHead, headNext)) {
                    headNext.action.resume(Unit)
                    return (headNext.element as E)
                }
            }
        }
    }


    private open class Node {
        val next = AtomicReference<Node>(null)
    }

    private class Receiver<E>(
        val action : Continuation<E>
    ) : Node()

    private class Sender<E>(
        val element : E,
        val action : Continuation<Unit>
    ) : Node()
}