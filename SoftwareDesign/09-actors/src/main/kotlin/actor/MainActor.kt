package actor

import akka.actor.Props
import akka.actor.ReceiveTimeout
import akka.actor.UntypedAbstractActor
import request.Response
import request.Site
import scala.concurrent.duration.Duration
import java.util.concurrent.CompletableFuture

class MainActor(
    private val sites: List<Site>,
    private val futureResult: CompletableFuture<HashMap<String, String>>,
    duration: Duration?
) : UntypedAbstractActor() {
    private val result = HashMap<String, String>()

    override fun onReceive(message: Any?) {
        when (message) {
            is ReceiveTimeout -> complete()
            is String -> request(message)
            is Response -> {
                result["${message.site.name}:${message.site.port}"] = message.response
                if (result.size == sites.size) complete()
            }
        }
    }

    private fun request(req: String) =
        sites.forEach { context.actorOf(Props.create(ChildActor::class.java, it)).tell(req, self) }

    private fun complete() {
        futureResult.complete(result)
        context.system().stop(self)
    }

    init {
        context.setReceiveTimeout(duration)
    }
}
