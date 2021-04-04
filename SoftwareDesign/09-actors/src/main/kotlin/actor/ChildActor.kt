package actor

import akka.actor.UntypedAbstractActor
import request.Response
import request.Site
import java.net.URI
import java.net.http.HttpClient
import java.net.http.HttpRequest
import java.net.http.HttpResponse

class ChildActor(private val site: Site) : UntypedAbstractActor() {
    override fun onReceive(message: Any?) {
        if (message is String) {
            val uri = URI.create("""http://${site.name}:${site.port}/?q=${message}""")

            val client = HttpClient.newBuilder().build()
            val request = HttpRequest.newBuilder().uri(uri).build()
            val response = client.send(request, HttpResponse.BodyHandlers.ofString()).body().intern()

            sender().tell(Response(response, site), self)
        }
    }
}
