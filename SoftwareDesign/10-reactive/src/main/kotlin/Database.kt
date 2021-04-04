import com.mongodb.client.model.Filters.eq
import com.mongodb.rx.client.MongoClients
import org.bson.Document
import rx.Observable
import rx.Subscription

class Database {
    private val client = MongoClients.create()
    private val database = client.getDatabase("app")

    fun addUser(username: String, currency: String): Subscription =
        database.getCollection("users")
            .insertOne(
                Document("_id", username)
                    .append("username", username)
                    .append("currency", currency)
            )
            .subscribe()

    fun getUsers(): Observable<User> =
        database.getCollection("users")
            .find()
            .toObservable()
            .map { x -> User(x) }

    fun getUser(username: String): Observable<User> =
        database.getCollection("users")
            .find(eq("_id", username))
            .toObservable()
            .map { x -> User(x) }

    fun addProduct(name: String, price: Double): Subscription =
        database.getCollection("products")
            .insertOne(
                Document("name", name)
                    .append("price", price)
            )
            .subscribe()

    fun getProducts(): Observable<Product> =
        database.getCollection("products")
            .find()
            .toObservable()
            .map { x -> Product(x) }
}
