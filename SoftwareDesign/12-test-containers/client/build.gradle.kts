plugins {
    application
    kotlin("jvm") version "1.4.32"
}

version = "0.0.1"

application {
    mainClass.set("io.ktor.server.netty.EngineMain")
}

tasks {
    test {
        dependsOn(":market:test", ":market:buildImage")
        useJUnitPlatform()
    }
}

repositories {
    mavenLocal()
    jcenter()
    maven { url = uri("https://kotlin.bintray.com/ktor") }
}

val ktorVersion = "1.5.1"

dependencies {
    implementation("org.jetbrains.kotlin:kotlin-stdlib-jdk8:1.4.32")

    implementation("ch.qos.logback:logback-classic:+")

    implementation("io.ktor:ktor-server-netty:$ktorVersion")
    implementation("io.ktor:ktor-client-apache:$ktorVersion")
    implementation("io.ktor:ktor-server-core:$ktorVersion")
    implementation("io.ktor:ktor-jackson:$ktorVersion")

    testImplementation("io.ktor:ktor-server-tests:$ktorVersion")

    testImplementation("org.testcontainers:testcontainers:+")
    testImplementation("org.junit.jupiter:junit-jupiter-api:+")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine:+")
}

kotlin.sourceSets["main"].kotlin.srcDirs("src")
kotlin.sourceSets["test"].kotlin.srcDirs("test")

sourceSets["main"].resources.srcDirs("resources")
