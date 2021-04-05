import io.ktor.application.*

inline fun <reified T : Any> ApplicationCall.getParameter(name: String): T? {
    val value = request.queryParameters[name] ?: return null
    return when (T::class.qualifiedName) {
        "kotlin.String" -> value as T
        "kotlin.Int" -> value.toInt() as T
        "kotlin.Long" -> value.toLong() as T

        else -> error("Unsupported conversion to '${T::class.qualifiedName}'")
    }
}

inline fun <reified T : Any> ApplicationCall.requireParameter(name: String): T =
    getParameter<T>(name) ?: error("Required parameter '$name' not present")
