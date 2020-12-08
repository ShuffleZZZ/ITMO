import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

plugins {
    kotlin("jvm") version "1.4.20"
}

repositories {
    mavenCentral()
}

dependencies {
    testImplementation("org.junit.jupiter:junit-jupiter-api:+")
    testImplementation("org.junit.jupiter:junit-jupiter-engine:+")
    testImplementation("org.mockito:mockito-core:+")

    implementation("org.twitter4j", "twitter4j-core", "4.0.7")

    implementation("org.apache.logging.log4j:log4j-core:+")
    implementation("org.apache.logging.log4j:log4j-jul:+")

    implementation("com.natpryce:konfig:+")
}

tasks.test {
    useJUnit()
}

tasks.withType<KotlinCompile>() {
    kotlinOptions.jvmTarget = "1.8"
}
