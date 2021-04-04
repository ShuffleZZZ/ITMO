package request

import akka.actor.ActorRef
import akka.actor.ActorSystem
import akka.actor.Props
import scala.concurrent.duration.Duration
import actor.MainActor
import java.util.concurrent.CompletableFuture

data class Site(val name: String, val port: Int)

data class Response(val response: String, val site: Site)

class Request {
    private val sites = mutableListOf<Site>()

    fun add(site: Site) = sites.add(site)

    fun search(message: String?, duration: Duration?): HashMap<String, String> {
        val actorSystem = ActorSystem.create("Request")

        val result = CompletableFuture<HashMap<String, String>>()
        val main = actorSystem.actorOf(Props.create(MainActor::class.java, sites, result, duration))
        main.tell(message, ActorRef.noSender())

        return result.get()
    }
}
