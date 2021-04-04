import org.bson.Document

class User(
    private val username: String,
    val currency: String
) {
    constructor(doc: Document) : this(doc.getString("username"), doc.getString("currency"))

    override fun toString() = "username: $username, currency: $currency"
}
