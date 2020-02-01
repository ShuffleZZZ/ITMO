import java.util.concurrent.atomic.*
import kotlin.coroutines.Continuation
import kotlin.coroutines.resume
import kotlin.coroutines.suspendCoroutine

class BlockingStackImpl<E> : BlockingStack<E> {
    private val enqIdx: AtomicReference<Receiver<E>>
    private val deqIdx: AtomicReference<Receiver<E>>

    init {
        val dummy = Receiver<E>()
        enqIdx = AtomicReference(dummy)
        deqIdx = AtomicReference(dummy)
    }

    private suspend fun suspend(): E {
        return suspendCoroutine sc@ { cont ->
            val newTail = Receiver(cont)

            while (true) {
                val oldTail = deqIdx.get()
                if (oldTail.next.compareAndSet(null, newTail)) {
                    deqIdx.compareAndSet(oldTail, newTail)
                    break
                }
            }
        }
    }

    private fun resume(element: E) {
        while (true) {
            val oldHead = enqIdx.get()
            if (oldHead == deqIdx.get()) continue

            val newHead = oldHead.next.get()
            if (newHead != null && enqIdx.compareAndSet(oldHead, newHead)) {
                newHead.action!!.resume(element)
                return
            }
        }
    }

    private class Receiver<E>(val action: Continuation<E>? = null) {
        val next = AtomicReference<Receiver<E>>(null)
    }

    private val head = AtomicReference<Node<E>?>()
    private val elements = AtomicInteger()

    override fun push(element: E) {
        val elements = this.elements.getAndIncrement()
        if (elements >= 0) {
            while (true) {
                val oldHead = head.get()
                if (oldHead != null && oldHead.element == SUSPENDED) {
                    val newHead = oldHead.next.get()
                    if (head.compareAndSet(oldHead, newHead)) {
                        resume(element)
                        return
                    }
                } else {
                    val newHead = Node(element, oldHead)
                    if (head.compareAndSet(oldHead, newHead)) {
                        return
                    }
                }
            }
        } else {
            resume(element)
        }
    }

    override suspend fun pop(): E {
        val elements = this.elements.getAndDecrement()
        if (elements > 0) {
            while (true) {
                val oldHead = head.get()
                if (oldHead != null) {
                    val newHead = oldHead.next.get()
                    if (head.compareAndSet(oldHead, newHead)) {
                        return oldHead.element as E
                    }
                } else {
                    val newHead = Node<E>(SUSPENDED)
                    if (head.compareAndSet(oldHead, newHead)) {
                        return suspend()
                    }
                }
            }
        } else {
            return suspend()
        }
    }
}

private class Node<E>(val element: Any? = null, next: Node<E>? = null) {
    val next = AtomicReference(next)
}

private val SUSPENDED = Any()