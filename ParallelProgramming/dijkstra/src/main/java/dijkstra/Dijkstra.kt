package dijkstra

import kotlinx.atomicfu.atomic
import java.util.*
import java.util.concurrent.Phaser
import kotlin.Comparator
import kotlin.concurrent.thread

private val NODE_DISTANCE_COMPARATOR = Comparator<Node> { o1, o2 -> o1!!.distance.compareTo(o2!!.distance) }

fun shortestPathParallel(start: Node) {
    val workers = Runtime.getRuntime().availableProcessors()
    start.distance = 0
    val q = PriorityQueuesList(workers, NODE_DISTANCE_COMPARATOR)
    q.addAndIncrement(start)
    val onFinish = Phaser(workers + 1)
    repeat(workers) {
        thread {
            while (true) {
                val cur: Node = q.poll() ?: if (q.isReallyEmpty()) break else continue

                for (e in cur.outgoingEdges) {
                    while (true) {
                        val oldDistance = e.to.distance
                        val newDistance = cur.distance + e.weight

                        if (oldDistance > newDistance) {
                            if (e.to.casDistance(oldDistance, newDistance)) {
                                q.addAndIncrement(e.to)
                            } else continue
                        }
                        break
                    }
                }
                q.decrement()
            }
            onFinish.arrive()
        }
    }
    onFinish.arriveAndAwaitAdvance()
}

private class PriorityQueuesList(val workers: Int, comparator: Comparator<Node>) {
    val queueList: MutableList<PriorityQueue<Node>> = Collections.nCopies(workers, PriorityQueue(comparator))
    val size = atomic(0)
    val random = Random()

    fun poll(): Node? {
        var i = 0
        var j = 0
        while (i == j) {
            i = random.nextInt(workers)
            j = random.nextInt(workers)
        }

        synchronized(queueList[i]) {
            synchronized(queueList[j]) {
                val isFirstEmpty = queueList[i].isEmpty()
                val isSameEmptiness = isFirstEmpty == queueList[j].isEmpty()

                val pollIndex = if (isSameEmptiness)
                    if (!isFirstEmpty)
                        if (queueList[i].peek().distance < queueList[j].peek().distance) i else j
                    else -1
                else if (isFirstEmpty) j else i

                return if (pollIndex != -1) queueList[pollIndex].poll() else null
            }
        }
    }

    fun isReallyEmpty(): Boolean {
        return size.compareAndSet(0, 0)
    }

    fun addAndIncrement(element: Node) {
        val randomIndex = random.nextInt(workers)

        synchronized(queueList[randomIndex]) {
            queueList[randomIndex].add(element)
        }

        size.incrementAndGet()
    }

    fun decrement() {
        size.decrementAndGet()
    }
}