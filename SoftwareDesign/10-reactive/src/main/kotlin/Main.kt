fun main() {
    val database = Database()
    val server = Server(database)
    server.startServer()
}
