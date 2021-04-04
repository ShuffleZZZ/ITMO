import org.jetbrains.kotlin.gradle.tasks.KotlinCompile


plugins {
    kotlin("jvm") version "1.4.31"
}

repositories {
    mavenCentral()
}

dependencies {
    implementation(kotlin("stdlib"))

    implementation("org.slf4j:slf4j-api:+")
    implementation("org.slf4j:slf4j-simple:+")

    implementation("io.reactivex.rxjava3:rxjava:+")

    implementation("org.mongodb:mongodb-driver-rx:+")

    implementation("io.reactivex:rxnetty-http:+")
    implementation("io.reactivex:rxnetty-common:+")
    implementation("io.reactivex:rxnetty-tcp:+")

    implementation("io.netty:netty-all:+")
}

tasks.withType<KotlinCompile> {
    kotlinOptions.jvmTarget = "1.8"
}
