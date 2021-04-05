package container

import org.testcontainers.containers.FixedHostPortGenericContainer

class MarketContainer(dockerImageName: String) : FixedHostPortGenericContainer<MarketContainer>(dockerImageName)
