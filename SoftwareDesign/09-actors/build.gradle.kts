import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

plugins {
    kotlin("jvm") version "1.4.30"
}

repositories {
    mavenCentral()
    jcenter()
}

dependencies {
    implementation("com.typesafe.akka:akka-actor_2.13:+")
    implementation("org.mock-server:mockserver-netty:+")

    implementation("org.slf4j:slf4j-api:+")
    implementation("org.slf4j:slf4j-simple:+")

    testImplementation(kotlin("test-junit5"))
    testImplementation("org.junit.jupiter:junit-jupiter-api:+")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine:+")
}

tasks.test {
    useJUnitPlatform()
}

tasks.withType<KotlinCompile> {
    kotlinOptions.jvmTarget = "1.8"
}
