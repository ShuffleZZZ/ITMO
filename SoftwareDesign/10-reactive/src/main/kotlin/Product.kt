import org.bson.Document

class Product(
    private val name: String,
    private var price: Double
) {
    constructor(doc: Document) : this(doc.getString("name"), doc.getDouble("price"))

    fun toString(currency: String): String {
        val alpha = when (currency.toLowerCase()) {
            "usd" -> 76.44
            "eur" -> 89.88
            "sek" -> 8.76
            else -> 1.0
        }

        return "name: $name, price: ${price / alpha}"
    }
}
