import com.bmuschko.gradle.docker.tasks.image.DockerBuildImage
import com.bmuschko.gradle.docker.tasks.image.DockerRemoveImage
import com.bmuschko.gradle.docker.tasks.image.Dockerfile

plugins {
    application
    kotlin("jvm") version "1.4.32"
    id("com.bmuschko.docker-remote-api") version "6.7.0"
}

version = "0.0.1"

application {
    mainClass.set("io.ktor.server.netty.EngineMain")
}

tasks {
    jar {
        enabled = true
        manifest {
            attributes["Main-Class"] = "ApplicationKt"
        }
    }
}

tasks.create("copyJar", Copy::class) {
    dependsOn("jar")
    from("build/libs/market-${project.version}.jar")
    into("build/docker")
    rename { it.replace("-${project.version}", "") }
}

tasks.create("createDockerfile", Dockerfile::class) {
    dependsOn("copyJar")
    from("openjdk:8")
    addFile("market.jar", "/app/market.jar")
    exposePort(8080, 49152)
    defaultCommand("java", "-jar", "/app/market.jar")
}

tasks.create("removeImage", DockerRemoveImage::class) {
    targetImageId("market:latest")
}

tasks.create("buildImage", DockerBuildImage::class) {
    dependsOn("removeImage", "createDockerfile")
    images.add("market:latest")
}

tasks.test {
    useJUnitPlatform()
}

repositories {
    mavenLocal()
    jcenter()
    maven { url = uri("https://kotlin.bintray.com/ktor") }
}

val ktorVersion = "1.5.1"

dependencies {
    implementation("org.jetbrains.kotlin:kotlin-stdlib-jdk8:1.4.32")

    implementation("io.ktor:ktor-server-netty:$ktorVersion")
    implementation("io.ktor:ktor-server-core:$ktorVersion")
    implementation("io.ktor:ktor-jackson:$ktorVersion")

    implementation("ch.qos.logback:logback-classic:+")

    testImplementation("io.ktor:ktor-server-tests:$ktorVersion")

    testImplementation("org.junit.jupiter:junit-jupiter-api:+")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine:+")
}

kotlin.sourceSets["main"].kotlin.srcDirs("src")
kotlin.sourceSets["test"].kotlin.srcDirs("test")

sourceSets["main"].resources.srcDirs("resources")
